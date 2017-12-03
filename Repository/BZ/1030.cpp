#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

const int SIGMA_SIZE=26,MAXNODE=6005,MAXS=65,MOD=1e4+7;

struct ACA
{
	int ch[MAXNODE][SIGMA_SIZE];
	int f[MAXNODE];
	bool danger[MAXNODE];
	int sz;
	int idx(char c){return c-'A';}
	void insert(char *s, int id)
	{
		int i,u=0,sL=strlen(s);
		for(i=0;i<sL;i++)
		{
			int c=idx(s[i]);
			if(!ch[u][c]) ch[u][c]=++sz;
			u=ch[u][c];
		}
		danger[u]=true;
	}

	std::queue<int> que;
	void getFail()
	{
		f[0]=0;
		for(int c=0;c<SIGMA_SIZE;c++)
		{
			int u=ch[0][c];
			if(u){que.push(u);}
		}
		while(!que.empty())
		{
			int u=que.front();que.pop();
			danger[u]|=danger[f[u]];
			for(int c=0;c<SIGMA_SIZE;c++)
			{
				int v=ch[u][c];
				if(v)
				{
					f[v]=ch[f[u]][c];
					que.push(v);
				}
				else ch[u][c]=ch[f[u]][c];
			}
		}
	}
};

int N,M;
ACA aca;
char s[105];
int f[MAXNODE][MAXNODE];

int main()
{
	int i,j,k;
	scanf("%d%d",&N,&M);
	for(i=1;i<=N;i++) scanf("%s",s),aca.insert(s,i);
	aca.getFail();
	f[0][0]=1;
	for(i=1;i<=M;i++)
		for(j=0;j<=aca.sz;j++)
			if(!aca.danger[j]&&f[i-1][j]>0)
				for(k=0;k<26;k++)
					f[i][aca.ch[j][k]]=(f[i][aca.ch[j][k]]+f[i-1][j])%MOD;
	int cnt=0,tot=1,ans;
	for(i=1;i<=M;i++) tot=(tot*26)%MOD;
	for(i=0;i<=aca.sz;i++) if(!aca.danger[i]) cnt=(cnt+f[M][i])%MOD;
	ans=(tot-cnt+MOD)%MOD;
	printf("%d\n",ans);
	return 0;
}
