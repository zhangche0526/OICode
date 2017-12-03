/*
ID:zhangch33
LANG:C++
TASK:milk2
*/
#include<iostream>
#include<cstdio>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
using namespace std;

const int MAXN=5e3,INF=1e9;
int N;
struct rang
{
	int l,r;int pre,nex;
	int getlen(){return r-l;}
} t[MAXN+1];int tcnt;

int main()
{
	freopen("milk2.in","r",stdin);
	freopen("milk2.out","w",stdout);
	int i,j;
	int a,b;
	cin>>N;
	scanf("%d%d",&a,&b);
	t[0].nex=1;t[1].l=a,t[1].r=b,++tcnt;
	for(i=1;i<=N;i++)
	{
		scanf("%d%d",&a,&b);
		for(int tmp=t[0].nex;tmp;tmp=t[tmp].nex)
		{
			if((!t[tmp].nex)&&a>t[tmp].r)//走到最右边，只好加一个
			{
				t[t[tmp].nex].pre=++tcnt,t[tcnt].nex=t[tmp].nex,t[tmp].nex=tcnt,t[tcnt].pre=tmp;
				t[tcnt].l=a,t[tcnt].r=b;
				break;
			}
			else if((!t[tmp].pre)&&b<t[tmp].l)//最左边
			{
				t[t[tmp].pre].nex=++tcnt,t[tcnt].pre=t[tmp].pre,t[tmp].pre=tcnt,t[tcnt].nex=tmp;
				t[tcnt].l=a,t[tcnt].r=b;
				break;
			}else if(a>t[tmp].r&&b<t[t[tmp].nex].l)
			{
				t[t[tmp].nex].pre=++tcnt,t[tcnt].nex=t[tmp].nex,t[tmp].nex=tcnt,t[tcnt].pre=tmp;
				t[tcnt].l=a,t[tcnt].r=b;
				break;
			}
			else if(!(a>t[tmp].r||b<t[tmp].l))
			{
				t[tmp].l=min(t[tmp].l,a);
				t[tmp].r=max(t[tmp].r,b);
				for(j=t[tmp].pre;j;j=t[tmp].pre)
					if(t[j].r>=t[tmp].l)
					{
						t[tmp].l=min(t[tmp].l,t[j].l);
						t[t[j].pre].nex=tmp;
						t[tmp].pre=t[j].pre;
					}else break;
				for(j=t[tmp].nex;j;j=t[tmp].nex)
					if(t[j].l<=t[tmp].r)
					{
						t[tmp].r=max(t[tmp].r,t[j].r);
						t[t[j].nex].pre=tmp;
						t[tmp].nex=t[j].nex;
					}else break;
				break;
			}
		}
	}
	int ansa=0,ansb=0;
	for(int tmp=t[0].nex;tmp;tmp=t[tmp].nex)
		ansa=max(ansa,t[tmp].getlen());
	for(int tmp=t[0].nex;t[tmp].nex;tmp=t[tmp].nex)
		ansb=max(ansb,t[t[tmp].nex].l-t[tmp].r);
	cout<<ansa<<" "<<ansb<<endl;
}
