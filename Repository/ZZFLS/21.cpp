#include<cstdio>
#include<complex>
#include<cmath>
using namespace std;

typedef complex<double> C;

const int MAXN=262145;
const double PI=acos(-1);
int n,m,L;
int R[MAXN];
C a[MAXN],b[MAXN];

inline void swap(C &a,C &b)
{C t=a;a=b,b=t;}

void FFT(C * A,int type)
{
	for(int i=0;i<n;++i)
		if(i<R[i])
			swap(A[i],A[R[i]]);
	for(int i=1;i<n;i<<=1)
	{
		C wn(cos(PI/i),type*sin(PI/i));
		for(int p=i<<1,j=0;j<n;j+=p){
			C w(1,0);
			for(int k=0;k<i;++k,w*=wn)
			{
				C x=A[j+k],y=w*A[j+k+i];
				A[j+k]=x+y;A[j+k+i]=x-y;
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0,x;i<=n;++i)
		scanf("%d",&x),a[i]=x;
	for(int i=0,x;i<=m;++i)
		scanf("%d",&x),b[i]=x;
	m+=n;
	for(n=1;n<m;n<<=1) ++L;
	for(int i=0;i<n;++i)
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	FFT(a,1);FFT(b,1);
	for(int i=0;i<=n;++i)
		a[i]*=b[i];
	FFT(a,-1);
	for(int i=0;i<=m;++i)
		printf("%d ",int(a[i].real()/n+0.5));
	return 0;
}
