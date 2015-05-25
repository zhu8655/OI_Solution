#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 50010;
const int INF = 0x7777777f;
const LL MOD = 100003;
inline LL read() {
	LL x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}/*====================Template====================*/
LL n, m;

LL pow(LL a, LL b){
	LL q = 1;
	for ( ; b > 0; b >>= 1){
		if (b & 1) q = (q * a) % MOD;
		a = (a * a) % MOD;
	} return q;
}
int main() {
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	
	m = read(); n = read();
	LL tmp1 = pow(m, n), tmp2 = m*pow(m-1, n-1)%MOD;
	printf("%lld", (tmp1-tmp2+MOD)%MOD);
	
	return 0;
}