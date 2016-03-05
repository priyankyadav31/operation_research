#include <iostream>
#include<iomanip>
#include<limits>
#include <math.h>
#include <cmath> 

using namespace std;

void copymat(float A[][20],float B[][20],int row,int column)
{
     for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            B[i][j]=A[i][j];
}


void copycol(float A[][20],float B[][20],int row,int column,int c1,int c2)
{
	 for(int i=0;i<row;i++)
	     B[i][c2]=A[i][c1];
}



void printmat(float A[][20],int row,int column)
{
     int i,j;
     for(i=0;i<row;i++)
     {
         for(j=0;j<column;j++)
         {   
             cout.width(14);
             cout.precision(4);
             cout<<A[i][j];
         }
         cout<<endl;
     } cout<<endl<<endl;
}

void matmul(float A[20][20],float B[20][20],float C[20][20],int r1,int c,int c2)
{
	 float temp;
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

int main()
{
	float A[20][20],B1[20][20],B[20][20],C[20][20],e[20][20],E1[20][20],E2[20][20],temp,l,m;
	int i,j,k,n;
	cout<<"ENTER THE SIZE OF MATRIX\n";
	cin>>n;
	cout<<"ENTER THE MATRIX\n";
	for(i=0;i<n;i++)
	    for(j=0;j<n;j++)
		{
		    cin>>A[i][j];
		    if(i==j) B[i][j]=B1[i][j]=E2[i][j]=1;
		    else B[i][j]=B1[i][j]=E2[i][j]=0;
	    }
	copymat(B,E1,n,n);
	printmat(A,n,n);
	cout<<"--------------------------------------------------------\n";
	for(i=0;i<n;i++)
	{
		copycol(A,B1,n,n,i,i);
		printmat(B1,n,n);
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
        printmat(E1,n,n);
        cout<<"--------------------------------------------------------\n";
    }
	return 0;
	}
	
		    
	
    
	

