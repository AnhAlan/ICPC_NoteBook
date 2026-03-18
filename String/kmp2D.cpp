//maxs <= 12000 for safe
const int maxns = 8005;
string s;
int kmp[maxns][maxns];
void build_kmp2d(){
    //kmp[l][r] : substr(l,r)
    s = "#" + s;
    int n = s.size() - 1;
    for(int i=1;i<=n;i++){
        int k = 0;
        for(int j=1;j<=n-i;j++){
            while(k && s[j+i] != s[k+i]){
                k = kmp[i][k-1];
            }
            if(s[j+i] == s[k+i]){
                ++k;
            }
            kmp[i][j] = k;
        }
    }
}