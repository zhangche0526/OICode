#include<iostream>
#include<cstdio>
#include<algorithm>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}

const int MAXN=1e5+5;

int n;
struct L{int l,r;} ln[MAXN];int lcnt;
bool cmp(const L &a,const L &b)
{return a.r<b.r||(a.r==b.r&&a.l<b.l);}

int main()
{
	int i;scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		int a,b;scanf("%d%d",&a,&b);
		if(a+b<n) ln[++lcnt]=(L){a+1,n-b};
	}
	std::sort(ln+1,ln+lcnt+1,cmp);
	static int f[MAXN];
	int j=1;
	for(i=1;i<=n;i++)
	{
		f[i]=f[i-1];while(ln[j].r<i&&j<=lcnt) j++;
		for(int res=0;ln[j].r==i&&j<=lcnt;j++)
		{
			if(ln[j].l==ln[j-1].l) res++;
			else res=1;
			umx(f[i],f[ln[j].l-1]+min(res,i-ln[j].l+1));
		}
	}
	printf("%d",n-f[n]);
	return 0;
}
