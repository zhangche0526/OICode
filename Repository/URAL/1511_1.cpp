#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;

const int MAXN=15,MOD=3e4+5,MAXST=1e6+5;

int N,M;

bool mp[MAXN][MAXN];int code[MAXN];
int ex,ey;
struct HM
{
	int hd[MOD],nxt[MAXST],sz;
	ll state[MAXST],f[MAXST];
	void init(){sz=0;memset(hd,-1,sizeof(hd));}
	void push(ll st,ll ans)
	{
		int i;
		int s=st%MOD;
		for(i=hd[s];i!=-1;i=nxt[i])
			if(state[i]==st)                                                                          
			{
				f[i]+=ans;
				return;
			}
		state[sz]=st,f[sz]=ans,nxt[sz]=hd[s],hd[s]=sz;
		sz++;
	}
} hm[2];
void decode(ll st)
{
	for(int i=M;i>=0;i--,st>>=3)
		code[i]=st&7;
}

int ch[MAXN];
ll encode()
{
	int cnt=1;
	memset(ch,-1,sizeof(ch));
	ch[0]=0;
	ll res=0;
	for(int i=0;i<=M;i++)
	{
		if(ch[code[i]]==-1) ch[code[i]]=cnt++;
		code[i]=ch[code[i]];
		res<<=3;
		res|=code[i];
	}
	return res;
}

void shift()
{
	for(int i=M;i;i--) code[i]=code[i-1];
	code[0]=0;
}

void dpBlank(int i,int j,int cur)
{
	int L,U;
	for(int k=0;k<hm[cur].sz;k++)
	{
		decode(hm[cur].state[k]);
		L=code[j-1];
		U=code[j];
		if(L&&U)
		{
			if(L==U)
			{
				if(i==ex&&j==ey)
				{
					code[j-1]=code[j]=0;
					if(j==M) shift();
					hm[cur^1].push(encode(),hm[cur].f[k]);
				}
			}else
			{
				code[j-1]=code[j]=0;
				for(int t=0;t<=M;t++)
					if(code[t]==U)
						code[t]=L;
				if(j==M) shift();
				hm[cur^1].push(encode(),hm[cur].f[k]);
			}
		}else if((L&&(!U))||((!L)&&U))
		{
			int t;
			if(L) t=L;
			else t=U;
			if(mp[i][j+1])
			{
				code[j-1]=0,code[j]=t;
				hm[cur^1].push(encode(),hm[cur].f[k]);
			}
			if(mp[i+1][j])
			{
				code[j-1]=t,code[j]=0;
				if(j==M) shift();
				hm[cur^1].push(encode(),hm[cur].f[k]);
			}
		}
		else
		{
			if(mp[i][j+1]&&mp[i+1][j])
			{
				code[j-1]=code[j]=13;
				hm[cur^1].push(encode(),hm[cur].f[k]);
			}
		}
	}
}
void dpBlock(int i,int j,int cur)
{
	for(int k=0;k<hm[cur].sz;k++)
	{
		decode(hm[cur].state[k]);
		code[j-1]=code[j]=0;
		if(j==M) shift();
		hm[cur^1].push(encode(),hm[cur].f[k]);
	}
}

int main()
{
	int i,j;
	scanf("%d%d",&N,&M);
	char c;
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
		{
			do c=getchar();while(c!='*'&&c!='.');
			if(c=='.') ex=i,ey=j,mp[i][j]=true;
		}
	if(!ex) {printf("0\n");return 0;}
	int cur=0;ll ans=0;
	hm[cur].init();
	hm[cur].push(0,1);
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
		{
			hm[cur^1].init();
			if(mp[i][j]) dpBlank(i,j,cur);
			else dpBlock(i,j,cur);
			cur^=1;
		}
	for(i=0;i<hm[cur].sz;i++)
		ans+=hm[cur].f[i];
	printf("%I64d\n",ans);
	return 0;
}
