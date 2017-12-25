#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(a,b,c) for (int a=b;a<=c;a++)
#define per(a,b,c) for (int a=b;a>=c;a--)
#define go(u) for (int o=ft[u],v;v=E[o].t;o=E[o].n)
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef double dob;
typedef pair<int,int> par;
const int P=998244353;
int flag,n,m,ans,f[1010][1030][3][3];
char mp[15][1010];
void work1(){
	flag=1;
}
void work2(){
	m>>=1;
	rep(i,1,n) rep(j,1,m) mp[i][j]+=mp[i][j+m]<<1;
}
#define _(x) (1<<(x-1))
void upd(int &x,int y){x=(x+y%P)%P;}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%s",mp[i]+1);
	rep(i,1,n) rep(j,1,m) mp[i][j]-='0';
	if (m&1) work1(); else work2();
	rep(i,1,n){
		if (mp[i][1]&1) f[1][_(i)][0][0]=1;
		if (mp[i][1]&2) f[1][_(i)][1][1]=1;
	}
	f[1][0][2][2]=1;
	int lim=(1<<n)-1;
	rep(i,2,m) rep(j,0,lim){
		rep(k,1,n) if ((j&_(k))==0){
			if (mp[k][i]&1){
				upd(f[i][j|_(k)][0][0],f[i-1][j][0][1]+f[i-1][j][0][2]);
				upd(f[i][j|_(k)][1][0],f[i-1][j][1][1]+f[i-1][j][1][2]);
				upd(f[i][j|_(k)][2][0],f[i-1][j][2][1]+f[i-1][j][2][2]);
			}
			if (mp[k][i]&2){
				upd(f[i][j|_(k)][0][1],f[i-1][j][0][0]+f[i-1][j][0][2]);
				upd(f[i][j|_(k)][1][1],f[i-1][j][1][0]+f[i-1][j][1][2]);
				upd(f[i][j|_(k)][2][1],f[i-1][j][2][0]+f[i-1][j][2][2]);
			}
		}
		rep(k,0,2){
			upd(f[i][j][0][2],f[i-1][j][0][k]);
			upd(f[i][j][1][2],f[i-1][j][1][k]);
			upd(f[i][j][2][2],f[i-1][j][2][k]);
		}
	}
	upd(ans,f[m][lim][0][flag]);
	upd(ans,f[m][lim][0][2]);
	upd(ans,f[m][lim][1][flag^1]);
	upd(ans,f[m][lim][1][2]);
	upd(ans,f[m][lim][2][0]);
	upd(ans,f[m][lim][2][1]);
	upd(ans,f[m][lim][2][2]);
	ans=(ans+P)%P;
	printf("%d\n",ans);
	return 0;
}
