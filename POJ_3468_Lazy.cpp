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

/*根据儿子的信息更新*/
inline void update(tnode &p){
    p.data = tree[p.lc].data + tree[p.rc].data;
}
/*根据父亲的tag更新(注意tag类型)*/
inline void update(tnode &p, LL tag){
    p.data += (p.r-p.l+1)*tag;
}
/*下传tag信息*/
inline void pushdown(tnode &p){
    if (!p.tag) return; if (p.l == p.r){p.tag = 0; return;}
    int mid = (p.l+p.r)>>1;
    if (p.lc) {tree[p.lc].tag += p.tag; update(tree[p.lc], p.tag);}
    if (p.rc) {tree[p.rc].tag += p.tag; update(tree[p.rc], p.tag);}
    p.tag = 0;
}
/*建树*/
void build(tnode &p, int l, int r){
    p.l = l; p.r = r;
    if (l == r) {p.data = a[l]; return;}
    int mid = (l+r)>>1;
    p.lc = ++tCnt; build(tree[p.lc], l, mid);
    p.rc = ++tCnt; build(tree[p.rc], mid+1, r);
    update(p);
}
/*修改*/
void change(tnode &p, int l, int r, int x){
    pushdown(p);
    if (l<=p.l && p.r<=r){p.tag = x; update(p, x); return;}
    int mid = (p.l+p.r)>>1;
    if (l <= mid) change(tree[p.lc], l, r, x);
    if (mid  < r) change(tree[p.rc], l, r, x);
    update(p);
}
/*查询(注意返回类型)*/
LL query(tnode &p, int l, int r){
    pushdown(p);
    if (l<=p.l && p.r<=r) {return p.data;}
    int mid = (p.l+p.r)>>1; LL ret = 0;
    if (l <= mid) ret += query(tree[p.lc], l, r);
    if (mid  < r) ret += query(tree[p.rc], l, r);
    return ret;
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