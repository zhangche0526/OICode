#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

const int SIGMA_SIZE=26,MAXNODE=11000,MAXS=160;

struct ACA
{
	int ch[MAXNODE][SIGMA_SIZE];
	int f[MAXNODE],val[MAXNODE],last[MAXNODE];
	int cnt[MAXS];
	int sz;
	ACA()
	{
		sz=1;
		memset(ch[0],0,sizeof(ch[0]));
		memset(cnt,0,sizeof(cnt));
	}
	int idx(char c){return c-'a';}
	void insert(char *s, int id)
	{
		int i,u=0,sL=strlen(s);
		for(i=0;i<sL;i++)
		{
			int c=idx(s[i]);
			if(!ch[u][c])
			{
				memset(ch[sz],0,sizeof(ch[sz]));
				val[sz]=0;
				ch[u][c]=sz++;
			}
			u = ch[u][c];
		}
		val[u]=id;
	}

	void print(int x) 
	{
		if(x)
		{
			cnt[val[x]]++;
			print(last[x]);
		}
	}

	int find(char *T) 
	{
		int i,j,TL=strlen(T);
		for(i=j=0;i<TL;i++)
		{
			int c=idx(T[i]);
			while(j&&!ch[j][c]) j=f[j];
			j=ch[j][c];
			if(val[j]) print(j);
			else if(last[j]) print(last[j]);
		}
	}

	void getFail()
	{
		std::queue<int> que;
		f[0]=0;
		for(int c=0;c<SIGMA_SIZE;c++)
		{
			int u=ch[0][c];
			if(u){f[u]=0;que.push(u);last[u]=0;}
		}
		while(!que.empty())
		{
			int r=que.front();que.pop();
			for(int c=0;c<SIGMA_SIZE;c++)
			{
				int u=ch[r][c];
				if(!u) continue;
				que.push(u);
				int v=f[r];
				while(v&&!ch[v][c]) v=f[v];
				f[u]=ch[v][c];
				last[u]=val[f[u]]?f[u]:last[f[u]];
			}
		}
	}
};

ACA aca;
char T[1000001],P[151][80];
int n;

int main()
{
	while(scanf("%d",&n)!=EOF&&n)
	{
		int i;
		aca=ACA();
		for(i=1;i<=n;i++)
		{
			scanf("%s",P[i]);
			aca.insert(P[i],i);
		}
		aca.getFail();
		scanf("%s",T);
		aca.find(T);
		int maxT=-1;
		for(i=1;i<=n;i++)
			maxT=std::max(aca.cnt[i],maxT);
		printf("%d\n",maxT);
		for(i=1;i<=n;i++)
			if(aca.cnt[i]==maxT) printf("%s\n",P[i]);
	}
	return 0;
}
