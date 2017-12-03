#include<iostream>
#include<cstdio>
#include<cmath>
#include<complex>
using namespace std;

typedef complex<double> C;

const int MAXN=262145;
const double PI=acos(-1);
int pos[MAXN],bit;
int n,m;
C a[MAXN],b[MAXN];

void FFT(C * A,int type)
{
	int i,j,k;
	for(i=1;i<n;i++)
		if(i<pos[i])
			swap(A[i],A[pos[i]]);
	for(i=1;i<n;i<<=1)
	{
		C wn(cos(PI/i),type*sin(PI/i));
		for(j=0;j<n;j+=i<<1)
		{
			C w(1,0);
			for(k=0;k<i;k++,w*=wn)
			{
				C x=A[j+k],y=w*A[i+j+k];
				A[j+k]=x+y,A[i+j+k]=x-y;
			}
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	//n,m:��������ʽ������
	int i,x;
	for(i=0;i<n;i++)
		scanf("%d",&x),a[i]=x;
	for(i=0;i<m;i++)
		scanf("%d",&x),b[i]=x;
	m+=n;//��ʱm�ĺ���ת��Ϊ�����������
	for(n=1;n<m;n<<=1) ++bit;//n�ĺ���ת��Ϊ����m���2^k����С��
	//pos[]:����ģ��ݹ�����������˳��
	for(i=1;i<n;i++)
		pos[i]=(pos[i>>1]>>1)|((i&1)<<(bit-1));//������pos[]
	FFT(a,1),FFT(b,1);
	for(i=0;i<n;i++)
		a[i]*=b[i];
	FFT(a,-1);
	for(i=0;i<=m;i++)
		printf("%d ",int(a[i].real())/n+0.5);
	return 0;
}
