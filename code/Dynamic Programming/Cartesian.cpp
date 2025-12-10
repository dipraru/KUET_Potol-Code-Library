// Build a max-heap Cartesian tree over `h[0..n-1]`.
// Returns the index of the root.
// Outputs left-child in L[], right-child in R[].
int buildCartesianTree(const vector<int> &h, vector<int> &L, vector<int> &R)
{
    int n = h.size();
    L.assign(n, -1);
    R.assign(n, -1);
    vector<int> parent(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++)
    {
        int last = -1;
        while (!st.empty() && h[st.top()] < h[i])
        {
            last = st.top();
            st.pop();
        }
        if (!st.empty())
        {
            parent[i] = st.top();
            R[st.top()] = i;
        }
        if (last != -1)
        {
            parent[last] = i;
            L[i] = last;
        }
        st.push(i);
    }
    int root = -1;
    for (int i = 0; i < n; i++)
    {
        if (parent[i] == -1)
        {
            root = i;
            break;
        }
    }
    return root;
}
