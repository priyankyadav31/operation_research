#include <iostream>
#include<iomanip>
#include<limits>
#include <math.h>

using namespace std;
int counter=0;

int negative(float A[20][20],int row,int col)
{   double neg=0;
    int loc=-1;
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

delcol void(float A[][20],int row,int col,int k)
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

int main()
{
    int m,n,i,j,neg,l,r,Rn[20],Cn[20],flag1=0,flag2=0,flag3=0,sign[20][20],less=0,great=0,equal=0,ntemp=0,mtemp=0,temp3=0,flag0,ntemp2;
    float A[20][20],B[20][1],C[20][20],d,tempA[20][20],p,k1,k2,X[20],Y[20],Z[20],Cb[20],Cnb[20],temp1=0,temp2=0;
    char Rc[20],Cc[20];
    for(i=0;i<20;i++)
    {    
      X[i]=Y[i]=Z[i]=Cb[i]=Cnb[i]=0;
    }
    for(i=0;i<20;i++)
    {
        Rn[i]=Cn[i]=i;
        Rc[i]='x';
    }
    for(i=0;i<20;i++)
        for(j=0;j<20;j++)
            A[i][j]=0;
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
        cin>>B[i][0];
    cout<<"Press 1 for >=\nPress 0 for =\nPress -1 for <=\n";
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
    cout<<"ENTER C\n";
    for(i=0;i<n;i++)
        cin>>C[i][0];
    cout<<"Press 1 for max\nPress -1 for min\n";
    cin>>flag0;
    if(flag0==-1)
       for(i=0;i<n+great;i++)
           C[i][0]=-1*C[i][0];
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
        if(sign[i][0]==1 || sign[i][0]==0) Cb[i]=-1;
        else Cb[i]=0;
    }
    ntemp=n+j;
    mtemp=m+1;
    cout<<endl;
    for(i=0;i<m;i++)
        A[i][ntemp]=B[i][0];
    for(j=0;j<ntemp+1;j++)
    {
        temp1=0;
        for(i=0;i<m;i++)
        {
          temp1+=A[i][j]*Cb[i];
        }
        A[m][j]=temp1-Cnb[j];
    }
    copy(A,tempA,mtemp,ntemp+1);
    printmat(A,mtemp,ntemp+1);
    while(1)
    {
          neg=negative(A,mtemp,ntemp);
          if(neg==-1) break;
          else
          {   
             if(A[m][neg]==0) break;
             r=minratio(A,m,ntemp+1,neg);
             if(r==-1)
                break;
             else
             {
                p=A[r][neg];
                for(i=0;i<ntemp+1;i++)
                    tempA[r][i]=A[r][i]/p;
                for(i=0;i<mtemp;i++)
                    tempA[i][neg]=-(A[i][neg]/p);
                tempA[r][neg]=1/p;
                for(i=0;i<mtemp;i++)
                    for(j=0;j<ntemp+1;j++)
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
                copy(tempA,A,mtemp,ntemp+1);
             }
          }
          printmat(A,mtemp,ntemp+1);
    }
    if(A[m][ntemp]!=0)
       cout<<"The system of equations have infeasible solutions\n";
    else
    {
       temp1=0;
       for(j=0;j<ntemp-temp1;j++)
       {
           if(Rc[j]=='a')
           {  
              delcol(A,mtemp,ntemp+1-temp1,j);
              for(i=j;i<ntemp-1-temp1;i++)
              {
                  Rc[i]=Rc[i+1];
                  Rn[i]=Rn[i+1];
                  Cnb[i]=Cnb[i+1];
              }
              temp1++;
           }

       }
       temp2=ntemp;
       ntemp=ntemp-temp1;
       printmat(A,mtemp,ntemp+1);

       cout<<"-------------------Phase 1 has been completed------------------\n";

       temp1=temp3=0;
       for(i=0;i<m;i++)
       {
           if(Cc[i]=='x')
              Cb[i]=C[Cn[i]][0];
            else if(Cc[i]=='s')
            {
                    temp1++;
                    Cb[i]=0;
            }
            else if(Cc[i]=='a')
            {
                    temp3++;
                    Cb[i]=0;
            }
       }
       for(i=0;i<ntemp;i++)
       {
           if(Rc[i]=='x') Cnb[i]=C[Rn[i]][0];
           else Cnb[i]=0;
       }
       cout<<endl;
       for(j=0;j<ntemp+1;j++)
       {
           temp1=0;
           for(i=0;i<m;i++)
           {
               temp1+=A[i][j]*Cb[i];
           }
           A[m][j]=temp1-Cnb[j];
       }
       flag1=0;
       copy(A,tempA,mtemp,ntemp+1);
       while(1)
       {     
             printmat(A,mtemp,ntemp+1);
             neg=negative(A,mtemp,ntemp);
             if(neg==-1) break;
             else
             {   
                if(A[m][neg]==0) flag1++;
                j=0;  
                for(i=0;i<m;i++)
                {
                    if(A[i][neg]<0 && Cc[i]=='a')
                    {
                       r=i;
                       j++;
                    }
                }
                if(j==0)
                   r=minratio(A,m,ntemp+1,neg);
                if(r==-1) break;
                else
                {
                   p=A[r][neg];
                   if(j==0)
                   {  
                      for(i=0;i<ntemp+1;i++)
                          tempA[r][i]=A[r][i]/p;
                      for(i=0;i<mtemp;i++)
                          tempA[i][neg]=-(A[i][neg]/p);
                   }
                   else if(j>0)
                   {  
                      for(i=0;i<ntemp+1;i++)
                          tempA[r][i]=-A[r][i]/p;
                      for(i=0;i<mtemp;i++)
                          tempA[i][neg]=A[i][neg]/p;
                   }
                   tempA[r][neg]=1/p;
                   for(i=0;i<mtemp;i++)
                       for(j=0;j<ntemp+1;j++)
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
                   if(flag1>=1) 
                   {
                      if(tempA[m][ntemp]==A[m][ntemp]) break;
                   } 
                   copy(tempA,A,mtemp,ntemp+1);
                }
             }
       }

       flag2=0;
       for(i=0;i<ntemp;i++)
       {
           if(A[m][i]<0) flag2=-1;
       }
       if(r==-1 && flag2==-1) 
          cout<<"The given problem is unbounded";
       else if(flag1>=1 && r!=-1) 
       {
            for(i=0;i<mtemp;i++)
                if(A[i][ntemp]!=tempA[i][ntemp])
                   flag3=-1;
            if(flag3==-1) cout<<"Infinitely many solution\n"; 
       }
       else
       {  
          for(i=0;i<m;i++)
          {
              if(Cc[i]=='x') 
              {
                 X[Cn[i]]=A[i][ntemp];
              }
              else if(Cc[i]=='s') 
              {
                      Y[Cn[i]]=A[i][ntemp];
              }
          }
          if(flag0==-1) A[m][ntemp]=-1*A[m][ntemp];
          if(r!=-1 || flag2==0)
          { 
             cout<<"**** Optimat solution ****\n";
             for(i=0;i<temp2;i++)
                 cout<<"X["<<i<<"] = "<<X[i]<<"  ";
              cout<<endl<<endl;
              cout<<"slack variables-:  ";
              for(i=0;i<less;i++)
                  cout<<"Y["<<i<<"] = "<<Y[i]<<"  ";
              if(i==0) cout<<"NONE";
              cout<<endl<<endl;
              cout<<"Optimal value value is : "<<A[m][ntemp]<<endl;
          }
       }
   }
    return 0;
}
