#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXL=105;

char s[MAXL];
int f[MAXL][MAXL];

inline bool jud(char a,char b)
{return (a=='('&&b==')')||(a=='['&&b==']');}

void print(int i,int j)
{
	if(i>j) return;
	if(i==j)
	{
		if(s[i]=='('||s[i]==')') printf("()");
		else printf("[]");
		return;
	}
	int ans=f[i][j];
	if(jud(s[i],s[j])&&ans==f[i+1][j-1])
	{
		putchar(s[i]);print(i+1,j-1);putchar(s[j]);
		return;
	}
	for(int k=i;k<j;k++)
		if(ans==f[i][k]+f[k+1][j])
		{
			print(i,k);print(k+1,j);
			return;
		}
}

int main()
{
	int T;
	fgets(s,MAXL,stdin);
  	sscanf(s,"%d",&T);
  	fgets(s,MAXL,stdin);
	while(T--)
	{
		int i,j,k;
		fgets(s,MAXL,stdin);
		int sL=strlen(s)-1;
		memset(f,0,sizeof(f));
		for(i=0;i<sL;i++) f[i][i]=1;
		for(i=sL-2;i>=0;i--)
			for(j=i+1;j<sL;j++)
			{
				f[i][j]=sL;
				if(jud(s[i],s[j])) f[i][j]=std::min(f[i][j],f[i+1][j-1]);
				for(k=i;k<j;k++) f[i][j]=std::min(f[i][j],f[i][k]+f[k+1][j]);
			}
		print(0,sL-1);
		putchar('\n');if(T) putchar('\n');
		fgets(s,MAXL,stdin);
	}
	return 0;
}
