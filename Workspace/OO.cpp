#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;
const int MAXN=705,P=1e9+7;

int num[MAXN],len;

int f[MAXN][MAXN];
int v;
int F(int lv,int cnt,bool lim)
{
	if(cnt<0) return 0;
	int &o=f[lv][cnt];
	if(!lim&&~o) return o;
	if(!lv) return !cnt;
	int n=lim?num[lv]:9;
	int i,res=0;
	for(i=0;i<=n;i++)
		res=(res+F(lv-1,cnt-(i>=v),lim&&i==n))%P;
	if(!lim) o=res;
	return res;
}

int main()
{
	static char s[MAXN];scanf("%s",s);len=strlen(s);
	for(int i=0;i<len;i++) num[len-i]=s[i]-'0';
	int ans=0;
	for(v=1;v<=9;v++)
	{
		memset(f,-1,sizeof f);
		for(int i=1,x=1;i<=len;i++,x=(10LL*x+1)%P)
			ans=(ans+(ll)x*F(len,i,1)%P)%P;
	}
	printf("%d",ans);
	return 0;
}
/*
987654321
*/
