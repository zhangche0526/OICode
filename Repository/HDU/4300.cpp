#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int nex[100005];
char str[27];
char s1[100005],s2[100005];

void getnext(char *t)
{
    int i = 0,j = -1;
    nex[0] = -1;
    while(t[i])
    {
        if(j == -1 || t[i] == t[j])
        {
            i++;
            j++;
            nex[i] = j;
        }
        else
            j = nex[j];
    }  
}  
  
int kmp(char *s,char *t)  
{  
    int i = 0,j = 0;  
    int slen =strlen(s),tlen = strlen(t);  
    getnext(t);  
    while(i<slen && j<tlen)  
    {  
        if(j == -1 || s[i] == t[j])  
        {  
            i++;  
            j++;
            if(i == slen)
                return j;
        }  
        else
            j = nex[j];
    }
    return 0;
}
  
int main()  
{  
    int casenum;  
    cin>>casenum;  
    while(casenum--)  
    {
        scanf("%s",str);  
        scanf("%s",s1);  
        int len = strlen(s1);  
        strcpy(s2,s1+(len+1)/2);  
        printf("%s",s1);  
        for(int i = 0; s1[i]; i++)  
        {  
            for(int j = 0; j<26; j++)  
            {  
                if(s1[i] == str[j])  
                {  
                    s1[i] = 'a'+j;  
                    break;  
                }  
            }  
        }  
        int flag = kmp(s2,s1);  
        for(int i = flag; i<len-flag; i++)  
        {  
            printf("%c",s1[i]);  
        }  
        cout << endl;  
    }  
  
    return 0;  
}  
