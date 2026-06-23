template<typename T>
class forest : public graph<T> {
    public:
    using graph<T>:: adj;
    using graph<T>:: edges;
    using graph<T>:: n;
    forest(int _n = 0) : graph<T>(_n){}
    int add(int from, int to, T cost = 1){
        int id = (int) edges.size();
        assert(id < n - 1);
        adj[from].push_back(id);
        adj[to].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }
};