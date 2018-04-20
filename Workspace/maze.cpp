#include "maze.h"
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;

void findpath(int initialDeep, int T)
{
	srand(time(0));
	int dpt=initialDeep,la=-1;
	while(true)
	{
		int seq[3];for(int i=0;i<3;i++) seq[i]=i;
		int CNT=0;
		std::random_shuffle(seq,seq+3);
		for(int i=0;i<3;i++)
		{
			int d=seq[i];
			if(la==d) continue;
			if(move(d)) return;
			if(~la&&CNT==1) {dpt--,la=d;break;}
			if(CNT==2) {dpt--,la=d;break;}
			int ndpt=query();CNT++;
			if(ndpt>dpt) move(d);
			else {dpt=ndpt,la=d;break;}
		}
	}
}
