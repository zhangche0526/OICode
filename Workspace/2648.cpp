//  Created by Sengxian on 4/26/16.
//  Copyright (c) 2016年 Sengxian. All rights reserved.
//  BZOJ 2648 k-d 树
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#define ls ch[0]
#define rs ch[1]
using namespace std;

inline int ReadInt() {
    static int n, ch;
    n = 0, ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) n = (n << 3) + (n << 1) + ch - '0', ch = getchar();
    return n;
}
const int maxn = 500000 + 3, maxm = 500000 + 3, INF = 0x3f3f3f3f;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
}ps[maxn];

bool dimension;

//比较当前维度下大小关系
bool cmp(const Point &p1, const Point &p2) {
    if (dimension == 0) return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
    return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x);
}

//计算距离
int dis(const Point &p1, const Point &p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

struct kdTree *null, *pit;
struct kdTree {
    kdTree *ch[2];
    Point p, r1, r2;
    kdTree(Point p): p(p), r1(p), r2(p) {ch[0] = ch[1] = null;}
    kdTree() {}
    void* operator new(size_t) {return pit++;}
    void maintain() { //维护当前点覆盖的矩形
        r1.x = min(min(ls->r1.x, rs->r1.x), r1.x);
        r1.y = min(min(ls->r1.y, rs->r1.y), r1.y);
        r2.x = max(max(ls->r2.x, rs->r2.x), r2.x);
        r2.y = max(max(ls->r2.y, rs->r2.y), r2.y);
    }
    int dis(const Point &p) { //计算点到矩形边界的最近距离
        if (this == null) return INF;
        int res = 0;
        if (p.x < r1.x || p.x > r2.x) res += p.x < r1.x ? r1.x - p.x : p.x - r2.x;
        if (p.y < r1.y || p.y > r2.y) res += p.y < r1.y ? r1.y - p.y : p.y - r2.y;
         return res;
    }
}pool[maxn + maxm], *root;

int n, m;

void init() {
    pit = pool;
    null = new kdTree();
    null->r1 = Point(INF, INF), null->r2 = Point(-INF, -INF);
}

kdTree* build(int l, int r, bool d) {
    if (l >= r) return null;
    int mid = (l + r) / 2;
    dimension = d;
    nth_element(ps + l, ps + mid, ps + r, cmp); //使用中位数来使树尽量平衡
    kdTree *o = new kdTree(ps[mid]);
    o->ls = build(l, mid, d ^ 1), o->rs = build(mid + 1, r, d ^ 1);
    o->maintain();
    return o;
}

int ans;
void query(const kdTree* o, const Point &p) {
    if (o == null) return;
    ans = min(ans, dis(p, o->p));
    int d = o->ls->dis(p) > o->rs->dis(p); //优先递归查询点到左右儿子矩形距离小的那个
    query(o->ch[d], p);
    if (o->ch[d ^ 1]->dis(p) < ans) query(o->ch[d ^ 1], p); //如果另一个儿子有可能比当前结果小，就递归下去
}

void modify(kdTree* &o, const Point &p) {
    if (o == null) {o = new kdTree(p); return;}
    int d = cmp(p, o->p) ^ 1; dimension ^= 1;
    modify(o->ch[d], p);
    o->maintain();
}

int main() {
	freopen("angel18.in","r",stdin);
	freopen("std.out","w",stdout);
    init();
    n = ReadInt(), m = ReadInt();
    for (int i = 1; i <= n; ++i)
        ps[i].x = ReadInt(), ps[i].y = ReadInt();
    root = build(1, n+1, 0);
    while (m--) {
        int type = ReadInt(), x = ReadInt(), y = ReadInt();
        if (type == 1) {
            dimension = 0;
            modify(root, Point(x, y));
        } else if (type == 2) {
            ans = INF;
            query(root, Point(x, y));
            printf("%d\n", ans);
        }
    }
    return 0;
}

