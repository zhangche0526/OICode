#include<iostream>
#include<cstdio>
#include<cstring>
using std::min;
using std::max;

const int MAXN=3e7+5;

int rL[MAXN];
int manacher(char *s)
{
    int i,sL=strlen(s);
    for(i=sL-1;i>=0;i--) s[i+1<<1]=s[i];
    for(i=0;i<=sL;i++) s[i<<1^1]='#';
    sL=sL+1<<1;
    s[0]='(',s[sL]=')';

    int mxr=0,pos=0,res=1;
    for(i=0;i<sL;i++)
    {
        rL[i]=i<mxr?min(rL[pos*2-i],mxr-i):1;
        while(s[i-rL[i]]==s[i+rL[i]]) rL[i]++;
        if(rL[i]+i>mxr) mxr=rL[i]+i,pos=i;
        res=max(res,rL[i]-1);
    }
    return res;
}

char s[MAXN];

int main()
{
    scanf("%s",s);
    printf("%d",manacher(s));
    return 0;
}

