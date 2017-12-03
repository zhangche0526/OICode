/**************************************************************
    Problem: 1026
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:1288 kb
****************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;

ll f[15][10];

int abs(int x){return x>0?x:-x;}

inline void initDp()
{
	int i,j,k;
	for(i=0;i<=9;i++) f[1][i]=1;
	for(i=2;i<=12;i++)
		for(j=0;j<=9;j++)
			for(k=0;k<=9;k++)
				if(abs(j-k)>=2)
					f[i][j]+=f[i-1][k];
}

int num[15];
ll calc(ll x)
{
	if(!x) return 0;
	memset(num,0,sizeof(0));
	int i,j,len=0;
	ll res=0;
	while(x) num[++len]=x%10,x/=10;
	for(i=1;i<len;i++)
		for(j=1;j<=9;j++) 
			res+=f[i][j];
	for(i=1;i<num[len];i++)
		res+=f[len][i];
	for(i=len-1;i;i--)
	{
		for(j=0;j<num[i];j++)
			if(abs(num[i+1]-j)>=2) 
				res+=f[i][j];
		if(abs(num[i+1]-num[i])<2) break;
	}
	return res;
}

int main()
{
	ll a,b;
	scanf("%lld%lld",&a,&b);
	initDp();
	printf("%lld",calc(b+1)-calc(a));
}
