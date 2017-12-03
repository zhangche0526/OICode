#include<iostream> 
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;

const int MAXN=1e6+5;

int n;

class H
{
public:
	const int rt=1;
	int t[MAXN],sz;
	void push(int x)
	{
		t[++sz]=x;
		for(int u=sz;u>>1;u>>=1)
		{
			if(t[u]>=t[u>>1]) break;
			std::swap(t[u],t[u>>1]);
		}
	}
	void pop()
	{
		t[rt]=t[sz--];
		for(int u=1,v=2;v<=sz;u=v,v=u<<1)
		{
			if(v<sz&&t[v+1]<t[v]) v++;
			if(t[u]<=t[v]) break;
			std::swap(t[u],t[v]);
		}
	}
	int top(){return t[rt];}
} heap;

int main()
{
	scanf("%d",&n);
	while(n--)
	{
		int opt;scanf("%d",&opt);
		switch(opt)
		{
			case 1:int x;scanf("%d",&x);heap.push(x);break;
			case 2:printf("%d\n",heap.top());break;
			case 3:heap.pop();break;
		}
	}
	return 0;
}
