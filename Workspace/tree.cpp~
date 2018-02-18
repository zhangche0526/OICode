bool vis[MAXN];int rt;
int mxv[MAXN],mnv;

void calSz(int u,int la)
{
	sz[u]=1,mxv[u]=0;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la||vis[v]) continue;
		calSz(v,u);
		sz[u]+=sz[v];
		umx(mxv[u],sz[v]);
	}
}

void calRt(int u,int la,int r)
{
	umx(mxv[u],sz[r]-sz[u]);
	if(mxv[u]<mnv) mnv=mxv[u],rt=u;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la||vis[v]) continue;
		calRt(v,u);
	}
}

void treeDC(int u)
{
	mnv=n;calSz(u,0);calRt(u,0,u);
	vis[rt]=true;
	dfs(rt);
	for(i=G[rt];i;i=e[i].next)
	{
		int v=e[i].to;
		if(vis[v]) continue;
		treeDC(v);
	}	
}
