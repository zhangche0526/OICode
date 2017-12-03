
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN=20;
struct note{int V,K;} na[MAXN+1];int nap;
int N,C;int rV,rK;
int ans;

bool cmp(const note & a,const note & b)
{
	return a.V<b.V;
}

int main()
{
	int i;
	ios::sync_with_stdio(false);
	freopen("2.in","r",stdin);
	freopen("2.out","w",stdout);
	cin>>N>>C;
	for(i=1;i<=N;i++)
	{
		cin>>rV>>rK;
		if(rV>=C)
		{
			ans+=rK;
			continue;
		}
		na[++nap].V=rV;
		na[nap].K=rK;
	}
	sort(na+1,na+nap+1,cmp);
	while(true)
	{
		int delta=C;//此日还剩多少钱需要支付
		for(i=nap;i>=1;i--)
			if(na[i].K>0&&delta>=na[i].V)
				do
				{
					na[i].K--;
					delta-=na[i].V;
				}while(na[i].K>0&&delta>=na[i].V);
		if(delta>0)
			for(i=1;i<=nap;i++)
				if(na[i].K>0&&delta<na[i].V)
				{
					na[i].K--;
					delta-=na[i].V;
					break;
				}
		if(delta>0) break;
		ans++;
	}
	cout<<ans<<endl;
	return 0;
}
