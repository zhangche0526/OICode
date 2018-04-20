#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
using std::abs;

double randPct(){return (double)rand()/32767.0;}
int randInt(int l,int r){return randPct()*randPct()*(r-l+1)+l;}

const int MAXN=1005,PopSz=20,GenLim=100;
const double Pc=0.5,Pm=0.1;

int n,t,sum,diff;

int S[MAXN];
bool pop[PopSz+5][MAXN],pop1[PopSz+5][MAXN];
bool chs[MAXN];

inline void preprd()
{
	int i,j;sum=0;
	for(i=1;i<=n;i++) sum+=S[i];
	if(sum<=t)
	{
		for(i=1;i<=n;i++) chs[i]=true;
		return;
	}
	int k=sum/t;
	for(i=1;i<=PopSz;i++)
		for(j=1;j<=n;j++) pop[i][j]=randInt(1,k)==1;
	diff=t;
}

int dc;
int f1[PopSz+5];
bool work;

int f[PopSz+5],g[PopSz+5];
void slcRpd()
{
	int i,j,k,fm=0;memset(f,0,sizeof f);
	for(i=1;i<=PopSz;i++)
	{
		for(j=1;j<=n;j++) f[i]+=S[j]*pop[i][j];
		f[i]-=t;
		if(f[i]<0&&abs(f[i])<diff)
		{
			diff=abs(f[i]);
			dc=0;
			memcpy(chs,pop[i],sizeof pop[i]);
		}
		if(!f[i])
		{
			work=false;
			return;
		}
		if(abs(fm)<abs(f[i])) fm=f[i];
	}
	for(i=1;i<=PopSz;i++) f[i]=abs(fm-f[i]);
	dc++;
	int fs=0;for(i=1;i<=PopSz;i++) fs+=abs(f[i]);
	k=0;
	for(i=1;i<=PopSz;i++)
	{
		g[i]=(double)abs(f[i])/fs*PopSz;
		k+=g[i];
	}
	while(k<PopSz) g[randInt(1,PopSz)]++,k++;
	k=0;
	for(i=1;i<=PopSz;i++)
	{
		for(j=1;j<=g[i];j++)
		{
			pop1[++k]=pop[i];
			f1[k]=f[i];
		}
		memcpy(pop,pop1,sizeof pop1);
	}
}

void cross()
{
	int i,j,k;
	for(i=1;i<=int(Pc*PopSz+0.5);i++)
	{
		int u=randInt(1,PopSz),v=randInt(1,PopSz);
		int l=randInt(1,n),r=randInt(1,n);
		if(l>r) std::swap(l,r);
		k=0;
		for(j=l;j<=r;j++) k+=pop[u][j]-pop[v][j];
		if(!((f1[u]<0&&f1[v]<0&&k>0)||(f1[u]>0&&f1[v]<0&&k<0)))
			continue;
		f1[u]-=k,f1[v]+=k;
		for(j=l;j<=r;j++) std::swap(pop[u][j],pop[v][j]);
	}
}

void mutate()
{
	int i,j,k;
	for(i=1;i<=int(n*Pm*PopSz+0.5);i++)
	{
		j=randInt(1,PopSz),k=rand(1,n);
		if((f1[j]<0&&!pop[j][k])||(f1[j]>0)&&pop[j][k])
			f1[j]+=(1-2*pop[j][k])*S[k],pop[j][k]^=1;
	}
}

void GA()
{
	if(sum<=t) return;
	work=true;
	dc=0;
	while(work)
	{
		slcRpd();
		if(dc>GenLim) return;
		if(work)
		{
			cross();
			mutate();
		}
	}
}

int main()
{
	int i;scanf("%d%d",&n,&t);
	for(i=1;i<=n;i++) scanf("%d",S+i);
	preprd();
	GA();
	int ans=0,cnt=0;
	for(i=1;i<=n;i++) if(chs[i]) ans+=S[i],cnt++;
	printf("%d\n%d\n",ans,cnt);
	for(i=1;i<=n;i++) if(chs[i]) printf("%d ",i);
	return 0;
}
