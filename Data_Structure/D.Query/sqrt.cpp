int block; // block = sqrt(n)
struct Query{
    int l, r, id;
    Query(){}
    Query(int _l, int _r, int _id) : l(_l), r(_r), id(_id) {}
    bool operator < (const Query &other){
        int blockA = l / block;
        int blockB = other.l / block;
        if (blockA != blockB) return blockA < blockB;
        return r < other.r;
    }
};

