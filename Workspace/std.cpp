#include <cstdio>
#include <cstring>
#include <algorithm>
#define mod 30031
using namespace std;
int c[1030] , w[1030] , v[130] , n;
struct data
{
	int v[130][130];
	data() {memset(v , 0 , sizeof(v));}
	int *operator[](int a) {return v[a];}
	data operator*(data &a)
	{
		data ans;
		int i , j , k;
		for(i = 1 ; i <= n ; i ++ )
			for(j = 1 ; j <= n ; j ++ )
				for(k = 1 ; k <= n ; k ++ )
					ans[i][j] = (ans[i][j] + v[i][k] * a[k][j]) % mod;
		return ans;
	}
}A;
data pow(data x , int y)
{
	data ans;
	int i;
	for(i = 1 ; i <= n ; i ++ ) ans[i][i] = 1;
	while(y)
	{
		if(y & 1) ans = ans * x;
		x = x * x , y >>= 1;
	}
	return ans;
}
int main()
{
	int m , k , p , i , j;
	scanf("%d%d%d" , &m , &k , &p);
	for(i = 1 ; i < (1 << p) ; i ++ )
	{
		c[i] = c[i - (i & -i)] + 1;
		if(c[i] == k && i & (1 << (p - 1))) w[i] = ++n , v[n] = i;
	}
	for(i = 1 ; i <= n ; i ++ )
	{
		if(v[i] & 1) A[i][w[(1 << (p - 1)) | (v[i] >> 1)]] = 1;
		else
			for(j = 0 ; j < p ; j ++ )
				if(v[i] & (1 << j))
					A[i][w[(1 << (p - 1)) | ((v[i] ^ (1 << j)) >> 1)]] = 1;
	}
	A = pow(A , m - k);
	i = w[(1 << p) - (1 << (p - k))];
	printf("%d\n" , A[i][i]);
	return 0;
}
