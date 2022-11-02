
int e[N];
int ne[N];
int h[N];
int idx;

void insert(int t) {
    int k = hash(t);
    e[idx] = t;
    ne[idx] = h[k];
    h[k] = idx++;
}

int find(int t) {
    int k = hash(t);
    for (int i = h[k]; i != -1; i = ne[i]) {
        if (e[i] == t) {
            return t;
        }
    }
    return -1;
}

int h[N], size;

void init() {
    for (int i = size / 2; i ; i--) down(i);
}

void down(int u) {
    int t = u;
    if (2 * u < size && h[2 * u] < h[u])  t = 2 * u;
    if (2 * u + 1 < size && h[2 * u + 1] < h[u]) t = 2 * u + 1;

    if (t != u) {
        swap(h[u], h[t]);
        down(t);
    }
}

void up(int u) {
    while (u / 2 && h[u] < h[u / 2]) {
        swap(h[u], h[u / 2]);
        u >> 1;
    }
}

    


