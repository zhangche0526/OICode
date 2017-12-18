#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using std::fabs;
const int MAXN=5e5+5;
const double eps=1e-9,INF=1e10;

int n;

struct P
{
	double x,y;
	P(double x=0,double y=0):x(x),y(y){}
};
bool operator <(const P &a,const P &b)
{return a.x<b.x||(fabs(a.x-b.x)<eps&&a.y<b.y);}
P operator +(P a,P b){return P(a.x+b.x,a.y+b.y);}
P operator -(P a,P b){return P(a.x-b.x,a.y-b.y);}
double operator *(P a,P b){return a.x*b.x+a.y*b.y;}
double cross(P a,P b){return a.x*b.y-a.y*b.x;}

struct O
{
	double x,y;bool *ans;
	O(){}
	O(double x,double y,bool *ans=NULL):x(x),y(y),ans(ans){}
} opt[MAXN];

P pt[MAXN],ch[MAXN];int ccnt;
inline P find(P p0)
{
	P res;
	int l=1,r=ccnt;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(p0*(ch[mid]-ch[mid-1])<-eps) r=mid-1,res=ch[mid];
		else l=mid+1;
	}
	return res;
}
void cdq(int l,int r)
{
	if(l==r) return;
	int i,mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);

	int ncnt=0;
	for(i=l;i<=mid;i++) if(!opt[i].ans) pt[++ncnt]=P(opt[i].x,opt[i].y);
	if(!ncnt) return;
	
	std::sort(pt+1,pt+ncnt+1);
	ccnt=0;
	for(i=n;i;i--)
	{
		while(ccnt>1&&cross(ch[ccnt]-ch[ccnt-1],pt[i]-ch[ccnt-1])>eps) ccnt--;
		ch[++ccnt]=pt[i];
	}
	ch[ccnt+1]=P(ch[ccnt].x-eps,INF);
	for(i=mid+1;i<=r;i++) if(opt[i].ans) if(*opt[i].ans)
	{
		P p0=P(opt[i].x,opt[i].y);
		P p=find(p0);
		*opt[i].ans &= 2*(p0.x*p.x+p0.y*p.y)-p0.x*p0.x-p0.y*p0.y > eps;
	}
}

bool ans[MAXN];int acnt;
int main()
{
	int i;
	scanf("%d",&n);
	bool hasCir=false;
	for(i=1;i<=n;i++)
	{
		int optTyp;double x,y;scanf("%d%lf%lf",&optTyp,&x,&y);
		if(optTyp)
		{
			ans[++acnt]=hasCir;
			opt[i]=O(x,y,&ans[acnt]);
		}
		else opt[i]=O(x,y),hasCir=true;
	}
	cdq(1,n);
	for(i=1;i<=acnt;i++) puts(ans[i]?"Yes":"NO");
	return 0;
}
