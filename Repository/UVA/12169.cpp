#include<iostream>
#include<cstdio>
using std::cin;
using std::cout;
using std::endl;

const int MAXN=105,M=10001;

int T;
int x1[MAXN],x2[MAXN];

void solve()
{
	int i,a,b;
	for(a=0;a<M;a++)
		for(b=0;b<M;b++)
		{
			bool ok=true;
			for(i=1;i<=T;i++)
			{
				x2[i]=(a*x1[i]+b)%M;
				if(i!=T&&x1[i+1]!=(a*x2[i]+b)%M){ok=false;break;}
			}
			if(ok) return;
		}
}

int main()
{
	while(cin>>T)
	{
		int i;
		for(i=1;i<=T;i++) cin>>x1[i];
		solve();
		for(i=1;i<=T;i++) cout<<x2[i]<<endl;
	}
	return 0;
}
