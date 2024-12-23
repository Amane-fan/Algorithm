std::vector<int> pre_function(std::string t) {
    int m = t.size();
    std::vector<int> pi(m);
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && t[i] != t[j]) j = pi[j - 1];
        if (t[i] == t[j]) j++;
        pi[i] = j;
    }
    return pi;
}

std::vector<int> KMP(std::string s,std::string t) {
    int n = s.size(),m = t.size();
    std::vector<int> pi = pre_function(t);
    std::vector<int> res;
    for (int i = 0,j = 0; i < n; i++) {
        while (j > 0 && s[i] != t[j]) j = pi[j - 1];
        if (s[i] == t[j]) j++;
        if (j == m) {
            res.push_back(i - j + 1);
            j = pi[j - 1];
        }
    }
    return res;
}