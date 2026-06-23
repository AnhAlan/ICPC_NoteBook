template<typename T>
class digraph : public graph<T> {
    public:
    using graph<T>:: adj;
    using graph<T>:: edges;
    using graph<T>:: n;
    digraph(int _n = 0) : graph<T>(_n){}
    int add(int from, int to, T cost = 1){
        int id = (int) edges.size();
        adj[from].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }
};