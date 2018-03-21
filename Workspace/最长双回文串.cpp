#include<iostream>
#include<cstdio>
#include<cstring> 
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
using std::min;
const int MAXN=2e5+5;

int n;
char s[MAXN];
int L[MAXN],R[MAXN];
void manacher()
{
	int i;static int r[MAXN];
	for(i=n-1;~i;i--) s[i+1<<1]=s[i];
	for(i=0;i<=n;i++) s[i<<1|1]='#';
	n=n+1<<1;
	s[0]='(',s[n]=')';
	int mxv=0,mxp;
	for(i=0;i<n;i++)
	{
		r[i]=i<mxv?min(r[mxp*2-i],mxv-i):1;
		while(s[i-r[i]]==s[i+r[i]]) r[i]++;
		if(r[i]+i>mxv) mxv=r[i]+i,mxp=i;
		umx(L[i+(r[i]-1)],r[i]-1);
		umx(R[i-(r[i]-1)],r[i]-1);
	}
}

int main()
{
	int i;scanf("%s",s);n=strlen(s); 
	manacher();
	for(i=n-1;i>=1;i-=2) umx(L[i],L[i+2]-2);
	for(i=1;i<n;i+=2) umx(R[i],R[i-2]-2);
	int ans=0;
	for(i=1;i<n;i+=2) if(L[i]&&R[i]) umx(ans,L[i]+R[i]);
	printf("%d",ans);
	return 0;
}
