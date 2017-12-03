/*
ID:zhangch33
LANG:C++
TASK:ride
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXL=6,P=47;
char a[MAXL+1],b[MAXL+1];
int resa=1,resb=1;
int main()
{
	freopen("ride.in","r",stdin);
	freopen("ride.out","w",stdout);
	cin>>a>>b;
	int i;
	for(i=0;i<strlen(a);i++) resa=(resa*(int)(a[i]-'A'+1))%P;
	for(i=0;i<strlen(b);i++) resb=(resb*(int)(b[i]-'A'+1))%P;
	if(resa==resb) cout<<"GO"<<endl;
	else cout<<"STAY"<<endl;
	return 0;
}
