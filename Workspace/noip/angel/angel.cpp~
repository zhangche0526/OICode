#include<iostream>
#include<cstdio>

const int MAXN=1e6+5;

int n,m;

char sT[MAXN],sP[MAXN];
int T[MAXN],P[MAXN],pos[MAXN];
int ans[MAXN];

inline void kmp1()
{
	static int next[MAXN];
    int i,j;
    for(i=1,j;i<n;i++)
    {
        j=next[i];
        while(j&&sP[i]!=sP[j]) j=next[j];
        next[i+1]=(sP[i]==sP[j]?j+1:0);
    }
    for(i=j=0;i<m;i++)
    {
        while(j&&sT[i]!=sP[j]) j=next[j];
        if(sT[i]==sP[j]) j++;
        if(j==n) ans[i-n+1]++;
    }
}

inline void kmp2()
{
	static int p1[MAXN],p2[MAXN],pre[MAXN],nxt[MAXN],next[MAXN];
	int i,j;
    for(i=0;i<n;i++) pre[i]=i-1,nxt[i]=(i==n-1)?-1:i+1;
    for(i=n-1;i>=0;i--)
    {
        p1[i]=(pre[P[i]]==-1)?-1:(i-pos[pre[P[i]]]);
        p2[i]=(nxt[P[i]]==-1)?-1:(i-pos[nxt[P[i]]]);
        if(nxt[P[i]]!=-1)   pre[nxt[P[i]]]=pre[P[i]];
        if(pre[P[i]]!=-1)   nxt[pre[P[i]]]=nxt[P[i]];
    }
    i=0,j=-1,next[0]=-1;
    while(i<n)
    {
        if(j==-1||((p1[j]==-1||P[i-p1[j]]<P[i])&&(p2[j]==-1||P[i-p2[j]]>P[i])))   next[++i]=++j;
        else    j=next[j];
    }
    i=j=0;
    while(i<m)
    {
        if(j==-1||((p1[j]==-1||T[i-p1[j]]<T[i])&&(p2[j]==-1||T[i-p2[j]]>T[i])))   i++,j++;
        else    j=next[j];
        if(j==n)
        {
            ans[i-n]++,j=next[j];
        }
    }
}

int main()
{
    int i;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		char s[10];scanf("%s",s);
		sP[i]=s[0];
		int x;scanf("%d",&x);
		P[i]=x-1;pos[P[i]]=i;
	}
	scanf("%d",&m);
	for(i=0;i<m;i++)
	{
		char s[10];scanf("%s",s);
		sT[i]=s[0];
		scanf("%d",T+i);
	}
	kmp1();
	kmp2();
	for(i=0;i<m;i++) if(ans[i]==2)
		printf("%d\n",i+1);
    return 0;
}
