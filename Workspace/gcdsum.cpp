#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXN=1e5+5;

ll f[MAXN];
int pri[MAXN],pcnt;bool notPri[MAXN];
int p[MAXN],a[MAXN];
inline void preTab()
{
	int i,j;
	f[1]=1;
	for(i=2;i<MAXN;i++)
	{
		if(!notPri[i]) pri[++pcnt]=i,f[i]=2*i-1,p[i]=i,a[i]=1;
		for(j=1;j<=pcnt&&i*pri[j]<MAXN;j++)
		{
			notPri[i*pri[j]]=true;
			if(i%pri[j])
			{
				f[i*pri[j]]=(ll)f[pri[j]]*f[i];
				if(pri[j]<p[i]) p[i*pri[j]]=pri[j],a[i*pri[j]]=1;
				else p[i*pri[j]]=p[i],a[i*pri[j]]=a[i];
			}
			else
			{
				f[i*pri[j]]=f[i]/((ll)(a[i]+1)*p[i]-a[i])
					        *((ll)(a[i]+2)*p[i]*p[i]-(ll)(a[i]+1)*p[i]);
				p[i*pri[j]]=p[i],a[i*pri[j]]=a[i]+1;
				break;
			}
		}
	}
	for(i=2;i<MAXN;i++) f[i]+=f[i-1];
}

int main()
{
	preTab();
	int n,m;scanf("%d%d",&n,&m);
	printf("%lld",);
	return 0;
}
