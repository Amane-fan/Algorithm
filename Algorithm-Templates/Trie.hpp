struct Trie {
    struct Node {
        int cnt;
        array<int,26> ch;
        Node(): cnt(0), ch{} {}
    };
    vector<Node> t;
    Trie() {
        init();
    }
    void init() {
       newNode();
    }
    int newNode() {
        t.push_back(Node());
        return t.size() - 1;
    }
    int get(char c) {
        return c - 'a';
    }
    void insert(const string &s) {
        int n = s.size();
        int p = 0;
        for (int i = 0; i < n; i++) {
            int u = get(s[i]);
            if (t[p].ch[u] == 0) {
                int k = newNode();
                t[p].ch[u] = k;
            }
            p = t[p].ch[u];
        }
        t[p].cnt++;
    }
    Node query(const string &s) {
        int n = s.size();
        int p = 0;
        for (int i = 0; i < n; i++) {
            int u = get(s[i]);
            if (t[p].ch[u] == 0) return Node();
            p = t[p].ch[u];
        }
        return t[p];
    }
};