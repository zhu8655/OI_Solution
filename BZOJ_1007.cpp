#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 50010;
const int INF = 0x7777777f;
inline LL read() {
	LL x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}/*====================Template====================*/
LL n, s[MAXN], tot = 0, x[MAXN];
struct node {LL k , b, x;} a[MAXN];

bool cmp(node U, node V) {
	if (U.k < V.k) return true;
	if (U.k > V.k) return false;
	return U.b >= V.b;
}
bool judge(int x) {return (a[s[tot]].b-a[x].b)*(a[s[tot]].k-a[s[tot-1]].k)-(a[s[tot-1]].b-a[s[tot]].b)*(a[x].k-a[s[tot]].k) <= 0;}
int main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		a[i].k = read();
		a[i].b = read();
		a[i].x = i;
	}
	sort(a+1, a+1+n, cmp);
	s[++tot] = 1; s[++tot] = 2;
	for (int i = 3; i <= n; i++) {
		while (judge(i) && tot > 1) tot--;
		s[++tot] = i;
	}
	for (int i = 1; i <= tot; i++) x[i] = a[s[i]].x; sort(x+1, x+1+tot);
	
	for (int i = 1; i <= tot; i++) printf("%lld ", x[i]);
	return 0;
}