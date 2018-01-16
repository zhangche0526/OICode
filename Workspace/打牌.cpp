#include<iostream>
#include<cstdio>
using std::min;
using std::max;

int readCard()
{
	char s[5];scanf("%s",s);
	switch(s[0])
	{
		case 'A':return 1;
		case 'T':return 10;
		case 'J':return 11;
		case 'Q':return 12;
		case 'K':return 13;
		default:return s[0]-'0';
	}
}

int vs(int a,int b)
{
	if(a==b) return a;
	if(a==1) return 1;
	if(b==1) return -1;
	if(a>b) return a;
	return -b;
}

int calc(int a,int b,int c,int d)
{
	int res=vs(a,b);
	if(res>0) res+=vs(c,d);
	else res-=vs(d,c);
	return res;
}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int a,b,c,d;a=readCard();b=readCard();c=readCard();d=readCard();
		int r1=calc(a,c,b,d),r2=calc(a,d,b,c),r3=calc(b,c,a,d),r4=calc(b,d,a,c);
		int ans=max(min(r1,r2),min(r3,r4));
		printf("%d\n",ans);
	}
	return 0;
}
