void floyd()
{
    for(int k=1;k<=n;k++)
        for(int u=1;u<=n;u++)
            for(int v=1;v<=n;v++) d[u][v]=min(d[u][k]+d[k][v], d[u][v]);
}