int dcp(int st,int ed,int opt1,int opt2,int n)
{ if(st>ed)return opt1;
int mid=(st+ed)/2;
int opt=opt1;
ll anss=inf;
ll cost=ans(1,1,n,min(mid,opt2)+1,mid,mid);
for(int i=min(opt2,mid); i>=opt1; i--)
{
if(nxt[i]<=mid)cost=cost+nxt[i]-i;
if(cost+tem[i-1]<anss)
{ anss=cost+tem[i-1];
opt=i;
}
}
tk[mid]=anss;
if(st==ed)return opt;
opt1=dcp(st,mid-1,opt1,opt,n);
opt2=dcp(mid+1,ed,opt,opt2,n);
return opt2;
}
