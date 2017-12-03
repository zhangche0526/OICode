#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=20000;
int heap[MAXN+1];
int heapsize=0,n;

void swap(int &a,int &b)
{
	int t=a;a=b;b=t;
}

int get()
{
	int now,next,res;
	res=heap[1];
	heap[1]=heap[heapsize--];
	now=1;
	while(now*2<=heapsize)
	{
		next=now*2;
		if(next<heapsize&&heap[next+1]<heap[next])
			next++;
		if(heap[now]<=heap[next]) return res;
		swap(heap[now],heap[next]);
		now=next;
	}
	return res;
}
void put(int x)
{
	int now,next;
	heap[++heapsize]=x;
	now=heapsize;
	while(now>1)
	{
		next=now>>1;
		if(heap[now]>=heap[next]) return;
		swap(heap[now],heap[next]);
		now=next;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	freopen("5.in","r",stdin);
	freopen("5.out","w",stdout);
	int i,x,y,ans=0;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>x;
		put(x);
	}
	for(i=1;i<n;i++)
	{
		x=get();
		y=get();
		ans+=x+y;
		put(x+y);
	}
	cout<<ans<<endl;
	return 0;
}
