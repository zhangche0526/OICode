#include<iostream>
#include<cstdio>
using namespace std;

typedef long long ll;
const int MAXN=100,P=1e9+7;
struct matrix{int s[MAXN+1][MAXN+1];};
int N,K;

matrix mul(matrix a,matrix b)
{
	matrix res;
	memset(res.s,0,sizeof(res.s));
	int i,j,k;
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
			for(k=1;k<=N;k++)
				res.s[i][j]=((ll)res.s[i][j]+(ll)a.s[i][k]*b.s[k][j]%P)%P;
	return res;
}

matrix qpow(matrix a,ll k)
{
	matrix im;
	memset(im.s,0,sizeof(im.s));
	int i;
	for(i=1;i<=N;i++) im.s[i][i]=1; 
	for(int i=1;i<=k;i<<1,a=mul(a,a))
		if(i&k) im=mul(im,a);
	return im;
}

int main()
{
	cin>>N>>K;
	int i,j;
	int x;
	matrix m;
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
		{
			scanf("%d",&x);
			m.s[i][j]=x;
		}
	matrix ans=qpow(m,K);
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N;j++)
			printf("%d ",ans.s[i][j]);
		printf("\n");
	}
			
}
