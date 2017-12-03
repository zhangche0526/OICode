#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>

const int MAXC=1300,MAXR=4100,MAXNODE=17000;

class DLX
{
	int n,sz;
	int ncnt[MAXC];
	int row[MAXNODE],col[MAXNODE];
	int L[MAXNODE],R[MAXNODE],U[MAXNODE],D[MAXNODE];
	int ans[MAXR],acnt;
	void rm(int c)
	{
		L[R[c]]=L[c];
		R[L[c]]=R[c];
		int i,j;
		for(i=D[c];i!=c;i=D[i])
			for(j=R[i];j!=i;j=R[j])
				U[D[j]]=U[j],D[U[j]]=D[j],ncnt[col[j]]--;
	}

	void rstr(int c)
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

DLX solver(1024);

const int SLOT=0,ROW=1,COL=2,SUB=3;

int encode(int a,int b,int c){return a*256+b*16+c+1;}

void decode(int code,int &a,int &b,int &c)
{code--;c=code%16;code/=16;b=code%16;code/=16;a=code;}

char mp[16][20];
bool read()
{
	for(int i=0;i<16;i++)
		if(scanf("%s",mp[i])!=1)
			return false;
	return true;
}

int main()
{
	bool isFir=true;
	while(read())
	{
		int i;
		if(isFir) isFir=false;
		else putchar('\n');
		solver=DLX(1024);
		for(int r=0;r<16;r++)
			for(int c=0;c<16;c++)
				for(int v=0;v<16;v++)
					if(mp[r][c]=='-'||mp[r][c]=='A'+v)
					{
						std::vector<int> cv;
						cv.push_back(encode(SLOT,r,c));
						cv.push_back(encode(COL,r,v));
						cv.push_back(encode(ROW,c,v));
						cv.push_back(encode(SUB,(r/4)*4+c/4,v));
						solver.addRow(encode(r,c,v),cv);
					}
		static std::vector<int> ans;
		solver.solve(ans);
		for(i=0;i<ans.size();i++)
		{
			int r,c,v;
			decode(ans[i],r,c,v);
			mp[r][c]='A'+v;
		}
		for(i=0;i<16;i++) printf("%s\n",mp[i]);
	}
}
/*
--A----C-----O-I
-J--A-B-P-CGF-H-
--D--F-I-E----P-
-G-EL-H----M-J--
----E----C--G---
-I--K-GA-B---E-J
D-GP--J-F----A--
-E---C-B--DP--O-
E--F-M--D--L-K-A
-C--------O-I-L-
H-P-C--F-A--B---
---G-OD---J----H
K---J----H-A-P-L
--B--P--E--K--A-
-H--B--K--FI-C--
--F---C--D--H-N-

--A----C-----O-I
-J--A-B-P-CGF-H-
--D--F-I-E----P-
-G-EL-H----M-J--
----E----C--G---
-I--K-GA-B---E-J
D-GP--J-F----A--
-E---C-B--DP--O-
E--F-M--D--L-K-A
-C--------O-I-L-
H-P-C--F-A--B---
---G-OD---J----H
K---J----H-A-P-L
--B--P--E--K--A-
-H--B--K--FI-C--
--F---C--D--H-N-
*/
