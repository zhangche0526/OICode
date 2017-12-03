#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=100,MAXM=1e4;
int scc[MAXN+1],indgr[MAXN+1],outdgr[MAXN+1];
int head[MAXN+1],ecnt;
struct node{int next,to;}e[MAXN+1];
void add(int x,y,z){++ecnt,e[ecnt].to=y,e[ecnt].next=head[x],head[x]=ecnt;}

int main()
{
	
	return 0;
}
