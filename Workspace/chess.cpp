#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
using std::vector;
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
typedef long long ll;
const int MAXN=15,INF=1061109567;

int R,C;
int A[MAXN][MAXN],B[MAXN][MAXN],mxc[MAXN];

inline ll encode(int r,int c)
{
	ll res=0;
	for(int i=1;i<=R;i++) res=res*11+mxc[i];
	res=res*11+r;res=res*11+c;
	return res;
}

const int MAXNODE=1e6+5,SZ=61,PR[20]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,51,53,57,59,61};
class HT
{
	struct HTN
	{
		ll key;
		int val;
		bool occ;
		int c[SZ];
	} t[MAXNODE];int tcnt;
	bool find(int o,int lv,ll key,int *&val)
	{
		if(t[o].occ) if(t[o].key==key) {val=&t[o].val;return true;}
		int pos=key%PR[lv];
		if(!t[o].c[pos]) return false;
		return find(t[o].c[pos],lv+1,key,val);
	}
	int *nnd(int o,int lv,ll key)
	{
		if(!t[o].occ) {t[o].key=key,t[o].occ=true;return &t[o].val;}
		int pos=key%PR[lv];
		if(!t[o].c[pos]) t[o].c[pos]=++tcnt;
		return nnd(t[o].c[pos],lv+1,key);
	}
public:
	bool find(ll key){int *tmp;return find(1,0,key,tmp);}
	int &operator [](ll key)
	{
		int *res;
		if(find(1,0,key,res))
			return *res;
		return *nnd(1,0,key);
	}
	HT(){tcnt=1;t[1].occ=true,t[1].key=-1;};
} f;


//std::map<ll,int> mp;
int CNT;
int dfs(int lv,int r,int c)
{
//	if(f.find(encode())) return f[encode()];
	ll cd=encode(r,c);
	if(f.find(cd)) return f[cd];
	CNT++;
	int res=0;
	if(lv<R*C)
	{
		mxc[r]++;
		res=(lv&1)?INF:-INF;
		for(int i=1;i<=R;i++) if(mxc[i]<mxc[i-1])
		{
			int tmp=dfs(lv+1,i,mxc[i]+1);
			if(lv&1) umn(res,tmp);
			else umx(res,tmp);
		}
		mxc[r]--;
	}
	res+=(lv&1)?A[r][c]:-B[r][c];
	return f[cd]=res;
//	return res;//f[encode()]=res;
}

int main()
{
	int i,j;scanf("%d%d",&R,&C);
//	for(i=1;i<=R;i++) for(j=1;j<=C;j++) scanf("%d",&A[i][j]);
//	for(i=1;i<=R;i++) for(j=1;j<=C;j++) scanf("%d",&B[i][j]);
	mxc[0]=C;
	dfs(1,1,1);
	std::cerr<<CNT;
	return 0;
}
