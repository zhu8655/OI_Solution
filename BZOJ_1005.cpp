#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1010;
const int INF = 0x7777777f;
/*===============Template===============*/
inline int read() {
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int n, d[MAXN], cnt = 0, tot = 0, sum = 0;
int p[MAXN], num[MAXN][MAXN], ans[MAXN];
int len = 1, a[100100];
void init() {
	int vis[1010]; p[0] = 0;
	for (int i = 2; i <= 1000; i++) vis[i] = 0;
	for (int i = 2; i <= 1000; i++) {
		if (!vis[i]) p[++p[0]] = i;
		for (int j = 1; j <= p[0]; j++) {
			if (i*p[j] > 1000) break;
			vis[i*p[j]] = 1;
			if (i%p[j] == 0) break;
		}
	}
	for (int i = 2; i <= 1000; i++) {
		for (int j = 1; j <= p[0]; j++) {
			int tmp = i;
			while (tmp%p[j] == 0) {
				num[i][j]++;
				tmp /= p[j];
			}
		}
	}
}
inline void add(int N, int X) {
	for (int i = 1; i <= p[0]; i++)
		ans[i] += N*num[X][i];
}
void mul(int X) {
	int tmp = 0;
	for (int i = 1; i <= len; i++) {
		a[i] = a[i]*X+tmp;
		tmp = a[i]/10;
		a[i] %= 10;
	}
	while (tmp) {
		a[++len] = tmp%10;
		tmp /= 10;
	}
}
int main() {
	init();
	n = read();
	for (int i = 1; i <= n; i++) {
		int x = read();
		if (!x) {printf("0"); return 0;}
		if (x == -1) cnt++;
		else {d[++tot] = x-1; sum += d[tot];}
	}
	if (sum > n-2) {printf("0"); return 0;}
	for (int i = n-1-sum; i <= n-2; i++) add(1, i); add(n-2-sum, cnt);
	for (int i = 1; i <= tot; i++)
		for (int j = 2; j <= d[i]; j++)
			add(-1, j);
	a[1] = 1;
	for (int i = 1; i <= p[0]; i++)
		for (int j = 1; j <= ans[i]; j++)
			mul(p[i]);
		
	for (int i = len; i >= 1; i--) printf("%d", a[i]);
	return 0;
}