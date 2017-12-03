#include<iostream>
#include<cstdio>
#include<cstring>
#define binget(x,y) (((x)>>(y<<1))&3)
#define binmv(x,y) ((x)<<(y<<1))
#define binclr(x,i,j) ((x)&(~(3<<(i<<1)))&(~(3<<(j<<1))))

typedef long long ll;

const int MAXN=15,MOD=(1<<15)-1,MAXNST=1e6+5;

int N,M;
int mp[MAXN][MAXN];
int ex,ey;

struct HM
{  
    int sz,hd[MOD+5],nxt[MOD+5];
    int state[MAXNST];
    ll f[MAXNST];
    void init()
	{  
        memset(hd,-1,sizeof(hd));
        for(int i=0;i<sz;i++) f[i]=0;
        sz=0;
    }  
    void push(int st,ll v)
	{  
        int s=st & MOD;
        for(int i=hd[s];~i;i=nxt[i])   
            if(state[i]==st)
			{  
                f[i]+=v;return;
            }  
        f[sz]=v;state[sz]=st;nxt[sz]=hd[s];hd[s]=sz++;
    }  
} hm[2];

int findL(int st,int x)
{  
    int cnt=1;
    for(int i=x-1;i>=0;i--)
	{  
        int s=((st>>(i<<1))&3);
        if(s==2) cnt++;
        else if(s==1) cnt--;
        if(!cnt) return i;
    }
    return -1;
}  
int findR(int st,int x)
{  
    int cnt=1;
    for(int i=x+1;i<=M;i++)
	{  
        int s=((st>>(i<<1))&3);
        if(s==1) cnt++;
        else if(s==2) cnt--;
        if(!cnt) return i;
    }  
    return -1;
}

ll solve()
{
	int i,j,k;
    int cur=0;
	hm[0].init();hm[0].push(0,1);
    for(i=1;i<=N;i++)
	{  
        cur^=1;
        hm[cur].init();
        for(j=0;j<hm[cur^1].sz;j++)
            hm[cur].push(hm[cur^1].state[j]<<2,hm[cur^1].f[j]);
        for(j=1;j<=M;j++)
		{  
            cur^=1;hm[cur].init();
            for(k=0;k<hm[cur^1].sz;k++)
			{  
                int L=binget(hm[cur^1].state[k],j-1),
					U=binget(hm[cur^1].state[k],j),
					st=binclr(hm[cur^1].state[k],j-1,j);
                if(!L&&!U)
				{
                    if(!mp[i][j]) hm[cur].push(st,hm[cur^1].f[k]);
                    else if(i<N&&j<M&&mp[i+1][j]&&mp[i][j+1])  
                        hm[cur].push(st|binmv(1,j-1)|binmv(2,j),hm[cur^1].f[k]);
                }  
                else if(!L||!U) 
				{  
                    int dir=L?L:U;
                    if(i<N&&mp[i+1][j]) hm[cur].push(st|binmv(dir,j-1),hm[cur^1].f[k]);
                    if(j<M&&mp[i][j+1]) hm[cur].push(st|binmv(dir,j),hm[cur^1].f[k]);
                }  
                else if(L==1&&U==1)   
                    hm[cur].push(st^binmv(3,findR(st,j)),hm[cur^1].f[k]);
                else if(L==2&&U==2)  
                    hm[cur].push(st^binmv(3,findL(st,j-1)),hm[cur^1].f[k]);
                else if(L==2&&U==1)  
                    hm[cur].push(st,hm[cur^1].f[k]);
                else if(i==ex&&j==ey)  
                    hm[cur].push(st,hm[cur^1].f[k]);
            }  
        }  
    }  
    for(i=0;i<hm[cur].sz;i++)
        if(!hm[cur].state[i])
			return hm[cur].f[i];
    return 0;
}  
int main() 
{
	int i,j;
	scanf("%d%d",&N,&M);
	char c;
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
		{
			do c=getchar();while(c!='*'&&c!='.');
			if(c=='.') ex=i,ey=j,mp[i][j]=true;
		}
	printf("%I64d\n",solve());
}  
