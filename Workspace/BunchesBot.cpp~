#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using std::min;
using std::max;
inline void umn(int &a,int b){a=min(a,b);}
inline void umx(int &a,int b){a=max(a,b);}

const int MAXN=1005,PR[11]={2,3,5,7,11,13,17,19,23,29,31},PSN=200,MAXS=(1<<11)+5;

int mxPF[MAXN],stt[MAXN];
int mnPF[MAXN],pri[MAXN],pcnt;
inline void preTab()
{
	int i,j;
	for(i=2;i<MAXN;i++)
	{
		if(!mnPF[i]) mnPF[i]=pri[++pcnt]=i;
		for(j=1;j<=pcnt&&pri[j]*i<MAXN;j++)
		{
			mnPF[pri[j]*i]=pri[j];
			if(i%pri[j]==0) break;
		}
	}
	for(i=2;i<MAXN;i++)
	{
		for(j=0;j<=10;j++) if(i%PR[j]==0) stt[i]|=1<<j;
		for(int x=i;x>1;x/=mnPF[x]) umx(mxPF[i],mnPF[x]);
	}
}

int gid[MAXN],gcnt;std::vector<int> gr[PSN];

int f[PSN][MAXS];
int solve(int n,int k)
{
	int i,aS=0;for(i=2;i<=n;i++) if(i!=k) aS|=stt[i];
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	
	for(i=2;i<=n;i++) if(i!=k)
	{
		if(mxPF[i]>31)
		{
			if(!gid[mxPF[i]]) gr[gid[mxPF[i]]=++gcnt].clear();
			gr[gid[mxPF[i]]].push_back(stt[i]);
		}
		else
		{
			umn(f[0][stt[i]],1);
			for(int laS=aS;laS;laS=(laS-1)&aS)
				umn(f[0][stt[i]|laS],f[0][laS]+1);
		}
	}
	
	unsigned p;
	for(i=1;i<=gcnt;i++)
		for(int oS=gr[i][p=0];p<gr[i].size();oS=gr[i][++p])
		{
			umn(f[i][oS],1);
			for(int laS=aS;laS;laS=(laS-1)&aS)
				umn(f[i][oS|laS],f[i-1][laS]+1);
		}
	return f[gcnt][aS];
}

int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	preTab();
	int Case,T;scanf("%d",&T);
	for(Case=1;Case<=T;Case++)
	{
		int n,k;scanf("%d%d",&n,&k);
		printf("Case #%d: %d\n",Case,solve(n,k));
	}
	return 0;
}
