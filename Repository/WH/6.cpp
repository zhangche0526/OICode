#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN=1e4;
int N;
struct node{int X,U;} st[MAXN+2];

bool cmp(const node & a,const node & b){return a.X>b.X;}

int main()
{
	ios::sync_with_stdio(false);
	freopen("6.in","r",stdin);
	freopen("6.out","w",stdout);
	int i,ans=0,rn=0;
	bool able=false;
	cin>>N;
	for(i=1;i<=N;i++) cin>>st[i].X>>st[i].U;
	cin>>st[0].X>>st[0].U;
	sort(st+1,st+N+1,cmp);
	int now=0;
	while(now<=N)
	{
		ans++;
		rn+=st[now].U;
		if(rn>=st[now].X)
		{
			able=true;
			break;
		}
		for(i=now;i<=N;i++)
			if((st[now].X-st[i].X)<=rn&&(st[now].X-st[i+1].X)>rn)
				break;
		if(i==now)
		{
			able=false;
			break;
		}
		now=i;
	}
	if(able) cout<<ans<<endl;
	else cout<<-1<<endl;
	return 0;
}
