#include<iostream>
#include<cstdio>
#include<cmath>
typedef long long ll;

ll R,ans=0;

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

bool check(ll y,double x)
{
	if(x==std::floor(x))
	{
		ll x1=(ll)floor(x);
		if(gcd(x1*x1,y*y)==1&&x1*x1!=y*y)
			return true;
	}
	return false;
}
int main()
{
	scanf("%lld",&R);
	for(ll d=1;d*d<2*R;d++)
		if((2*R)%d==0)
		{
			for(ll a=1;a*a<=2*R/(2*d);a++)
			{
				double b=std::sqrt(2*R/d-a*a);
				if(check(a,b)) ans++;
			}
			if(d!=2*R/d)
				for(ll a=1;a*a<=d/2;a++)
				{
					double b=sqrt(d-a*a);
					if(check(a,b)) ans++;
				}
		}
	printf("%lld\n",ans*4+4);
	return 0;
}
