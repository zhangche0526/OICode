#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
using std::max;

const int MAXL=1e6+5,SZ=26;
char s[MAXL];

class SAM
{
private:
	int rt,last;
	struct SAMN
	{
		int sz,mx,fa;
		int c[SZ];
		int &operator [](int p){return c[p];}
	} t[MAXL<<1];int tcnt;
	int idx(char c){return c-'a';}
	int nnd(int mx){t[++tcnt]=(SAMN){1,mx};return tcnt;}
	int cpnd(int u){t[++tcnt]=t[u];t[tcnt].sz=0;return tcnt;}
	void ext(int c)
	{
		int cur=last,u=nnd(t[last].mx+1);
		for(;cur&&!t[cur][c];cur=t[cur].fa)	t[cur][c]=u;
		if(!cur) t[u].fa=rt;
		else
		{
			int v=t[cur][c];
			if(t[v].mx==t[cur].mx+1) t[u].fa=v;
			else
			{
				int w=cpnd(t[cur][c]);
				t[w].mx=t[cur].mx+1;
				t[v].fa=t[u].fa=w;
				for(;t[cur][c]==v;cur=t[cur].fa) t[cur][c]=w;
			}
		}
		last=u;
	}
	int toposeq[MAXL<<1],dgr[MAXL];
	void toposort()
	{
		int i;
		for(i=1;i<=tcnt;i++) dgr[t[i].mx]++;
		for(i=1;i<=t[last].mx;i++) dgr[i]+=dgr[i-1];
		for(i=1;i<=tcnt;i++) toposeq[dgr[t[i].mx]--]=i;
	}
public:
	SAM(){rt=tcnt=last=1;}
	void ist(char *s)
	{
		for(int i=0,len=strlen(s);i<len;i++)
			ext(idx(s[i]));
	}
	ll cal()
	{
		toposort();
		int i;ll res=0;
		for(i=tcnt;i;i--)
		{
			int u=toposeq[i];
			t[t[u].fa].sz+=t[u].sz;
			if(t[u].sz>1) res=max(res,(ll)t[u].sz*t[u].mx);
		}
		return res;
	}
}sam;

int main()
{
	scanf("%s",s);
	sam.ist(s);
	printf("%lld",sam.cal());
	return 0;
}
