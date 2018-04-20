#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int MaxN = 50000 + 5, Mod = 10007;
 
int n, m, Len, MaxLen, Ans, Sumf;
int A[MaxN], Sum[MaxN], f[MaxN][2];
 
inline int gmax(int a, int b) {
    return a > b ? a : b;
}
inline int gmin(int a, int b) {
    return a < b ? a : b;
}
 
bool Check(int x) {
    if (x < MaxLen) return false;
    int Add = 0, Cut = 0;
    for (int i = 1; i <= n; i++) {
        if (Add + A[i] > x) {
            Cut++;
            if (Cut > m) return false;
            Add = 0;
        }
        Add += A[i];
    }
    return true;
}
 
int main()
{
    scanf("%d%d", &n, &m);
    MaxLen = 0;
    memset(Sum, 0, sizeof(Sum));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        MaxLen = gmax(MaxLen, A[i]);
        Sum[i] = Sum[i - 1] + A[i];
    }
    int l = 0, r = 50000000, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (Check(mid)) r = mid - 1;
        else l = mid + 1;
    }
    Len = r + 1;
    memset(f, 0, sizeof(f));
    Ans = 0;
    int Now = 0, Last = 1, Mink;
    for (int i = 0; i <= m; i++) {
        Sumf = 0;
        Mink = 1;
        for (int j = 1; j <= n; j++) {
            if (i == 0) {
                if (Sum[j] <= Len) f[j][Now] = 1;
                else f[j][Now] = 0;
            }
            else {
                while (Mink < j && Sum[j] - Sum[Mink] > Len) {
                    Sumf -= f[Mink][Last];
                    Sumf = (Sumf + Mod) % Mod;
                    ++Mink;
                }
                f[j][Now] = Sumf;
            }
            Sumf += f[j][Last];
            Sumf %= Mod;
        }
        Ans += f[n][Now];
        Ans %= Mod;
        Now ^= 1;
        Last = Now ^ 1;
    }
    printf("%d %d\n", Len, Ans);
    return 0;
}
