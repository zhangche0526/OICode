#include<iostream> 
#include <cstdio>
using namespace std;
typedef long long int ll;
const int MAXN = 40000;

ll a[MAXN+1];
int N;

int main()
{
	int i;
	ios::sync_with_stdio(false);
	freopen("33.in","r",stdin);
	freopen("33.out","w",stdout);
	cin>>N;
	a[1] = 1;
	for(i = 2; i <= N; i++) if(!a[i])
		for(int j = i; j <= N; j += i) {
			if(!a[j]) a[j] = j;
			a[j] = a[j] / i * (i-1);
		}
	ll ans = 0;
	for(i = 2; i < N; i++) ans += a[i];
	cout<<ans*2 + 3<<endl;
	return 0;
}
