#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 110;
const int MAXP = 10010;
const int INF = 0x7777777f;
/*===============Template===============*/
int l, r, mid, ans;
int n, p, a[MAXN], b[MAXP], tot, sum[MAXP], waste;
 
int dfs(int Ak, int Bk) {
    if (Bk == 0) return 1;
    if (waste+sum[mid] > tot) return 0;
    int ok = 0;
    for (int i = Ak; i <= n; i++)
        if (a[i] >= b[Bk]) {
            a[i] -= b[Bk];
            if (a[i] < b[1]) waste += a[i];
            if (b[Bk] == b[Bk-1]) {
                if (dfs(i, Bk-1)) ok = 1;
            }
            else if (dfs(1, Bk-1)) ok = 1;
            if (a[i] < b[1]) waste -= a[i];
            a[i] += b[Bk];
            if (ok) return ok;
        }
    return 0;
}
int judge(int X) {
    waste = 0;
    if (dfs(1, X)) return 1;
    return 0;
}
int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", &a[i]); sort(a+1, a+1+n);
    scanf("%d", &p); for (int i = 1; i <= p; i++) scanf("%d", &b[i]); sort(b+1, b+1+p);
    for (int i = 1; i <= n; i++) tot += a[i];
    for (int i = 1; i <= p; i++) sum[i] = sum[i-1]+b[i];
 
    if (a[n] < b[1]) {
        printf("0");
        return 0;
    }
    l = 1, r = p;
    while (l <= r) {
        mid = (l+r)>>1;
        if (judge(mid)) {
            ans = mid;
            l = mid+1;
        }
        else r = mid-1;
    }
 
    printf("%d\n", ans);
    return 0;
}