#include<iostream>
#include<cstdio>
#include<algorithm>
const int MAXN=5e4+5,P=10007;

inline int add(int a,int b){return (a+b)%P;}
inline void uadd(int &a,int b){a=add(a,b);}
inline int mns(int a,int b){return (a-b+P)%P;}
inline void umns(int &a,int b){a=mns(a,b);}

int n,m;
int L[MAXN],Lsum[MAXN];
int len;

inline bool check(int len)
{
	int res=0,la=0;
	for(int i=1;i<=n;i++)
		if(Lsum[i]-Lsum[la]>len) la=i-1,res++;
	return res<=m;
}

inline int calLen()
{
	int l=*std::max_element(L+1,L+n+1),r=Lsum[n];
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	return l;
}

int f[MAXN][2],ans;
inline void dp()
{
	int i,j;
	for(i=1;i<=n;i++) f[i][0]=Lsum[i]<=len;
	ans=f[n][0];
	for(j=1;j<=m;j++)
	{
		int fsum=0,pos=1;
		for(i=1;i<=n;i++)
		{
			while(pos<i&&Lsum[i]-Lsum[pos]>len)
				umns(fsum,f[pos++][j&1^1]);
			f[i][j&1]=fsum;
			uadd(fsum,f[i][j&1^1]);
		}
		uadd(ans,f[n][j&1]);
	}
}

int main()
{
	int i;scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",L+i),Lsum[i]=Lsum[i-1]+L[i];
	len=calLen();
	dp();
	printf("%d %d",len,ans);
	return 0;
}
/*
3 2                           
1 
1
10
*/
