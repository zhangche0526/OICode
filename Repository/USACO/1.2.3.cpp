/*
ID:zhangch33
LANG:C++
TASK:namenum
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXNODE=5000,SIGMASIZE=26;
char i2c[10][5]={{},{},"ABC","DEF","GHI","JKL","MNO","PRS","TUV","WXY"};
struct Trie
{
	int ch[MAXNODE][SIGMASIZE];
	bool val[MAXNODE];
	int sz;
	Trie(){sz=1;memset(ch[0],0,sizeof(ch[0]));}
	int idx(char c){return c-'A';}
	
	void insert(char * s)
	{
		int u=0,n=strlen(s);
		for(int i=0;i<n;i++)
		{
			int c=idx(s[i]);
			if(!ch[u][c])
			{
				memset(ch[sz],0,sizeof(ch[sz]));
				val[sz]=0;
				ch[u][c]=sz++;
			}
			u=ch[u][c];
		}
		val[u]=true;
	}
	bool search(char * s)
	{
		int u=0,n=strlen(s);
		for(int i=0;i<n;i++)
		{
			int c=idx(s[i]);
			u=ch[u][c];
			if((i==n-1)&&val[u])
				return true;
		}
		return false;
	}
};
Trie tr;
int qpow(int x,int y)
{
	int res=1;
	for(int i=1;i<=y;i<<=1,x*=x)
		if(i&y) res*=x;
	return res;
}
int main()
{
	freopen("dict.txt","r",stdin);
	int i,j;
	char name[20];
	while(scanf("%s",name)!=EOF)
		tr.insert(name);
	///
	freopen("namenum.in","r",stdin);
	freopen("namenum.out","w",stdout);
	char num[20];
	scanf("%s",num);
	int nl=strlen(num);
	char req[20];
	memset(req,0,sizeof(req));
	for(i=0;i<=qpow(3,nl);i++)
	{
		int resti=i;
		int tmp=3;
		for(j=0;j<nl;j++,tmp*=3)
			req[j]=i2c[num[j]-'0'][resti%tmp],resti/=tmp;
		if(tr.search(req))
			printf("%s\n",req);
	}
	return 0;
}
