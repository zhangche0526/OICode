#include <cstdio>
#include <algorithm>

using std::sort;

const int MAXN=500005;
int n;
double k;
int a[MAXN],rk[MAXN],ans[MAXN];
int he[MAXN],sz[MAXN];

struct line{int to,nex;}ed[MAXN];

class segT{
#define ls (u<<1)
#define rs (ls|1)
	private:
		int cnt[MAXN<<2];
		void upd(int u){cnt[u]=cnt[ls]+cnt[rs];}
		void mdf(int u,int l,int r,int pos,int x){
			if(l==r){
				cnt[u]+=x;
				return;
			}
			int mid=l+r>>1;
			if(pos<=mid) mdf(ls,l,mid,pos,x);
			else mdf(rs,mid+1,r,pos,x);
			upd(u);
		}
		//在当前需求下，k=当前要给某个点赋的值的第几个（可能有好多相同的）
		//在线段树上二分找最小的赋给它，
		//相当于它以及标号大于它而有这个需求的点都可以赋这个值，
		//由于这是贪心的将小的值尽量赋给标号大的节点，所以是最优的方案
		int qry(int u,int l,int r,int k){
			if(l==r) return l;
			int mid=l+r>>1;
			if(k<=cnt[rs]) return qry(rs,mid+1,r,k);
			else return qry(ls,l,mid,k-cnt[rs]);
		}
	public:
		void mdf(int pos,int x){mdf(1,1,n,pos,x);}
		int qry(int k){return qry(1,1,n,k);}
#undef ls
#undef rs
}T;

inline void addE(int u,int v){
	static int cnt;
	ed[++cnt]=(line){v,he[u]};
	he[u]=cnt;
}

inline void greedy(){
	for(int i=n,fa;i;--i){
		fa=i/k;
		addE(fa,i);
		sz[fa]+=++sz[i]; //1,2,...,n是这个树的一个拓扑排序
	}
	for(int i=he[0],v;i;i=ed[i].nex){
		v=ed[i].to;
		T.mdf(v,sz[v]); //标号>=v的点之前都有一个sz[v]的需求，要将小的值分过去
	}
	sort(a+1,a+n+1);
	for(int i=n;i;--i)
		rk[i]= a[i]==a[i+1] ? rk[i+1]+1:1;
	for(int i=1,u;i<=n;++i){
		u=T.qry(rk[i]);
		ans[u]=a[i];
		T.mdf(u,-sz[u]);
		for(int j=he[u],v;j;j=ed[j].nex){
			v=ed[j].to;
			T.mdf(v,sz[v]);
		}
	}
}

int main(){
	scanf("%d%lf",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	greedy();
	for(int i=1;i<=n;++i)
		printf("%d ",ans[i]);
	return 0;
}
