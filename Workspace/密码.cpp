#include<iostream>
#include<cstdio>
using std::min;
const int MAXN=1e5+5;

int n;
char s[MAXN<<1];

bool vis[MAXN<<1][26];
int d[MAXN<<1],r[MAXN<<1];
inline void antiManacher()
{
	int i,j,mxv=0,mxp;
	for(i=1;i<n<<1;i++)
	{
		if(mxv<i)
		{
			for(j=0;j<26;j++)
				if(!vis[i][j])
					break;
			s[i]='a'+j;
		}
		for(j=(mxv>=i?min(mxv-i+1,d[2*mxp-i]):1);j<=d[i];j++)
			s[i+j]=s[i-j];
		if(i>d[i]) vis[i+d[i]+1][s[i-d[i]-1]-'a']=true;
		if(i+d[i]>mxv) mxv=i+d[i],mxp=i;
	}
	for(i=0;i<n;i++) s[i]=s[i<<1|1];
}

int main()
{
	int i;scanf("%d",&n);s[0]='#';
	for(i=0;i<n;i++) scanf("%d",&d[i<<1|1]);
	for(i=1;i<n;i++) scanf("%d",&d[i<<1]);
	antiManacher();
	for(i=0;i<n;i++) putchar(s[i]);
	return 0;
}
