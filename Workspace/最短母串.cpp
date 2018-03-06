#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>

const int MAXN=13,MAXL=51;

struct TRIEN{int c[26],fail,last,val,ec;} t[MAXN*MAXL];int tcnt;
void ist(char *s,int id)
{
	int i,u=0,sL=strlen(s);
	for(i=0;i<sL;i++)
	{
		int c=s[i]-'A';
		if(!t[u].c[c])
		{
			t[u].c[c]=++tcnt;
			t[tcnt].ec=c;
		}
		u=t[u].c[c];
	}
	t[u].val=1<<id;
}
void getFail()
{
	static std::queue<int> que;
	for(int c=0;c<26;c++) if(t[0].c[c]) que.push(t[0].c[c]);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		t[u].val|=t[t[u].last].val;
		for(int c=0;c<26;c++)
		{
			int v=t[u].c[c];if(!v) continue;
			que.push(v);
			int fu=t[u].fail;
			while(fu&&!t[fu].c[c]) fu=t[fu].fail;
			t[v].fail=t[fu].c[c];
			t[v].last=t[t[v].fail].val?t[v].fail:t[t[v].fail].last;
		}
	}
}

int n;

const int MAXS=1<<13;

struct QN{int id,S;} la[MAXN][MAXS];
std::queue<QN> que;
int vis[MAXN][MAXS];
void print(QN u)
{
	static char s[MAXN];int sL=0;
	while(u.id)
	{
		s[sL++]=t[u.id].ec+'A';
		int laid=u.id,laS=u.S;
		u=la[laid][laS];
	}
	std::reverse(s,s+sL);
	printf("%s\n",s);
}
void solve()
{
	getFail();
	int S=(1<<n)-1;
	que.push((QN){0,0});vis[0][0]=0;
	while(!que.empty())
	{
		int u=que.front().id,uS=que.front().S;que.pop();
		for(int c=0;c<26;c++)
		{
			int v=t[u].c[c],vS=uS|t[v].val;
			if(!v) continue;
			if(vis[v][vS]) continue;
			vis[v][vS]=true;
			la[v][vS]=(QN){u,uS};
			if(vS==S)
			{
				print((QN){v,vS});
				return;
			}
			que.push((QN){v,vS});
		}
	}
}

char s[MAXL];
int main()
{
	int i;scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%s",s);
		ist(s,i);
	}
	solve();
}

