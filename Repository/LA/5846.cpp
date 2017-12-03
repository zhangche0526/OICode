#include<iostream>
#include<cstdio>
#include<cstring>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;

const int MAXN=1005;

int a[MAXN];

int main()
{
	int T;cin>>T;
	while(T--)
	{
		int i,j,n;memset(a,0,sizeof(a));
		cin>>n;
		for(i=1;i<n;i++)
			for(j=i+1;j<=n;j++)
			{
				int c;scanf("%d",&c);
				if(c) a[i]++,a[j]++;
			}
		ll ans=(ll)n*(n-1)*(n-2);
		ll cnt=0;
		for(i=1;i<=n;i++) cnt+=a[i]*(n-1-a[i]);
		cnt/=2;
		ans-=cnt;
		cout<<ans<<endl;
	}
	return 0;
}
