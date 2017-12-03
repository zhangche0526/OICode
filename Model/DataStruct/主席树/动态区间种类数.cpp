#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
const int MAXN=1e4+5;
struct Tn{int lc,rc;ll sum;} t[MAXN*600];int tcnt;
int n,m;
int na[MAXN],srtdNa[MAXN],X[55],Y[55],A[MAXN],B[MAXN],C[MAXN],nextPos[MAXN],la[MAXN*100],rt[MAXN];
int ncnt,xcnt,ycnt;

int lowbit(int x){return x&(-x);}

void insert(int l,int r,int x,int &y,int k,int v)
{
	if(!y) y=++tcnt,t[y]=t[x];
	t[y].sum+=(ll)v;
	if(l==r) return;
	int mid=l+r>>1;
	if(k<=mid) insert(l,mid,t[x].lc,t[y].lc,k,v);
	else insert(mid+1,r,t[x].rc,t[y].rc,k,v);
}

void add(int x,int v)
{
	for(int i=x;i<=n+1;i+=lowbit(i))
		insert(1,n+1,rt[i],rt[i],nextPos[x],v);
}

ll query(int l,int r,int v)
{
	int i;ll sum=0;
	if(r<v) return 0;
	if(l>=v)
	{
		for(i=1;i<=xcnt;i++) sum-=t[X[i]].sum;
		for(i=1;i<=ycnt;i++) sum+=t[Y[i]].sum;
		return sum;
	}
	int laX[55],laY[55];
	for(i=1;i<=xcnt;i++) laX[i]=X[i];
	for(i=1;i<=ycnt;i++) laY[i]=Y[i];
	int mid=l+r>>1;
	for(i=1;i<=xcnt;i++) X[i]=t[laX[i]].lc;
	for(i=1;i<=ycnt;i++) Y[i]=t[laY[i]].lc;
	sum+=query(l,mid,v);
	for(i=1;i<=xcnt;i++) X[i]=t[laX[i]].rc;
	for(i=1;i<=ycnt;i++) Y[i]=t[laY[i]].rc;
	sum+=query(mid+1,r,v);
	return sum;
}
int main()
{
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%d",na+i);
		if(la[na[i]]) nextPos[la[na[i]]]=i;
		la[na[i]]=i;
	}
	for(i=1;i<=n;i++) if(!nextPos[i]) nextPos[i]=n+1;
	for(i=1;i<=m;i++)
	{
		char s[10];scanf("%s%d%d",s,A+i,B+i);
		if(s[0]=='Q') C[i]=1;
	}
	for(i=1;i<=n;i++) add(i,1);
	for(i=1;i<=m;i++)
	{
		xcnt=ycnt=0;
		if(C[i])
		{
			memset(X,0,sizeof(X));memset(Y,0,sizeof(Y));
			for(j=A[i]-1;j;j-=lowbit(j)) X[++xcnt]=rt[j];
			for(j=B[i];j;j-=lowbit(j)) Y[++ycnt]=rt[j];
			printf("%d\n",query(1,n+1,B[i]+1));
		}
		else
		{
			add(A[i],-1);
			na[A[i]]=B[i];
			nextPos[A[i]]=n+1;
			for(k=A[i]+1;k<=n;k++)
				if(na[k]==B[i])
				{
					nextPos[A[i]]=k;
					break;
				}
			add(A[i],1);
			for(j=A[i]-1;j;j--)
			{
				if(nextPos[j]==A[i])
				{
					add(j,-1);
					nextPos[j]=n+1;
					for(k=j+1;k<=n;k++)
						if(na[k]==na[j])
						{
							nextPos[j]=k;
							break;
						}
					add(j,1);
				}
				if(na[j]==B[i]&&nextPos[j]>A[i])
				{
					add(j,-1);
					nextPos[j]=A[i];
					add(j,1);
				}
			}
		}
	}
	return 0;
}
