#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 50010;
const int INF = 0x7777777f;
inline int read() {
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}/*====================Template====================*/
int n, m, MOD, a[25];
int next[25], mt[25][25], pre[25][25];

void prep() {
	int j = 0;
	for (int i = 2; i <= m; i++) {
		while (j > 0 && a[j+1] != a[i]) j = next[j];
		if (a[j+1] == a[i]) j++;
		next[i] = j;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j <= 9; j++) {
			int k = i;
			while (k > 0 && a[k+1] != j) k = next[k];
			if (a[k+1] == j) k++;
			if (k < m) pre[i][k] = (pre[i][k]+1)%MOD;
		}
	}
	mt[0][0] = 1;
}
void mul(int a[25][25], int b[25][25], int ans[25][25]) {
	int tmp[25][25];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			tmp[i][j] = 0;
			for (int k = 0; k < m; k++)
				tmp[i][j] = (tmp[i][j]+a[i][k]*b[k][j])%MOD;
		}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			ans[i][j] = tmp[i][j];
}
int main() {
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	
	n = read(); m = read(); MOD = read();
	for (int i = 1; i <= m; i++) a[i] = getchar()-'0'; prep();
	
	while (n) {
		if (n&1) mul(mt, pre, mt);
		mul(pre, pre, pre);
		n >>= 1;
	}
	
	int ans = 0;
	for (int i = 0; i < m; i++) ans = (ans+mt[0][i])%MOD;
	printf("%d", ans);
	return 0;
}