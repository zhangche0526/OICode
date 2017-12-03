#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=1e5,MAXM=1e5;
int N,M;
int A[MAXN+1];

bool check(int x)
{
	int i,mcnt=0,Ap=0,msum=0;//monthcount,Arraypointer,moneysum
	for(i=1;i<=M;i++)
	{
		while(true)
		{
			if(Ap==N) break;
			msum+=A[++Ap];
			if(msum<=x&&msum+A[Ap+1]>x) break;
		}
	}
	if(Ap==N) return true;
	else return false;
}

int main()
{
	ios::sync_with_stdio(false);
	freopen("3.in","r",stdin);
	freopen("3.out","w",stdout);
	int i,maxnum=0,sum=0;
	int ans;
	cin>>N>>M;
	for(i=1;i<=N;i++) cin>>A[i];
	for(i=1;i<=N;i++)
	{
		if(A[i]>maxnum) maxnum=A[i];
		sum+=A[i];
	}
	int l=maxnum,r=sum;
	while(l<r)
	{
		int mid=(r+l)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
	}ans=r;
	cout<<ans<<endl;
	return 0;
}
