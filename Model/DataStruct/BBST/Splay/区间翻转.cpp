#include<cstdio>
#include<cstring>
using namespace std;
const int N=300005;
int va[N],ch[N][2],fa[N],cnt[N],root,tot;
bool tag[N],vis[N];
int a[N],n,m;

void swap(int &x,int &y)
{
	int t=x;x=y;y=t;
}
void pushdown(int x)
{
	if(tag[x])
		{
			swap(ch[x][0],ch[x][1]);
			tag[ch[x][0]]^=1;
			tag[ch[x][1]]^=1;
			tag[x]=0;
		}
}
void upload(int x)
{
	cnt[x]=cnt[ch[x][0]]+cnt[ch[x][1]]+1;
}
void rotate(int x,int c)
{
	int y=fa[x];
	pushdown(x),pushdown(y);
	ch[y][!c]=ch[x][c];
	if(ch[y][!c])	fa[ch[y][!c]]=y;
	upload(y);
	if(fa[y])
		{
			if(ch[fa[y]][0]==y)
				ch[fa[y]][0]=x;
			else
				ch[fa[y]][1]=x;	
		}
	fa[x]=fa[y];
	fa[y]=x;
	ch[x][c]=y;	
}
void splay(int x,int f)
{
	while(fa[x]!=f)
		{
			int y=fa[x],z=fa[fa[x]];
			if(z==f)
				{
					if(ch[y][0]==x)
						rotate(x,1);
					else
						rotate(x,0);	
				}
			else
				{
					if(ch[z][0]==y)
						{
							if(ch[y][0]==x)
								rotate(y,1),rotate(x,1);
							else
								rotate(x,0),rotate(x,1);	
						}
					else
						{
							if(ch[y][1]==x)
								rotate(y,0),rotate(x,0);
							else
								rotate(x,1),rotate(x,0);	
						}	
				}	
		}
	upload(x);	
	if(f==0)	root=x;	
}

void rotateto(int x,int to)
{
	int k=root;
	while(1)
		{
			pushdown(k);
			if(x==(cnt[ch[k][0]]+1))
				break;
			else
				{
					if(x<(cnt[ch[k][0]]+1))
						k=ch[k][0];
					else
						{
							x-=cnt[ch[k][0]]+1;
							k=ch[k][1];
						}	
				}	
		}
	splay(k,to);	
}

void build(int l,int r,int &now,int fat)
{
	int mid=(l+r)>>1;
	now=++tot;
	fa[now]=fat;
	va[now]=a[mid];
	build(l,mid-1,ch[now][0],now);
	build(mid+1,r,ch[now][1],now);
	upload(now);
}

void TAG(int l,int r)
{
	rotateto(l-1,0);
	rotateto(r+1,root);
	int now=ch[ch[root][1]][0];
	tag[now]^=1;
}

void cut(int l,int r,int c)
{
	rotateto(l-1,0);
	rotateto(r+1,root);
	int now=ch[ch[root][1]][0];
	ch[ch[root][1]][0]=0;
	fa[now]=0;
	upload(ch[root][1]);
	upload(root);
	rotateto(c,0);
	rotateto(c+1,root);
	pushdown(ch[root][1]);
	ch[ch[root][1]][0]=now;
	fa[now]=ch[root][1];
	upload(ch[root][1]);
	upload(root);
}

void OUT(int now)
{
	if(ch[now][0]&&!vis[now])
		OUT(ch[now][0]);
	printf("%d ",va[now]);
	vis[now]=1;
	if(ch[now][1]&&vis[now])
		OUT(ch[now][1]);	
}

void init()
{
	memset(tag,0,sizeof(tag));
	memset(va,0,sizeof(va));
	memset(ch,0,sizeof(ch));
	memset(cnt,0,sizeof(cnt));
	memset(vis,0,sizeof(vis));
	memset(fa,0,sizeof(fa));
	tot=root=0;
}

int main()
{
	freopen("1.txt","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF&&n>0&&m>0)
		{
			init();
			a[1]=a[n+2]=0;
			for(int i=2;i<=n+1;++i)
				scanf("%d",&a[i]);
			build(1,n+2,root,0);
			char s[10];
			int a,b,c;
			for(int i=1;i<=m;++i)
				{
					scanf("%s",s);
					if(s[0]=='C')
						{
							scanf("%d%d%d",&a,&b,&c);
							cut(a+1,b+1,c+1);
						}
					else
						{
							scanf("%d%d",&a,&b);
							TAG(a+1,b+1);
						}	
				}	
			OUT(root);	
		}
	return 0;	
}
