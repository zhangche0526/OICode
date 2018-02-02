#include<iostream>
#include<cstdio>

const int MAXN=1e5+5;

int n;

char s[MAXN];
int nxt[MAXN],vis[MAXN];

int main()
{
	int i,j,x;scanf("%d",&n);
	nxt[0]=-1;
	for(i=1;i<=n;i++) {scanf("%d",&x);nxt[i]=i-x;}
	for(i=1;i<=n;i++)
	{
		if(nxt[i]) s[i]=s[nxt[i]];
		else
		{
			for(j=nxt[i-1];~j;j=nxt[j]) vis[s[j+1]-'a']=i;
			for(j=0;j<26;j++) if(vis[j]!=i) {s[i]=j+'a';break;}
		}
	}
	printf("%s",s+1);
	return 0;
}
