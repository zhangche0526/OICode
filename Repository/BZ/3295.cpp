#include<iostream>
#include<cstdio>

const int MAXN=1e5+5;
struct node{int time,pos,val;} a[MAXN],b[MAXN];
int n,m,del[MAXN];
long long ans[MAXN];

int na[MAXN];
void add(int x,int y){for(;x<=n;x+=x&(-x)) na[x]+=y;}
int calSum(int x){int y=0;for(;x;x-=x&(-x)) y+=na[x];return y;}

void CDQ(int l,int r)
{
	if(l==r) return;
	int i,mid=l+r>>1;
	for(i=l;i<=r;i++)
		if(a[i].time<=mid) add(n-a[i].val+1,1);
		else ans[a[i].time]+=calSum(n-a[i].val+1);
	for(i=l;i<=r;i++) 
		if(a[i].time<=mid) add(n-a[i].val+1,-1);
	for(i=r;i>=l;i--)
		if(a[i].time<=mid) add(a[i].val,1);
		else ans[a[i].time]+=calSum(a[i].val);
	for(i=r;i>=l;i--)
		if(a[i].time<=mid) add(a[i].val,-1);
	for(i=l,x=l,y=mid+1;i<=r;i++)
		if(a[i].time<=mid) b[x++]=a[i];
		else b[y++]=a[i];
	for(i=l;i<=r;i++) a[i]=b[i];
	CDQ(l,mid);CDQ(mid+1,r);
}
int main()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i].val);
	for(i=1,x;i<=m;i++)
		scanf("%d",&x),del[x]=n-i+1;
	for(i=1,j=0;i<=n;i++)
		a[i].pos=i,a[i].time=del[a[i].val]?del[a[i].val]:++j;
	CDQ(1,n);
	for(i=1;i<=n;i++) ans[i]+=ans[i-1];
	for(i=n;i>n-m;i--) printf("%lld\n",ans[i]);
}
