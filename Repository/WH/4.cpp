#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN=5000;
int L,N,M;
struct node{int value,pre,next;} D[MAXN+1];
int a[MAXN+1];
void Init()
{
	for(int i=1;i<=N;i++)
	{
		D[i].pre=i-1;
		D[i].next=i+1;
		D[i].value=a[i];
	}
	D[0].pre=-1,D[0].next=1,D[0].value=0;
	D[N+1].pre=N,D[N+1].next=N+2,D[N+1].value=L;
}
void del(int x)
{
	D[D[x].pre].next=D[x].next;
	D[D[x].next].pre=D[x].pre;
}
int getdis(int x)
{
	return D[D[x].next].value-D[x].value;
}
bool check(int x)
{
	Init();
	int cnt=0;
	for(int tmp=0;tmp<N;tmp=D[tmp].next)
		while(getdis(tmp)<x)
		{
			if(D[tmp].next>N) break;
			del(D[tmp].next);
			cnt++;
		}
	if(getdis(D[N+1].pre)<x) 
	{
		del(D[N+1].pre);
		cnt++;
	}
	if(cnt<=M) return true;
	else return false;
}

int main()
{
	ios::sync_with_stdio(false);
	freopen("4.in","r",stdin);
	freopen("4.out","w",stdout);
	int i;
	cin>>L>>N>>M;
	for(i=1;i<=N;i++) cin>>a[i];
	sort(a+1,a+N+1);
	Init();
	int mindis=getdis(0);
	for(i=1;i<=N;i++)
		if(getdis(i)<mindis) 
			mindis=getdis(1);
	int l=mindis,r=L;
	while(l<r)
	{
		int mid=(l+r+1)/2;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	cout<<r<<endl;
	return 0;
}
