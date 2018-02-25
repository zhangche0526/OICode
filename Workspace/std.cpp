#include <cstdio>
#include <algorithm>
int f[1000010] , l[1000010] , r[1000010] , v[1000010] , d[1000010] , die[1000010];
int find(int x)
{
    return x == f[x] ? x : f[x] = find(f[x]);
}
int merge(int x , int y)
{
    if(!x) return y;
    if(!y) return x;
    if(v[x] > v[y]) std::swap(x , y);
    r[x] = merge(r[x] , y);
    if(d[l[x]] < d[r[x]]) std::swap(l[x] , r[x]);
    d[x] = d[r[x]] + 1;
    return x;
}
int main()
{
    int n , i , m , x , y , tx , ty;
    scanf("%d%d" , &n,&m);
    for(i = 1 ; i <= n ; i ++ )
        scanf("%d" , &v[i]) , f[i] = i , d[i] = 1;
    while(m -- )
    {
    	int opt;
        scanf("%d%d" , &opt , &x);
        if(opt == 1)
        {
            scanf("%d" , &y);
            if(!die[x] && !die[y])
            {
                tx = find(x) , ty = find(y);
                if(tx != ty) f[tx] = f[ty] = merge(tx , ty);
            }
        }
        else
        {
            if(die[x]) printf("-1\n");
            else
            {
                tx = find(x);
                die[tx] = 1;
                printf("%d\n" , v[tx]);
                ty = merge(l[tx] , r[tx]);
                f[tx] = f[ty] = ty;
            }
        }
    }
    return 0;
}
