#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 10010;
const int INF = 0x7777777f;
/*===============Template===============*/
int n, m, K, eCnt, d, visable[110][25], f[110];
int e[400][2], fir[25], nxt[400];
int q[10000], vis[25], dis[25];

void addEdge(int U, int V, int W, int E) {
	e[E*2-1][0] = V; e[E*2-1][1] = W; nxt[E*2-1] = fir[U]; fir[U] = E*2-1;
	e[E*2][0] = U; e[E*2][1] = W; nxt[E*2] = fir[V]; fir[V] = E*2;
}
int SPFA(int L, int R) {
	for (int i = 2; i <= m; i++) {vis[i] = 0; dis[i] = INF;}
	for (int i = L; i <= R; i++)
		for (int j = 1; j <= m; j++)
			if (visable[i][j]) vis[j] = 2;
	int h = 0, t = 1; q[t] = 1; dis[1] = 0;
	while (h < t) {
		int U = q[++h]; vis[U] = 0;
		for (int E = fir[U]; E; E = nxt[E]) {
			int V = e[E][0];
			if (vis[V] != 2 && dis[V] > dis[U]+e[E][1]) {
				dis[V] = dis[U]+e[E][1];
				if (vis[V] == 0) {
					vis[V] = 1; q[++t] = V;
				}
			}
		}
	}
	return dis[m];
}
int main(){
	int u, v, w, l, r;
	
	scanf("%d%d%d%d",&n, &m, &K, &eCnt);
	for (int i = 1; i <= eCnt; i++) {
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w, i);
	}
	scanf("%d", &d);
	for (int i = 1; i <= d; i++) {
		scanf("%d%d%d", &u, &l, &r);
		for (int j = l; j <= r; j++) visable[j][u] = 1;
	}
	
	for (int i = 1; i <= n; i++) {
		f[i] = SPFA(1, i);
		if (f[i] < INF) f[i] *= i;
		for (int j = 1; j < i; j++) {
			int cost = SPFA(j+1, i);
			if (cost == INF) continue;
			f[i] = min(f[i], f[j]+cost*(i-j)+K);
		}
	}
	
	printf("%d", f[n]);
	return 0;
}