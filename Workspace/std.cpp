#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 1005, mo = 1e9+7;
inline int read() {
    char c=getchar(); int x=0,f=1;
    while(c<'0'||c>'9') {if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    return x*f;
}

int n, m; char str[20], c[10] = "ACGT";
int trans[1<<15][4], f[2][1<<15];
void init() {
    static int d[20], g[20];
    for(int s=0; s < 1<<n; s++) {
        for(int j=0; j<n; j++) d[j+1] = d[j] + bool(s & (1<<j));
        for(int k=0; k<4; k++) {
            for(int j=1; j<=n; j++) {
                g[j] = max(g[j-1], d[j]);
                if(c[k] == str[j]) g[j] = max(g[j], d[j-1]+1);
            }
            trans[s][k] = 0;
            for(int j=0; j<n; j++) if(g[j+1] - g[j]) trans[s][k] |= 1<<j; 
        }
    }
}
int ans[N];
int main() {
    int T = read();
    while(T--) {
        scanf("%s", str+1); m = read(); n = strlen(str+1);
        init();
        memset(ans, 0, sizeof(ans));
        memset(f, 0, sizeof(f));
        f[0][0] = 1; int p = 0;
        for(int i=1; i<=m; i++, p ^= 1) {
            memset(f[p^1], 0, sizeof(f[p^1]));
            for(int s=0; s < 1<<n; s++)
                for(int k=0; k<4; k++) (f[p^1][trans[s][k]] += f[p][s]) %= mo;
        }
        for(int s=0; s < 1<<n; s++) (ans[__builtin_popcount(s)] += f[p][s]) %= mo;
        for(int i=0; i<=n; i++) printf("%d\n", ans[i]);
    }
}
