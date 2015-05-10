#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 10010;
const int INF = 0x7777777f;
/*===============Template===============*/
int n;
const int d[] = {1, 10, 100, 1000};
struct bignum {
	int len, num[MAXN];
	void init(const char *s) {
		len = 0; int tmp = 0, j = 0;
		for (int i = strlen(s)-1; i >= 0; i--) {
			tmp += d[j++]*(s[i]-'0');
			if (j == 4) {num[++len] = tmp; tmp = 0; j = 0;}
		}
		if (tmp) num[++len] = tmp;
	}
	void print() {
		printf("%d", num[len]);
		for (int i = len-1; i >= 1; i--) {
			if (num[i]<1000) printf("0");
			if (num[i]<100) printf("0");
			if (num[i]<10) printf("0");
			if (num[i]<1) printf("0");
			printf("%d", num[i]);
		}
		printf("\n");
	}
} a[3];
bignum mul(bignum a) {
	int cnt = 0;
	for (int i = 1; i <= a.len; i++) {
		a.num[i] = a.num[i]*3+cnt;
		cnt = a.num[i]/10000; a.num[i] %= 10000;
	}
	if (cnt) a.num[++a.len] = cnt; return a;
}
bignum sub(bignum a, const bignum &b) {
	int cnt = 0;
	a.num[1] += 2;
	for (int i = 1; a.num[i] > 10000; i++) {
		a.num[i] %= 10000;
		a.num[i+1] += 1;
	}
	if (a.num[a.len]) a.len++;
	for (int i = 1; i <= a.len; i++) {
		a.num[i] = a.num[i]-b.num[i]+cnt;
		if (a.num[i]<0) {
			a.num[i] = 10000+a.num[i];
			cnt = -1;
		}
		else cnt = 0;
	}
	if (!a.num[a.len]) a.len--; return a;
}

int main(){
	int now[] = {2, 1, 0};
	a[0].init("1"); a[1].init("5");
	
	scanf("%d", &n);
	if (n==1) {printf("1"); return 0;}
	if (n==2) {printf("5"); return 0;}
	for (int i = 3; i <= n; i++) {
		a[now[0]] = sub(mul(a[now[1]]), a[now[2]]);
		now[0] = (now[0]+1)%3;
		now[1] = (now[1]+1)%3;
		now[2] = (now[2]+1)%3;
	}
	
	a[now[1]].print();
	return 0;
}