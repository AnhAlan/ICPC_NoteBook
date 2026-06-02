const int maxn = 1e6 + 5;
int n;
int a[maxn];
int leftC[maxn], rightC[maxn], par[maxn];
int buildCartesian(){
    stack<int> st;
    for(int i = 1; i <= n; i++){
        int last = 0;
        while(!st.empty() && a[st.top()] < a[i]){
            last = st.top();
            st.pop();
        }
        if(!st.empty()){
            rightC[st.top()] = i;
            par[i] = st.top();
        }
        if(last){
            leftC[i] = last;
            par[last] = i; 
        }
        st.push(i);
    }
    int root = 1;
    while(par[root]){
        root = par[root];
    }
    return root;
}
