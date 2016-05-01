#include <iostream>
#include <iomanip>
#include <limits>
#include <math.h>
#include <cmath> 

using namespace std;

void copymat(double A[][20],double B[][20],int row,int column)
{
     for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            B[i][j]=A[i][j];
}

void copycol(double A[][20],double B[][20],int row,int column,int c1,int c2)
{
	 for(int i=0;i<row;i++)
	     B[i][c2]=A[i][c1];
}

void printmat(double A[][20],int row,int column)
{
     int i,j;
     cout<<" "<<endl;
     for(i=0;i<row;i++)
     {
         for(j=0;j<column;j++)
         {   
             cout.width(14);
             cout.precision(5);
             cout<<A[i][j];
         }
         cout<<endl;
     } cout<<endl<<endl;
}

void matmul(double A[20][20],double B[20][20],double C[20][20],int r1,int c,int c2)
{
	 double temp;
	 int i,j,k;
	 for(i=0;i<r1;i++)
	     for(j=0;j<c2;j++)
	     {
	         temp=0;
	         for(k=0;k<c;k++)
	         {
	         	 temp+=A[i][k]*B[k][j];
	         }
	         C[i][j]=temp;
	     }
}

void product_form_inverse(double A[][20],int n)
{
	double B1[20][20],B[20][20],C[20][20],e[20][20],E1[20][20],E2[20][20],temp,l,m;
	int i,j,k;
	for(i=0;i<n;i++)
	    for(j=0;j<n;j++)
		{
		    if(i==j) B[i][j]=B1[i][j]=E2[i][j]=1;
		    else B[i][j]=B1[i][j]=E2[i][j]=0;
	    }
	copymat(B,E1,n,n);
	//printmat(A,n,n);
	for(i=0;i<n;i++)
	{
		copycol(A,B1,n,n,i,i);
		//printmat(B1,n,n);
		copycol(B1,C,n,n,i,0);
		matmul(E1,C,e,n,n,1);
		temp=-e[i][0];
		for(j=0;j<n;j++)
		{
			if(j==i) e[i][0]=1/e[i][0];
			else e[j][0]=e[j][0]/temp;
		}
	    copycol(e,E2,n,n,0,i);
	    matmul(E2,E1,C,n,n,n);
	    copymat(C,E1,n,n);
	    copymat(B,E2,n,n);
       // printmat(E1,n,n);
    }
     copymat(E1,A,n,n);
}

int negative(double A[20][20],int row,int col)
{   int neg=0,loc=-1;
    for(int i=0;i<row;i++)
    {
        if(A[i][0]<=neg)
        {
            neg=A[row-1][i];
            loc=i;
        }
    }
    return loc;
}

void putdiagonal(double A[][20],double X[][20],int size)
{
    int i,j;
    for(i=0;i<size;i++)
        A[i][i]=X[i][0];
}

void transpose(double A[][20],double B[][20],int row,int col)
{
    int i,j;
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
            B[j][i]=A[i][j];
}

void subtract(double A[][20],double B[][20],double C[][20],int row,int col)
{
    int i,j;
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
            C[i][j]=A[i][j]-B[i][j];
}

void addition(double A[][20],double B[][20],double C[][20],int row,int col)
{
    int i,j;
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
            C[i][j]=A[i][j]+B[i][j];
}

int main()
{
    int m,n,i,j,neg,k,flag0,sign[20][20],less=0,great=0,equal=0,ntemp=0,mtemp=0,temp1=0,temp2=0;
    double A[20][20],A1[20][20],X[20][20],v,max,tempM2[20][20],tempM3[20][20],I[20][20],min=100000,B[20][1],C[20][20],C1[20][20],X1[20][20],D[20][20],X2[20][20],Din[20][20],tempM1[20][20],P[20][20],temp=0;
    for(i=0;i<20;i++)
        for(j=0;j<20;j++)
        {
            A[i][j]=B[i][j]=C[i][j]=D[i][j]=P[i][j]=0;
            if(i==j)
               I[i][j]=1;
            else
               I[i][j]=0;

        }
    cout<<"ENTER THE NO OF EQUATIONS\n";
    cin>>m;
    cout<<"ENTER THE NUMBER OF VARIABLES\n";
    cin>>n;
    cout<<"ENTER THE LEFT EQUATION MATRIX\n";
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
           cin>>A[i][j];
    cout<<"ENTER THE RIGHT MATRIX\n";
    for(i=0;i<m;i++)
    {
        cin>>B[i][0];
        if(B[i][0]<min)
           min=B[i][0];
    }
    for(i=0;i<n;i++)
        X[i][0]=min/1000;
    cout<<"Press 1 for >=\nPress 0 for =\nPress -1 for <=\n";
    j=0;
    for(i=0;i<m;i++)
    {
       cin>>sign[i][0];
       temp=0;
       if(sign[i][0]==1)
       {  
          great++;
          A[i][n+j]=-1;
          X[n+j][0]=1;
          j++;
          A[i][n+j]=1;
          for(k=0;k<n;k++)
              temp+=(A[i][k]*X[k][0]);
          X[n+j][0]=B[i][0]+1-temp;
          j++;
       }
       else if(sign[i][0]==-1)
       {
           less++;
           A[i][n+j]=1;
           for(k=0;k<n;k++)
               temp+=(A[i][k]*X[k][0]);
           X[n+j][0]=B[i][0]-temp;
           j++;
       }
    }
    for(i=0;i<m;i++)
    {
        temp=0;
     	if(sign[i][0]==0)
        {  
           equal++;
           if(great>0)
           {
              A[i][n+j]=1;
              for(k=0;k<n;k++)
                  temp+=(A[i][k]*X[k][0]);
              X[n+j][0]=B[i][0]-temp;
              j++;
           }
        }
    }
    ntemp=n+j;
    mtemp=m;
    //X[0][0]=0.0005;X[1][0]=0.0005;X[2][0]=20.999;X[3][0]=26.998;X[4][0]=44.9965;X[5][0]=29.998;
    //X[0][0]=2;X[1][0]=2;X[2][0]=4;
    copymat(X,X1,ntemp,1);
    cout<<"ENTER C\n";
    for(i=0;i<n;i++)
    {
        cin>>C[i][0];
    }
    cout<<"Press 1 for max\nPress -1 for min\n";
    cin>>flag0;
    if(flag0==-1)
       for(i=0;i<n+great;i++)
       {
           C[i][0]=-1*C[i][0];
       }
    cout<<endl;
    cout<<"X = \n";
        printmat(X,ntemp,1);
    while(1)
    {
        max=0;
        copymat(X1,X,ntemp,1);
       // cout<<"X = \n";
       // printmat(X,ntemp,1);
        putdiagonal(D,X1,ntemp);
       // cout<<"D =\n";
       // printmat(D,ntemp,ntemp);
        copymat(D,Din,ntemp,ntemp);
        product_form_inverse(Din,ntemp);
        //cout<<"D (inverse) =\n";
       // printmat(Din,ntemp,ntemp);
        matmul(Din,X1,X2,ntemp,ntemp,1);
     //   cout<<"X~ =\n";
     //   printmat(X2,ntemp,1);
        matmul(A,D,tempM1,m,ntemp,ntemp);
        copymat(tempM1,A1,m,ntemp);
       // cout<<"A~ =\n";
       // printmat(A1,m,ntemp);
        matmul(D,C,tempM1,ntemp,ntemp,1);
        copymat(tempM1,C1,ntemp,1);
       // cout<<"C~ =\n";
       // printmat(C1,ntemp,1);
        transpose(A1,tempM1,m,ntemp);
       // cout<<"A~ (T) =\n";
      //  printmat(tempM1,ntemp,m);
        matmul(A1,tempM1,tempM2,m,ntemp,m);
      //  cout<<"A~ * A~(T) = \n";
      //  printmat(tempM2,m,m);
        product_form_inverse(tempM2,m);
      //  cout<<"{A~ * A~(T)}(inverse) =\n";
     //   printmat(tempM2,m,m);
        matmul(tempM1,tempM2,tempM3,ntemp,m,m);
        matmul(tempM3,A1,tempM2,ntemp,m,ntemp);
        subtract(I,tempM2,P,ntemp,ntemp);
     //   cout<<"P = \n";
     //   printmat(P,ntemp,ntemp);
        matmul(P,C1,tempM3,ntemp,ntemp,1);
        neg=negative(tempM3,ntemp,1);
        v=abs(tempM3[neg][0]);
        for(i=0;i<ntemp;i++)
            tempM3[i][0]=(0.5/v)*tempM3[i][0];
        addition(X2,tempM3,X2,ntemp,1);
        matmul(D,X2,X1,ntemp,ntemp,1);
     //   cout<<"X~ (new) = \n";
     //   printmat(X2,ntemp,1);
        cout<<"X (new) = \n";
        printmat(X1,ntemp,1);
        cout<<"----------------------------------------------------------\n";
        for(i=0;i<ntemp;i++)
        {
            if(abs(X[i][0]-X1[i][0])>max)
               max=abs(X[i][0]-X1[i][0]);
        }
        if(max<.001) break;
    }
    cout<<" OPTIMAL SOLUTION = \n";
    printmat(X1,ntemp,1);
    transpose(C,C1,ntemp,1);
    matmul(C1,X1,X,1,ntemp,1);
    cout<<"OPTIMUM VALUE = "<<X[0][0]<<endl;
}



















    
    
