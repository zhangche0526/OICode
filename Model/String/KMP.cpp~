#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXN=1e6+5;

char s1[MAXN],s2[MAXN];

int nxt[MAXN];
void kmp(char *T,char *P)
{
    int i,j,TL=strlen(T),PL=strlen(P);
    for(i=1,j;i<PL;i++)
    {
        j=nxt[i];
        while(j&&P[i]!=P[j]) j=nxt[j];
        nxt[i+1]=(P[i]==P[j]?j+1:0);
    }
    for(i=j=0;i<TL;i++)
    {
        while(j&&T[i]!=P[j]) j=nxt[j];
        if(T[i]==P[j]) j++;
        if(j==PL) printf("%d\n",i-PL+1+1);
    }
    for(i=1;i<=PL;i++) printf("%d ",nxt[i]);
}

int main()
{
    scanf("%s%s",s1,s2);
    kmp(s1,s2);
    return 0;
}

