#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define inf 0x7fffffff
#define ll long long
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,cnt,ans;
int head[1000005];
bool mark[1000005];
struct data{int to,next;}e[2000005];
inline void insert(int u,int v)
{
	e[++cnt].to=v;e[cnt].next=head[u];head[u]=cnt;
}
void getans(int x,int fa)
{
	bool flag=0;
	for(int i=head[x];i;i=e[i].next)
	{
	    if(e[i].to==fa)continue;
	    getans(e[i].to,x);
	    if(mark[e[i].to])flag=1;
	}
    if(!flag&&!mark[x]&&!mark[fa]){ans++;mark[fa]=1;}
}
int main()
{
    n=read();
    for(int i=1;i<n;i++)
    {
    	int u=read(),v=read();
    	insert(u,v);
    	insert(v,u);
    }
    getans(1,0);
    printf("%d",ans);
	return 0;
}
