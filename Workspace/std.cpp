#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxl=2000010;
int n,m,ans;
int rank,tot1,tot2;
int rt[2010],lp[2010],rp[2010];
char str[maxl],s1[maxl],s2[maxl];
struct trie
{
    int ch[26],org,l,r;
}t1[maxl];
struct ktrie
{
    int ch[26],siz;
}t2[maxl];
void insert(int x,int y,int z)
{
    rt[y]=++tot2,y=rt[y];
    int i,j,a;
    for(i=rp[z]-1;i>=lp[z];i--)
    {
        a=str[i]-'a',t2[y].ch[a]=++tot2;
        for(j=0;j<26;j++)    if(j!=a)    t2[y].ch[j]=t2[x].ch[j];
        y=t2[y].ch[a],x=t2[x].ch[a],t2[y].siz=t2[x].siz+1;
    }
}
int query(int x,int y)
{
    int i,a=strlen(s2),b;
    for(i=a-1;i>=0;i--)  b=s2[i]-'a',y=t2[y].ch[b],x=t2[x].ch[b];
    return t2[y].siz-t2[x].siz;
}
void dfs(int x)
{
    t1[x].l=rank+1;
    if(!x)  return ;
    if(t1[x].org)   t1[x].l=t1[x].r=++rank,insert(rt[rank-1],rank,t1[x].org);
    for(int i=0;i<26;i++)    dfs(t1[x].ch[i]);
    t1[x].r=rank;
}
int main()
{
    scanf("%d",&n);
    int i,j,a,b,u;
    tot1=1;
    for(i=1;i<=n;i++)
    {
        lp[i]=rp[i-1],scanf("%s",str+lp[i]),rp[i]=strlen(str);
        for(u=1,j=lp[i];j<rp[i];j++)
        {
            b=str[j]-'a';
            if(!t1[u].ch[b])    t1[u].ch[b]=++tot1;
            u=t1[u].ch[b];
        }
        t1[u].org=i;
    }
    t1[0].l=1<<30,t1[0].r=0,dfs(1);
    scanf("%d",&m);
    for(i=1;i<=m;i++)
    {
        scanf("%s%s",s1,s2),a=strlen(s1),b=strlen(s2),u=1;
        for(j=0;j<a;j++) s1[j]=(s1[j]-'a'+ans)%26+'a';
        for(j=0;j<b;j++) s2[j]=(s2[j]-'a'+ans)%26+'a';
        for(j=0;j<a;j++) u=t1[u].ch[s1[j]-'a'];
        if(!u)  ans=0;
        else    ans=query(rt[t1[u].l-1],rt[t1[u].r]);
        printf("%d\n",ans);
    }
    return 0;
}
