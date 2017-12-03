#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

long long d[1000];
int N;

int main()
{
	ios::sync_with_stdio(false);
	freopen("27.in","r",stdin);
	freopen("27.out","w",stdout);
	int sum,i,j;
	cin>>N;
	sum=(N+1)*N/2;
	if(sum%2==1)
	{
		cout<<0<<endl;
		return 0;
	}
	sum/=2;
	d[0]=1;
	for(i=1;i<=N;i++)
		for(j=sum;j>=i;j--)
		d[j]+=d[j-i];
	cout<<d[sum]/2<<endl;
	return 0;
}
