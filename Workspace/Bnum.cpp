#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;

const int TEN[]={1,10,9,12,3,4,1,10,9,12,3,4,1,10,9,12,3,4};

int num[16],len;

ll f[16][10][13][2];
ll F(int lv,int la,int r,bool b,bool lim)
{
	if(!lv) return !r&&b;
	ll &o=f[lv][la][r][b];
	if(!lim&&~o) return o;
	int n=lim?num[lv]:9;
	ll res=0;
	for(int i=0;i<=n;i++)
		res+=F(lv-1,i,(r+i*TEN[lv-1])%13,b||(la==1&&i==3),lim&&i==n);
	if(!lim) return o=res;
	return res;
}

int main()
{
	ll x;scanf("%lld",&x);
	for(;x;x/=10) num[++len]=x%10;
	memset(f,-1,sizeof f);
	printf("%lld",F(len,0,0,0,1));
	return 0;
}
