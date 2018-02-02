#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
const int MAXN=1e6+5,P=1e9+7;

struct E{int next,to;} e[MAXN];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}

int num[MAXN];

int st[MAXN],tp;
void dfs(int u)
{
	st[++tp]=u;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		num[v]=std::upper_bound(st+1,st+tp+1,v>>1)-st-1;
		dfs(v);

	}
	tp--;
}

int nxt[MAXN];

int n;char s[MAXN];

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int i,j;memset(G,0,sizeof G);ecnt=0;
		scanf("%s",s);n=strlen(s);
		for(i=1,j;i<n;i++)
		{
			j=nxt[i];
			while(j&&s[i]!=s[j]) j=nxt[j];
			nxt[i+1]= s[i]==s[j]?j+1:0;
		}
		for(i=1;i<=n;i++) addEdge(nxt[i],i);
		dfs(0);
		ll ans=1;
		for(i=1;i<=n;i++) ans=ans*num[i]%P;
		printf("%lld\n",ans);
	}
	return 0;
}

/*
1
abcbaabcba
*/
