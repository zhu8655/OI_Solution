#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define lowbit(a) ((a)&(-a))
#define MAXN 200100
#define INF 0x777777f
typedef long long LL;
/*===============Template===============*/
int n, minn, ans, delta;
int root, tail, f[MAXN], s[MAXN][2];
int key[MAXN], sz[MAXN], num[MAXN];
int newnode(int X){
	int U = ++tail;
	f[U] = s[U][0] = s[U][1] = 0;
	key[U] = X; sz[U] = 1; num[U] = 1; return U;
}
void link(int U, int S, int V){
	s[U][S] = V; if (V) f[V] = U;
}
void update(int U){
	sz[U] = num[U] + (s[U][0] ? sz[s[U][0]] : 0) + (s[U][1] ? sz[s[U][1]] : 0);
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
	if (FF){
		link(FF, s[FF][1] == F, U);
	}
	else{
		f[U] = 0;
		root = U;
	}
}
void splay(int U, int TAR){
	int F = f[U], FF = f[F];
	for (; F != TAR && FF != TAR; F = f[U], FF = f[F]){
		if ((s[FF][0] == F) == (s[F][0] == U)){
			rot(F); rot(U);
		}
		else{
			rot(U); rot(U);
		}
	}
	if (F != TAR) rot(U); update(U);
}
int find(int X){
	int U = root;
	while (U && key[U] != X)
		U = s[U][key[U]>X];
	if (U) splay(U, 0); return U;
}
void ins(int X){
	if (!root){
		root = newnode(X);
		return;
	}
	int U = root, V;

	while (U){
		if (key[U] == X){ num[U]++; update(U); splay(U, 0); return; }
		V = U;
		U = s[U][key[U]>X];
	}
	U = newnode(X);
	link(V, key[V]>X, U);
	splay(U, 0);
}
int findKth(int K){
	if (sz[root]<K) return 0;
	int U = root;
	while (K){
		if ((sz[s[U][0]]<K) && (sz[s[U][0]] + num[U] >= K)) break;
		if (sz[s[U][0]] <= K - 1){
			K -= sz[s[U][0]] + num[U];
			U = s[U][1];
		}
		else{
			U = s[U][0];
		}
	}
	if (U) splay(U, 0); return U;
}
int prev(){
	int U = s[root][0];
	if (!U) return 0;
	while (s[U][1]) U = s[U][1];
	splay(U, 0); return U;
}
int succ(){
	int U = s[root][1];
	if (!U) return 0;
	while (s[U][0]) U = s[U][0];
	splay(U, 0); return U;
}
void del(int L, int R){
	if (!find(L)) { ans--; ins(L); } int U = prev();
	if (!find(R)) { ans--; ins(R); } int V = succ();
	if (!U && !V){
		ans += sz[root];
		root = 0; return;
	}if (!U){
		ans += sz[s[root][0]];
		s[root][0] = 0;
		update(root); return;
	}if (!V){
		splay(U, 0);
		ans += sz[s[root][1]];
		s[root][1] = 0;
		update(root); return;
	}
	splay(U, V);
	ans += sz[s[U][1]];
	s[U][1] = 0;
	update(U); update(V);
}
int main(){
	int i, k, a;
	char c;

	scanf("%d%d", &n, &minn);
	for (i = 1; i <= n; i++){
		getchar(); c = getchar(); scanf("%d", &k);
		if (c == 'I'){
			if (k >= minn) ins(k - delta);
		}
		else if (c == 'A'){
			delta += k;
		}
		else if (c == 'S'){
			delta -= k;
			del(minn - delta - 1, -INF);
		}
		else{
			a = findKth(k);
			if (a == 0) printf("-1\n");
			else printf("%d\n", key[a] + delta);
		}
	}
	printf("%d", ans);
	return 0;
}