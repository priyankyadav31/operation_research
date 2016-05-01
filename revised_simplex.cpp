#include <iostream>
#include <iomanip>
#include <limits>
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
             cout.width(10);
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

void product_form_inverse(float A[][20],int n)
{
	float B1[20][20],B[20][20],C[20][20],e[20][20],E1[20][20],E2[20][20],temp,l,m;
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

int negative(float A[20][20],int row,int col)
{   int neg=0,loc=-1;
    for(int i=0;i<col;i++)
    {
        if(A[row-1][i]<=neg)
        {
            neg=A[row-1][i];
            loc=i;
        }
    }
    return loc;
}

int minratio(float A[20][20],float B[20][20],int row)
{
    int i,j,loc=-1;
    int r,min=20000;
    for(i=0;i<row;i++)
    {
        if(B[i][0]>0)
        {
           r=A[i][0]/B[i][0];
           if(r<min)
           {  
              min=r;
              loc=i;
           }
        }     
    }
    return loc;
}

void copy(float A[][20],float B[][20],int row,int column)
{
     for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            B[i][j]=A[i][j];
}



void Swapc(char &a,char &b)
{
     char temp;
     temp=a;
     a=b;
     b=temp;
}

void Swapn(int &a,int &b)
{
     int temp;
     temp=a;
     a=b;
     b=temp;
}

void delcol(float A[][20],int row,int col,int k)
{
     int i,j;
     for(j=k;j<col-1;j++)
     {
         for(i=0;i<row;i++)
         {
             A[i][j]=A[i][j+1];
         }
     }
}
void Swapcol(float A[][20],int row,int col,int k1,int k2)
{
    int temp,i;
    for(i=0;i<row;i++)
    {
        temp=A[i][k1];
        A[i][k1]=A[i][k2];
        A[i][k2]=temp;
    }
}

int main()
{
    int m,n,i,j,neg,l,r,Rn[20],Cn[20],flag0=0,flag1=0,flag2=0,sign[20][20],less=0,great=0,equal=0,ntemp=0,mtemp=0,temp1=0,temp2=0,b=0;
    float A[20][20],B[20][1],C[20][20],Xb[20][20],sum=0,tempA[20][20],tempB[20][20],tempM[20][20],P[20][20],k1,k2,X[20],Y[20][20],Z[20],Cb[20][20],Cnb[20][20],temp3=0,tempCb[20][20];
    char Rc[20],Cc[20];
    for(i=0;i<20;i++)
    {    
      X[i]=Z[i];
    }
    for(i=0;i<20;i++)
    {
        Rn[i]=Cn[i]=i;
        Rc[i]='x';
    }
    for(i=0;i<20;i++)
        for(j=0;j<20;j++)
        {
            A[i][j]=0;
            Y[i][j]=0;
            Cb[i][j]=0;
            Cnb[i][j]=0;
        }
    cout<<" ENTER THE NO OF EQUATIONS\n";
    cin>>m;
    cout<<" ENTER THE NUMBER OF VARIABLES\n";
    cin>>n;
    cout<<" ENTER THE LEFT EQUATION MATRIX\n";
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
           cin>>A[i][j];
    cout<<" ENTER THE RIGHT MATRIX\n";
    for(i=0;i<m;i++)
        cin>>B[i][0];
    cout<<" Press 1 for >=\n Press 0 for =\n Press -1 for <=\n";
    for(i=0;i<m;i++)
    {
       cin>>sign[i][0];
       if(sign[i][0]==1)
       {  
          great++;
          Cc[i]='a';
       }
       else if(sign[i][0]==0)
       {       
               equal++;
               Cc[i]='a';
       }
       else if(sign[i][0]==-1)
       {
           less++;
           Cc[i]='s';
       }
    }
    b=less+great+equal;
    cout<<" ENTER C\n";
    for(i=0;i<n;i++)
    {
        cin>>Cnb[0][i];
        C[0][i]=Cnb[0][i];
    }
    cout<<" Press 1 for max\nPress -1 for min\n";
    cin>>flag0;
    if(flag0==-1)
       for(i=0;i<n+great;i++)
       {
           Cnb[0][i]=-1*Cnb[0][i];
           C[0][i]=-1*C[0][i];
       }
    j=0;
    for(i=0;i<m;i++)
    {
     	if(sign[i][0]==1)
        {  
           A[i][n+j]=-1;++j;
        }
    }
    for(i=0;i<m;i++)
    {
    	if(sign[i][0]==-1 || sign[i][0]==0 || sign[i][0]==1 )
    	{
    	   A[i][n+j]=1;j++;
    	}
    }
    ntemp=n+j;
    mtemp=m+1;
    cout<<endl;
    for(i=0;i<m;i++)
        A[i][ntemp]=B[i][0];
    
    flag1=n+great;
    flag2=ntemp-1;
    while(1)
    {     
          printmat(A,m,ntemp+1);
          temp1=flag2-flag1+1;
          temp2=flag1;
          for(i=0;i<temp1;i++)
          {
          	  copycol(A,tempB,m,ntemp+1,temp2,i);
          	  ++temp2;
          }
          cout<<" B = \n";
          printmat(tempB,m,m);
          product_form_inverse(tempB,m);
          cout<<" Inverse B = \n";
          printmat(tempB,m,m);
          matmul(Cb,tempB,Y,1,m,m);
          cout<<" Y: \n";
          printmat(Y,1,m);
          for(j=0;j<n+great;j++)
          {
              copycol(A,P,m,n+great,j,0);
              matmul(Y,P,tempM,1,m,1);
              A[m][j]=tempM[0][0]-Cnb[0][j];
          }
          cout<<" Y*Pj-cj= \n";
          printmat(A,m+1,ntemp+1);
          copycol(A,tempM,m,ntemp+1,ntemp,0);
          matmul(tempB,tempM,Xb,m,m,1);
          neg=negative(A,m+1,n+great);
          if(neg==-1) break;
          copycol(A,P,m,n+great,neg,0);
          matmul(tempB,P,tempM,m,m,1);
          r=minratio(Xb,tempM,m);
          if(r==-1) break;
          Swapc(Cc[r],Rc[neg]);
          Swapn(Cn[r],Rn[neg]);
          temp2=Cb[0][r];
          Cb[0][r]=Cnb[0][neg];
          Cnb[0][neg]=temp2;
          Swapcol(A,m,n,neg,n+r);
          cout<<" Xb=\n";
          printmat(Xb,m,1);
          cout<<"-------------------------------------------------------------------------\n";
    }
    cout<<" Xb= \n";
    printmat(Xb,m,1);
    for(i=0;i<m;i++)
    {
        cout<<" "<<Cc[i]<<"["<<Cn[i]<<"] = "<<Xb[i][0]<<"  ";
    }
    for(i=0;i<n+great;i++)
    {
        cout<<" "<<Rc[i]<<"["<<Rn[i]<<"] = "<<0<<"  ";
    }
    for(i=0;i<m;i++)
    {
        if(Cc[i]=='x')
           sum+=(Xb[i][0]*C[0][Cn[i]]);
    }
    cout<<endl<<endl;
    cout<<" Optimum value Z: "<<sum<<endl;
    return 0;
}

    
