#include<iostream>
#include<cstdio>

const int MAXK=500,P=1e6+7;

int n,m,k;

int C[MAXK+5][MAXK+5];
inline void preTab()
{
	int i,j;
	C[0][0]=1;
	for(i=1;i<=MAXK;i++)
	{
		C[i][0]=C[i][i]=1;
		for(j=1;j<i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
	}
}

int main()
{
	preTab();
	int Case,T;scanf("%d",&T);
	for(Case=1;Case<=T;Case++)
	{
		int ans=0;
		scanf("%d%d%d",&n,&m,&k);
		for(int S=0;S<16;S++)
		{
			int cnt=0,r=n,c=m;
			if(S&1) r--,cnt++;if(S&2) r--,cnt++;
			if(S&4) c--,cnt++;if(S&8) c--,cnt++;
			if(cnt&1) ans=(ans-C[r*c][k]+P)%P;
			else ans=(ans+C[r*c][k])%P;
		}
		printf("Case %d: %d\n",Case,ans);
	}
	return 0;
}
