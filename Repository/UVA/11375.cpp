#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int MAXN=2e3,c[10]={6,2,5,5,4,5,6,3,7,6};

struct BN
{
	int num[1000],len;
	BN(int x=0)
	{
		len=-1;memset(num,0,sizeof(num));
		while(x) num[++len]=x%10,x/=10;
		std::reverse(num,num+len);
	}
	void out()
	{
		for(int i=len;i>=0;i--) putchar('0'+num[i]);
		if(len==-1) putchar('0');
	}
};
BN operator +(BN a,BN b)
{
	BN res;res.len=std::max(a.len,b.len);
	for(int i=0;i<=res.len;i++)
	{
		res.num[i]+=a.num[i]+b.num[i];
		res.num[i+1]=res.num[i]/10,res.num[i]%=10;
	}
	if(res.num[res.len+1]) res.len++;
	return res;
}

BN f[MAXN+5],g[MAXN+5];

inline void preTab()
{
	int i,j;
	g[0]=BN(1);
	for(i=0;i<=MAXN;i++)
		for(j=0;j<10;j++)
			if((i||j)&&i+c[j]<=MAXN)
				g[i+c[j]]=g[i+c[j]]+g[i];
	for(i=1;i<=MAXN;i++) f[i]=f[i-1]+g[i];
	for(i=6;i<=MAXN;i++) f[i]=f[i]+BN(1);
}

int main()
{
	preTab();
	int N;
	while(~scanf("%d",&N)) f[N].out(),putchar('\n');
	return 0;
}
