template<class Node>
struct Trie {
    Node* root;
    Trie() {
        root = new Node();
    }
    ~Trie() {
        deleteTree(root);
    }
    void deleteTree(Node* node) {
        if (node == nullptr) return;
        for (auto &e : node->trie) {
            deleteTree(e);
        }
        delete node;
    }
    void insert(string s) {
        int n = s.size();
        Node* p = root;
        for (int i = 0; i < n; i++) {
            int u = get(s[i]);
            if (p->trie[u] == nullptr) p->trie[u] = new Node();
            p = p->trie[u];
        }
        p->cnt++;
    }
    Node* query(string s) {
        int n = s.size();
        Node* p = root;
        for (int i = 0; i < n; i++) {
            int u = get(s[i]);
            if (p->trie[u] == nullptr) return nullptr;
            p = p->trie[u];
        }
        return p;
    }
    int get(char c) {
        return c - 'a';
    }
};

struct Node {
    int cnt;
    int ans;
    array<Node*, 26> trie;
    Node():cnt(0),ans(0) {
        fill(trie.begin(), trie.end(), nullptr);
    }
};