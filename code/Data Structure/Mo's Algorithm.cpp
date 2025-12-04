//sort function
bool cmp(query a, query b)
{
    if(a.l/B != b.l/B) return a.l/B < b.l/B;
    return ((a.l / B) & 1) ? a.r > b.r : a.r < b.r;
}