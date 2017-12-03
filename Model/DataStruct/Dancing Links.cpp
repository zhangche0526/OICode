class DLX
{
	int n,sz;
	int ncnt[MAXC];
	int row[MAXNODE],col[MAXNODE];
	int L[MAXNODE],R[MAXNODE],U[MAXNODE],D[MAXNODE];
	int ans[MAXR],acnt;
	void rm(int c)//remove
	{
		L[R[c]]=L[c];
		R[L[c]]=R[c];
		int i,j;
		for(i=D[c];i!=c;i=D[i])
			for(j=R[i];j!=i;j=R[j])
				U[D[j]]=U[j],D[U[j]]=D[j],ncnt[col[j]]--;
	}

	void rstr(int c)//restore
	{
		int i,j;
		for(i=U[c];i!=c;i=U[i])
			for(j=L[i];j!=i;j=L[j])
				U[D[j]]=j,D[U[j]]=j,ncnt[col[j]]++;
		L[R[c]]=c;
		R[L[c]]=c;
	}

	bool dfs(int lv)
	{
		if(!R[0])
		{acnt=lv;return true;}
		int i,j;
		int c=R[0];
		for(i=R[0];i;i=R[i])
			if(ncnt[i]<ncnt[c]) c=i;
		rm(c);
		for(i=D[c];i!=c;i=D[i])
		{
			ans[lv]=row[i];
			for(j=R[i];j!=i;j=R[j]) rm(col[j]);
			if(dfs(lv+1)) return true;
			for(j=L[i];j!=i;j=L[j]) rstr(col[j]);
		}
		rstr(c);
		return false;
	}
public:
	DLX(int n=0):n(n)
	{
		for(int i=0;i<=n;i++)
			U[i]=D[i]=i,L[i]=i-1,R[i]=i+1;
		R[n]=0,L[0]=n;
		sz=n+1;
		memset(ncnt,0,sizeof(ncnt));
	}

	void addRow(int r,std::vector<int> cv)
	{
		int fir=sz;
		for(int i=0;i<cv.size();i++)
		{
			int c=cv[i];
			L[sz]=sz-1,R[sz]=sz+1,D[sz]=c,U[sz]=U[c];
			D[U[c]]=sz;U[c]=sz;
			row[sz]=r,col[sz]=c;
			ncnt[c]++,sz++;
		}
		R[sz-1]=fir,L[fir]=sz-1;
	}

	bool solve(std::vector<int> &v)
	{
		v.clear();
		if(!dfs(0)) return false;
		for(int i=0;i<acnt;i++) v.push_back(ans[i]);
		return true;
	}
};
