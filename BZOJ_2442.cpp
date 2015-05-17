#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define lowbit(a) ((a)&(-a))
#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)<(b)?(a):(b))
#define MAXN 100100
#define INF 0x777777f
typedef long long LL;
/*===============Template===============*/
int n, m;
LL a[MAXN], sum[MAXN], dp[MAXN], q[MAXN], p[MAXN], ans;
void read(){
	int i;
	for(i = 1; i<=n; i++)
		scanf("%lld", &a[i]);
	for(i = 1; i<=n; i++)
		sum[i] = sum[i-1]+a[i];
}
void work(){
	int i, h, t;
	h = 1; t = 1; q[1] = 0; p[1] = -a[1];
	for(i = 1; i<=m; i++){
		dp[i] = sum[i];
		while(h<=t&&p[t]<=dp[i]-sum[i+1]) t--;
		q[++t] = i; p[t] = dp[i]-sum[i+1];
	}
	for(i = m+1; i<=n; i++){
		while(i-q[h]>m+1&&h<=t) h++;
		dp[i] = p[h]+sum[i];
		while(h<=t&&p[t]<=dp[i]-sum[i+1]) t--;
		q[++t] = i; p[t] = dp[i]-sum[i+1];
	}
	ans = 0;
	for(i = 1; i<=n; i++)
		ans = max(ans, dp[n]);
	printf("%lld\n", ans);
}
int main(){
	while(scanf("%d%d", &n, &m) == 2){
	        read();
	        work();
	    }
	return 0;
}
