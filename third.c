#include<stdio.h>
#include<stdlib.h>

void transpose(int S, int D, double** X, double** XT)
{
for(int i=0;i<S;i++)
    {   
      for(int j=0; j<D;j++)
	{
	  XT[j][i]=X[i][j];
	}
    }
}

void print(int S,int D,double** Z)
{
  for(int i=0;i<S;i++)
    {    for(int j=0; j<D;j++)
	{
	  printf("%lf\t",Z[i][j]);
	}
      printf("\n");
    }
}

void inverse(int S, double** XTX, double** INV,double** XTXINV)
{
  double t;
  int i,j;
  int k;
  for(i=0;i<S;i++)
    {
      for(j=0;j<2*S;j++)
	{
	  if(j==(i+S))
	    INV[i][j]=1;
	  else if(j>=S)
	    INV[i][j]=0;
	  else if(j<S)
	    INV[i][j]=XTX[i][j];
	}
    } 

  // print(S,2*S,INV);
  //printf("\n");

  for(i=0;i<S;i++)
  {
    for(j=0;j<S;j++)
      {	if(j!=i)
	  {
	    t=INV[j][i]/INV[i][i];
	    for(k=0;k<S*2;k++)
	      {
		INV[j][k]=INV[j][k]-INV[i][k] * t;
	      }  	    
	  }}
  }



  //print(S,2*S,INV);
  //printf("\n");

  for(i=0;i<S;i++)
  {
    t=INV[i][i];
    for(j=0;j<2*S;j++)
    {
    	 INV[i][j]=INV[i][j]/t;
    }
  }

  // print(S,2*S,INV);
  // printf("\n");

  for(i=0;i<S;i++)
  {
   for(j=S;j<2*S;j++)
     {
  	 XTXINV[i][j-S]=INV[i][j];
     }
  }
   // print(S,S,XTXINV);
  //  printf("\n");
}



int main(int argc, char** argv)
{
 
  if(argc<3)
    return 0;

  FILE* fp = fopen(argv[1],"r");
  if(fp == NULL)
    return 0;

  FILE* fq = fopen(argv[2],"r");
  if(fq==NULL)
    return 0;

  int K;
  fscanf(fp,"%d\n",&K);
  int P=K+1;

  int N;
  fscanf(fp,"%d\n",&N);

  int K2=2*P;

  int M;
  fscanf(fq,"%d\n",&M);

  int i,j;
 int k;

 // double Y[N][1];
 double **Y;
 Y=malloc(N*sizeof(double*));
 for(i=0;i<N;i++)
   Y[i]=malloc(1*sizeof(double));

 // double X[N][P];
 double **X;
 X=malloc(N*sizeof(double*));
 for(i=0;i<N;i++)
   X[i]=malloc(P*sizeof(double));

 //double XT[P][N];
 double **XT;
 XT=malloc(P*sizeof(double*));
 for(i=0;i<P;i++)
   XT[i]=malloc(N*sizeof(double));

 //double XTX[P][P];
 double **XTX;
 XTX=malloc(P*sizeof(double*));
 for(i=0;i<P;i++)
   XTX[i]=malloc(P*sizeof(double));

 // double INV[P][K2];
 double **INV;
 INV=malloc((P)*sizeof(double*));
 for(i=0;i<P;i++)
   INV[i]=malloc(K2*sizeof(double));

 //double XTXINV[P][P];
 double **XTXINV;
 XTXINV=malloc(P*sizeof(double*));
 for(i=0;i<P;i++)
   XTXINV[i]=malloc(P*sizeof(double));

 //double XTXINVXT[P][N];
 double **XTXINVXT;
 XTXINVXT=malloc(P*sizeof(double*));
 for(i=0;i<P;i++)
   XTXINVXT[i]=malloc(N*sizeof(double));
  
  //double W[P][1];
 double **W;
 W=malloc(P*sizeof(double*));
 for(i=0;i<P;i++)
   W[i]=malloc(1*sizeof(double));

  for(i=0;i<N;i++)
    {
      for(j=0;j<=P;j++)
	{
	  if(j==P)
	    fscanf(fp,"%lf",&Y[i][0]);
	  else if(j==0)
	    X[i][j]=1;
	  else
	  fscanf(fp,"%lf,",&X[i][j]);
	}
      fscanf(fp,"\n");
    }
  //		 printf("X\n");
		 // print(N,P,X);
  // printf("\n");
  //		 printf("Y\n");
  // print(N,1,Y);

  transpose(N,P,X,XT);
  
  // printf("XTX\n");

  for(i=0;i<P;i++)
    {
      for(j=0;j<P;j++)
	{
	  for(k=0;k<N;k++)
	    {
	      XTX[i][j]+=XT[i][k]*X[k][j];
	    }
	}
    }
  
  // print(P,P,XTX);
  // printf("\n");

  inverse(P,XTX,INV,XTXINV);
  
  // printf("XTXINV\n");
  // print(P,P,XTXINV);
  //printf("\n");

for(i=0;i<P;i++)
  {
    for(j=0;j<N;j++)
	{
	  for(k=0;k<P;k++)
	    {
	      XTXINVXT[i][j]+=XTXINV[i][k]*XT[k][j];
	    }
	}
  }
//print(P,N,XTXINVXT);
//printf("\n");
  
for(i=0;i<P;i++)
  {
    for(j=0;j<1;j++)
	{
	  for(k=0;k<N;k++)
	    {
	      W[i][j]+=XTXINVXT[i][k]*Y[k][j];
	    }
	}
  }
  
//print(P,1,W);
//printf("\n");

 double **test1;
 test1=malloc(P*sizeof(double*));
 for(i=0;i<P;i++)
   test1[i]=malloc(P*sizeof(double));

 for(i=0;i<P;i++)
   {
     for(j=0;j<P;j++)
       {
	 for(k=0;k<P;k++)
	   {
	     test1[i][j]+=XTX[i][k]*XTXINV[k][j];
	   }
       }
   }
 //print(P,P,test1);


 double **test;
 test=malloc(M*sizeof(double*));
 for(i=0;i<M;i++)
   test[i]=malloc(P*sizeof(double));


 for(i=0;i<M;i++)
   {
   for(j=0;j<P;j++)
     {
       if(j==0)
	 test[i][j]=1;
       else
       fscanf(fq,"%lf,",&test[i][j]);
     }
   fscanf(fq,"\n");
   }
 // print(M,P,test);

 
 double sum=0;
 for(j=0;j<M;j++)
   {
     for(i=0;i<K+1;i++)
       {
	 sum=sum+(W[i][0]*test[j][i]);
       }
     printf("%0.0lf\n",sum);
     sum=0;
   }

 free(X);

 free(XT);

 free(XTX);

 free(XTXINV);

 free(INV);

 free(XTXINVXT);

 free(W);

 free(Y);

 free(test);
 
  fclose(fp);
  fclose(fq);

  return 0;
}
