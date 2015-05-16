#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define lowbit(a) ((a)&(-a))
#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)<(b)?(a):(b))
#define MAXN 16010
#define MAXM 110
#define INF 0x777777f
typedef long long LL;
/*===============Template===============*/
struct node{int l, p, s;} a[MAXM];
int n, m, le[MAXM], re[MAXM], q[MAXM], dp[MAXM][MAXN];
bool cmp(const node &a, const node &b){return a.s<b.s;}
void read(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i<=m; i++)
		scanf("%d%d%d", &a[i].l, &a[i].p, &a[i].s);
	sort(a+1, a+m+1, cmp);
	for(int i = 1; i<=m; i++){
		le[i] = max(0, a[i].s-a[i].l);		//�����߽�
		re[i] = min(n, a[i].s+a[i].l-1);	//����ұ߽�
	}
}
void work(){
	int i, j, l, p, s, h, t;
	
	for(i = 1; i<=m; i++){
		l = a[i].l;
		p = a[i].p;
		s = a[i].s;
		for(j = 0; j<=re[i]; j++)
			dp[i][j] = dp[i-1][j];			//��ת�Ƶ�i���˲�ˢ
		h = 1; t = 0;
		for(j = le[i]; j<a[i].s; j++){		//ά����������
			while(h<=t&&dp[i-1][j]-j*p>=dp[i-1][q[t]]-q[t]*p) t--;
			q[++t] = j;
		}
		for(j = s; j<=re[i]; j++){
			while(h<t&&j-q[h]>l) h++;		//�������Ͼ�pop
			dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
			dp[i][j] = max(dp[i][j], dp[i-1][q[h]]+(j-q[h])*p);
		}
		for(j = re[i]+1; j<=n; j++)
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
	}
	int ans = 0;
	for(int i = 1; i<=n; i++)
		ans = max(ans, dp[m][i]);
	printf("%d\n", ans);
}
int main(){
	read();
	work();
	return 0;
}