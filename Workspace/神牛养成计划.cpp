#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXL=2e6+5,MAXN=2005,MAXC=26,INF=1061109567;

int n,m;
int lp[MAXN],rp[MAXN];
char s[MAXL],s1[MAXL],s2[MAXL];int L1,L2;
struct TR{int c[26],l,r,wd;} t1[MAXL];int t1cnt=1,rk;
struct PTR{int c[26],sz;} t2[MAXL];int t2cnt,rt[MAXN];

void ist(int x,int y,int z)
{
	rt[y]=++t2cnt;y=rt[y];
	int i,j,c;
	for(i=rp[z]-1;i>=lp[z];i--)
	{
		c=s[i]-'a';t2[y].c[c]=++t2cnt;
		for(j=0;j<26;j++) if(j!=c) t2[y].c[j]=t2[x].c[j];
		y=t2[y].c[c],x=t2[x].c[c],t2[y].sz=t2[x].sz+1;
	}
}

int qry(int x,int y)
{
	int i,L2=strlen(s2),c;
	for(i=L2-1;i>=0;i--) c=s2[i]-'a',y=t2[y].c[c],x=t2[x].c[c];
	return t2[y].sz-t2[x].sz;
}

void dfs(int u)
{
	t1[u].l=rk+1;
	if(!u) return;
	if(t1[u].wd) t1[u].l=t1[u].r=++rk,ist(rt[rk-1],rk,t1[u].wd);
	for(int i=0;i<26;i++) dfs(t1[u].c[i]);
	t1[u].r=rk;
}

int main()
{
	int i,j;scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		lp[i]=rp[i-1];scanf("%s",s+lp[i]);rp[i]=strlen(s);
		int u;
		for(u=1,j=lp[i];j<rp[i];j++)
		{
			int c=s[j]-'a';
			if(!t1[u].c[c]) t1[u].c[c]=++t1cnt;
			u=t1[u].c[c];
		}
		t1[u].wd=i;
	}
	t1[0].l=INF,t1[0].r=0;
	dfs(1);
	scanf("%d",&m);
	int ans=0;
	for(i=1;i<=m;i++)
	{
		scanf("%s%s",s1,s2);L1=strlen(s1),L2=strlen(s2);
		for(j=0;j<L1;j++) s1[j]=(s1[j]-'a'+ans)%26+'a';
		for(j=0;j<L2;j++) s2[j]=(s2[j]-'a'+ans)%26+'a';
		int u;
		for(j=0;j<L1;j++) u=t1[u].c[s1[j]-'a'];
		ans=u? qry(rt[t1[u].l-1],rt[t1[u].r]):0;
		printf("%d\n",ans);
	}
	return 0;
}
