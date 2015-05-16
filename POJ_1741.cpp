#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)<(b)?(a):(b))
#define MAXN 10010
#define MAXM 20010
typedef long long LL;

int eCnt, fir[MAXN]; struct edge{int v, w, nxt;} eg[MAXM];
int n, k, ans, q[MAXN], size[MAXN], maxx[MAXN], vis[MAXN], dis[MAXN];

void addedge(int u, int v, int w){
    eg[++eCnt].v = v; eg[eCnt].w = w;
    eg[eCnt].nxt = fir[u]; fir[u] = eCnt;
}
void init(){
    eCnt = ans = 0;
    for (int i = 0; i <= n; i++){
        vis[i] = fir[i] = 0;
    }
}
/*找出树的重心*/
int bfs_root(int u){
    int h = 1, t = 1, ret = 0; maxx[0] = INF;
    q[t] = u; maxx[u] = 0; size[u] = 1; vis[u] = 2;
    for ( ; h <= t; h++){
        for (int u = q[h], e = fir[u]; e != 0; e = eg[e].nxt){
            if (!vis[eg[e].v]){
                vis[eg[e].v] = 2;
                q[++t] = eg[e].v;
                size[eg[e].v] = 1;
                maxx[eg[e].v] = 0;
            }
        }
    }
    for (h--; h > 0; h--){
        int u = q[h];
        vis[u] = 0;
        for (int e = fir[u]; e != 0; e = eg[e].nxt){
            if (!vis[eg[e].v]){
                size[u] += size[eg[e].v];
                maxx[u] = max(maxx[u], size[eg[e].v]);
            }
        }
        maxx[u] = max(t-size[u], maxx[u]);
        if (maxx[u] < maxx[ret]) ret = u;
    }
    return ret;
}
/*预处理root到子节点的距离*/
int dfs_dis(int u){
    int h = 1, t = 1;
    q[t] = u; dis[t] = 0; vis[u] = 2;
    for ( ; h <= t; h++){
        for (int u = q[h], e = fir[u]; e != 0; e = eg[e].nxt){
            if (!vis[eg[e].v]){
                vis[eg[e].v] = 2;
                q[++t] = eg[e].v;
                dis[t] = dis[h] + eg[e].w;
            }
        }
    }
    for (h = 1; h <= t; h++) vis[q[h]] = 0;
    return t;
}
/*计算满足长度小于k且经过u的路径的数量，且路径可以不合法*/
int dfs_calc(int u, int k){
    int num = dfs_dis(u), ret = 0;
    sort(dis+1, dis+1+num);
    for (int i = 1, j = num; i < j; i++){
        for ( ; dis[i] + dis[j] > k; j--)
            if (i == j) break;
        ret += j - i;
    }
    return ret;
}
/*点分治*/
void dfs(int u){
    int root = bfs_root(u);
    ans += dfs_calc(root, k);
    vis[root] = 1;
    for (int e = fir[root]; e != 0; e = eg[e].nxt){
        int v = eg[e].v;
        if (vis[v]) continue;
        ans -= dfs_calc(v, k-eg[e].w*2);
        dfs(v);
    }
}
int main(){
    int u, v, w;
    for ( ; ; ){
        init();
        scanf("%d%d", &n, &k);
        if (n == 0 && k == 0) break;
        for (int i = 1; i < n; i++){
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        dfs(1);
        printf("%d\n", ans);
    }
    return 0;
}