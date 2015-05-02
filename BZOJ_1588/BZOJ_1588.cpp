#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define lowbit(a) ((a)&(-a))
#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)<(b)?(a):(b))
#define ab(a) ((a)>(0)?(a):(-a))
#define MAXN 100010
#define INF 0x777777f
typedef long long LL;
/*===============Template===============*/
int n;
int root, tail, f[MAXN], s[MAXN][2];
int key[MAXN], sz[MAXN];
int newnode(int X){
	int U = ++tail;
	f[U] = s[U][0] = s[U][1] = 0;
	key[U] = X; sz[U] = 1; return U;
}
void link(int U, int S, int V){
	s[U][S] = V; if (V) f[V] = U;
}
void update(int U){
	sz[U] = 1 + (s[U][0] ? sz[s[U][0]] : 0) + (s[U][1] ? sz[s[U][1]] : 0);
}
void rot(int U){
	int F = f[U], FF = f[F];
	if (s[F][0] == U){
		link(F, 0, s[U][1]);
		link(U, 1, F);
	}
	else{
		link(F, 1, s[U][0]);
		link(U, 0, F);
	}
	update(F);
	if (FF)
		link(FF, s[FF][1] == F, U);
	else{
		f[U] = 0; root = U;
	}
}
void splay(int U, int TAR){
	int F = f[U], FF = f[F];
	for (; F != TAR&&FF != TAR; F = f[U], FF = f[F]){
		if ((s[FF][0] == F) && (s[F][0] == U)){
			rot(F); rot(U);
		}
		else{
			rot(U); rot(U);
		}
	}
	if (F != TAR) rot(U); update(U);
}
void ins(int X){
	if (!root){
		root = newnode(X); return;
	}
	int U = root, V;
	while(U){
		V = U;
		U = s[U][key[U] < X];
	}
	U = newnode(X);
	link(V, key[V] < X, U);
	splay(U, 0);
}
int prev(){
	int U = s[root][0];
	if (!U) return 0;
	while (s[U][1]) U = s[U][1];
	return U;
}
int succ(){
	int U = s[root][1];
	if (!U) return 0;
	while (s[U][0]) U = s[U][0];
	return U;
}


int main(){
	int i, x, ans, tmp1, tmp2;
	scanf("%d", &n); scanf("%d", &ans); ins(ans);
	for (i = 2; i <= n; i++){
		x = 0;
		scanf("%d", &x); ins(x);
		tmp1 = prev();
		tmp2 = succ();
		if (!tmp1) { ans += ab((x - key[tmp2])); continue; }
		if (!tmp2) { ans += ab((x - key[tmp1])); continue; }
		ans += min(ab((x - key[tmp1])), ab((x - key[tmp2])));
	}
	printf("%d", ans);
	return 0;
}