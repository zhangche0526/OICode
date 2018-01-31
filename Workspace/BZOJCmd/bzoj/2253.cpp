#include <cstdio>
#include <algorithm>
#include <cstring>

using std::sort;
using std::max;
using std::unique;
using std::lower_bound;

const int MAXN=50005;
int n,a,p,bit_n;
int ans[MAXN];

struct option{
	int a,b,c;
	int *ans;
	static bool cmp_a(const option &a,const option &b){
		return a.a<b.a;
	}
	static bool cmp_b(const option &a,const option &b){
		return a.b<b.b;
	}
}opt[MAXN];

#define i j

class BIT{
	private:
		int c[MAXN];
		int lowbit(register int x){return x&-x;}
	public:
		void clear(int l){
			for(;l<=bit_n;l+=lowbit(l))
				c[l]=0;
		}
		void add(int l,int x){
			for(;l<=bit_n;l+=lowbit(l))
				c[l]=max(c[l],x);
		}
		int qry(int r){
			int ret=0;
			for(;r;r-=lowbit(r))
				ret=max(ret,c[r]);
			return ret;
		}
};

inline void gen_data(){
	int a=1;
	for(int i=1;i<=n;++i){
		ans[i]=1;
		opt[i].ans=&ans[i];
		a=(long long)a*::a%p;
		opt[i].a=a;
		a=(long long)a*::a%p;
		opt[i].b=a;
		a=(long long)a*::a%p;
		opt[i].c=a;
	}
}

inline void decrete_c(){
	static int tmp[MAXN];
	for(int i=1;i<=n;++i)
		tmp[i]=opt[i].c;
	sort(tmp+1,tmp+n+1);
	bit_n=tmp[0]=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;++i)
		opt[i].c=lower_bound(tmp+1,tmp+tmp[0]+1,opt[i].c)-tmp;
}

inline int separate(int l,int r){
	int mid=l+r>>1,ret;
	ret=mid;
	while(ret<r && opt[ret].a==opt[ret+1].a)
		++ret;
	if(ret<r) return ret;
	ret=mid;
	while(ret>l && opt[ret].a==opt[ret-1].a)
		--ret;
	if(ret>l) return ret;
	return 0;
}

void CDQ_DC(int l,int r){
	static BIT ta;
	if(l==r) return;
	int mid=separate(l,r);
	if(!mid) return;
	CDQ_DC(l,mid);
	sort(opt+l,opt+mid+1,option::cmp_b);
	sort(opt+mid+1,opt+r+1,option::cmp_b);
	for(int cur=l,lp=l,rp=mid+1;cur<=r;++cur){
		if(rp>r || (lp<=mid && opt[lp].b<=opt[rp].b)){
			ta.add(opt[lp].c,*opt[lp].ans);
			++lp;
		}
		else{
			*opt[rp].ans=max(*opt[rp].ans,ta.qry(opt[rp].c-1)+1);
			++rp;
		}
	}
	for(int i=l;i<=mid;++i)
		ta.clear(opt[i].c);
	sort(opt+mid+1,opt+r+1,option::cmp_a);
	CDQ_DC(mid+1,r);
}

int main(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	scanf("%d%d%d",&a,&p,&n);
	gen_data();
	decrete_c();
	sort(opt+1,opt+n+1,option::cmp_a);
	CDQ_DC(1,n);
	for(int i=1;i<=n;++i)
		ans[0]=max(ans[0],ans[i]);
	printf("%d\n",ans[0]);
	return 0;
}
