int p[2*N];
void manacher (string s)
{
    int n=s.size();
    char ss[2*n+2];
    ss[2*n+1]='\0';
    for(int i=0; i<2*n+1; i++)
    {
        p[i]=0;
        if(i%2==0)ss[i]='#';
        else ss[i]=s[i/2];
    }
    int l = 0, r = 0;
    for(int i = 0; i <=2*n; i++)
    {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while((p[i]+i<=2*n)&&(i-p[i]>=0)&&(ss[i - p[i]] == ss[i + p[i]]))
        {
            p[i]++;
        }
        if(i + p[i] > r)
        {
            l = i - p[i], r = i + p[i];
        }
    }
}
bool check(int l,int r)
{
    return p[l+r+1]>r-l;
}
