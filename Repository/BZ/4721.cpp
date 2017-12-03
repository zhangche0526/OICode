#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
typedef long long ll;
const int MAXN=1e5+5,INF=1e9;
int n,m,q,u,v,t,a[MAXN];
std::queue<int> que[3];
int main()
{
	int i,j;
	scanf("%d%d%d%d%d%d",&n,&m,&q,&u,&v,&t);
	for(i=1;i<=n;i++) scanf("%d",a+i);
	std::sort(a+1,a+n+1);
	for(i=n;i;i--) que[0].push(a[i]);
	int tag=0,rk=0;
	for(i=1;i<=m;i++)
	{
		int maxv=-INF,fr;
		for(j=0;j<3;j++) if(!que[j].empty()) 
			if(que[j].front()>maxv) maxv=que[j].front(),fr=j;
		que[fr].pop();
		maxv+=tag;rk++;if(rk%t==0) printf("%d ",maxv);
		int new1=(ll)maxv*u/v,new2=maxv-new1;
		tag+=q;new1-=tag,new2-=tag;
		que[1].push(new1);que[2].push(new2);
	}
	putchar('\n');rk=0;
	int tmp=que[0].size()+que[1].size()+que[2].size();
	for(i=1;i<=n+m;i++)
	{
		int maxv=-INF,fr;
		for(j=0;j<3;j++) if(!que[j].empty()) 
			if(que[j].front()>maxv) maxv=que[j].front(),fr=j;
		que[fr].pop();
		maxv+=tag;rk++;if(rk%t==0) printf("%d ",maxv);
	}
	putchar('\n');
	return 0;
}
