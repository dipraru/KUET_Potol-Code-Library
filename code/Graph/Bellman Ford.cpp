void bellman()
{
    for(int i=0;i<n;i++)
    {
        for(int node=1;node<=n;node++)
        {
            for(auto adj_node:adj_list[node])
            {
                int u=node;
                int v=adj_node.first;
                int w=adj_node.second;
                if(d[v]>d[u]+w)
                {
                    d[v]=d[u]+w;
                    parent[v]=u;
                    if(i==n-1) negative_cycle=true,selected_node=v;
                }
            }
        }
    }
}