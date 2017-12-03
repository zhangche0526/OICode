#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
const int MAXN=1e5;
const int P=1e9+9;
struct cow{ll sum;int p;} a[MAXN+2];
bool cmp(const cow &x,const cow &y){return x.sum<y.sum;}
int L,R,N,p[MAXN+2];
ll sum[MAXN+2];
int lowbit(int x){return x&(-x);}
void update(int x,ll val)
{
    	while(x<=N)
	{
        	sum[x]=(sum[x]+val)%P;
        	x+=lowbit(x);
    	}
}
ll cal(int x)
{
    	ll tmp=0;
    	while(x)
    	{
        	tmp=(tmp+sum[x])%P;
        	x-=lowbit(x);
    	}
    	return tmp;
}
int main()
{
	ios::sync_with_stdio(false);
	freopen("11.in","r",stdin);
	freopen("11.out","w",stdout);
    	cin>>N;
    	for(int i=1;i<=N;i++)
    	{
        	ll val;
		cin>>val;
        	a[i].sum=a[i-1].sum+val;
        	a[i].p=i;
    	}
    	a[N+1].sum=0;
    	a[N+1].p=N+1;
    	sort(a+1,a+N+2,cmp);
    	int t=0;
    	for(int i=1;i<=N+1;i++)
	{
        	if(i==1||a[i].sum!=a[i-1].sum) ++t;
        	p[a[i].p]=t;
    	}
    	update(p[N+1],1);
    	ll tmp=0;
    	for(int i=1;i<=N;i++){
        	tmp=cal(p[i]);
        	update(p[i],tmp);
    	}
    	cout<<tmp<<endl;
}
