#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;

ll n,m,k;int P;

inline void uadd(int &a,int b){a=(a+b)%P;}
int prd[64];

int f[100][2][2][2],g[100][2][2][2];
inline void DP()
{
	memset(f,0,sizeof f);memset(g,0,sizeof g);
	f[0][1][1][1]=1,g[0][1][1][1]=0;
	for(int i=0;i<64;i++)
		for(int an=0;an<2;an++)
		for(int am=0;am<2;am++)
		for(int ak=0;ak<2;ak++)
		if(f[i][an][am][ak])
		{
			int bn=((n&(1ll<<(63-i)))==0)?0:1,bm=((m&(1ll<<(63-i)))==0)?0:1,bk=((k&(1ll<<(63-i)))==0)?0:1;
			for(int x=0;x<2;x++) if(!an||x<=bn)
			for(int y=0;y<2;y++)
			{
				if(am&&y>bm) continue;
				int z=x^y;if(ak&&z<bk) continue;
				int cn=an&&x==bn,cm=am&&y==bm,ck=ak&&z==bk;
				uadd(f[i+1][cn][cm][ck],f[i][an][am][ak]);
				uadd(g[i+1][cn][cm][ck],g[i][an][am][ak]+(ll)(z==0)*prd[63-i]*f[i][an][am][ak]%P);
			}
		}
}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int i;scanf("%lld%lld%lld%d",&n,&m,&k,&P);n--,m--;
		for(prd[0]=i=1;i<64;i++) prd[i]=(ll)prd[i-1]*2%P;
		DP();k%=P;
		int ans=0;
		for(int an=0;an<2;an++)
			for(int am=0;am<2;am++)
				for(int ak=0;ak<2;ak++)
					uadd(ans,f[64][an][am][ak]+P-k*g[64][an][am][ak]%P);
		printf("%d\n",ans);
	}
	return 0;
}
