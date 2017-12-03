#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
const ll BASE=1e8;

struct BN
{
	ll num[2000],len;
	BN(int x=0)
	{
		memset(num,0,sizeof(num));
		if(!x) len=0;
		else
		{
			len=-1;
			while(x) num[++len]=x%BASE,x/=BASE;
		}
	}
	void out(){printf("%d",num[len]);for(int i=len-1;i>=0;i--) printf("%08d",num[i]);}
};
BN operator +(BN a,BN b)
{
	BN res;res.len=std::max(a.len,b.len);
	for(int i=0;i<=std::max(a.len,b.len);i++)
	{
		res.num[i]+=a.num[i]+b.num[i];
		if(res.num[i]>=BASE)
			res.num[i]-=BASE,res.num[i+1]++;
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
			res.num[i]+=BASE,res.num[i+1]--;
	}
	while(!res.num[res.len]) res.len--;
	return res;
}

BN t[2000];
BN operator *(BN a,BN b)
{
	int i,j;
	for(i=0;i<=a.len;i++) t[i]=BN();
	for(i=0;i<=a.len;i++)
	{
		for(j=0;j<=b.len;j++)
			t[i].num[i+j]=a.num[i]*b.num[j];
		for(j=0;j<=b.len;j++)
			t[i].num[i+j+1]+=t[i].num[i+j]/BASE,t[i].num[i+j]%=BASE;
		t[i].len=i+b.len;
		if(t[i].num[t[i].len+1]) t[i].len++;
	}
	BN res;
	for(i=0;i<=a.len;i++) res=res+t[i];
	return res;
}
