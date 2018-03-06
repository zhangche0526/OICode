#include<iostream>
#include<cstdio>
 
const int MAXN=2005;
 
int n,m,q;
int fV[MAXN][MAXN],fR[MAXN][MAXN],fC[MAXN][MAXN];
 
inline int calc(int f[MAXN][MAXN],int x1,int y1,int x2,int y2)
{return f[x2][y2]-f[x1-1][y2]-f[x2][y1-1]+f[x1-1][y1-1];}
 
int main()
{
	int i,j;scanf("%d%d%d",&n,&m,&q);
	for(i=1;i<=n;i++) for(j=1;j<=m;j++)
	{
		char c;do c=getchar();while(c!='0'&&c!='1');
		fV[i][j]= c=='1';
	}
	for(i=1;i<=n;i++) for(j=1;j<=m;j++)
		if(fV[i][j]) fR[i][j]+=fV[i+1][j],fC[i][j]+=fV[i][j+1];
	for(i=1;i<=n;i++) for(j=1;j<=m;j++)
		fV[i][j]+=fV[i][j-1],fR[i][j]+=fR[i][j-1],fC[i][j]+=fC[i][j-1];
	for(j=1;j<=m;j++) for(i=1;i<=n;i++)
		fV[i][j]+=fV[i-1][j],fR[i][j]+=fR[i-1][j],fC[i][j]+=fC[i-1][j];
	while(q--)
	{
		int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		int ans=calc(fV,x1,y1,x2,y2)-calc(fR,x1,y1,x2-1,y2)-calc(fC,x1,y1,x2,y2-1);
		printf("%d\n",ans);
	}
	return 0;
}
