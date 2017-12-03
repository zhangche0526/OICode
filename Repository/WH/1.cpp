#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=1e5;
int N,A[MAXN+1];

int main()
{
	ios::sync_with_stdio(false);
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int i,sum=0,max=0;
	bool an=true;//全是非正数
	cin>>N;
	for(i=1;i<=N;i++) cin>>A[i];
	//
	for(i=1;i<=N;i++) if(A[i]>0) an=false;
	if(an)
	{
		A[0]=-1001;
		for(i=1;i<=N;i++) if(A[i]>A[0]) A[0]=A[i];
		cout<<A[0]<<endl;
		return 0;
	}
	for(i=1;i<=N;i++)
	{
		if(sum>=0) sum+=A[i];
		else sum=A[i];
		if(sum>max) max=sum;
	}
	cout<<max<<endl;
	return 0;
}
