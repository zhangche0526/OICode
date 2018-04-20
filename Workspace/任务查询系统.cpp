#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using std::vector;
using std::min;
typedef long long ll;
const int MAXN=1e5+5;

int n,m;
int L[MAXN],R[MAXN],V[MAXN];

int val[MAXN],blg[MAXN],gcnt;
inline void dcrt()
{
	int i;memcpy(val,V,sizeof V);
	std::sort(val+1,val+n+1);
	gcnt=std::unique(val+1,val+n+1)-(val+1);
	for(i=1;i<=n;i++) blg[i]=std::lower_bound(val+1,val+gcnt+1,V[i])-val;
}

struct CMT{int lc,rc,sz;ll sum;} t[MAXN*20];int tcnt,rt[MAXN];
void ist(int &o,int la,int l,int r,int p)
{
	t[o=++tcnt]=t[la];
	t[o].sz+=p/abs(p),t[o].sum+=p/abs(p)*val[abs(p)];
	if(l==r) return;
	int mid=l+r>>1;
	if(abs(p)<=mid) ist(t[o].lc,t[la].lc,l,mid,p);
	else ist(t[o].rc,t[la].rc,mid+1,r,p);
}
inline void ist(int p,int v){ist(rt[p],rt[p]?rt[p]:rt[p-1],1,gcnt,v);}

ll calSum(int o,int l,int r,int k)
{
	if(l==r) return (ll)min(k,t[o].sz)*val[l];
	int lsz=t[t[o].lc].sz;
	int mid=l+r>>1;
	if(k<=lsz) return calSum(t[o].lc,l,mid,k);
	return t[t[o].lc].sum+calSum(t[o].rc,mid+1,r,k-lsz);
}
inline ll qry(int p,int k){return calSum(rt[p],1,gcnt,k);}

int main()
{
	int i;scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d%d%d",L+i,R+i,V+i);dcrt();
	static vector<int> opt[MAXN];
	for(i=1;i<=n;i++) opt[L[i]].push_back(blg[i]),opt[R[i]+1].push_back(-blg[i]);
	for(i=1;i<=m;i++)
	{
		for(vector<int>::iterator it=opt[i].begin();it!=opt[i].end();it++)
			ist(i,*it);
		if(!opt[i].size()) rt[i]=rt[i-1];
	}
	ll ans=1;
	while(m--)
	{
		int x,k,a,b,c;scanf("%d%d%d%d",&x,&a,&b,&c);k=(ans%c*a+b)%c+1;
		printf("%lld\n",ans=qry(x,k));
	}
	return 0;
}
/*
4 3
1 2 6
2 3 3
1 3 2
3 3 4
3 1 3 2
1 1 3 4
2 2 4 3
*/
