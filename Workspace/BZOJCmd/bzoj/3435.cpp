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
			void operator delete[](void *u){ //ɾ������
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
		int lt_cnt(int val){ //С��val��ֵ�ĸ���
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
	//pre T ��
	private:
		int he[MAXN];
		int anc[17][MAXN],dis[MAXN],de[MAXN];
		struct line{int to,nex,w;}ed[MAXN<<1];
		void addE(int u,int v,int w){
			static int cnt;
			ed[++cnt]=(line){v,he[u],w};
			he[u]=cnt;
		}
		void prepare_LCA(int u,int fa){ //�����¼���ĵ�ı�������
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
		int ist(int u,int fa,int w){ //�¼���u��
			addE(u,fa,w),addE(fa,u,w);
			de[u]=de[fa]+1,dis[u]=dis[fa]+w;
			prepare_LCA(u,fa);
			return upd(u,fa);
		}
	//DCT ��
	private:
		static const double ALPHA;
		int idx; //���ʱ��
		int use[MAXN],vis[MAXN]; //�ò��øõ㣬�õ�����ع��Ƿ���ʹ�
		int sz[MAXN];
		int fa[MAXN]; //�ϲ�����
		set<int> dct[MAXN]; //������
		Treap plus[MAXN],minus[MAXN]; //��֮ǰ�Ķ�̬�������·һ��
		void DFS_del(int u){ //ɾ����������u��������treap�ͱ�
			//��Ϊֻ��������������ȥ�������������ģ�
			//����ֻ���������ǵȻ���Ե��ĵ�
			//�����ǻ�gg����treeDC���������Ծ�ģ�
			//������ֻ�ؽ���һ���֣�û���ؽ��Ĳ���û�з��ʱ�ǣ�
			//�����Ż�����ȥ�������ؽ��ĵط�
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
		void DFS_ist(int u,int fa,int dis,Treap::node *&tp_rt){ //��3730��Щһ����·
			Treap::ist(tp_rt,dis-r[u]);
			for(int i=he[u],v;i;i=ed[i].nex){
				v=ed[i].to;
				if(vis[v]!=idx && use[v]==idx && v!=fa)
					DFS_ist(v,u,dis+ed[i].w,tp_rt);
			}
		}
		int treeDC(int u){ //���������мӵ������treeDC()��֮ǰ���в�ͬ
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
			//���treap�����fa����ģ����Կ��Ա���
			//treeDC�������ͬ��
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
		int upd(int u,int fa){ //���£�����u��������Ӱ��
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
