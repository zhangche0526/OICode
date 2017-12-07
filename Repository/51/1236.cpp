#include<iostream>
#include<cstdio>
#include<cstring>
using std::cin;
using std::cout;
using std::endl;

typedef long long ll;
const int P=1e9+9;
ll n,k;

const int MAXK=1e5+5,s5=383008016,s5Inv=723398404,X=691504013,Y=308495997;
int fac[MAXK],facInv[MAXK];
inline void initFac()
{
	int i;fac[0]=facInv[0]=1;
	for(i=1;i<MAXK;i++) fac[i]=i;
	facInv[1]=1;for(int i=2;i<MAXK;i++) facInv[i]=((ll)(P-P/i)*facInv[P%i])%P;
	for(i=2;i<MAXK;i++) fac[i]=(ll)fac[i-1]*fac[i]%P,facInv[i]=(ll)facInv[i]*facInv[i-1]%P;
}
inline int C(int a,int b){return (ll)fac[a]*facInv[a-b]%P*facInv[b]%P;}
int qpow(int a,ll x)
{
	int res=1;
	for(;x;x>>=1,a=(ll)a*a%P)
		if(x&1) res=(ll)res*a%P;
	return res;
}
inline int solve()
{
	initFac();
	int i,ans=0,a1,Sn,res;
	for(i=0;i<=k;i++)
	{
		a1=(ll)qpow(X,k-i)*qpow(Y,i)%P;
		if(a1==1) Sn=n%P;
		else Sn=(ll)a1*(qpow(a1,n)-1)%P*qpow(a1-1,P-2)%P;
		res=(ll)(i&1?-1:1)*C(k,i)*Sn%P;
		ans=((ll)ans+res+P)%P;
	}
	ans=(ll)qpow(qpow(s5,P-2),k)*ans%P;
	return ans;
}

int main()
{
	int T;cin>>T;
	while(T--)
	{
		cin>>n>>k;
		cout<<solve()<<endl;
	}
	return 0;
}
