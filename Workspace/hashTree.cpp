#include<iostream>
#include<cstdio>
#include<cstring>
#include<string> 
using std::cin;
using std::cout;
using std::endl;
using std::string;
typedef long long ll;

const int MAXNODE=1005,SZ=32,PR[10]={2,3,5,7,11,13,17,19,23,29};
const ll P=419340454199820289LL,seed=1331;
class HT
{
	struct HTN
	{
		ll key;
		string val;
		bool occ;
		int c[SZ];
	} t[MAXNODE];int tcnt;
	bool find(int o,int lv,ll key,string *&val)
	{
		if(t[o].occ) if(t[o].key==key) {val=&t[o].val;return true;}
		int pos=key%PR[lv];
		if(!t[o].c[pos]) return false;
		return find(t[o].c[pos],lv+1,key,val);
	}
	string *nnd(int o,int lv,ll key)
	{
		if(!t[o].occ) {t[o].key=key,t[o].occ=true;return &t[o].val;}
		int pos=key%PR[lv];
		if(!t[o].c[pos]) t[o].c[pos]=++tcnt;
		return nnd(t[o].c[pos],lv+1,key);
	}
public:
	bool find(ll key){string *tmp;return find(1,0,key,tmp);}
	string &operator [](ll key)
	{
		string *res;
		if(find(1,0,key,res))
			return *res;
		return *nnd(1,0,key);
	}
	HT(){tcnt=1;t[1].occ=true,t[1].key=-1;};
} ht;

ll hash(string s)
{
	ll res=0;
	for(int i=0;i<s.length();i++)
		res=(res*seed+s[i]+P)%P;
	return res;
}

int main()
{
	int n,m,i;cin>>n>>m; 
	for(i=1;i<=n;i++)
	{
		string p,m;cin>>p>>m;
		ht[hash(p)]=m;
	}
	cout<<"²éÑ¯£º"<<endl;
	while(m--)
	{
		string p;cin>>p;
		if(ht.find(hash(p))) cout<<ht[hash(p)]<<endl;
		else cout<<"²»´æÔÚ"<<endl;
	}
	return 0;
}
/*
69 10
*/ 
