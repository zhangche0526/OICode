#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int MAXN=5e6+5;

int n,m;
struct T{int lc,rc,sum;} t[MAXN];int tcnt;
int rt[MAXN];
int ncnt;
int A[MAXN],B[MAXN],C[MAXN],a[MAXN],b[MAXN],X[MAXN],xcnt,Y[MAXN],ycnt;

int lowbit(int x){return x&(-x);}

void insert(int l,int r,int x,int &y,int k,int v)
{
	if(!y) y=++tcnt,t[y]=t[x];
	t[y].sum+=v;
	if(l==r) return;
	int mid=l+r>>1;
	if(k<=mid) insert(l,mid,t[x].lc,t[y].lc,k,v);
	else insert(mid+1,r,t[x].rc,t[y].rc,k,v);
}

void add(int x,int v)
{
	int k=std::lower_bound(b+1,b+ncnt+1,a[x])-b;
	for(;x<=n;x+=lowbit(x))
		insert(1,ncnt,rt[x],rt[x],k,v);
}

int query(int l,int r,int k)
{
	int i,sum=0,mid=l+r>>1;
	if(l==r) return l;
	for(i=1;i<=xcnt;i++) sum-=t[t[X[i]].lc].sum;
	for(i=1;i<=ycnt;i++) sum+=t[t[Y[i]].lc].sum;
	if(k<=sum) 
	{
		for(i=1;i<=xcnt;i++) X[i]=t[X[i]].lc;
		for(i=1;i<=ycnt;i++) Y[i]=t[Y[i]].lc;
		return query(l,mid,k);
	}else
	{
		for(i=1;i<=xcnt;i++) X[i]=t[X[i]].rc;
		for(i=1;i<=ycnt;i++) Y[i]=t[Y[i]].rc;
		return query(mid+1,r,k-sum);
	}
}
int main()
{
	freopen("dynrank.in","r",stdin);
	freopen("dynrank.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--)
	{
		memset(rt,0,sizeof(rt));
		memset(C,0,sizeof(C));
		ncnt=tcnt=0;
		int i,j;
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++)
			scanf("%d",a+i),b[++ncnt]=a[i];
		for(i=1;i<=m;i++)
		{
			char s[10];scanf("%s%d%d",s,A+i,B+i);
			if(s[0]=='Q') scanf("%d",C+i);
			else b[++ncnt]=B[i];
		}
		std::sort(b+1,b+ncnt+1);
		ncnt=std::unique(b+1,b+ncnt+1)-(b+1);
		for(i=1;i<=n;i++) add(i,1);
		for(i=1;i<=m;i++)
			if(C[i])
			{
				xcnt=ycnt=0;
				for(j=A[i]-1;j;j-=lowbit(j)) X[++xcnt]=rt[j];
				for(j=B[i];j;j-=lowbit(j)) Y[++ycnt]=rt[j];
				printf("%d\n",b[query(1,ncnt,C[i])]);
			}
			else
			{
				add(A[i],-1);
				a[A[i]]=B[i];
				add(A[i],1);
			}
	}
}
