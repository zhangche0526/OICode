#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=1e3;
int N,M;
int tl[MAXN+1];
int K;

int main()
{
	int i;int X,Y;char ch;
	ios::sync_with_stdio(false);
	freopen("9.in","r",stdin);
	freopen("9.out","w",stdout);
	cin>>N>>M;
	memset(tl,-1,sizeof(tl));
	for(i=1;i<=M;i++)
	{
		cin>>X>>Y>>ch;
		if(tl[X]==-1||tl[X]==1)
		{
			if(ch=='T') 
			{
				if(tl[Y]==0) break;
				else 
				{
					tl[Y]=1;
					if(tl[X]==-1) tl[X]=1;
				}
			}
			else 			
			{
				if(tl[Y]==1) break;
				else 
				{
					tl[Y]=0;
					if(tl[X]==-1) tl[X]=1;
				}
			}
		}else
		{
			if(ch=='T') 
			{
				if(tl[Y]==1) break;
				else tl[Y]=0;
			}
			else 			
			{
				if(tl[Y]==0) break;
				else tl[Y]=1;
			}
		}
	}
	K=i-1;
	cout<<K<<endl;
	return 0;
}
