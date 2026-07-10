template<typename T>
class Graph{
    public:
    struct Edge{
        int from, to;
        T cost;
    };
    int n;
    vector<vector<int> > adj;
    vector<Edge> edges;
    Graph(int _n = 0) : n(_n){
        adj.resize(n + 1);
    }
    virtual int add(int from, int to, T cost = 1) = 0;
};
