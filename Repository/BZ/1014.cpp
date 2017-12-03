#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 2e5+1;
const int inf = 0x7fffffff;
const int mod = 9875321;
typedef long long ll;
int size[N],son[N][2],fa[N],p[mod*3],w[N],id[N],h[N];
bool tag[N],rev[N];
char a[N];
int tot,root,sz;
void update(int x)
{
	int l=son[x][0];int r=son[x][1];
	size[x]=size[l]+size[r]+1;
	h[x]=h[l]+(ll)w[x]*p[size[l]%mod]%mod+(ll)p[size[l]%mod+1]*h[r]%mod;
	h[x]%=mod;
	return;
}

void rotate(int x)
{
	int y=fa[x],z=fa[y],t=son[y][0]==x;
	fa[y]=x;fa[x]=z;
	if(z) son[z][son[z][1]==y]=x;
	son[y][!t]=son[x][t];fa[son[x][t]]=y;
	son[x][t]=y;
	update(x);update(y);
	return;
}
void splay(int x,int s)
{
	while(fa[x]!=s)
	{
		int y=fa[x],z=fa[y];
		if(z!=s)
		{
			if(son[y][0]==x^son[z][0]==y)	rotate(x);
			else							rotate(y);
		}
		rotate(x);
	}
	if(!s)root=x;
	return;
}

int find(int x)
{
    int y=root;
    while(x<=size[son[y][0]]||x>size[son[y][0]]+1)
    {
        if(x<=size[son[y][0]]) y=son[y][0];
        else x-=size[son[y][0]]+1,y=son[y][1];
    }
    return y;
}
int query(int k,int val)
{
	int x=find(k),y=find(k+val+1);
	splay(x,0);splay(y,x);
	return h[son[y][0]];
}
int solve(int x,int y)
{
	int l=1,r=min(sz-x,sz-y)-1,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(query(x,mid)==query(y,mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	return ans;
}
void insert(int k,int val)
{
	int x=find(k+1),y=find(k+2);
	splay(x,0);splay(y,x);
	int z=++sz;son[y][0]=z;fa[z]=y;w[z]=val;
	update(z);update(y);update(x);
}
void build(int l,int r,int s)
{
	if(l>r)return;
	int mid=l+r>>1,now=id[mid],last=id[s];
	if(l==r)
	{
		size[now]=1;
		fa[now]=last;
		son[last][s<=mid]=now;
		w[now]=h[now]=a[mid]-'a'+1;
		return;
	}
	build(l,mid-1,mid);build(mid+1,r,mid);
	w[now]=h[now]=a[mid]-'a'+1;fa[now]=last;update(now);
	son[last][mid>=s]=now;
	return;
}
char op[11],d[3];
int l,r,m;
int main()
{
	scanf("%s",a+2);
	int n=strlen(a+2);p[0]=1;
	for(int i=1;i<=N-1;++i)p[i]=p[i-1]*27%mod;
	for(int i=1;i<=n+2;++i)id[i]=i;
	build(1,n+2,0);tot=n+2;sz=n+2;root=(n+3)>>1;
	scanf("%d",&m);
	while(m--)
	{
		scanf("%s",op);
		if(op[0]=='Q')
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",solve(l,r));
		}
		if(op[0]=='R')
		{
			scanf("%d%s",&l,&d);
			int x=find(l+1);splay(x,0);
			w[root]=d[0]-'a'+1;update(root);
		}
		if(op[0]=='I')
		{
			scanf("%d%s",&l,&d);
			insert(l,d[0]-'a'+1);
		}
	}
}
