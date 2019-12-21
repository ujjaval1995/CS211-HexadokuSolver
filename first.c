#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int solve(char hexa[16][16]);
//int unassigned(int hexa[16][16], int row, int col);
int safe(char hexa[16][16],int row, int col, char num);
int usedRow(char hexa[16][16], int row, char num);
int usedCol(char hexa[16][16], int col, char num);
int usedSquare(char hexa[16][16], int rowStart, int colStart, char num);
void print(char hexa[16][16]);






int usedRow(char hexa[16][16], int row, char num){
 for(int g=0;g<16;g++)
    if(hexa[row][g]==num)
	return 1;
  return 0;
}

int usedCol(char hexa[16][16], int col, char num){
for(int m=0; m<16;m++)
if(hexa[m][col]==num)
	return 1;
  return 0;
}

int usedSquare(char hexa[16][16], int rowStart, int colStart, char num)
{
  for(int p=0; p<4;p++)
    for(int q= 0; q<4;q++)
	if(hexa[p+rowStart][q+colStart]==num)
	  return 1;
return 0;
}

int safe(char hexa[16][16], int row, int col, char num)
{
  return !usedRow(hexa,row,num) && !usedCol(hexa,col,num) && !usedSquare(hexa, row-row%4, col-col%4, num);
} 



  void print(char hexa[16][16])
  {
    for(int i=0;i<16;i++)
      {
	for(int j=0; j<16;j++)
	  {
	    printf("%c",hexa[i][j]);
	    printf("\t");
	      }
	printf("\n");
      }
  }
      
  int solve(char hexa[16][16])
{
 for(int i=0;i<16;i++)
{
for(int j=0; j<16; j++)
{ if(hexa[i][j]=='G')
    return 0;
}
}
return 1;
}
// if(!unassigned(hexa[][]))
     //   return 1;

// for(int num=0; num<=; num++)
//  {
//	if(safe(hexa,row,col,num))
//	  {
//	    hexa[row][col]=num;
//	 
//	    if(solve(hexa))
//	      return 1;
//
//	    hexa[row][col]= -1;
//	  }
//	  
//  }
//	return 0;
//}

int main(int argc, char** argv)
{
  //char s[256];
  int i,j,k;
 
  char value[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  if(argc<2)
    return 0;

  FILE* fp=fopen(argv[1],"r");
  if(fp==NULL)
    return 0;

  char hexaGrid[16][16];

 
  for(i=0;i<16;i++)
    {
      for(j=0;j<16;j++)
	{
	  fscanf(fp,"%c",&hexaGrid[i][j]);
	  fscanf(fp,"\t");
	 
	  if(hexaGrid[i][j]=='-')
	  hexaGrid[i][j]='G';
	  
	}
      fscanf(fp,"\n");
    }
  //  print(hexaGrid);
  // printf("\n");

  int n=0;
  do{
    
    for(i=0;i<16;i++)
      {
	for(j=0;j<16;j++)
	  {
	    if(hexaGrid[i][j]=='G')
	      {
		for(k=0;k<16;k++)
		  {
		   
		    if(safe(hexaGrid,i,j,value[k]))
		      hexaGrid[i][j]=value[k];
		    
		  }
	      }
	  }
      }
 n++;
  }
    while( n!=1);

  int count[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  if(solve(hexaGrid) == 1)
    {
      for(i=0;i<16;i++)
	{for(j=0;j<16;j++)
	    { for(k=0;k<16;k++)
		{
		  if(hexaGrid[j][k]==value[i])
		    count[i]++;
	
		}
	    }
	}
      for(i=0;i<16;i++)
	if(count[i]!=16)
	  {
	    printf("no-solution");
	    return 0;
	  }
  print(hexaGrid);
    }
else
  printf("no-solution\n");


 fclose(fp);

 return 0;
}






