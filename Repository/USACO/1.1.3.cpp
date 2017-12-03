/*
ID:zhangch33
LANG:C++
TASK:friday
*/
#include<iostream>
#include<cstdio>
using namespace std;
const int d[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31}};
int N;
int n[7];
int main()
{
	freopen("friday.in","r",stdin);
	freopen("friday.out","w",stdout);
	int i,j;
	cin>>N;
	int ld=0;
	++n[ld];
	for(i=0;i<N;i++)
		for(j=1;j<=12;j++)
			if(((1900+i)%4)||((!((1900+i)%100))&&(1900+i)%400))
			{
				ld=(ld+d[0][j])%7;
				++n[ld];
			}else
			{
				ld=(ld+d[1][j])%7;
				++n[ld];
			}
	--n[ld];
	for(i=0;i<6;i++) cout<<n[i]<<" ";
	cout<<n[6]<<endl;
	return 0;
}
