#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;

const int MAXN=1e4+5,MAXM=5e4+5;

int N,M;

struct E{int from,to,next;} e[MAXM];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){u,v,G[u]};G[u]=ecnt;}

stack<int> st;
bool inSt[MAXN];
int belong[MAXN],gcnt,gsz[MAXN];

int dfn[MAXN],low[MAXN];
int dcnt;
void tarjan(int u)
{
    int i;
    dfn[u]=low[u]=++dcnt;
    st.push(u);inSt[u]=true;
    for(i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else 
            if(inSt[v])
                low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        ++gcnt;
        do
        {
            u=st.top();st.pop();
            inSt[u]=false;
            belong[u]=gcnt;
            ++gsz[gcnt];
        }while(low[u]!=dfn[u]);
    }
}

int outDgr[MAXN];

int main()
{
    int i;
    scanf("%d%d",&N,&M);
    for(i=1;i<=M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addEdge(u,v);
	}
	for(i=1;i<=N;i++)
		if(!dfn[i]) tarjan(i);
	for(i=1;i<=M;i++)
		if(belong[e[i].from]!=belong[e[i].to])
			outDgr[belong[e[i].from]]++;
	int ans;
	bool exist=false;
	for(i=1;i<=gcnt;i++)
		if(!outDgr[i])
			if(exist)
			{
				exist=false;
				break;
			}else exist=true,ans=i;
	if(exist) printf("%d\n",gsz[ans]);
	else printf("0\n");
	return 0;
}
