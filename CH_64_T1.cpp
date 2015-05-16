#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100100;
const int INF = 0x7777777f;
const LL P = 1e9+7;
const LL PP = 1e10;
/*===============Template===============*/
int n, x[MAXN];
LL w[18][2];

int main(){
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d",&x[i]);
	
	for (int i = 0; i < n; i++) {
		int tmp = i, j = 1;
		while (j <= 17) {
			w[j][tmp & 1] += x[i];
			tmp >>= 1; j++;
		}
	}
	for (int i = 0; i < n; i++) {
		int tmp = i, j = 1;
		LL ans = 0;
		while (j <= 17) {
			ans = (ans+w[j][!(tmp & 1)])%P;
			tmp >>= 1; j++;
		}
		printf("%d ", ans);
	}
	
	return 0;
}