//just create one PTree for all the test cases and reset everytime
struct PTree{
    //// N should be set so that N >= max_string_length + 5
	int S[N],nx[N];
	int head[N],nxt[N],ch[N];
    int link[N],len[N],cnt[N],lst,nd,n,e;
    ll total;
    PTree(){reset();}
	inline int newnode(int L){
		cnt[nd]=0,len[nd]=L,head[nd]=0;
		return nd++;
	}
	//O(1)
	inline void reset(){
		total=e=nd=n=0,lst=1;
		newnode(0),newnode(-1);
		S[0]=-1,link[0]=1;
	}
	inline int getLink(int v){
		while(S[n-len[v]-1]!=S[n]) v=link[v];
		return v;
	}
	inline void add(int c){
		S[++n]=c;
		int cur=getLink(lst),i,j;
		for(i=head[cur];i;i=nxt[i]) if(nx[i]==c) break;
		if(!i){
			int now=newnode(len[cur]+2);
			int x=getLink(link[cur]);
			for(j=head[x];j;j=nxt[j]) if(nx[j]==c) break;
			if(j) link[now]=ch[j];else link[now]=0;
			nxt[++e]=head[cur];
			head[cur]=e;
			nx[e]=c;ch[e]=now;
			cnt[now]=cnt[link[now]]+1;
			lst=now;
		}else lst=ch[i];
        total+=cnt[lst];
	}
};