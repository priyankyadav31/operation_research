#include <iostream>
#include<iomanip>
#include<limits>
#include <math.h>

using namespace std;
int counter=0;

//function to  print the matrix
void printmat(double a[][20],int row,int column)
{
     int i,j;
     for(i=0;i<row;i++)
     {
         for(j=0;j<column;j++)
         {
             cout<<a[i][j];
             cout<<" ";
         }
         cout<<endl;
     } cout<<endl;
}

//function to swap two rows of a matrix
void swaprow(double a[][20],int row,int column,int k)
{   int i,j;
    double temp;
    for(i=k+1;i<row;i++)
        if(a[i][k]!=0) break;
    for(j=0;j<column;j++)
    {
        temp=a[i][j];
        a[i][j]=a[k][j];
        a[k][j]=temp;
    }
}

//function to calculate the rank of the matrix
int rank(double a[][20],int row,int column)
{
  int i,j,k;
  double l;
  for(k=0;k<(row-1);k++)
  {   if(a[k][k]==0) swaprow(a,row,column,k);
      for(i=row-1;i>k;i--)
      {   l=a[i][k];
          for(j=k;j<column;j++)
          {
              a[i][j]=a[i][j]-(a[k][j]/a[k][k])*l;
          }
      }
  }
  k=0;
  for(i=row-1;i>=0;i++)
  {
      for(j=0;j<column;j++)
      {
          if(a[i][j]!=0) break;
      }
      if(j==column) ++k;
      else break;
  }
  return (row-k);
}

//Function to copy matrix
void copy(double A[][20],double B[][20],int row,int column)
{
     for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            B[i][j]=A[i][j];
}

//Function to delete the column of the matrix
void del(double A[][20],int row,int column,int k)
{
    for(int j=k;j<column-1;j++)
        for(int i=0;i<row;i++)
        {
            A[i][j]=A[i][j+1];
        }
   // printmat(A,row,column-1);
}

//Function to find the solve the equation using Gaussjorden method
void gaussjorden(double A[][20],int row,int column)
{
    double l;
    rank(A,row,column);
    for(int k=row-1;k>0;k--)
    {  for(int i=0;i<k;i++)
        {   l=A[i][k];
            for(int j=column-1;j>=0;j--)
            {
                A[i][j]=A[i][j]-(A[k][j]/A[k][k])*l;
            }
        }
    }
    // printmat(A,row,column);
    for(int i=0;i<row;i++)
       A[i][column-1]=A[i][column-1]/A[i][i];
   // printmat(A,row,column);
}
//function to permute the set
void subset ( int A [] , int k ,int j ,int z,double Y[][20],int m,int n)
{
 int i;
 if(z==k)
 {
    for(i =0; i <k; i++)
        Y[counter][A[i]-1]=0;
    counter++;
 }
 for(i=j+1; i <= n ;++ i )
 {
     A[ k ]= i ;
     subset (A , k +1 , i , z,Y,m,n );
 }
}

//function to calculate factorial of a number
long factorial(int n)
{
    int i;
    long fact = 1;

     //for Loop Block
     for (int i = 1; i <= n; i++)
     {
         fact = fact * i;
     }

  return fact;
}


int main()
{
    int i,j,r1,r2,m,n,z,k,l=0,counter=0,flag=0,choice,zero[20],p,count=0,ntemp;
    cout<<"Enter the no of Equations\n";
    cin>>m;
    cout<<"Enter the no of unknowns\n";
    cin>>n;
    double A[m][20],B[m][1],C[20][1],X[n][1],AG[m][20],temp[m][20],tempx[n][1],Z[20],maxz=0,minz=2000;
    for(i=0;i<m;i++)
        for(j=0;j<20;j++)
            {A[i][j]=0;C[j][0]=0;}
    cout<<"Enter the A\n";
    for(i=0;i<m;i++)
    {   cout<<"Press -1 for <=\nPress 0 for =\nPress 1 for >=\n";
        cin>>choice;
        if(choice==-1 || choice==1) count++;
        for(j=0;j<n;j++)
        {
            cin>>A[i][j];
        }
        if(choice==-1) A[i][n+count-1]=1;
        else if(choice==1)
             {
                A[i][n+count-1]=-1;
             }


    }
    cout<<"Enter B\n";
    for(i=0;i<m;i++)
        cin>>B[i][0];
    cout<<"Enter C\n";
    for(i=0;i<n;i++)
        cin>>C[i][0];
    ntemp=n;
    n=n+count;
    copy(A,AG,m,n);
    for(i=0;i<m;i++)
        AG[i][n]=B[i][0];
    cout<<"Press 0 for max\n"<<"Press 1 for min\n";
    cin>>choice;
    copy(AG,temp,m,n+1);
    r1=rank(temp,m,n+1);
    copy(AG,temp,m,n+1);
    r2=rank(temp,m,n);
    if(r1!=r2) cout<<"The system of equation is inconsistent";
    else{
         cout<<"The system is consistent\n";
         z=n-r1;
         p=factorial(n)/(factorial(z)*factorial(n-z));
         copy(AG,temp,m,n+1);
         double Y[p][20];
         for(i=0;i<p;i++)
             for(j=0;j<n;j++)
                 Y[i][j]=1;
         subset(zero,0,0,z,Y,p,n);
         for(i=0;i<p;i++)
         {   count=0;
             for(j=0;j<n;j++)
             {
                 if(Y[i][j]==0)
                 {
                    del(temp,m,n+1-count,j-count);
                    ++count;
                 }
             }
             if(m==n-count) {gaussjorden(temp,m,m+1);}
             else if(m>(n-count)) gaussjorden(temp,n-count,n-count+1);
             l=0;
             for(j=0;j<n;j++)
             {
                 if(Y[i][j]!=0) {Y[i][j]=temp[l][n-count];l++;}
             }
             copy(AG,temp,m,n+1);
          }
          cout<<"------------------------------------------------------------\n";
          for(i=1;i<=n;i++)
          {
              cout.width(8);
              cout<<"X"<<i;
          }
          cout<<"\n------------------------------------------------------------";
          cout<<endl<<endl;
          for(i=0;i<p;i++)
          {   flag=0;
              for(j=0;j<n;j++)
              {
                  cout.width(9.5);
                  if(Y[i][j]<0 || isfinite(Y[i][j])==0) flag=1;
                  cout<<setprecision(3)<<Y[i][j];
              }
          if(flag==0) cout<<" * Basic feasible solution";
          cout<<endl<<"------------------------------------------------------------"<<endl;
         }
         for(i=0;i<p;i++)
         {
             Z[i]=0;
             for(j=0;j<n;j++)
             {   if(Y[i][j]<0 || isfinite(Y[i][j])==0)
                 {
                    Z[i]=0;
                    break;
                 }
                 Z[i]+=(Y[i][j]*C[j][0]);
             }
             if(Z[i]>maxz) {maxz=Z[i];}
         }
         if(choice==0)
         {  count=0;
            cout<<"\nOptimum solution is -:\n\n";
            for(j=0;j<p;j++)
            {
                if(float(Z[j])==float(maxz))
                {  ++count;
                   for(i=0;i<n;i++)
                       cout<<"X["<<i+1<<"]"<<"="<<Y[j][i]<<"  ";
                   cout<<endl;
                }
            }
            if(count>1) cout<<"The eqution has infinitely many solutions\n";
            cout<<"\n\nOptimal value for Zmax is "<<maxz<<endl;
         }
         for(i=0;i<p;i++)
         {
             Z[i]=0;
             for(j=0;j<n;j++)
             {   if(Y[i][j]<0||isfinite(Y[i][j])==0)
                 {
                    Z[i]=-1;
                    break;
                 }
                  Z[i]+=(Y[i][j]*C[j][0]);
             }
            if(Z[i]<minz && Z[i]>=0) {minz=Z[i];}
        }
        if(choice==1)
        {
           count=0;
           cout<<"\nOptimum solution for min is ";
           for(j=0;j<p;j++)
           {
               if(float(Z[j])==float(minz))
               {
                  for(i=0;i<n;i++)
                      cout<<"X["<<i+1<<"]"<<"="<<Y[j][i]<<"  ";
                  cout<<endl;
               }
           }
            cout<<"\n\nOptimal value for Zmin is "<<minz<<endl;
        }

  }return 0;
}
