#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXL=205,MAXN=20;
char SEQ[4]={'W','I','N','G'};
int POS[300];

int tot[4];
char A[4][MAXN],B[4][MAXN];
char s[MAXL];

int f[MAXL][MAXL][4];
bool dp(int l,int r,int t)
{
	if(l==r) return	SEQ[t]==s[l];
	if(~f[l][r][t]) return f[l][r][t];
	int i,j;
	for(i=1;i<=tot[t];i++)
		for(j=l;j<r;j++)
			if(dp(l,j,POS[A[t][i]])&&dp(j+1,r,POS[B[t][i]]))
				return f[l][r][t]=true;
	return f[l][r][t]=false;
}

int main()
{
	int i,t;
	memset(f,-1,sizeof f);
	for(t=0;t<4;t++) 
		scanf("%d",tot+t),POS[SEQ[t]]=t;
	for(t=0;t<4;t++)
		for(i=1;i<=tot[t];i++)
			scanf("%s",s),A[t][i]=s[0],B[t][i]=s[1];
	int sL;scanf("%s",s+1);sL=strlen(s+1);
	bool gg=true;
	for(t=0;t<4;t++) if(dp(1,sL,t)) putchar(SEQ[t]),gg=false;
	if(gg) puts("The name is wrong!");
	return 0;
}
