#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int MAXN=55;

struct BN
{
	int num[1005],len;
	BN(int x=0)
	{
		len=-1;memset(num,0,sizeof(num));
		while(x) num[++len]=x%10,x/=10;
		std::reverse(num,num+len);
	}
};
BN operator +(BN a,BN b)
{
	BN res;res.len=std::max(a.len,b.len);
	for(int i=0;i<=std::max(a.len,b.len);i++)
	{
		res.num[i]+=a.num[i]+b.num[i];
		if(res.num[i]>=10)
			res.num[i]-=10,res.num[i+1]++;
	}
	if(res.num[res.len+1]) res.len++;
	return res;
}
BN operator -(BN a,BN b)
{
	BN res;res.len=std::max(a.len,b.len);
	for(int i=0;i<=std::max(a.len,b.len);i++)
	{
		res.num[i]+=a.num[i]-b.num[i];
		if(res.num[i]<0)
			res.num[i]+=10,res.num[i+1]--;
	}
	while(!res.num[res.len]) res.len--;
	return res;
}

BN t[1005];
BN operator *(BN a,BN b)
{
	int i,j;
	for(i=0;i<=a.len;i++) t[i]=BN();
	for(i=0;i<=a.len;i++)
	{
		for(j=0;j<=b.len;j++)
			t[i].num[i+j]=a.num[i]*b.num[j];
		for(j=0;j<=b.len;j++)
			t[i].num[i+j+1]+=t[i].num[i+j]/10,t[i].num[i+j]%=10;
		t[i].len=i+b.len;
		if(t[i].num[t[i].len+1]) t[i].len++;
	}
	BN res;
	for(i=0;i<=a.len;i++) res=res+t[i];
	return res;
}

BN qpow(BN x,int n)
{
	int i;
	BN res=BN(1);
	for(i=1;i<=n;i<<=1,x=x*x)
		if(i&n) res=res*x;
	return res;
}

BN f[MAXN],C[MAXN][MAXN],h[MAXN];

inline void initTab()
{
	int i,j;
	for(i=0;i<MAXN;i++) 
		h[i]=qpow(BN(2),i*(i-1)/2);
	C[0][0]=BN(1);
	for(i=1;i<MAXN;i++)
	{
		C[i][0]=C[i][i]=BN(1);
		for(j=1;j<i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(i=1;i<MAXN;i++)
	{
		f[i]=h[i];
		for(j=1;j<i;j++)
			f[i]=f[i]-(C[i-1][j-1]*f[j]*h[i-j]);
	}
}

void print(BN x)
{
	for(int i=x.len;i>=0;i--)
		putchar(x.num[i]+'0');
}

int main()
{
	int i,n;
	initTab();
	while(scanf("%d",&n)!=EOF&&n)
	{
		print(f[n]);
		putchar('\n');
	}
}
