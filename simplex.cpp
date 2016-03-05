#include <iostream>
#include<iomanip>
#include<limits>
#include <math.h>

using namespace std;
int counter=0;

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

int minratio(float A[20][20],int row,int col,int neg)
{
    int i,j,loc=-1;
    float r,min=20000;
    for(i=0;i<row;i++)
    {
        r=A[i][col-1]/A[i][neg];
        if(r>0 && r<min)
        {
            min=r;
            loc=i;
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

void printmat(float A[][20],int row,int column)
{
     int i,j;
     for(i=0;i<row;i++)
     {
         for(j=0;j<column;j++)
         {   
             cout.width(12);
             cout.precision(3);
             cout<<A[i][j];
         }
         cout<<endl;
     } cout<<endl;
}

int main()
{
    int m,n,i,j,neg,l,r,X[20],Z[20],flag1=0,flag2=0;
    float A[20][20],B[20][1],C[20][1],d,tempA[20][20],p,k1,k2;
    for(i=0;i<20;i++)
        X[i]=0;
    for(i=0;i<20;i++)
        Z[i]=-1;
    cout<<"ENTER THE NO OF EQUATIONS\n";
    cin>>m;
    cout<<"ENTER THE NUMBER OF VARIABLES\n";
    cin>>n;
    cout<<"ENTER THE EQUATION\n";
    for(i=0;i<m;i++)
        for(j=0;j<n+1;j++)
           cin>>A[i][j];
    cout<<"ENTER C\n";
    for(i=0;i<n;i++)
        cin>>C[i][0];
    cout<<"ENTER d\n";
    cin>>d;
    for(i=0;i<n;i++)
        A[m][i]=-C[i][0];
    A[m][n]=d;
    while(1)
    {
          neg=negative(A,m+1,n);
          if(neg==-1) break;
          else
          {   
             if(A[m][neg]==0) flag1++;
             r=minratio(A,m,n+1,neg);
             if(r==-1)
                break;
             else
             {
                p=A[r][neg];
                for(i=0;i<n+1;i++)
                    tempA[r][i]=A[r][i]/p;
                for(i=0;i<m+1;i++)
                    tempA[i][neg]=-(A[i][neg]/p);
                tempA[r][neg]=1/tempA[r][neg];
                for(i=0;i<m+1;i++)
                    for(j=0;j<n+1;j++)
                    {
                        if(i!=r && j!=neg)
                        {
                           k1=A[i][j]*p;
                           k2=A[i][neg]*A[r][j];
                           tempA[i][j]=(k1-k2)/p;
                        }
                   }
                   X[neg]=r;
                   Z[r]=0;
                printmat(tempA,m+1,n+1);
                if(flag1>=1) 
                {
                   if(tempA[m][n]==A[m][n]) break;
                } 
                copy(tempA,A,m+1,n+1);
             }
          }
    }
    if(r==-1) cout<<"The given problem is unbounded";
    else if(flag1>=1) 
    {
       for(i=0;i<m+1;i++)
          if(A[i][n]!=tempA[i][n])
            flag2=-1;
       if(flag2==-1) cout<<"Infinitely many solution\n"; 
    }
    else
    {
       for(i=0;i<n;i++)
          if(X[i]!=0)
          {
             X[i]=A[X[i]][n];
          }
          for(i=0;i<m;i++)
          {
              if(Z[i]!=0)
                 Z[i]=A[i][n];
          }
       for(i=0;i<n;i++)
           cout<<"X["<<i<<"] = "<<X[i]<<"  ";
       cout<<endl;
       for(i=0;i<m;i++)
           cout<<"Z["<<i<<"] = "<<Z[i]<<"  ";
       cout<<endl;
    }
    if(r!=-1) cout<<"Max value is : "<<A[m][n];

    return 0;
}
