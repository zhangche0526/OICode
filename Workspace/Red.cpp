#include<iostream>
#include<cstdio>
using std::max;
typedef long long ll;

const int MAXN=5005;

int R,B;
double f[2][MAXN];

int main()
{
    scanf("%d%d",&R,&B);
    for (int i=0,p=0;i<=R;i++,p^=1,f[p][0]=i)
        for (int j=1;j<=B;j++)
            f[p][j]=max(0.0,1.0*i/(i+j)*(f[p^1][j]+1)+1.0*j/(i+j)*(f[p][j-1]-1));
    printf("%lf",ll(f[R&1][B]*1e6)/1e6);
    return 0;
}
