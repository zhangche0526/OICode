#include<cstdio>
#include<iostream>
using namespace std;

int n, m, a[100009], l, r=0, mid, sum, ans, maxx=0;

int check(int s)
{
	sum = 0,ans = 1;//ans:分的段数，至少分一段
	for(int i = 1; i <= n; i ++)
	{
		sum = sum + a[i];
		if(sum > s){ans ++, sum = a[i];}
	}
	if(ans > m){return 1;}
	else{return 0;}
}
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i ++)
	{
		cin >> a[i];
		if(a[i] > maxx){maxx = a[i];}
		r = r + a[i];
	}
	l = maxx;
	if(m == n){cout << l; return 0;}
	while(l + 1 < r)
	{
		mid = (l + r) / 2;
		if(check(mid)){l = mid;}
		else{r = mid;}
	}
	if(! check(r - 1)){cout <<　r - 1;return 0;}
	cout << r;
	return 0;
}

