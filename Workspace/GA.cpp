
#include<stdio.h>          //调用输入输出函数所需要的头文件
#include<stdlib.h>         //调用随机函数所需要的头文件

typedef struct Chrom                           // 结构体类型，为单个染色体的结构；
{
	short int bit[6];
	int fit;
}chrom;                                        

void *evpop(chrom popcurrent[4]);              //定义将会用到的几个函数；
int x(chrom popcurrent);
int y(int x);
void *pickchroms(chrom popcurrent[4]);
void *crossover(chrom popnext[4]);
void *mutation(chrom popnext[4]);

int main()                                    // 主函数；
{
	int num;                                    // 迭代次数；
	int i,j,l,Max,k;
	Max=0;                                      // 函数最大值

	printf("\nWelcome to the Genetic Algorithm coded by Luay Al-wesi,editd by xujinpeng\n");  // introduction to the program，欢迎词；
	printf("The Algorithm is based on the function y = -x^2 + 5 to find the maximum value of the function.\n");

enter:printf("\nPlease enter the no. of iterations\n"); 
	  scanf("%d",&num);                           // 输入迭代次数，传送给参数num；

	  chrom popcurrent[4];                        // 初始种群规模为4；
	  chrom popnext[4];                           // 更新后种群规模仍为4；


	  if(num<1)                                   
		  goto enter;                                 // 判断输入的迭代次数是否为负或零，是的话重新输入；

	  evpop(popcurrent);                          // 随机产生初始种群；

	  for(i=0;i<num;i++)                          // 开始迭代；
	  {

		  printf("\ni = %d\n",i);                 // 输出当前迭代次数；

		  for(j=0;j<4;j++) 
		  {
			  popnext[j]=popcurrent[j];           // 更新种群；
		  }

		  pickchroms(popnext);                    // 挑选优秀个体；
		  crossover(popnext);                     // 交叉得到新个体；
		  mutation(popnext);                      // 变异得到新个体；

		  for(j=0;j<4;j++)  
		  {
			  popcurrent[j]=popnext[j];              // 种群更替； 
		  }

	  }                                           // 等待迭代终止；

	  for(l=0;l<3;l++)
	  {
		  if(popcurrent[l].fit > Max)
		  {
			  Max=popcurrent[l].fit;
			  k=l;
		  }

	  }
	  printf("\n f(%d)=%d",k,Max);

	  return 0;
}                                              



void *evpop(chrom popcurrent[4])               // 函数：随机生成初始种群；
{
	int i,j,value;
	int random;
	for(j=0;j<4;j++)                            // 从种群中的第1个染色体到第4个染色体
	{
		for(i=0;i<6;i++)                       // 从染色体的第1个基因位到第6个基因位
		{
			random=rand();                     // 产生一个随机值
			random=(random%2);                 // 随机产生0或者1
			popcurrent[j].bit[i]=random;       // 随机产生染色体上每一个基因位的值，0或1；
		}   

		value=x(popcurrent[j]);                // 将二进制换算为十进制，得到一个整数值；
		popcurrent[j].fit=y(x(popcurrent[j])); // 计算染色体的适应度值；
		printf("\n popcurrent[%d]=%d%d%d%d%d%d  value=%d  fitness = %d",j,popcurrent[j].bit[5],popcurrent[j].bit[4],popcurrent[j].bit[3],popcurrent[j].bit[2],popcurrent[j].bit[1],popcurrent[j].bit[0],value,popcurrent[j].fit);  
		// 输出整条染色体的编码情况，

	}                                                                        
	return(0);                 
}                                        


int x(chrom popcurrent)                        // 函数：将二进制换算为十进制；
{
   int z;
   z=(popcurrent.bit[0]*1)+(popcurrent.bit[1]*2)+(popcurrent.bit[2]*4)+(popcurrent.bit[3]*8)+(popcurrent.bit[4]*16);

   if(popcurrent.bit[5]==1)
   {
       z=z*(-1);                               // 考虑到符号；
   }

   return(z);                            
}                                      
 
int y(int x)                                   // 函数：求个体的适应度；
{
    int y;
    y=5*x*x*x*x+2*x*x*x+10*x*x+7*x+2;                              // 目标函数： y= - ( x^ 2 ) +5；
    return(y);              
}                                     

void *pickchroms(chrom popcurrent[4])          // 函数：选择个体；
{
    int i,j;
    chrom temp;                                // 中间变量

    for(i=0;i<3;i++)                           // 根据个体适应度来排序；（冒泡法）
	{
		for(j=0;j<3;j++)
         {
             if(popcurrent[j+1].fit>popcurrent[j].fit)
               {
                 temp=popcurrent[j+1];
                 popcurrent[j+1]=popcurrent[j];
                 popcurrent[j]=temp;

               }   
         }                
	}
    for(i=0;i<4;i++)
	{
        printf("\nSorting:popnext[%d] fitness=%d",i,popcurrent[i].fit); 
        printf("\n");                      
	}
    return(0);
}                                          

void *crossover(chrom popnext[4])              // 函数：交叉操作；
{

    int random;
    int i;
    random=rand();                             // 随机产生交叉点；
    random=((random%5)+1);                     // 交叉点控制在1到5之间；
    for(i=0;i<random;i++)                    
    {
        popnext[2].bit[i]=popnext[0].bit[i];   // child 1 cross over
        popnext[3].bit[i]=popnext[1].bit[i];   // child 2 cross over
    } 

    for(i=random;i<6;i++)                      // crossing the bits beyond the cross point index
    {
       popnext[2].bit[i]=popnext[1].bit[i];    // child 1 cross over
       popnext[3].bit[i]=popnext[0].bit[i];    // chlid 2 cross over
    }   

    for(i=0;i<4;i++)
	{
       popnext[i].fit=y(x(popnext[i]));        // 为新个体计算适应度值；
	}

    for(i=0;i<4;i++) 
	{
       printf("\nCrossOver popnext[%d]=%d%d%d%d%d%d    value=%d    fitness = %d",i,popnext[i].bit[5],popnext[i].bit[4],popnext[i].bit[3],popnext[i].bit[2],popnext[i].bit[1],popnext[i].bit[0],x(popnext[i]),popnext[i].fit);  
                                               // 输出新个体；
	}
    return(0);
}                                           

void *mutation(chrom popnext[4])               // 函数：变异操作；
{
  
   int random;
   int row,col,value;                                      
   random=rand()%50;                           // 随机产生0到49之间的数；

   if(random==25)                              // random==25的概率只有2%，即变异率为0.02；
   {
      col=rand()%6;                            // 随机产生要变异的基因位号；
      row=rand()%4;                            // 随机产生要变异的染色体号；
      
      if(popnext[row].bit[col]==0)             // 1变为0；
	  {
		  popnext[row].bit[col]=1 ;
	  }
      else if(popnext[row].bit[col]==1)        // 0变为1；
	  {
		  popnext[row].bit[col]=0;
	  }
      popnext[row].fit=y(x(popnext[row]));     // 计算变异后的适应度值；
      value=x(popnext[row]);
      printf("\nMutation occured in popnext[%d] bit[%d]:=%d%d%d%d%d%d    value=%d   fitness=%d",row,col,popnext[row].bit[5],popnext[row].bit[4],popnext[row].bit[3],popnext[row].bit[2],popnext[row].bit[1],popnext[row].bit[0],value,popnext[row].fit);

                                               // 输出变异后的新个体；
   }                                           
 
   return(0);
}   
