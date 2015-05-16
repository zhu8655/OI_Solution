#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define lowbit(a) ((a)&(-a))
#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)<(b)?(a):(b))
#define MAXN 100100
#define PI 3.1415926
#define E 2.718281828
#define INF 0x777777f
typedef long long LL;

struct tnode{
    int lc, rc, l, r; LL data, tag;
    void clear(){data = tag = lc = rc = 0;}
} tree[MAXN*4];
int n, m, tCnt; int a[MAXN];

/*建树*/
void build(tnode &p, int l, int r){
    p.l = l; p.r = r;
    if (l == r) {p.data = a[l]; return;}
    int mid = (l+r)>>1;
    p.lc = ++tCnt; build(tree[p.lc], l, mid);
    p.rc = ++tCnt; build(tree[p.rc], mid+1, r);
    /*update_p*/
        p.data = tree[p.lc].data+tree[p.rc].data;
    /*update_p*/
}
/*修改(l、r都在p的范围内)*/
void change(tnode &p, int l, int r, int v){
    /*update_p*/
        p.data += (r-l+1)*v;
        if (l==p.l && p.r==r) {p.tag += v; return;}
    /*update_p*/
    int mid = (p.l+p.r)>>1;
    if (r <= mid) {change(tree[p.lc], l, r, v); return;}            //全在左子树
    if (l >  mid) {change(tree[p.rc], l, r, v); return;}            //全在右子树
    change(tree[p.lc], l, mid, v); change(tree[p.rc], mid+1, r, v);    //越过中点
}
/*查询(注意返回类型，其他同上)*/
LL query(tnode &p, int l, int r){
    if (l==p.l && p.r==r) {return p.data;}
    int mid = (p.l+p.r)>>1; LL ret = (r-l+1)*p.tag;
    if (r <= mid) return ret+query(tree[p.lc], l, r);
    if (l >  mid) return ret+query(tree[p.rc], l, r);
    return ret+query(tree[p.lc], l, mid)+query(tree[p.rc], mid+1, r);
}
int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    tCnt = 1; build(tree[1], 1, n);
    char c = getchar(); int l, r, x;
    for (int i = 1; i <= m; i++){
        c = getchar();
        if (c=='C'){
            scanf("%d%d%d", &l, &r, &x);
            change(tree[1], l, r, x);
        }
        else {
            scanf("%d%d", &l, &r);
            printf("%I64d\n", query(tree[1], l, r));
        }
        getchar();
    }
    return 0;
}