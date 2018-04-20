#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using std::cin;
using std::cout;
typedef long long ll;

int num[12],len;

ll f[12][10][4][2][2];
ll dfs(int lv,int la,int cnt,bool b4,bool b8,bool lim)
{
	if(b4&&b8) return 0;
	if(!lv) return cnt==3;
	ll &f=::f[lv][la][cnt][b4][b8];
	if(!lim&&~f) return f;
	ll res=0;
	int n=lim?num[lv]:9;
	for(int i=lv==n;i<=n;i++)
	{
		int nxtcnt= cnt==3?3:(i==la?cnt+1:1);
		res+=dfs(lv-1,i,nxtcnt,b4||i==4,b8||i==8,lim&&i==n);
	}
	if(!lim) f=res;
	return res;
}

inline ll calc(ll x)
{
	for(len=0;x;x/=10) num[++len]=x%10;
	return dfs(len,0,1,0,0,1);
}

int main()
{
	memset(f,-1,sizeof f);
	ll l,r;cin>>l>>r;
	cout<<(l==10000000000?calc(r):calc(r)-calc(l-1));
	return 0;
}
