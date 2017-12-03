#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

map<int,int> mp;

const int MAXN=2e5,MAXQ=2e5;
int n,Q;
int a[MAXN+1],times[MAXN+1];

struct FT
{
	int na[MAXN+1];
	int lowbit(int x) {return x&(-x);}
	void add(int x,int y) {for(;x<=n;x+=lowbit(x)) na[x]+=y;}
	int calSum(int x) {int res=0;for(;x;x-=lowbit(x)) res+=na[x];return res;}
} ft;

struct R
{
	int l,r;
	int qid,flag;
} range[3*MAXN+1];int rcnt;
bool cmp(const R & a,const R & b){return a.r<b.r;}

int ans[MAXQ+1];

int main()
{
	int i;
	scanf("%d%d",&n,&Q);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		times[i]=mp[a[i]];
		mp[a[i]]=i;
	}
	for(i=1;i<=Q;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		range[++rcnt]=(R){x,y,i,-1};
		range[++rcnt]=(R){y+1,z,i,-1};
		range[++rcnt]=(R){x,z,i,1};
	}
	sort(range+1,range+rcnt+1,cmp);
	int j=1,k=0;
	for(i=1;i<=n;i++)
	{
		if(times[i])
		{
			ft.add(times[i],1);
			++k;
		}
		for(;j<=rcnt&&range[j].r==i;j++)
			ans[range[j].qid]+=(k-ft.calSum(range[j].l-1))*range[j].flag;
	}
	for(i=1;i<=Q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
