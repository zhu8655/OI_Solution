#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 2000010;
const int MAXM = 6000000;
const int INF = 0x7777777f;
/*===============Template===============*/
int n, m, node[1010][1010][2];
struct Dijkstra{
	int hCnt, idx[MAXN][2];
	int nCnt, mCnt, fir[MAXN], nxt[MAXM], e[MAXM][2], dis[MAXN], vis[MAXN];
	
	void swim(int U) {
		int tmp = idx[U][0];
		for (int V = U>>1; V; U = V, V >>= 1) {
			if (dis[idx[V][0]] > dis[tmp]) {
				idx[U][0] = idx[V][0];
				idx[idx[U][0]][1] = U;
			}
			else break;
		}
		idx[U][0] = tmp; idx[idx[U][0]][1] = U;
	}
	void sink(int U) {
		int tmp = idx[U][0];
		for (int V = U<<1; V <= hCnt; U = V, V <<= 1) {
			if (V < hCnt && dis[idx[V][0]] > dis[idx[V+1][0]]) V++;
			if (dis[idx[V][0]] < dis[tmp]) {
				idx[U][0] = idx[V][0];
				idx[idx[U][0]][1] = U;
			}
			else break;
		}
		idx[U][0] = tmp; idx[idx[U][0]][1] = U;
	}
	void push(int P) {idx[++hCnt][0] = P; swim(hCnt);}
	void pop() {idx[1][0] = idx[hCnt][0]; hCnt--; sink(1);}
	inline void addEdge(int U, int V, int W) {
		e[++mCnt][0] = V; e[mCnt][1] = W; nxt[mCnt] = fir[U]; fir[U] = mCnt;
		e[++mCnt][0] = U; e[mCnt][1] = W; nxt[mCnt] = fir[V]; fir[V] = mCnt;
	}
	int solve(int S, int T) {
		for (int i = 1; i <= nCnt; i++) {dis[i] = INF; vis[i] = 0;} dis[S] = 0; vis[S] = 1;
		for (int E = fir[S]; E; E = nxt[E]) if (dis[e[E][0]] > e[E][1]) dis[e[E][0]] = e[E][1];
		for (int i = 1; i <= nCnt; i++) if (i != S) push(i);
		while (hCnt) {
			int U = idx[1][0]; pop(); vis[U] = 1;
			if (vis[T]) return dis[T];
			for (int E = fir[U]; E; E = nxt[E]) {
				int V = e[E][0]; if (vis[V]) continue;
				if (dis[V] > dis[U]+e[E][1]) {
					dis[V] = dis[U]+e[E][1];
					swim(idx[V][1]);
				}
			}
		}
	}
} dij;

int main(){
	int x;
	
	dij.nCnt = 1;
	scanf("%d%d", &n, &m);
	if (n == 1) {
		int ans = INF;
		for (int i = 1; i < m; i++) {
			scanf("%d", &x);
			if (ans > x) ans = x;
		}
		printf("%d", ans); return 0;
	}
	if (m == 1) {
		int ans = INF;
		for (int i = 1; i < n; i++) {
			scanf("%d", &x);
			if (ans > x) ans = x;
		}
		printf("%d", ans); return 0;
	}
	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++) {
			node[i][j][0] = ++dij.nCnt;
			node[i][j][1] = ++dij.nCnt;
		}
	dij.nCnt++;
	for (int i = 1; i < m; i++) {
		node[0][i][0] = 1;
		node[n][i][1] = dij.nCnt;
	}
	for (int i = 1; i < n; i++) {
		node[i][0][1] = dij.nCnt;
		node[i][m][0] = 1;
	}
	//处理行
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < m; j++) {
			scanf("%d", &x);
			dij.addEdge(node[i-1][j][0], node[i][j][1], x);
		}
	//处理列
	for (int i = 1; i < n; i++)
		for (int j = 1; j <= m; j++) {
			scanf("%d", &x);
			dij.addEdge(node[i][j-1][1], node[i][j][0], x);
		}
	//处理斜
	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++) {
			scanf("%d", &x);
			dij.addEdge(node[i][j][0], node[i][j][1], x);
		}
	
	printf("%d", dij.solve(1, dij.nCnt));
	return 0;
}