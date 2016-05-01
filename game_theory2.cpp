#include <iostream>
#include<iomanip>
#include<limits>
#include <cmath>

using namespace std;

int negative(double A[20][20],int row,int col)
{   int neg=0,loc=-1;
    for(int i=0;i<row;i++)
    {   
        if(A[i][col-1]<neg)
        {
            neg=A[i][col-1];
            loc=i;
        }
    }
    return loc;
}

int minratio(double A[20][20],int row,int col,int neg)
{
    int j,loc=-1;
    double f,min=2000,r;
    for(j=0;j<col;j++)
    {   if(A[neg][j]<0)
        {
           f=A[row-1][j]/A[neg][j];
           r=abs(f);
           if(r<min)
           {  
              min=r; 
              loc=j;
           }    
    }   }
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
             cout.width(10);
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
    int m,n,i,j,mtemp,Rn[20],Cn[20],neg,r,count=0,t=0;
    double temp=0,A[20][20],B[20][20],C[20][20],S[20],X[20],flag1=0,flag2,temp1=0,Cb[20],Cnb[20],tempA[20][20],p,k1,k2,v;
    char Rc[20],Cc[20];
    cout<<"Enter the number of player A\n";
    cin>>m;
    cout<<"Enter the number of player B\n";
    cin>>n;
    for(i=0;i<20;i++)
        for(j=0;j<20;j++)
            B[i][j]=C[i][j]=0;
    for(i=0;i<20;i++)
        X[i]=S[i]=Cb[i]=Cnb[i]=0;
    cout<<"Enter the matrix\n";
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {
            cin>>A[i][j];
            if(A[i][j]!=0)
               A[i][j]=-A[i][j];
        }
    copy(A,B,m,n);
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            A[i][j]=B[j][i];
    for(i=0;i<20;i++)
    {
        Rn[i]=Cn[i]=i;
        Rc[i]='x';
    }
    for(i=0;i<m;i++)
    {
        Cc[i]='s';
        A[i][n]=-1;
    }
    for(i=0;i<n;i++)
        Cnb[i]=C[i][0]=-1;
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
          printmat(A,mtemp,n+1);
          neg=negative(A,mtemp-1,n+1);
          cout<<"neg= "<<neg<<" , "<<A[neg][n]<<endl;
          if(neg==-1) break;
          else
          {   
             if(A[m][neg]==-0) A[m][neg]=0;
             if(A[m][neg]==0) flag1++;
             r=minratio(A,mtemp,n,neg);
             if(r==-1) break;
             else
             {
                p=A[neg][r];
                cout<<p<<endl;
                for(i=0;i<n+1;i++)
                    tempA[neg][i]=A[neg][i]/p;
                for(i=0;i<mtemp;i++)
                    tempA[i][r]=-(A[i][r]/p);
                tempA[neg][r]=1/p;
                for(i=0;i<mtemp;i++)
                    for(j=0;j<n+1;j++)
                    {
                        if(i!=neg && j!=r)
                        {
                           k1=A[i][j]*p;
                           k2=A[i][r]*A[neg][j];
                           tempA[i][j]=(k1-k2)/p;
                        }
                    }
                Swapc(Rc[r],Cc[neg]);
                Swapn(Rn[r],Cn[neg]);
                temp1=Cb[neg];
                Cb[neg]=Cnb[r];
                Cnb[r]=temp1;
                cout<<endl;
                if(flag1>=1) 
                {
                   if(tempA[m][n]==A[m][n]) break;
                } 
                copy(tempA,A,mtemp,n+1);
             }
          }
    }
    if(r==-1) cout<<"The given problem is unbounded";
    else if(flag1>=1) 
    {
         for(i=0;i<mtemp;i++)
             if(A[i][n]!=tempA[i][n])
                flag2=-1;
         if(flag2==-1) cout<<"Infinitely many solution\n"; 
    }
    else
    {
        for(i=0;i<m;i++)
              {
                  if(Cc[i]=='x') 
                  {
                     X[Cn[i]]=A[i][n];
                     count++;
                  }
                  else if(Cc[i]=='s') 
                  {
                          S[Cn[i]]=A[i][n];
                  }
              }
        
        v=-1/A[m][n];
        cout<<"value of the game is "<<v<<endl;
        for(i=0;i<count;i++)
            X[i]=X[i]*v;
        cout<<"X values for player B : \n";
        for(i=0;i<count;i++)
            cout<<"X["<<i<<"] = "<<X[i]<<" , ";
    }
}



   