#include<iostream>
#include<cstdio>

const int MAXN=1005,MAXM=1e4+5,INF=1061109567;

struct SPLX
{
	int n,m;
	double ans;
	double (*A)[MAXN],*B,*C;
	inline void pvt(int o,int p)
	{
		int i,j;
		A[o][p]=1/A[o][p],B[o]*=A[o][p];
		for(i=1;i<=n;i++) if(i^p) A[o][i]*=A[o][p];
		for(i=1;i<=m;i++) if((i^o)&&A[i][p])
		{
			for(j=1;j<=n;j++) if(j^p) A[i][j]-=A[i][p]*A[o][j];
			B[i]-=A[i][p]*B[o],A[i][p]*=-A[o][p];
		}
		for(i=1;i<=n;i++) if(i^p) C[i]-=C[p]*A[o][i];
		ans+=C[p]*B[o],C[p]*=-A[o][p];
	}
	double solve()
	{
		int i,p;
		while(true)
		{
			for(p=1;p<=n;p++) if(C[p]>0) break;
			if(p==n+1) return ans;
			int o;double tmp=INF;
			for(i=1;i<=m;i++) if(A[i][p]>0&&B[i]/A[i][p]<tmp) tmp=B[i]/A[i][p],o=i;
			if(tmp==INF) return INF;
			pvt(o,p);
		}
	}
	SPLX(){}
	SPLX(int n,int m,double (*A)[MAXN],double *B,double *C):n(n),m(m),A(A),B(B),C(C){}
} splx;

int n,m;

double a[MAXM][MAXN],b[MAXM],c[MAXN];

int main()
{
	int i,j;scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%lf",c+i);
	for(i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d%lf",&l,&r,b+i);
		for(j=l;j<=r;j++) a[i][j]=1;
	}
	splx=SPLX(n,m,a,b,c);
	printf("%.0f",splx.solve());
	return 0;
}
