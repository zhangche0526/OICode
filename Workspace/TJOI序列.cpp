#include<iostream>
#include<cstdio>

const int MAXN=1e5+5;

int n;

struct BS
{
    uint bs[10];
    void set(){memset(bs,0xff,sizeof bs);}
    void flip(int p){bs[p>>5]^=1U<<p;}
    bool test(int p){return bs[p>>5]&(1U<<p);}
    uint &operator [](int p){return bs[p];}
};

struct CM //Chrom
{
	BS gn;
	int fit;
} pop[1005];int popsz=1000,gnsz;
inline void initpop()
{
	int i,j;
	for(i=1;i<=popsz;i++)
	{
		for(j=1;j<=
	}
}
