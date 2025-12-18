struct Node{
    int a;
    Node():a(0){}
    Node(int _a): a(_a){}
    friend Node merge(const Node &A, const Node &B)
    {
        return Node(((ll)A.a+B.a)%M);
    }
};
struct SegmentTree{
    //1 based string
    int n, base, M;
    int size;
    vector<Node> t;
    vector<ll> lazy;
    vector<bool> isLazy;
    oset<int> in;
    vector<int> pw;
    vector<int> inv;
    SegmentTree(int _n, int _base, int _M){init(_n, _base, _M);}
    void init(int _n, int _base, int _M)
    {
        n=_n, base=_base, M=_M;
        for(int i=1;i<=n;i++) in.insert(i);
        size=1;
        while(size<max(1ll,n)) size<<=1;
        t.assign(2*size,Node());
        lazy.assign(2*size,0);
        isLazy.assign(2*size,0);
        pw.resize(n+1,1);
        inv.resize(n+1,1);
        int finv=power(b1,M-2);
        for(int i=1;i<=n;i++) pw[i]=((ll)pw[i-1]*base)%M, inv[i]=((ll)inv[i-1]*finv)%M;
    }
    inline void pull(int nd){
        t[nd]=merge(t[nd<<1],t[nd<<1|1]);
    }
    inline void apply_node(int nd, int st, int en, ll val)
    {
        t[nd].a=((ll)t[nd].a*inv[val])%M;
        lazy[nd]=(lazy[nd]+val);
        isLazy[nd]=1;
    }
    inline void push(int nd, int st, int en)
    {
        if(!isLazy[nd] || nd>=size) return;
        int mid=(st+en)>>1;
        apply_node(nd<<1,st,mid,lazy[nd]);
        apply_node(nd<<1|1, mid+1, en, lazy[nd]);
        isLazy[nd]=0;
        lazy[nd]=0;
    }
    void update(int l, int r, int val) {update(1,1,size,l,r,val);}
    void update(int nd, int st, int en, int l, int r, ll val)
    {
        if(l>en || r<st) return;
        if(l<=st && en<=r){
            apply_node(nd,st,en,val);
            return;
        }
        push(nd,st,en);
        int mid=(st+en)>>1;
        update(nd<<1,st,mid,l,r,val);
        update(nd<<1|1, mid+1,en,l,r,val);
        pull(nd);
    }
    Node query(int l, int r){return query(1,1,size,l,r);}
    Node query(int nd, int st, int en, int l, int r){
        if(l>en || r<st) return Node();
        if(l<=st && en<=r) return t[nd];
        push(nd,st,en);
        int mid=(st+en)>>1;
        Node L=query(nd<<1,st,mid,l,r);
        Node R=query(nd<<1|1, mid+1, en, l, r);
        return merge(L,R);
    }
    void updatePoint(int p, ll v){updatePoint(1,1,size,p,v);}
    void updatePoint(int nd, int st, int en, int p, ll v)
    {
        if(st==en){
            t[nd]=Node(v);
            lazy[nd]=0;
            isLazy[nd]=0;
            return;
        }
        push(nd,st,en);
        int mid=(st+en)>>1;
        if(p<=mid) updatePoint(nd<<1,st,mid,p,v);
        else updatePoint(nd<<1|1,mid+1,en,p,v);
        pull(nd);
    }
    void updateIdx(int pos, char ch)
    {
        assert(pos>0 && pos<=in.size());
        int fache=*in.find_by_order(pos-1);
        updatePoint(fache,((ll)(ch+1007)*pw[in.size()-pos])%M);
    }
    void deleteIdx(int pos)
    {
        assert(pos>0 && pos<=in.size());
        int rpos=*in.find_by_order(pos-1);
        updatePoint(rpos,0);
        update(1,rpos,1);
        in.erase(rpos);
    }
    int range_hash(int l, int r)
    {
        assert(l>0 && r<=in.size());
        int ff=*in.find_by_order(l-1), fs=*in.find_by_order(r-1);
        ll hash=query(ff,fs).a;
        return (hash*inv[n-r])%M;
    }
};