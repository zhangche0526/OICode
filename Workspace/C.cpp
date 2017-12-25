#include<iostream>
#include<cstdio>
#include<cstring>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
const int MAXN=3e5+5;

int n;
int f[1<<21],s[MAXN];

int main()
{
	int i,k;scanf("%d",&n);
	memset(f,0x3f,sizeof f);f[0]=0;
	for(i=1;i<=n;i++) scanf("%d",s+i);
	for(i=1;i<=n;i++) s[i]^=s[i-1];
	for(i=1;i<=n;i++) umn(f[s[i]],i);
	for(k=0;k<=20;k++)
		for(i=1;i<1<<21;i++) if(!((i>>k)&1))
			umn(f[i],f[i|(1<<k)]);
	for(i=1;i<=n;i++)
	{
		int si=s[i],sj=0;
		for(k=20;~k;k--)
			if( !( (si>>k)&1 ) && f[sj|(1<<k)]<=i) sj|=1<<k;
		printf("%d\n",sj+(sj^si));
	}
	return 0;
}
