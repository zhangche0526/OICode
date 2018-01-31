#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <set>
#include <stack>

using std::swap;
using std::set;
using std::stack;

const int MAXN=100005,MOD=1e9;
int r[MAXN];

class Treap{
#define ls s[0]
#define rs s[1]
	public:
		struct node{
			int val,key,cnt,sz;
			node *s[2];
			node(){val=key=cnt=sz=0; s[0]=s[1]=Null;}
			node(int _val):val(_val),key(rand()){
				cnt=sz=1,ls=rs=Null;
			}
			void* operator new(size_t){
				node *ret;
				if(mem_cur>mem_pool) ret=&*(mem_cur--);
				else ret=mem_bin.top(),mem_bin.pop();
				return ret;
			}
			void operator delete[](void *u){ //删除子树
				if(((node*)u)->ls!=Null) delete[](((node*)u)->ls);
				if(((node*)u)->rs!=Null) delete[](((node*)u)->rs);
				mem_bin.push((node*)u);
			}
			void upd(){sz= ls->sz + rs->sz + cnt;}
		}*rt;
		static node *Null;
		Treap(){rt=Null;}
	private:
		static node mem_pool[MAXN*100];
		static node *mem_cur;
		static stack<node*> mem_bin;
	private:
		static node* rot(node *u,bool lr){
			node *son=u->s[lr];
			u->s[lr]=son->s[lr^1];
			son->s[lr^1]=u;
			u->upd(),son->upd();
			return son;
		}
		static node* maintain(node *u,bool lr){
			if(u->key > u->s[lr]->key)
				u=rot(u,lr);
			return u;
		}
	public:
		static void ist(node *&u,int val){
			if(u==Null){
				u= new node(val);
				return;
			}
			if(u->val == val) ++u->cnt;
			else{
				bool lr=(val > u->val);
				ist(u->s[lr],val);
				u=maintain(u,lr);
			}
			u->upd();
		}
		void ist(int val){ist(rt,val);}
		void clear(){
			if(rt!=Null) delete[](rt);
			rt=Null;
		}
		int size(){return rt->sz;}
		int lt_cnt(int val){ //小于val的值的个数
			node *u=rt; int ret=0;
			while(u!=Null){
				if(u->val <= val){
					ret+= u->ls->sz + u->cnt;
					u=u->rs;
				}
				else u=u->ls;
			}
			return ret;
		}
#undef ls
#undef rs
};
Treap::node Treap::mem_pool[MAXN*100];
Treap::node *Treap::Null=&mem_pool[0];
Treap::node *Treap::mem_cur=Treap::mem_pool+(MAXN*100)-1;
stack<Treap::node*> Treap::mem_bin;
class SG_dync_DCT{
	//pre T ↓
	private:
		int he[MAXN];
		int anc[17][MAXN],dis[MAXN],de[MAXN];
		struct line{int to,nex,w;}ed[MAXN<<1];
		void addE(int u,int v,int w){
			static int cnt;
			ed[++cnt]=(line){v,he[u],w};
			he[u]=cnt;
		}
		void prepare_LCA(int u,int fa){ //计算新加入的点的倍增数组
			anc[0][u]=fa;
			for(int i=1;i<17;++i)
				anc[i][u]=anc[i-1][anc[i-1][u]];
		}
		int LCA(int u,int v){
			if(de[u]<de[v]) swap(u,v);
			for(int d=de[u]-de[v],i=0;d;d>>=1,++i){
				if(d&1) u=anc[i][u];
			}
			if(u==v) return v;
			for(int i=16;i>=0;--i){
				if(anc[i][u]!=anc[i][v])
					u=anc[i][u],v=anc[i][v];
			}
			return anc[0][u];
		}
		int cal_dis(int u,int v){
			return dis[u]+dis[v]-(dis[LCA(u,v)]<<1);
		}
	public:
		int ist(int u,int fa,int w){ //新加入u点
			addE(u,fa,w),addE(fa,u,w);
			de[u]=de[fa]+1,dis[u]=dis[fa]+w;
			prepare_LCA(u,fa);
			return upd(u,fa);
		}
	//DCT ↓
	private:
		static const double ALPHA;
		int idx; //访问标号
		int use[MAXN],vis[MAXN]; //用不用该点，该点这次重构是否访问过
		int sz[MAXN];
		int fa[MAXN]; //上层重心
		set<int> dct[MAXN]; //重心树
		Treap plus[MAXN],minus[MAXN]; //和之前的动态点分治套路一样
		void DFS_del(int u){ //删除重心树的u的子树的treap和边
			//因为只有这里是正常下去遍历整棵子树的，
			//所以只能在这里标记等会可以到的点
			//后面标记会gg，在treeDC里遍历是跳跃的，
			//且这里只重建了一部分，没有重建的部分没有访问标记，
			//遍历着会绕上去到不该重建的地方
			use[u]=idx;
			plus[u].clear();
			for(set<int>::iterator iter=dct[u].begin();iter!=dct[u].end();++iter){
				minus[*iter].clear();
				DFS_del(*iter);
			}
			dct[u].clear();
		}
		int DFS_sz(int u,int fa){
			sz[u]=1;
			for(int i=he[u],v;i;i=ed[i].nex){
				v=ed[i].to;
				if(vis[v]!=idx && use[v]==idx && v!=fa)
					sz[u]+=DFS_sz(v,u);
			}
			return sz[u];
		}
		int get_grt(int u,int fa,int lim){
			for(int i=he[u],v;i;i=ed[i].nex){
				v=ed[i].to;
				if(vis[v]!=idx && use[v]==idx && v!=fa){
					if(sz[v]>lim) return get_grt(v,u,lim);
				}
			}
			return u;
		}
		void DFS_ist(int u,int fa,int dis,Treap::node *&tp_rt){ //和3730那些一个套路
			Treap::ist(tp_rt,dis-r[u]);
			for(int i=he[u],v;i;i=ed[i].nex){
				v=ed[i].to;
				if(vis[v]!=idx && use[v]==idx && v!=fa)
					DFS_ist(v,u,dis+ed[i].w,tp_rt);
			}
		}
		int treeDC(int u){ //这里由于有加点操作，treeDC()和之前略有不同
			u=get_grt(u,0,DFS_sz(u,0)>>1);
			vis[u]=idx;
			DFS_ist(u,0,0,plus[u].rt);
			Treap::node *minus_rt;
			for(int i=he[u],v;i;i=ed[i].nex){
				v=ed[i].to;
				if(vis[v]!=idx && use[v]==idx){
					minus_rt=Treap::Null;
					DFS_ist(v,u,ed[i].w,minus_rt);
					v=treeDC(v);
					this->fa[v]=u;
					dct[u].insert(v);
					minus[v].rt=minus_rt;
				}
			}
			return u;
		}
		void rebuild(int u){
			++idx;
			int fa=this->fa[u];
			if(fa) dct[fa].erase(u);
			DFS_del(u);
			//这个treap是针对fa而算的，所以可以保留
			//treeDC里的做法同理
			Treap::node *minus_rt=minus[u].rt;
			minus[u].rt=Treap::Null;
			u=treeDC(u);
			this->fa[u]=fa;
			if(fa) dct[fa].insert(u);
			minus[u].rt=minus_rt;
		}
		bool bal(int u){
			return plus[u].size()<ALPHA*plus[fa[u]].size()+0.5;
		}
		void maintain(int u){
			int cur=0;
			for(;fa[u];u=fa[u]){
				if(!bal(u)) cur=fa[u];
			}
			if(cur) rebuild(cur);
		}
		int upd(int u,int fa){ //更新：计算u所带来的影响
			this->fa[u]=fa;
			dct[fa].insert(u);
			int ret=0;
			for(int now=u,r=::r[u],fa,dis;now;now=fa){
				fa=this->fa[now];
				if(fa){
					dis=cal_dis(u,fa);
					ret+=plus[fa].lt_cnt(r-dis);
					ret-=minus[now].lt_cnt(r-dis);
					minus[now].ist(dis-r);
				}
				plus[now].ist(cal_dis(u,now)-r);
			}
			maintain(u);
			return ret;
		}
}DCT;
const double SG_dync_DCT::ALPHA=0.88;

int main(){
	srand(125);
	int n;
	scanf("%*d%d",&n);
	long long lastans=0;
	for(int i=1,fa,w;i<=n;++i){
		scanf("%d%d%d",&fa,&w,&r[i]);
		fa^=lastans%MOD;
		lastans+=DCT.ist(i,fa,w);
		printf("%lld\n",lastans);
	}
	return 0;
}
