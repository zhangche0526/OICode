#include<iostream>
#include<cstdio>
#include<cstring>
inline void bitAdd(int &x,int p,int v){x+=(v<<((p-1)*3));}
inline int bitGet(int x,int p){return (x>>((p-1)*3))&(7);}

double f[1<<27];
char crd[10][5][5];

double dp(int cnt,int cntSum)
{
	if(!cntSum) return 1;
	if(f[cnt]>-0.5) return f[cnt];
	int i,j,tot=0;double sum=0;
	for(i=1;i<=9;i++) if(bitGet(cnt,i)>0)
		for(j=i+1;j<=9;j++) if(bitGet(cnt,j)>0)
			if(crd[i][bitGet(cnt,i)][0]==crd[j][bitGet(cnt,j)][0])
			{
				tot++;
				bitAdd(cnt,i,-1),bitAdd(cnt,j,-1);
				sum+=dp(cnt,cntSum-2);
				bitAdd(cnt,i,1),bitAdd(cnt,j,1);
			}
	if(!tot) return f[cnt]=0;
	else return f[cnt]=sum/tot; 
}

bool read()
{
	int i,j;
	for(i=1;i<=9;i++)
		for(j=1;j<=4;j++)
			if(scanf("%s",crd[i][j])!=1)
				return false;
	return true;
}

int main()
{
	int i;
	while(read())
	{
		memset(f,-1,sizeof(f));
		int cnt=76695844;
		printf("%.6f\n",dp(cnt,36));
	}
	return 0;
}
