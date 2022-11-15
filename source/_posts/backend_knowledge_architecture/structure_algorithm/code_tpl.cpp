int qsm(int m, int k, int p) {
    int res = 1 % p; int t = m;
    while (k) {
        if (k & 1) res = res * t % p;
        t = t * t % p; k >>= 1;
    }
    return res;
}
void quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j) {
        do {i++;} while (a[i] < x)
        do {j--;} while (a[j] > x)
        if (i < j) std::swap(a[i], a[j]);
    }
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}
int tmp[];
void merge_sort(int q[], int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (q[i] <= q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];
    for (int i = l, j = 0; j < k; ++j; i++) q[i] = tmp[j];
}
int bsearch(int q[], int l, int r) {
    while (l < r){
        int mid = l + r >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return r;
}
int bsearch(int q[], int l, int r) {
    while (l < r ){
        int mid  = l + r + 1 >> 1;
        if (check(mid)) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }

    return r;
}


S[i] = a[1] + a[2] + ... a[i]
a[l] + ... + a[r] = S[r] - S[l - 1]

S[i, j] = 第i行j列格子左上部分所有元素的和

以(x1, y1)为左上角，(x2, y2)为右下角的子矩阵的和为：
S[x2, y2] - S[x1 - 1, y2] - S[x2, y1 - 1] + S[x1 - 1, y1 - 1]

给区间[l, r]中的每个数加上c：B[l] += c, B[r + 1] -= c

给以(x1, y1)为左上角，(x2, y2)为右下角的子矩阵中的所有元素加上c：
S[x1, y1] += c, S[x2 + 1, y1] -= c, S[x1, y2 + 1] -= c, S[x2 + 1, y2 + 1] += c

求n的第k位数字: n >> k & 1
返回n的最后一位1：lowbit(n) = n & -n

//双指针
for (int i = 0, j = 0; i < n; i ++ )
{
    while (j < i && check(i, j)) j ++ ;

    // 具体问题的逻辑
}

常见模型：【右边更大/小，从左到右递减/增；左边更大/小，从右到左递减/增】
int tt = 0;
for (int i = 1; i <= n; i ++ )
{
    while (tt && check(stk[tt], i)) tt -- ;
    stk[ ++ tt] = i;
}

常见模型：找出滑动窗口中的最大值/最小值
int hh = 0, tt = -1;
for (int i = 0; i < n; i ++ )
{
    while (hh <= tt && check_out(q[hh])) hh ++ ;  // 判断队头是否滑出窗口
    while (hh <= tt && check(q[tt], i)) tt -- ;
    q[ ++ tt] = i;
}

常见问题分类：
    (1) 对于一个序列，用两个指针维护一段区间
    (2) 对于两个序列，维护某种次序，比如归并排序中合并两个有序序列的操作

vector<int> alls; // 存储所有待离散化的值
sort(alls.begin(), alls.end()); // 将所有值排序
alls.erase(unique(alls.begin(), alls.end()), alls.end());   // 去掉重复元素

// 二分求出x对应的离散化的值
int find(int x) // 找到第一个大于等于x的位置
{
    int l = 0, r = alls.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1; // 映射到1, 2, ...n
}

void merge(vector<PII> &segs){// 将所有存在交集的区间合并
    vector<PII> res;
    sort(segs.begin(), segs.end());
    int st = -2e9, ed = -2e9;
    for (auto seg : segs)
        if (ed < seg.first) {
            if (st != -2e9) res.push_back({st, ed});
            st = seg.first, ed = seg.second;
        }
        else ed = max(ed, seg.second);

    if (st != -2e9) res.push_back({st, ed});
    segs = res;
}

// head存储链表头，e[]存储节点的值，ne[]存储节点的next指针，idx表示当前用到了哪个节点
int head, e[N], ne[N], idx;
void init(){// 初始化
    head = -1; idx = 0;
}
void insert(int a) {// 在链表头插入一个数a
    e[idx] = a, ne[idx] = head, head = idx ++ ;
}
void remove() {// 将头结点删除，需要保证头结点存在
    head = ne[head];
}

int e[N], l[N], r[N], idx;// e[]表示节点的值，l[]表示节点的左指针，r[]表示节点的右指针，idx表示当前用到了哪个节点
// 初始化
void init(){
    //0是左端点，1是右端点
    r[0] = 1, l[1] = 0; idx = 2;}
void insert(int a, int x) {// 在节点a的右边插入一个数x
    e[idx] = x; l[idx] = a, r[idx] = r[a]; l[r[a]] = idx, r[a] = idx ++ ;}
void remove(int a){// 删除节点a
    l[r[a]] = l[a]; r[l[a]] = r[a];
}

int stk[N], tt = 0;// tt表示栈顶
stk[ ++ tt] = x;// 向栈顶插入一个数
tt -- ;// 从栈顶弹出一个数
stk[tt];// 栈顶的值
if (tt > 0)// 判断栈是否为空

//队列
int q[N], hh = 0, tt = -1;// hh 表示队头，tt表示队尾
q[ ++ tt] = x;// 向队尾插入一个数
hh ++ ;// 从队头弹出一个数
q[hh];// 队头的值
if (hh <= tt)// 判断队列是否为空

//循环队列
int q[N], hh = 0, tt = 0;// hh 表示队头，tt表示队尾的后一个位
q[tt ++ ] = x; if (tt == N) tt = 0;// 向队尾插入一个数
hh ++ ; if (hh == N) hh = 0;// 从队头弹出一个数
q[hh];// 队头的值
if (hh != tt)// 判断队列是否为空

const int N = 100010;
int p[N];
int find(int x) {
    if (x != p[x]) p[x] = find[p[x]]
    return p[x];
}
int use() {
    //init
    for (int i = 0; i < N; ++i) q[i] = i;
    //merge
    int a, b;
    p[find(a)] = find(b);
}
//hash 
int h[N], ne[N], e[N], idx;
void init() {
    memset(h, sizeof(h), -1);
}
void add(int x) {
    int k = hash(x);
    e[idx] = x; ne[idx] = h[k]; h[k] = idx++;
}
bool find(int x) {
    int k = hash(x);
    for (int i = h[k]; i != -1; i = ne[i]) {
        if (x == e[i]) return true;
    }
    return false;
}

//heap
int h[N]; //h[1]是堆顶
for (int i = n / 2; i; i--) down(i);
void up(int u) {
    while (u / 2 && h[u / 2] > h[u]) {
        swap(h[u], h[u / 2]; u >>= 1;
    }
}
void down(int u) {
    int t = u;
    if (u * 2 <= size && h[u * 2] < h[t]) t = u * 2;
    if (u * 2 + 1 <= size && t[u * 2 + 1] < h[t]) t = 2 * u + 1;
    if (u != t ){
        swap(h[u], h[t]); down(t);
    }
}

//trie
int son[N][26], cnt[N], idx;
//添加新的字符串
void add(char* str) {
    int p = 0;
    for (int i = 0; str[i]; ++i) {
       int u =  str[i] - 'a';
       if !son[p][u] son[p][u] = ++idx;
       p = son[p][u];
    }
    cnt[p]++;
}
//返回str出现次数
int query(const char* str) {
    int p = 0;
    for (int i = 0; str[i]; ++i) {
        int u = str[i] - 'a';
        if !son[p][u] return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int dfs(int u)
{
    st[u] = true; // st[u] 表示点u已经被遍历过

    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j]) dfs(j);
    }
}

queue<int> q;
st[1] = true; // 表示1号点已经被遍历过
q.push(1);

while (q.size())
{
    int t = q.front();
    q.pop();

    for (int i = h[t]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            st[j] = true; // 表示点j已经被遍历过
            q.push(j);
        }
    }
}

bool topsort()
{
    int hh = 0, tt = -1;
    // d[i] 存储点i的入度
    for (int i = 1; i <= n; i ++ )
        if (!d[i])
            q[ ++ tt] = i;
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (-- d[j] == 0)
                q[ ++ tt] = j;
        }
    }
    // 如果所有点都入队了，说明存在拓扑序列；否则不存在拓扑序列。
    return tt == n - 1;
}

// 求1号点到n号点的最短路，如果不存在则返回-1
int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for (int i = 0; i < n - 1; i ++ )
    {
        int t = -1;     // 在还未确定最短路的点中，寻找距离最小的点
        for (int j = 1; j <= n; j ++ )
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;

        // 用t更新其他点的距离
        for (int j = 1; j <= n; j ++ )
            dist[j] = min(dist[j], dist[t] + g[t][j]);

        st[t] = true;
    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

typedef pair<int, int> PII;

int n;      // 点的数量
int h[N], w[N], e[N], ne[N], idx;       // 邻接表存储所有边
int dist[N];        // 存储所有点到1号点的距离
bool st[N];     // 存储每个点的最短距离是否已确定

// 求1号点到n号点的最短距离，如果不存在，则返回-1
int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});      // first存储距离，second存储节点编号

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;

        if (st[ver]) continue;
        st[ver] = true;

        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > distance + w[i])
            {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

// s[]是长文本，p[]是模式串，n是s的长度，m是p的长度
求模式串的Next数组：
for (int i = 2, j = 0; i <= m; i ++ ) {
    while (j && p[i] != p[j + 1]) j = ne[j];
    if (p[i] == p[j + 1]) j ++ ;
    ne[i] = j;
}
// 匹配
for (int i = 1, j = 0; i <= n; i ++ ) {
    while (j && s[i] != p[j + 1]) j = ne[j];
    if (s[i] == p[j + 1]) j ++ ;
    if (j == m) {
        j = ne[j];// 匹配成功后的逻辑
    }
}