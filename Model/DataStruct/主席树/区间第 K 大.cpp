#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int MAXN=2e5+5;

int n,m;

struct TN{int lc,rc,sz;} t[MAXN*20];int tcnt;//nlogn
int rt[MAXN];

void insert(int l,int r,int x,int &y,int pos)
{
	y=++tcnt;
	t[y]=t[x];t[y].sz++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) insert(l,mid,t[x].lc,t[y].lc,pos);
	else insert(mid+1,r,t[x].rc,t[y].rc,pos);
}

int r2i(int l,int r,int x,int y,int k)
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	int pos=t[t[y].lc].sz-t[t[x].lc].sz;
	if(k<=pos) return r2i(l,mid,t[x].lc,t[y].lc,k);
	else return r2i(mid+1,r,t[x].rc,t[y].rc,k-pos);
}

int ncnt,a[MAXN],b[MAXN];
int main()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
	std::sort(b+1,b+n+1);
	ncnt=std::unique(b+1,b+n+1)-b-1;
	for(i=1;i<=n;i++)
		insert(1,ncnt,rt[i-1],rt[i],std::lower_bound(b+1,b+ncnt+1,a[i])-b);
	for(i=1;i<=m;i++)
	{
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		printf("%d\n",b[r2i(1,ncnt,rt[x-1],rt[y],z)]);
	}
}
