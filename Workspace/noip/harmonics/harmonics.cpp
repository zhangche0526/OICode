
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;
typedef long long LL;
#define N 100010
#define L(x) (x<<1)
#define R(x) ((x<<1)|1)
#define MID(x,y) ((x+y)>>1)
#define inf 2000000000

int n, nn, m, q;
int w[N];
int head[N * 2], tot;
struct edge {
    int v, next, flag;
} ed[N * 4];
int dfn[N], low[N], idx, st[N], top;
pair<int, int> E[N * 10];
int Tmp[N];
int cutoradd[N * 2];
map<int, int> num[N * 2];

void add(int u, int v) {
    ed[tot].v = v;
    ed[tot].flag = 0;
    ed[tot].next = head[u];
    head[u] = tot++;
}

void tarjan(int u, int fa) {
    int i, j, v, son = 0;
    dfn[u] = low[u] = ++idx;
    for (i = head[u]; ~i; i = ed[i].next) {
        v = ed[i].v;
        if (ed[i].flag || dfn[v] >= dfn[u])
            continue;
        ed[i].flag = ed[i ^ 1].flag = 1;
        st[++top] = i;
        if (dfn[v] == -1) {
            son++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) {
                if (u != fa)
                    cutoradd[u] = 1;
                n++;
                cutoradd[n] = 1;
                do {
                    j = st[top--];
                    if (Tmp[ed[j].v] != n) {
                        E[m++] = make_pair(n, ed[j].v);
                        Tmp[ed[j].v] = n;
                    }
                    if (Tmp[ed[j ^ 1].v] != n) {
                        E[m++] = make_pair(n, ed[j ^ 1].v);
                        Tmp[ed[j ^ 1].v] = n;
                    }
                } while (j != i);
            }
        } else
            low[u] = min(low[u], dfn[v]);
    }
    if (u == fa && son > 1)
        cutoradd[u] = 1;
}

void bcc() {
    memset(dfn, -1, sizeof(dfn));
    idx = top = 0;
    for (int i = 1; i <= nn; i++) {
        if (dfn[i] == -1)
            tarjan(i, i);
    }
}

int belong[N * 2];

void build() {
    memset(head, -1, sizeof(head));
    tot = 0;
    for (int i = 0; i < m; i++) {
        int u = E[i].first;
        int v = E[i].second;
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++) {
        num[i][inf]++;
        if (cutoradd[i]) {
            belong[i] = i;
            if (i <= nn) //如果是割点就统计自己的值  如果是缩出来的点就统计相邻非割点值
                num[i][w[i]]++;
            else
                for (int j = head[i]; ~j; j = ed[j].next) {
                    int v = ed[j].v;
                    if (!cutoradd[v]) {
                        num[i][w[v]]++;
                        belong[v] = i;
                    }
                }
        }
    }
}

struct node {
    int l, r, mn;
} f[N * 8];

void init(int l, int r, int i) {
    f[i].l = l;
    f[i].r = r;
    f[i].mn = inf;
    if (l == r)
        return;
    int mid = MID(l,r);
    init(l, mid, L(i));
    init(mid + 1, r, R(i));
}

void update(int pos, int i, int key) {
    if (pos == f[i].l && f[i].l == f[i].r) {
        f[i].mn = key;
        return;
    }
    int mid = MID(f[i].l,f[i].r);
    if (pos <= mid)
        update(pos, L(i), key);
    else
        update(pos, R(i), key);
    f[i].mn = min(f[L(i)].mn, f[R(i)].mn);
}

int query(int l, int r, int i) {
    if (l == f[i].l && r == f[i].r)
        return f[i].mn;
    int mid = MID(f[i].l,f[i].r);
    if (r <= mid)
        return query(l, r, L(i));
    else if (l > mid)
        return query(l, r, R(i));
    else
        return min(query(l, mid, L(i)), query(mid + 1, r, R(i)));
}

int dep[N * 2], pre[N * 2], size[N * 2], hson[N * 2], Top[N * 2], tid[N * 2],
        ftid[N * 2];

void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    pre[u] = fa;
    size[u] = 1;
    for (int i = head[u]; ~i; i = ed[i].next) {
        int v = ed[i].v;
        if (v != fa && cutoradd[v]) {
            dfs1(v, u);
            size[u] += size[v];
            if (size[v] > size[hson[u]])
                hson[u] = v;
            if (u > nn) //将儿子割点并上来
                num[u][w[v]]++;
        }
    }
}

void dfs2(int u, int tp) {
    Top[u] = tp;
    tid[u] = idx;
    ftid[idx] = u;
    update(idx, 1, (*(num[u].begin())).first);
    idx++;
    if (hson[u])
        dfs2(hson[u], tp);
    for (int i = head[u]; ~i; i = ed[i].next) {
        int v = ed[i].v;
        if (v != hson[u] && v != pre[u] && cutoradd[v])
            dfs2(v, v);
    }
}

void ask(int u, int v) {
    int fu = Top[u], fv = Top[v];
    int ans = inf;
    while (fu != fv) {
        if (dep[fu] < dep[fv]) {
            swap(fu, fv);
            swap(u, v);
        }
        ans = min(ans, query(tid[fu], tid[u], 1));
        u = pre[fu];
        fu = Top[u];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    ans = min(ans, query(tid[u], tid[v], 1));
    u = pre[u];
    if (u && u <= nn) //如果是缩出来的点  就多查询一下父亲
        ans = min(ans, query(tid[u], tid[u], 1));
    printf("%d\n", ans);
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    nn = n;
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    memset(head, -1, sizeof(head));
    tot = 0;
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    m = 0;
    bcc();
    build();
    init(1, n, 1);
    idx = 1;
    for (int i = 1; i <= n; i++) {
        if (cutoradd[i]) {
            dfs1(i, 0);
            dfs2(i, i);
            break;
        }
    }
    while (q--) {
        int u, v;
        char op[5];
        scanf("%s%d%d", op, &u, &v);
        if (op[0] == 'C') {
            num[belong[u]][w[u]]--; //更新自己
            if (num[belong[u]][w[u]] == 0)
                num[belong[u]].erase(w[u]);
            if (cutoradd[u] && pre[u]) { //如果是割点  更新一下父亲 （并到父亲上去）
                num[pre[u]][w[u]]--;
                if (num[pre[u]][w[u]] == 0)
                    num[pre[u]].erase(w[u]);
            }
            w[u] = v;
            num[belong[u]][v]++;
            update(tid[belong[u]], 1, (*num[belong[u]].begin()).first);
            if (cutoradd[u] && pre[u]) {
                num[pre[u]][v]++;
                update(tid[pre[u]], 1, (*num[pre[u]].begin()).first);
            }
        } else {
            if (u == v) //注意
                printf("%d\n", w[u]);
            else
                ask(belong[u], belong[v]);
        }
    }
    return 0;
}


