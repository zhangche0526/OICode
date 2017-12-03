#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<stack>
typedef long long ll;
const int MAXN=1e5+5;

struct E{int next,fr,to;} e[MAXN];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],u,v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

std::vector<int> bcc[MAXN];int bcnt,belong[MAXN];

int low[MAXN],dfn[MAXN],dcnt;
std::stack<E> st;
bool isCut[MAXN];

void tarjan(int u,int la)
{
	int ccnt=0;low[u]=dfn[u]=++dcnt;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			++ccnt;
			st.push((E){0,u,v});
			tarjan(v,u);
			low[u]=std::min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				bcc[++bcnt].clear();
				isCut[u]=true;
				E t;
				do
				{
					t=st.top();st.pop();
					if(belong[t.fr]!=bcnt) bcc[bcnt].push_back(t.fr),belong[t.fr]=bcnt;
					if(belong[t.to]!=bcnt) bcc[bcnt].push_back(t.to),belong[t.to]=bcnt;
				}while(u!=t.fr||v!=t.to);
			}	
		}else if(dfn[v]<dfn[u])
		{
			st.push((E){0,u,v});
			low[u]=std::min(low[u],dfn[v]);
		}
	}
	if(la==0&&ccnt==1) isCut[u]=false;
}

int main()
{
	int Case=0,n;
	while(~scanf("%d",&n)&&n)
	{
		memset(G,0,sizeof(G));ecnt=0;
		int i,j;
		for(i=1;i<=n;i++)
		{
			int u,v;scanf("%d%d",&u,&v);
			addEdge2(u,v);
		}
		memset(dfn,0,sizeof(dfn));
		memset(belong,0,sizeof(belong));
		memset(isCut,false,sizeof(isCut));
		bcnt=dcnt=0;
		tarjan(1,0);
		int ans1=0;ll ans2=1;
		for(i=1;i<=bcnt;i++)
		{
			int ccnt=0;
			for(j=0;j<bcc[i].size();j++)
				if(isCut[bcc[i][j]]) ccnt++;
			if(ccnt==1) ans1++,ans2*=(ll)bcc[i].size()-ccnt;
		}
		if(bcnt==1) ans1=2,ans2=bcc[1].size()*(bcc[1].size()-1)/2;
		printf("Case %d: %d %lld\n",++Case,ans1,ans2);
	}
	return 0;
}
