#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<numeric>
using std::min;
using std::max;
using std::vector;
using std::string;

const int INF=1061109567;

unsigned popcount(unsigned u)
{
    u = (u & 0x55555555) + ((u >> 1) & 0x55555555);
    u = (u & 0x33333333) + ((u >> 2) & 0x33333333);
    u = (u & 0x0F0F0F0F) + ((u >> 4) & 0x0F0F0F0F);
    u = (u & 0x00FF00FF) + ((u >> 8) & 0x00FF00FF);
    u = (u & 0x0000FFFF) + ((u >> 16) & 0x0000FFFF);
    return u;
}

class FlippingBitsDiv1{public:int getmin(vector<string> Sv,int M);};

int FlippingBitsDiv1::getmin(vector<string> Sv,int M)
{
	string s=std::accumulate(Sv.begin(),Sv.end(),string());
	int N=s.length();

	int i,ans=INF;
	if(M<=17)
	{
		for(int S=0;S<(1<<M);S++)
		{
			int f[2];f[0]=f[1]=0;
			for(int op=0;op<N;op+=M)
			{
				int l=min(M,N-op);
				int oS=0;for(i=0;i<l;i++) if(s[op+i]-'0') oS|=1<<i;
				int msk=(1<<l)-1;
				int cst0=f[0]+popcount((S^oS)&msk),
					cst1=f[1]+popcount((~S^oS)&msk);
				f[0]=min(cst0,cst1+1);
				f[1]=min(cst1,cst0+1);
			}
			ans=min(ans,min(f[0],f[1]));
		}
	}else
	{
		int gnum=(N+M-1)/M;
		for(int fS=0;fS<(1<<gnum);fS++)
		{
			int res=0;bool o,la=false;
			for(i=0;i<gnum;i++)
			{
				o=fS&(1<<i);
				if(o^la) res++;
				la=o;
			}
			int g,cnt[2];
			for(int op=0;op<M;op++)
			{
				cnt[0]=cnt[1]=0;
				for(i=op,g=0;i<N;i+=M,g++)
					cnt[(s[i]-'0')^bool(fS&(1<<g))]++;
				res+=min(cnt[0],cnt[1]);
			}
			ans=min(ans,res);
		}
	}
	return ans;
}
