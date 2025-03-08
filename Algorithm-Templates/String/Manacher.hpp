vector<int> Manacher(string s) {
    string t = " #";
    for (int i = 1; i < s.size(); i++) {
        t.push_back(s[i]);
        t.push_back('#');
    }

    int n = t.size() - 1;
    vector<int> d(n + 1);
    int C = 1, R = 1;
    for (int i = 1; i <= n; i++) {
        d[i] = min(d[C * 2 - i], R - i);
        if (i >= R) {
            d[i] = 0;
        }
        while (i + d[i] + 1 <= n && t[i + d[i] + 1] == t[i - d[i] - 1]) {
            d[i]++;
        }
        if (i + d[i] > R) {
            C = i;
            R = i + d[i];
        }
    }
    return d;
}

pair<int, int> getOdd(vector<int> &d, int i) {
    int l = (i * 2 - d[i * 2] + 1) / 2;
    int r = (i * 2 + d[i * 2] - 1) / 2;
    return make_pair(l, r);
}

pair<int, int> getEven(vector<int> &d, int i) {
    int l = (i * 2 + 1 - d[i * 2 + 1] + 1) / 2;
    int r = (i * 2 + 1 + d[i * 2 + 1] - 1) / 2;
    return make_pair(l, r);
}