#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;

ll L,R;int N;
int num[20],len;
ll val[32][20][14][12];
inline void preTab()
{
	for(int a2=0;a2<=31;a2++)
		for(int a3=0;a3<=19;a3++)
			for(int a5=0;a5<=13;a5++)
				for(int a7=0;a7<=11;a7++)
				{
					ll &o=val[a2][a3][a5][a7];
					if(a2) o=val[a2-1][a3][a5][a7]*2;
					else if(a3) o=val[a2][a3-1][a5][a7]*3;
					else if(a5) o=val[a2][a3][a5-1][a7]*5;
					else if(a7) o=val[a2][a3][a5][a7-1]*7;
					else o=1;
				}
}

ll f[20][32][20][14][12][2];
ll F(int lv,int a2,int a3,int a5,int a7,bool all0,bool lim)
{
	ll prd=val[a2][a3][a5][a7];
	if(prd>N) return 0;
	if(!lv) return 1;
	ll &o=f[lv][a2][a3][a5][a7][all0];
	if(!lim&&~o) return o;
	int n=lim?num[lv]:9;
	ll res=0;
	for(int i=0;i<=n;i++)
	{
		if(!all0&&!i) continue;
		res+=F(lv-1,a2+(i==2||i==6||i==4||i==8)+(i==4||i==8)+(i==8),a3+(i==3||i==6||i==9)+(i==9),a5+(i==5),a7+(i==7),all0&&!i,lim&&i==n);
	}
	if(!lim) o=res;
	return res;
}

ll calc(ll x)
{
	for(len=0;x;x/=10) num[++len]=x%10;
	memset(f,-1,sizeof f);
	return F(len,0,0,0,0,1,1);
}

int main()
{
	preTab();
	scanf("%d%lld%lld",&N,&L,&R);
	printf("%lld",calc(R-1)-calc(L-1));
	return 0;
}
/*
10000
1 2
*/
