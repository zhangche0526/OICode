#include<iostream>
#include<cstdio>
#include<cstring>
using std::min;
using std::max;

const int MAXN=3e7+5;

int r[MAXN];
int manacher(char *s)
{
    int i,sL=strlen(s);
    for(i=sL-1;i>=0;i--) s[i+1<<1]=s[i];
    for(i=0;i<=sL;i++) s[i<<1^1]='#';
    sL=sL+1<<1;
    s[0]='(',s[sL]=')';

    int mxv=0,mxp=0,res=1;
    for(i=1;i<sL;i++)
    {
        r[i]=i<mxv?min(r[mxp*2-i],mxv-i):1;
        while(s[i-r[i]]==s[i+r[i]]) r[i]++;
        if(r[i]+i>mxv) mxv=r[i]+i,mxp=i;
        res=max(res,r[i]-1);
    }
    return res;
}

char s[MAXN];

int main()
{
    while(~scanf("%s",s))
		printf("%d",manacher(s));
    return 0;
}
/*
ababcbabccbaabc
abcba
*/

