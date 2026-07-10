struct Cartesian{
	int n;
	int root;
	vector<int> leftC, rightC, par;
	Cartesian(const vector<int> &_a){
		n = (int)_a.size() - 1;
		leftC.assign(n + 1, 0);
		rightC.assign(n + 1, 0);
		par.assign(n + 1, 0);
		stack<int> st;
		for(int i = 1; i <= n; i++){
			int last = 0;
			while(!st.empty() && _a[st.top()] < _a[i]){
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
		root = 1;
		while(par[root]){
			root = par[root];
		}
	}
};