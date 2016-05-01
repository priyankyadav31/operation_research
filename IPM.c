#include <stdio.h>
#include <stdlib.h>

void copy(float a[][10],float b[][10],int m,int n){
  //copy b to a
  int i,j;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      a[i][j]=b[i][j];
    }
  }
}

void multiplication(float mult[][10],float a[][10],float b[][10],int r1,int c1,int r2,int c2){
  // Multiplying matrix a and b and storing in array mult.
    int i,j,k;
    for(i=0;i<r1;i++)
    	for(j=0;j<c2;j++){
      		mult[i][j]=0;
    	}
    for(i=0; i<r1;i++)
    for(j=0; j<c2;j++)
    for(k=0; k<c1;k++)
    {
        mult[i][j]+=a[i][k]*b[k][j];
    }
}

void print(float a[10][10],int m,int n){
  int i,j;
  for (i=0;i<m;i++){
    for(j=0;j<n;j++){
      printf("%f\t",a[i][j]);
    }
    printf("\n");
  }
}

void multiply(float c[][10],float a[][10],float b[][10], int n,int n2){
	//code to multiply two matrices a*b and store in c
	int i,j,k;
  for(i=0; i<n; i++)
    for(j=0; j<n2; j++)
      c[i][j]=0.0;
    for(i=0; i<n; i++)
      for(j=0; j<n2; j++)
        for(k=0; k<n; k++){
          c[i][j]=c[i][j]+(a[i][k]*b[k][j]);
    }
}

void createDiagonalMat(float b[10][10], float a[10][10],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
				b[i][j]=a[i][0];
			else
				b[i][j]=0.0;
		}
	}
	//printf("sfdfz\n");
	//print(b,n,n);
}

void diagonalInverse(float a[10][10],float b[10][10],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if((i==j)&&(b[i][j]!=0.0))
				a[i][j]=1.0/b[i][j];
		}
		//printf("%f,%f\n",a[i][i],b[i][i]);
	}
}

void transpose(float atrans[10][10],float a[10][10],int m,int n){
	//finds transpose of matrix
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			atrans[i][j]=a[j][i];
		}
	}
}

void extract_col(float a[][10],float c[][10],int n,int r){
	//extracts column r of a and stores in c
	int i;
	for (i=0;i<n;i++){
		c[i][0]=a[i][r];
	}
}
void replace_col(float a[][10],float b[][10],int n, int r){
  //replaces column r of b with column a
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(j==r)
	      b[i][j]=a[i][0];
      else if (j==i)
	      b[i][j]=1.0;
      else
	      b[i][j]=0.0;
    }
  }
}

void fact_multiply2(float a[][10], float c[][10], int n, float k, int r){
  //code to multiply matrix a by a factor k and store in c by simplex laws
	int i,j;
  for(i=0; i<n; i++)
      c[i][0]=0.0;

	for(i=0;i<n;i++){
		if(i==r)
			c[i][0]=1/k;
		else
			c[i][0]=-a[i][0]/k;
	}
}

void replace_col2(float a[][10],float b[][10], int n, int r){
  //replaces column r of b with column a
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(j==r)
	      b[i][j]=a[i][0];
    }
  }
}

void compute_inverse(float inv[][10], float a[][10], float b[][10],int n,int r){
  //a --> whose inverse is to be found and stored in matrix inv, b--> whose inverse is known
  float C[10][10],e[10][10],eta[10][10],E[10][10];
  int i;
  float k;
  for(i=0;i<n;i++){
    C[i][0]=a[i][r];
  }
 // printf("C is\n");
  //print1(C,n,1);
  //printf("INVERSE Matrix is\n");
  //print(b,n);
  multiply(e,b,C,n,1);
  //printf("e is\n");
  //print1(e,n,1);
  k=e[r][0];
  if(k==0.0){
    printf("The matrix is non-invertible\n");
    exit(0);
  }
  //printf("k is %f\t",k);
  fact_multiply2(e,eta,n,k,r);
  //printf("eta is\n");
  //print1(eta,n,1);
  replace_col(eta,E,n,r);
  multiply(inv,E,b,n,n);
}


void inverse(float b[10][10],float a[10][10], int n)
{
	int m,i,j,k,r=0;
	float mat[10][10],B[10][10],temp1[10][10],temp2[10][10],temp3[10][10],C[10][10];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(i==j)
				B[i][j]=1.0;
			else
				B[i][j]=0.0;
	copy(temp2,B,n,n);
  //printf("temp2 is\n");
  //print(temp2,n);
  	copy(temp3,B,n,n);
  	copy(mat,a,n,n);
  //printf("temp3 is\n");
  //print(temp3,n);
  	i=0;
  	for(r=0;r<n;r++){
    extract_col(mat,C,n,r);
    //print1(C,n,1);
    replace_col2(C,temp2,n,r);
    //printf("TEMP 2 is\n");
    //print(temp2,n);
    compute_inverse(temp1,temp2,temp3,n,r);
    //printf("INVERSE is\n");
    //print(temp1,n);
    copy(temp3,temp1,n,n);
    //print(temp3,n);
    //printf("\n");
  }
  copy(b,temp3,n,n);
}

void subtract(float a[10][10],float b[10][10],float c[10][10],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			a[i][j]=b[i][j]-c[i][j];
		}
	}
}
void add(float a[10][10],float b[10][10],float c[10][10],int m,int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			a[i][j]=b[i][j]+c[i][j];
		}
	}
}

float find_v(float a[10][10],int m,int n)
{
	int i,j;
	float min=a[0][0];
	for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				if((a[i][j]<=0.0)&&(a[i][j]<=min))
				{
					min=a[i][j];
				}
			}
		}
	if (min<0.0)
		return (-1.0*min);
	else return 0.0;
}
void fact_multiply(float a[][10], int m, int n, float k){
  //code to multiply matrix a by a factor k and store in c by simplex laws
	int i,j;
    for(i=0;i<m;i++)
    {
    	for(j=0;j<n;j++)
    	{
    		a[i][j]=a[i][j]*k;
    	}
    }
}
int check(float a[10][10],float b[10][10],int m,int n)
{
	int i,j;
	int count=0;
	float value;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			value=a[i][j]-b[i][j];
			if (value<0.0)
				value=-1.0*value;
			if(value<0.001)
				count++;
		}
	}
	if (count==m*n)
		return 1;
	else return 0;
}

void main(){
  	int n,m,i,j,k,r=0,type,n_temp,w=0;
	float X[10][10],X_tilda[10][10],X_new[10][10],X_tilda_new[10][10],C[10][10],C_tilda[10][10];
	float A[10][10],A_tilda[10][10],Atrans[10][10],b[10][10],Cp[10][10],D[10][10],Dinv[10][10];
	float I[10][10],P[10][10],z[10],zmax[10][10],zopt[10][10],temp[10][10],inv[10][10],temp1[10][10];
	float mew,alpha=0.5;
	int stop=0;
 	printf("Enter number of equations\n");
 	scanf("%d",&m);
 	printf("Enter number of variables\n");
 	scanf("%d",&n);
 	n_temp=n;
 	for(i=0;i<m;i++){
     	for(j=0;j<n+m;j++){
       	A[i][j]=0.0;
     	}
   	}
 	for(i=0;i<m;i++){
    printf("Equation %d :\n",i+1);
    printf("Enter 1 for type_1, 2 for type_2, 3 for type_3 : ");
    scanf("%d",&type);
    printf("Enter coefficients of Equation %d\n",i+1);
    for(j=0;j<n;j++){
      scanf("%f",&A[i][j]);
    }
    if (type==1){
      A[i][n_temp]=1;
      n_temp=n_temp+1;
    }
   }
  	printf("Enter right hand side values in order\n");
  	for(i=0;i<m;i++)
   		scanf("%f",&b[i][0]);
  	printf("Enter the maximizing function (a1x1+a2x2+...)\n");
	for (i=0;i<n;i++){
 		scanf("%f",&C[i][0]);
	}
	for(i=0;i<n_temp;i++){
		for(j=0;j<n_temp;j++){
   		if (j==i)
     		I[i][j]=1.0;
   		else
     		I[i][j]=0.0;
    	}
	}


	printf("Enter the initial assumption\n");
	for(i=0;i<n_temp;i++)
	{
		scanf("%f",&X[i][0]);
	}
	copy(X_new,X,n_temp,1);

	while(stop!=1)
	{
	w++;
	copy(X,X_new,n_temp,1);
	printf("X is\n");
	print(X,n_temp,1);
	printf("Diagonal Mat is\n");
	createDiagonalMat(D,X,n_temp);
	print(D,n_temp,n_temp);
	inverse(Dinv,D,n_temp);
	printf("Diagonal Inverse is\n");
	print(Dinv,n_temp,n_temp);
	multiplication(X_tilda,Dinv,X,n_temp,n_temp,n_temp,1);
	printf("X tilda is\n");
	print(X_tilda,n_temp,1);
	multiplication(A_tilda,A,D,m,n_temp,n_temp,n_temp);
	printf("A tilda is\n");
	print(A_tilda,m,n_temp);
	multiplication(C_tilda,D,C,n_temp,n_temp,n_temp,1);
	printf("C tilda is\n");
	print(C_tilda,n_temp,1);
	transpose(Atrans,A_tilda,m,n_temp);
	printf("A transpose is\n");
	print(Atrans,n_temp,m);
    multiplication(temp,A_tilda,Atrans,m,n_temp,n_temp,m);
    inverse(inv,temp,m);
    multiplication(temp,Atrans,inv,n_temp,m,m,m);
    multiplication(temp1,temp,A_tilda,n_temp,m,m,n_temp);
    subtract(P,I,temp1,n_temp,n_temp);
    printf("P is\n");
	print(P,n_temp,n_temp);
    multiplication(Cp,P,C_tilda,n_temp,n_temp,n_temp,1);
    printf("Cp is\n");
	print(Cp,n_temp,1);
    mew=find_v(Cp,n_temp,1);
    if(mew==0.0)
    {
    	printf("Exiting\n");
    	exit(0);
    }
    fact_multiply(Cp,n_temp,1,(alpha/mew));
    add(X_tilda_new,X_tilda,Cp,n_temp,1);
    multiplication(X_new,D,X_tilda_new,n_temp,n_temp,n_temp,1);
    stop=check(X_new,X,n_temp,1);
    printf("Iteration %d\n",w);
    print(X_new,n_temp,1);
	}

	printf("Optimum solution is\n");
	for(i=0;i<n_temp;i++)
	{
		printf("X[%d] = %f\n",i+1,X_new[i][0]);
	}
}