#include <algorithm>
#include <iostream>
#include <climits>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <queue>
#include <cmath>

using namespace std;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while (!isdigit(ch)) f=ch=='-'?-1:f,ch=getchar();
    while (isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int buf[30];

inline void write(int x)
{
    if (x<0) putchar('-'),x=-x;
    for (;x;x/=10) buf[++buf[0]]=x%10;
    if (!buf[0]) buf[++buf[0]]=0;
    for (;buf[0];putchar('0'+buf[buf[0]--]));
}

const int INF=INT_MAX/2;
const int MAXN=100005;
const int MAXM=100005;
const int MAXQ=100005;
const int MAXA=350;
const int MAXB=2200;
const int MAXC=12000;

int last[MAXN],deg[MAXN],kth[MAXN];
int tov[MAXM],nxt[MAXM];
int opt[MAXQ][3];
int answer[MAXQ];
int n,m,q,tot,idx;

queue<int> que;

inline void insert(int x,int y){tov[++tot]=y,nxt[tot]=last[x],last[x]=tot;}

/*
Partition the point set
*/

bitset<MAXC> con[MAXN];
int C;

inline void Partition_Point_Set();
inline void Process_Connectedness(int l,int r);
inline void Solve_Query(int l,int r);

/*
Partition the queries of the second type
*/

int stt[MAXA],ent[MAXA];
int f[MAXA][MAXN];
int srt[MAXA];
int mintag[MAXN];
int op[MAXQ][3];
int A,cnt;

inline void Partition_Operation();
inline void Process_Block(int bid,int l,int r);
inline int Query_Range(int l,int x,int st,int en);

/*
Periodic Reconstruction (the queries of the first type)
*/

int cache[MAXB][2];//time point
int asstag[MAXN];//time value
int csize;
int B,btot;

inline void Initialization();
inline void Add_Operation(int id);
inline int Latest_Modification(int l,int x);
inline void Reconstruction();

void pre()
{
    idx=0;
    for (int x=1;x<=n;++x) if (!deg[x]) que.push(x);
    for (int x;!que.empty();)
    {
        kth[++idx]=x=que.front(),que.pop();
        for (int i=last[x],y;i;i=nxt[i])
            if (!--deg[y=tov[i]]) que.push(y);
    }
}

int main()
{
    n=read(),m=read(),q=read();
    for (int i=1,x,y;i<=m;++i) x=read(),y=read(),insert(x,y),++deg[y];
    pre();
    for (int i=1;i<=q;++i)
    {
        opt[i][0]=read(),opt[i][1]=read();
        if (opt[i][0]!=3) opt[i][2]=read();
    }
    Partition_Operation(),Partition_Point_Set();
    for (int i=1;i<=q;++i) if (opt[i][0]==3) write(answer[i]),putchar('\n');
    fclose(stdin),fclose(stdout);
    return 0;
}

/*----------------------------------------------------------------------------*/

inline void Partition_Operation()
{
    for (int i=1;i<=q;++i) if (opt[i][0]==2) op[++cnt][0]=i,op[cnt][1]=opt[i][1],op[cnt][2]=opt[i][2];
    A=trunc(sqrt(cnt))+1,btot=0;
    for (int lcur=1,rcur;lcur<=cnt;lcur=rcur+1)
    {
        rcur=min(lcur+A-1,cnt);
        stt[++btot]=op[lcur][0],ent[btot]=op[rcur][0];
        Process_Block(btot,lcur,rcur);
    }
}

inline bool cmp(int x,int y){return op[x][2]<op[y][2]||op[x][2]==op[y][2]&&op[x][0]>op[y][0];}

inline void Process_Block(int bid,int l,int r)
{
    for (int i=1;i<=n;++i) mintag[i]=INF;
    int tmp=0;
    for (int i=l;i<=r;++i) srt[++tmp]=i;
    sort(srt+1,srt+1+tmp,cmp);
    for (int j=1,x,tag;j<=tmp;++j)
    {
        if (mintag[x=op[srt[j]][1]]<=(tag=op[srt[j]][2])) continue;
        for (mintag[x]=tag,que.push(x);!que.empty();)
        {
            x=que.front(),que.pop();
            for (int i=last[x],y;i;i=nxt[i])
                if (mintag[y=tov[i]]>tag) mintag[y]=tag,que.push(y);
        }
    }
    for (int i=1;i<=n;++i) f[bid][i]=mintag[i];
}

inline int Query_Range(int l,int x,int st,int en)
{
    int ret=INF;
    for (int i=1,lcur=1,rcur;i<=btot;++i,lcur=rcur+1)
    {
        rcur=min(lcur+A-1,cnt);
        if (ent[i]<st) continue;
        if (stt[i]>en) break;
        if (stt[i]<=st)
        {
            for (int j=lcur;j<=rcur;++j)
                if (st<=op[j][0]&&op[j][0]<=en&&con[op[j][1]].test(x-l+1))
                    ret=min(ret,op[j][2]);
            continue;
        }
        if (en<=ent[i])
        {
            for (int j=lcur;j<=rcur;++j)
                if (op[j][0]<=en&&con[op[j][1]].test(x-l+1))
                    ret=min(ret,op[j][2]);
            continue;
        }
        ret=min(ret,f[i][x]);
    }
    return ret;
}

/*----------------------------------------------------------------------------*/

inline void Partition_Point_Set()
{
    C=30*int(sqrt(n))+1;
    for (int lcur=1,rcur;lcur<=n;lcur=rcur+1)
    {
        rcur=min(lcur+C-1,n);
        Process_Connectedness(lcur,rcur),Solve_Query(lcur,rcur);
    }
}

inline void Process_Connectedness(int l,int r)
{
    for (int x=1;x<=n;++x) con[x].reset();
    for (int j=n,x;j>=1;--j)
    {
        x=kth[j];
        if (l<=x&&x<=r) con[x].set(x-l+1);
        for (int i=last[x];i;i=nxt[i]) con[x]|=con[tov[i]];
    }
}

inline void Solve_Query(int l,int r)
{
    Initialization();
    for (int i=1;i<=q;++i)
        if (opt[i][0]==1) Add_Operation(i);
        else if (opt[i][0]==3&&l<=opt[i][1]&&opt[i][1]<=r)
        {
            int x=opt[i][1],lpass=Latest_Modification(l,x),mintg=Query_Range(l,x,lpass,i);
            answer[i]=min(opt[lpass][2],mintg);
        }
}

/*----------------------------------------------------------------------------*/

inline void Initialization()
{
    B=trunc(pow(q,2./3.))+1,csize=0;
    for (int i=1;i<=n;++i) asstag[i]=0;
}

inline void Add_Operation(int id)
{
    cache[++csize][0]=id,cache[csize][1]=opt[id][1];
    if (csize==B) Reconstruction();
}

inline int Latest_Modification(int l,int x)
{
    for (int i=csize;i>=1;--i) if (con[cache[i][1]].test(x-l+1)) return cache[i][0];
    return asstag[x];
}

inline void Reconstruction()
{
    for (int j=csize,x,tag;j>=1;--j)
    {
        if (asstag[x=cache[j][1]]>(tag=cache[j][0])) continue;
        for (asstag[x]=tag,que.push(x);!que.empty();)
        {
            x=que.front(),que.pop();
            for (int i=last[x],y;i;i=nxt[i])
                if (asstag[y=tov[i]]<cache[j][0]) asstag[y]=tag,que.push(y);
        }
    }
    csize=0;
}
