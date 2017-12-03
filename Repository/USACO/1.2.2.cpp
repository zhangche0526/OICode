/*
ID:zhangch33
LANG:C++
TASK:transform
*/
#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=10;
int n;
struct matrix
{
	bool s[MAXN+1][MAXN+1];
	bool operator ==(const matrix & b)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(b.s[i][j]!=s[i][j])
					return false;
		return true;
	}

	void rot(matrix & b)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				b.s[j][n-i+1]=s[i][j];
	}
	void mir(matrix & b)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				b.s[i][j]=s[i][n-j+1];
	}
};
void read(matrix & a)
{
	char x;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			do x=getchar();
			while(x!='-'&&x!='@');
			if(x=='@') a.s[i][j]=true;
		}
}
matrix orig[10],res;
int main()
{
	freopen("transform.in","r",stdin);
	freopen("transform.out","w",stdout);
	int i,ans=0;
	cin>>n;
	read(orig[0]);read(res);
	for(i=1;i<=3;i++)
	{
		orig[i-1].rot(orig[i]);
		if(orig[i]==res)
		{
			cout<<i<<endl;
			return 0;
		}
	}
	orig[0].mir(orig[4]);
	if(orig[4]==res)
	{
		cout<<4<<endl;
		return 0;
	}
	for(i=1;i<=3;i++)
	{
		orig[i].mir(orig[i+4]);
		if(orig[i+4]==res)
		{
			cout<<5<<endl;
			return 0;
		}
	}
	if(orig[0]==res)
	{
		cout<<6<<endl;
		return 0;
	}
	cout<<7<<endl;
	return 0;
}
