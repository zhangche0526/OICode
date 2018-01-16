#include<iostream>
#include<cstdio>
const int MAXN=2005,P=998244353;
inline void madd(int &a,int b){a=(a+b)%P;}

int D,N,M;

struct V
{
	int v[6];
	void read(){for(int i=1;i<=D;i++) scanf("%d",v+i);}
};
bool operator ==(const V &a,const V &b)
{for(int i=1;i<=D;i++) if(a.v[i]!=b.v[i]) return false;return true;}
bool operator <(const V &a,const V &b)
{for(int i=1;i<=D;i++) if(a.v[i]>=b.v[i]) return false;return true;}
bool operator >(const V &a,const V &b)
{for(int i=1;i<=D;i++) if(a.v[i]<=b.v[i]) return false;return true;}

V a[MAXN],b[MAXN];

int g[MAXN][MAXN][2],h[MAXN][MAXN][2];

int main()
{
	int i,j,s,t;scanf("%d",&D);
	scanf("%d",&N);
	for(i=1;i<=N;i++) a[i].read();
	scanf("%d",&M);
	for(i=1;i<=M;i++) b[i].read();

	int ans=0;
	for(i=1;i<=N;i++) for(j=1;j<=M;j++) for(s=0;s<2;s++)
	{
		if(a[i]==b[j])
		{
			t=h[i][j][s^1];
			if(!s) madd(t,1);
			if(t) madd(ans,t),madd(g[i+1][j][s],t);
		}
		if(g[i][j][s])
		{
			madd(g[i+1][j][s],g[i][j][s]);
			if((s&&a[i]<b[j])||(!s&&a[i]>b[j])) madd(h[i][j+1][s],g[i][j][s]);
		}
		if(h[i][j][s]) madd(h[i][j+1][s],h[i][j][s]);
	}
	printf("%d",ans);
	return 0;
}
