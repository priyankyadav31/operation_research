#include <iostream>
#include<iomanip>
#include<limits>
#include <math.h>

using namespace std;

int negative(double A[20][20],int row,int col)
{   int loc=-1;
    double neg=0;
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

int minratio(double A[20][20],int row,int col,int neg)
{
    int i,j,loc=-1;
    double r,min=20000;
    for(i=0;i<row;i++)
    {
        if(A[i][neg]>0)
        {
           r=A[i][col-1]/A[i][neg];
           if(r<min)
           {  
              min=r;
              loc=i;
           }
        }     
    }
    return loc;
}

void copy(double A[][20],double B[][20],int row,int column)
{
     for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            B[i][j]=A[i][j];
}

void printmat(double A[][20],int row,int column)
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
     } cout<<endl;
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


int main()
{
    int m,n,i,j,mtemp,Rn[20],Cn[20],neg,r,count=0;
    double temp=0,A[20][20],B[20][20],C[20][20],S[20],Y[20],flag,temp1=0,Cb[20],Cnb[20],tempA[20][20],p,k1,k2,v;
    char Rc[20],Cc[20];
    cout<<"Enter the number of player A\n";
    cin>>m;
    cout<<"Enter the number of player B\n";
    cin>>n;
    for(i=0;i<20;i++)
        for(j=0;j<20;j++)
            B[i][j]=C[i][j]=0;
    for(i=0;i<20;i++)
        Y[i]=S[i]=Cb[i]=Cnb[i]=0;
    cout<<"Enter the matrix\n";
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            cin>>A[i][j];
    for(i=0;i<20;i++)
    {
        Rn[i]=Cn[i]=i;
        Rc[i]='y';
    }
    for(i=0;i<m;i++)
    {
        Cc[i]='s';
        A[i][n]=1;
    }
    for(i=0;i<n;i++)
        Cnb[i]=C[i][0]=1;
    for(j=0;j<n+1;j++)
    {
        temp1=0;
        for(i=0;i<m;i++)
        {
          temp1+=A[i][j]*Cb[i];
        }
        A[m][j]=temp1-Cnb[j];
    }
    mtemp=m+1;
    copy(A,tempA,mtemp,n+1);
    printmat(A,mtemp,n+1);

    while(1)
    {
          neg=negative(A,mtemp,n);
          cout<<"neg= "<<neg<<endl;
          if(neg==-1) break;
          else
          {   
             if(A[m][neg]==0) break;
             r=minratio(A,m,n+1,neg);
             cout<<"r= "<<r<<endl;
             if(r==-1)
                break;
             else
             {
                p=A[r][neg];
                for(i=0;i<n+1;i++)
                    tempA[r][i]=A[r][i]/p;
                for(i=0;i<mtemp;i++)
                    tempA[i][neg]=-(A[i][neg]/p);
                tempA[r][neg]=1/p;
                for(i=0;i<mtemp;i++)
                    for(j=0;j<n+1;j++)
                    {
                        if(i!=r && j!=neg)
                        {
                           k1=A[i][j]*p;
                           k2=A[i][neg]*A[r][j];
                           tempA[i][j]=(k1-k2)/p;
                        }
                   }
                Swapc(Rc[neg],Cc[r]);
                Swapn(Rn[neg],Cn[r]);
                temp1=Cb[r];
                Cb[r]=Cnb[neg];
                Cnb[neg]=temp1;
                cout<<endl;
                copy(tempA,A,mtemp,n+1);
             }
          }
          printmat(A,mtemp,n+1);
    }
    if(r==-1) cout<<"The given problem is unbounded";
    for(i=0;i<m;i++)
          {
              if(Cc[i]=='y') 
              {
                 Y[Cn[i]]=A[i][n];
                 count++;
              }
              else if(Cc[i]=='s') 
              {
                      S[Cn[i]]=A[i][n];
              }
          }
    
    v=1/A[m][n];
    cout<<"value of the game is "<<v<<endl;
    for(i=0;i<n;i++)
        Y[i]=Y[i]*v;
    cout<<"Y values for player B : \n";
    for(i=0;i<n;i++)
        cout<<"Y["<<i<<"] = "<<Y[i]<<" , ";
}



   