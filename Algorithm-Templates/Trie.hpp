const int N = 5e6 + 10;

int trie[N][26];
int cnt[N];
int idx = 0;

void insert(string &s) {
    int n = s.size();
    int p = 0;
    for (int i = 0; i < n; i++) {
        int u = s[i] - 'a';
        if (!trie[p][u]) trie[p][u] = ++idx;
        p = trie[p][u];
    }
    cnt[p]++;
}

int query(string &s) {
    int n = s.size();
    int p = 0;
    for (int i = 0; i < n; i++) {
        int u = s[i] - 'a';
        if (!trie[p][u]) return -1;
        p = trie[p][u];
    }
    return cnt[p];
}