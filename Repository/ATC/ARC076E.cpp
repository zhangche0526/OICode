#include<iostream>
#include<cstdio>
#include<map>
 
const int MAXN=4e5+5;
 
int R,C,n;
 
int seq[MAXN];
inline int getp(int r,int c)
{
	if(!r) return c;
	if(c==C) return C+r;
	if(r==R) return C+R+C-c;
	if(!c) return C+R+C+R-r;
	return -1;
}
 
std::map<int,int> mp;
int st[MAXN],tp;
inline bool jud()
{
	for(std::map<int,int>::iterator i=mp.begin();i!=mp.end();i++) if(i->second)
		i->second^st[tp]?st[++tp]=i->second:tp--;
	return !tp;
}
 
int main()
{
	int i;scanf("%d%d%d",&R,&C,&n);
	for(i=1;i<=n;i++)
	{
		int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		int p1=getp(x1,y1),p2=getp(x2,y2);
		if(~p1&&~p2) mp[p1]=mp[p2]=i;
	}
	puts(jud()?"YES":"NO");
	return 0;
}
