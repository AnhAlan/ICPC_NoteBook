struct Kmp {
    string s, t;
    int lenS, lenT;
    vector<int> kmp;
    Kmp(string _s, string _t) {
        s = "#" + _s;
        t = "#" + _t;
        lenS = s.size() - 1;
        lenT = t.size() - 1;
        kmp.assign(lenS + 1, 0);
    }
    void build_kmp() {
        int k = 0;
        for (int i = 2; i <= lenS; i++) {
            while (k > 0 && s[i] != s[k + 1]) k = kmp[k];
            if (s[i] == s[k + 1]) ++k;
            kmp[i] = k;
        }
    }
    vector<int> match() {
        vector<int> ans;
        int k = 0;
        for (int i = 1; i <= lenT; i++) {
            while (k > 0 && t[i] != s[k + 1]) k = kmp[k];
            if (t[i] == s[k + 1]) ++k;
            if (k == lenS) {
                ans.push_back(i - lenS + 1);
                k = kmp[k];
            }
        }
        return ans;
    }
};
