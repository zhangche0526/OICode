#include<iostream>
#include<cstdio>
#include<set>
typedef unsigned int uint;

const int MAXNODE=1e4+5,SZ=32,PR[10]={2,3,5,7,11,13,17,19,23,29};
class HT
{
	struct HTN
	{
		uint key;
		bool occ;
		int c[SZ];
	} t[MAXNODE];int tcnt;
	bool find(int o,int lv,uint key)
	{
		if(t[o].occ) if(t[o].key==key) return true;
		int pos=key%PR[lv];
		if(!t[o].c[pos]) return false;
		return find(t[o].c[pos],lv+1,key);
	}
	void ist(int o,int lv,uint key)
	{
		if(!t[o].occ) {t[o].key=key,t[o].occ=true;return;}
		int pos=key%PR[lv];
		if(!t[o].c[pos]) t[o].c[pos]=++tcnt;
		ist(t[o].c[pos],lv+1,key);
	}
public:
	bool find(uint key){return find(1,0,key);}
	void ist(uint key){ist(1,0,key);}
	HT(){tcnt=1;t[1].occ=true,t[1].key=-1;};
} ht;

int m;

int main()
{
	int i;
	scanf("%d",&m);
	int cnt=0;
	for(i=1;i<=m;i++)
	{
		uint a;scanf("%u",&a);
		if(!ht.find(a)) cnt++,ht.ist(a);
	}
	int ans;
	if(cnt<=10) ans=10;
	else if(cnt<=100) ans=100;
	else if(cnt<=1000) ans=1000;
	else if(cnt<=9000) ans=1e4;
	else if(cnt<=9900) ans=1e5;
	else if(cnt<=9990) ans=1e6;
	else ans=1e7;
	printf("%d",ans);
	return 0;
}
