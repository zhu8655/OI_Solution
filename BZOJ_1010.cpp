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
int n, L, h, t, q[MAXN];
LL s[MAXN], f[MAXN];

double slope(int U, int V) {return double(f[U]-f[V]+s[U]*s[U]-s[V]*s[V])/double(2*(s[U]-s[V]));}
int main(){
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	
	n = read(); L = read()+1;
	for (int i = 1; i <= n; i++) s[i] = s[i-1]+1+read();
	
	for (int i = 1; i <= n; i++) {
		while (h < t && slope(q[h], q[h+1]) < s[i]-L) h++;
		f[i] = f[q[h]]+(s[i]-s[q[h]]-L)*(s[i]-s[q[h]]-L);
		while (h < t && slope(q[t-1], q[t]) > slope(q[t], i)) t--; q[++t]=i;
	}
	
	printf("%lld", f[n]);
	return 0;
}