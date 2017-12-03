#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXL=105;

char s[MAXL];

int main()
{
	while(scanf("%s",s)!=EOF)
	{
		int i,len=strlen(s);
		int a=0,b=0;
		for(i=0;i<len;i++) 
			if(s[i]=='0')
			{
				if(s[(i+1)%len]=='0') a++;
				b++;
			}
		if(a*len<b*b) printf("ROTATE\n");
		else if(a*len>b*b) printf("SHOOT\n");
		else printf("EQUAL\n");
	}
}
