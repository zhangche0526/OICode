int match[MAXN];
int times,fx[MAXN],fy[MAXN];
double lx[MAXN],ly[MAXN],slack[MAXN];

bool dfs(int u)
{
	int i;
	if(fx[u]==times) return false;
	fx[u]=times;
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(fy[v]==times) continue;
		double d=lx[u]+ly[v]-e[i].w;
		if(d>eps) slack[v]=std::min(slack[v],d);
		else
		{
			fy[v]=times;
			if(match[v]==0||dfs(match[v]))
			{
				match[v]=u;
				return true;
			}
		}
	}
	return false;
}

inline void adjust()
{
	int i;double a=INF;
	for(i=1;i<=N;i++) if(fy[i]<times) a=std::min(a,slack[i]);
	for(i=1;i<=N;i++) if(fx[i]==times) lx[i]-=a;
	for(i=1;i<=N;i++)
	{
		if(fy[i]==times) ly[i]+=a;
		else slack[i]-=a;
	}
}

double calc()
{
	int i,j;times=0;
	memset(fx,0,sizeof(fx));memset(fy,0,sizeof(fy));
	memset(ly,0,sizeof(ly));memset(match,0,sizeof(match));
	for(i=1;i<=N;i++)
	{
		lx[i]=-INF;
		for(j=G[i];j;j=e[j].next) lx[i]=std::max(lx[i],e[j].w);
	}
	for(i=1;i<=N;i++)
	{
		std::fill(slack+1,slack+1+N,INF);
		++times;
		int cnt=0;
		while(!dfs(i))
		{
			adjust();
			if(cnt++==N) return -INF;
			++times;
		}
	}
	double res=0;
	for(i=1;i<=N;i++) res+=lx[i]+ly[i];
	return res;
}
