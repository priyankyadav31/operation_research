#include <iostream>
#include<iomanip>
#include<limits>
#include<cmath>

using namespace std;
// class double{
// public:
//   int p;
//   int q;

//   int lcm(int a,int b){
//     return (a*b)/gcd(a,b);
//   }

//   int gcd(int a,int b){
//     while(a!=b){
//       if(a>b){
//         a = a-b;
//       }
//       else{
//         b = b-a;
//       }
//     }
//     return a;
//   }

//   void reduce(){
//     int n = this->p, d = this->q;
//     int hcf = gcd(abs(n),abs(d));
//     this->p = n/hcf;
//     this->q = d/hcf;
//   }

//   void read(){
//     cin >>p;
//     q=1;
//   }
//   void init(){
//     this->p=0;
//     this->q=1;
//   }
//   void print(){
//     cout << this->p << "/" << this->q;
//   }
//   void multiply(int m){
//     this->p = m * this->p;
//   }
//   double operator+(double& f){
//     double ft;
//     if(this->q == f.q){
//       ft.p = this->p + f.p;
//       ft.q = this->q;
//     }
//     else{
//       ft.q = lcm(this->q,f.q);
//       ft.p = (this->p)*((ft.q)/(this->q)) + (f.p)*((ft.q)/(f.q));
//     }
//     if(ft.p!=0)
//        ft.reduce();
//     return ft;
//   }

//   double operator-(double& f){
//     double ft;
//     if(this->q == f.q){
//       ft.p = this->p - f.p;
//       ft.q = this->q;
//     }
//     else{
//       ft.q = lcm(this->q,f.q);
//       ft.p = (this->p)*((ft.q)/(this->q)) - (f.p)*((ft.q)/(f.q));
//     }
//     if(ft.p!=0)
//        ft.reduce();
//     return ft;
//   }


//   double operator*(double& f){
//     double ft;
//     ft.p = this->p * f.p;
//     ft.q = this->q * f.q;
//     if(ft.p!=0)
//        ft.reduce();
//     return ft;
//   }
//   double operator/(double& f){
//     double ft;
//     ft.p = this->p * f.q;
//     ft.q = this->q * f.p;
//     if(ft.p!=0)
//        ft.reduce();
//     return ft;
//   }

//   double value()
//   {
//       return double(p)/double(q);
//   }

//   bool operator>=(double& f){
//     return (this->p)*(f.q) >= (this->q)*(f.p);
//   }

//   bool operator<=(double& f){
//     return (this->p)*(f.q) <= (this->q)*(f.p);
//   }

//   bool operator==(double& f){
//     return (this->p)*(f.q) == (this->q)*(f.p);
//   }

//   void operator=(const double& f){
//     p = f.p;
//     q = f.q;
//   }
// };

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
    double r,min=2000;
    for(i=0;i<row;i++)
    {
        if(A[i][neg]>0)
        {
           r=A[i][col-1]/A[i][neg];
           if(r<=min)
           {  
              min=r;
              loc=i;
           }
        }     
    }
    return loc;
}

int negative_dual(double A[20][20],int row,int col)
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

int minratio_dual(double A[20][20],int row,int col,int neg)
{
    int j,loc=-1;
    double f,min=2000,r;
    for(j=0;j<col;j++)
    {   
        f=A[row-1][j]/A[neg][j];
        r=abs(f);
        if(r<min)
        {  
           min=r; 
           loc=j;
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

int max_fract(double A[][20],int row,int column)
{
    int i,loc=-1;
    double max=0,r;
    for(i=0;i<row;i++)
    {
        //r=(A[i][column-1].p)/(A[i][column-1].q);
        r=A[i][column-1];
        //cout<<r;
        r=r-int(r);
        //cout<<r;
        if(r>max) 
        {
           max=r;
           loc=i;
        }
    }
    return loc;
}

int check_int(double A[][20],int row,int column)
{
  int i;
  double r;
  for(i=0;i<row;i++)
  {
    r=A[i][column-1];
    //cout<<r-int(r)<<endl;
    if((r-int(r)) > 0.0001) break;
  }
  if(i==row) return 1;
  else return 0;
}



int main()
{
    int m,n,i,j,neg,l,r,Rn[20],Cn[20],flag1=0,flag2=0,flag3=0,sign[20][20],less=0,great=0,equal=0,ntemp=0,mtemp=0,flag0,ntemp2,z;
    double A[20][20],B[20][1],C[20][20],d,tempA[20][20],p,k1,k2,X[20],Y[20],Z[20],Cb[20],Cnb[20],temp1,temp2;
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
    {
        cin>>C[i][0];
        Cnb[i]=C[i][0];
    }
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
           A[i][n+j]=-1;
           ++j;
        }
        
    }
    ntemp=n+j;
    mtemp=m+1;
    cout<<endl;
    for(i=0;i<m;i++)
        A[i][ntemp]=B[i][0];
    printmat(A,m,ntemp);
    for(j=0;j<ntemp+1;j++)
    {
        temp1=0;
        for(i=0;i<m;i++)
        {
            temp2= A[i][j]*Cb[i];
            temp1 = temp1+temp2;

        }
        A[m][j]=temp1-Cnb[j];
    }
    copy(A,tempA,mtemp,ntemp+1);
    printmat(tempA,mtemp,ntemp+1);
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
      // for(i=0;i<ntemp;i++)
      // {
      //     cout<<Rc[i]<<Rn[i]<<" ";
      //     Cnb[i].print();cout<<" ";
      // }
      // cout<<endl;
      // for(i=0;i<m;i++)
      // {
      //     cout<<Cc[i]<<Cn[i]<<" ";
      //     Cb[i].print();cout<<" ";
      // }
    while(1)
    {
      l=max_fract(A,m,ntemp+1);
      cout<<l;
      for(j=0;j<ntemp+1;j++)
      {
          i=int(A[l][j]);
         // cout<<" i";
          if(A[l][j]<0) i=i-1;
          tempA[l][j]=i-A[l][j];
      }
      for(j=0;j<ntemp+1;j++)
      {
          A[mtemp][j]=A[mtemp-1][j];
          A[mtemp-1][j]=tempA[l][j];
      }
      mtemp=mtemp+1;
      printmat(A,mtemp,ntemp+1);
      copy(A,tempA,mtemp,ntemp+1);
      while(1)
      {     
          printmat(A,mtemp,ntemp+1);
          neg=negative_dual(A,mtemp-1,ntemp+1);
          if(neg==-1) break;
          else
          {   
             if(A[m][neg]==0) flag1++;
             r=minratio_dual(A,mtemp,ntemp,neg);
             if(r==-1) break;
             else
             {
                p=A[neg][r];
                for(i=0;i<ntemp+1;i++)
                    tempA[neg][i]=A[neg][i]/p;
                for(i=0;i<mtemp;i++)
                    tempA[i][r]=-(A[i][r]/p);
                tempA[neg][r]=1/p;
                for(i=0;i<mtemp;i++)
                    for(j=0;j<ntemp+1;j++)
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
                   if(tempA[m][ntemp]==A[m][ntemp]) break;
                } 
                copy(tempA,A,mtemp,ntemp+1);
             }
          }
      }
         if(check_int(A,mtemp,ntemp+1)==1)  break;
    }
     for(i=0;i<mtemp;i++)
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

       if(flag0==-1) A[mtemp-1][ntemp]=-1*A[mtemp-1][ntemp];
       if(r!=-1)
       { 
          cout<<"**** Optimat solution ****\n";
          for(i=0;i<n;i++)
              cout<<"  X["<<i<<"] = "<<X[i]<<"  ";
           cout<<endl<<endl;
           cout<<"  slack variables-:  ";
           for(i=0;i<less+great;i++)
               cout<<"  Y["<<i<<"] = "<<Y[i]<<"  ";
           if(i==0) cout<<"NONE";
           cout<<endl<<endl;
           cout<<"  optimum value is : "<<A[mtemp-1][ntemp]<<endl;
       }
      return 0;
    }
   