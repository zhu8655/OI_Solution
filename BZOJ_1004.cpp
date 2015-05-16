#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100;
const int INF = 0x7777777f;
/*===============Template===============*/
int Sr, Sb, Sg, n, m, p, a[MAXN], ans = 0, rest = 0;
int vis[MAXN], r[MAXN], f[25][25][25];

int dfs(int U) {
	if (vis[U]) return 0;
	vis[U] = 1; return 1+dfs(a[U]);
}
int solve() {
	for (int i = 0; i <= Sr; i++)
		for (int j = 0; j <= Sb; j++)
			for (int k = 0; k <= Sg; k++)
				f[i][j][k] = 0;
	for (int i = 1; i <= n; i++) vis[i] = 0; r[0] = 0;
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		r[++r[0]] = dfs(i);
	}
	f[0][0][0] = 1;
	for (int o = 1; o <= r[0]; o++)
		for (int i = Sr; i >= 0; i--)
			for (int j = Sb; j >= 0; j--)
				for (int k = Sg; k >= 0; k--) {
					f[i][j][k] = 0;
					if (i >= r[o]) f[i][j][k] = (f[i][j][k]+f[i-r[o]][j][k])%p;
					if (j >= r[o]) f[i][j][k] = (f[i][j][k]+f[i][j-r[o]][k])%p;
					if (k >= r[o]) f[i][j][k] = (f[i][j][k]+f[i][j][k-r[o]])%p;
				}
	return f[Sr][Sb][Sg];
}
void exGcd(int a, int b, int &x, int &y) {
	if (b == 0) {x = 1; y = 0; return;}
	exGcd(b, a%b, x, y);
	int t = x; x = y; y = t-a/b*y;
}
int main() {
	scanf("%d%d%d%d%d", &Sr, &Sb, &Sg, &m, &p); n = Sr+Sb+Sg;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++)
			scanf("%d", &a[j]);
		ans = (ans+solve()) % p;
	}
	for (int i = 1; i <= n; i++) a[i] = i;
	ans = (ans+solve())%p;
	
	int x, y; m++;
	exgcd(m, p, x, y);
	while (x <= 0) x += p, y -= m;
	printf("%d", ans*x%p);
	return 0;
}
