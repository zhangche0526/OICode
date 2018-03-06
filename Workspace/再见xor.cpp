#include<iostream>
#include<cstdio>

const int MAXN=1e5+5,MAXL=31;

class LB
{
private:
	int a[MAXL];
	void ist(int x)
	{
		int i,j;
		for(i=MAXL-1;~i;i--)
		{
			if(!(x&(1<<i))) continue;
			if(a[i]) x^=a[i];
			else
			{
				for(j=0;j<i;j++) if(x&(1<<j)) x^=a[j];
				for(j=i+1;j<MAXL;j++) if(a[j]&(1<<i)) a[j]^=x;
				a[i]^=x;
				return;
			}
		}
	}
public:
	int calMxXor()
	{
		int i,res=0;
		for(i=0;i<MAXL;i++) res^=a[i];
		return res;
	}
	int calMnEle()
	{
		for(int i=0;i<MAXL;i++)
			if(a[i]) return a[i];
	}
	LB(int *S,int n){for(int i=1;i<=n;i++) ist(S[i]);}
};

int n;
int S[MAXN];
int main()
{
	int i;scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",S+i);
	static LB lb(S,n);
	int ans=lb.calMxXor();
	printf("%d %d",ans,ans^lb.calMnEle());
	return 0;
}
