#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXN=55,MAXT=1e4+5;

int N,T;

int f[MAXT],t[MAXN];

int main()
{
	int Case,Cases;scanf("%d",&Cases);
	for(Case=1;Case<=Cases;Case++)
	{
		int i,j,ans1=0,ans2;
		memset(f,0,sizeof(f));
		scanf("%d%d",&N,&T);T--;
		for(i=1;i<=N;i++) scanf("%d",t+i);
		for(i=1;i<=N;i++)
			for(j=T;j>=t[i];j--)
				if(j==t[i]||f[j-t[i]])
					ans1=std::max(ans1,f[j]=std::max(f[j],f[j-t[i]]+1));
		for(ans2=T;f[ans2]!=ans1;ans2--);
		if(ans1) printf("Case %d: %d %d\n",Case,ans1+1,ans2+678);
		else printf("Case %d: %d %d\n",Case,1,678);
	}
	return 0;
}
