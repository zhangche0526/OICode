#include<iostream>
#include<cstdio>
#include<cmath>

const int MAXN=505,INF=1e8;
const double eps=1e-10;

int n,m;

struct P
{
	double x,y;
	P(double x=0,double y=0):x(x),y(y){};
}A[MAXN],B[MAXN];

P operator +(P a,P b){return P(a.x+b.x,a.y+b.y);}
P operator -(P a,P b){return P(a.x-b.x,a.y-b.y);}
double cross(P a,P b){return a.x*b.y-a.y*b.x;}

int dis[MAXN][MAXN];

bool col(P a,P b)
{
	int i;
	if(a.x>b.x) std::swap(a,b);
	for(i=1;i<=m;i++)
		if(B[i].x<a.x||B[i].x>b.x) return false;
	if(a.y>b.y) std::swap(a,b);
	for(i=1;i<=m;i++)
		if(B[i].y<a.y||B[i].y>b.y) return false;
	return true;
}

int jud(P a,P b)
{
	int c1=0,c2=0;
	for(int i=1;i<=m;i++)
	{
		double t=cross(b-a,B[i]-a);
		if(t>eps) c1++;
		if(t<-eps) c2++;
		if(c1*c2) return 0;
	}
	if(!c1&&!c2&&col(a,b)){printf("2\n");return -1;}
	if(c1) return 1;
	if(c2) return 2;
	return 3;
}

void floyd()
{
	int ans=INF;
	int i,j,k;
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			if(dis[i][k]<INF)
				for(j=1;j<=n;j++)
					dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
	for(i=1;i<=n;i++) ans=std::min(ans,dis[i][i]);
	if(ans==INF||ans<=2) printf("-1\n");
	else printf("%d",ans);
}

void solve()
{
	int i,j;
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
		{
			int flag=jud(A[i],A[j]);
			if(flag==-1) return;
			if(flag==1) dis[i][j]=1;
			else if(flag==2) dis[j][i]=1;
			else if(flag==3) dis[i][j]=dis[j][i]=1;
		}
	floyd();
}

bool spj()
{
	for(int i=1;i<=m;i++)
		if(fabs(B[i].x-A[1].x)>eps||fabs(B[i].y-A[1].y)>eps)
			return 0;
	printf("1\n");
	return 1;
}

int main()
{
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) for(j=1;j<=n;j++) dis[i][j]=INF;
	double tmp;
	for(i=1;i<=n;i++) scanf("%lf%lf%lf",&A[i].x,&A[i].y,&tmp);
	for(i=1;i<=m;i++) scanf("%lf%lf%lf",&B[i].x,&B[i].y,&tmp);
	if(spj()) return 0;
	else solve();return 0;
}
