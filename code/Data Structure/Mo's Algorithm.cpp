class MoAlgorithm
{
public:
    struct Query
    {
        int l, r, idx;
    };
    MoAlgorithm(const vector<int> &array) : arr(array)
    {
        n = arr.size();
        distinctCount = 0;
        blockSize = static_cast<int>(sqrt(n));
    }
    void addQuery(int l, int r, int idx)
    {
        queries.push_back({l, r, idx});
    }
    vector<int> process()
    {
        int q = queries.size();
        vector<int> answers(q);
        sort(queries.begin(), queries.end(), [&](Query &a, Query &b)
             {
            int block_a = a.l / blockSize;
            int block_b = b.l / blockSize;
            if (block_a != block_b) 
                return block_a < block_b;
            return (block_a & 1) ? (a.r < b.r) : (a.r > b.r); });

        int currL = 0, currR = -1;
        for (const auto &query : queries)
        {
            while (currR < query.r) add(++currR);
            while (currR > query.r)remove(currR--);
            while (currL < query.l)remove(currL++);
            while (currL > query.l)add(--currL);
            answers[query.idx] = distinctCount;
        }
        return answers;
    }

private:
    vector<int> arr;
    vector<Query> queries;
    vector<int> freq = vector<int>(200005); // Dynamic frequency map
    int n, blockSize, distinctCount;
    void add(int pos)
    {
        int element = arr[pos];
        if (freq[element] == 0)distinctCount++;
        freq[element]++;
    }
    void remove(int pos)
    {
        int element = arr[pos];
        if (freq[element] == 1)distinctCount--;
        freq[element]--;
    }
};
