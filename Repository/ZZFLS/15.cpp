#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;

ll ct[26];

int pos;
ll times[100005];
ll mul[100005];
#define lowbit(a) (a&(-a))
ll calMul(int x)
{
	ll res=1;
	for(;x;x-=lowbit(x))
		res*=mul[x];
	return res;
}
void multi(int x,ll y)
{
	times[x]*=y;
	for(;x<=100005;x+=lowbit(x))
		mul[x]*=y;
}
void to1(int x)
{
	int y=times[x];
	for(;x<=100005;x+=lowbit(x))
		mul[x]/=y;
}


int main()
{
	int i;
	for(i=1;i<=100005;i++)
		times[i]=mul[i]=1;
	bool inkh=false;
	char c;c=getchar();
	while(c!='\n'&&c!=' ')
	{
		bool gotten=false;
		if('a'<=c&&c<='z')
		{
			ct[c-'a']+=calMul(pos);
			if(!inkh) to1(pos--);
		}else if('0'<=c&&c<='9')
		{
			ll num=0;
			while('0'<=c&&c<='9') 
			{
				num=num*10+c-'0';
				c=getchar();
			}gotten=true;
			multi(++pos,num);
		}else if(c=='(')
			inkh=true;
		else if(c==')')
		{
			inkh=false;
			to1(pos--);
		}
		if(!gotten) c=getchar(); 
	}
	for(i=0;i<26;i++)
		printf("%c %d\n",i='a',ct[i]);
}
