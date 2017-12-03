#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,t;
int a[305][305]; 
int main(){
	ios::sync_with_stdio(false);
	freopen("21.in","r",stdin);
	freopen("21.out","w",stdout);
	cin>>n>>m>>t;
	memset(a,0x3f,sizeof a);
	for(int i=0,x,y,z;i<m;i++){
		cin>>x>>y>>z;
		a[x][y]=min(a[x][y],z);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=min(a[i][j],max(a[i][k],a[k][j]));
			}
		}
	}
	for(int i=0,x,y;i<t;i++){
		cin>>x>>y;
		cout<<((a[x][y]==0x3f3f3f3f)?-1:a[x][y])<<endl;
	}
	return 0;
}
