#include<iostream>
#include<cstdio>

const int MAXN=233334,P=1e9+7;

int n;
int pos[MAXN],f[MAXN];

int main()
{
	int i,j,x;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&x),pos[x]=i;
	for(i=1;i<MAXN;i++) if(pos[i])
		for(j=i&(i-1);j;j=i&(j-1))
			if(pos[j]>pos[i])
				f[i]=(f[i]+f[j]+1)%P;
	int ans=0;
	for(i=1;i<MAXN;i++) ans=(ans+f[i])%P;
	printf("%d",ans);
}
