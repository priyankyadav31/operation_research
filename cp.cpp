#include<iostream>
#include<iomanip>
using namespace std;
int r=1,c=1,l=0;
void printd(double A[][10], int n, int m)
{
    int i,j;
    for(i=0;i<=m;i++)
    {
        for(j=0;j<=n;j++)
            {
                if(j==1)
                    cout<<"|";
                cout.width(5);
                cout<<setprecision(3)<<A[i][j]<<" ";
    }
        cout<<"\n";
        if(i==0)
        for(j=0;j<=n+1;j++)
        {   cout.width(5);
            cout<<"_____";  
        }
        cout<<"\n";
    }
}
void fdpvd(double A[][10],int n,int m)
{
    r=1;c=1;
    int i,j,k,z;
    double phi=100000,R;
    k=A[1][n];
    for(j=1;j<m;j++)
        if(k>=A[j][n])
        {   
            k=A[j][n];
            r=j;
        }
    //cout<<"R="<<r<<" ";
    for(j=1;j<n;j++)
        if(A[r][j]<0)
        {   R=A[m][j]/A[r][j];    
            if(R<0)
                R=(-1)*R;
            if(phi>R)
                {
                   phi = R;
                   c=j;
                }
        }   
    cout<<"\npivot element:"<<A[r][c]<<" ";
}
void tabd(double A[][10],int n,int m)
{
    int i,j,k;
    for(i=1;i<=m;i++)
    {
        if(i!=r){
        for(j=1;j<=n;j++)
        {
            if(j!=c)
                {
                    A[i][j]=((A[i][j]*A[r][c])-(A[r][j]*A[i][c]))/A[r][c];}
        }}
    }
    for(i=1;i<=n;i++)
        if(i!=c)
        A[r][i]=A[r][i]/A[r][c];
    for(i=1;i<=m;i++)
        if(i!=r)
        A[i][c]=A[i][c]/(-1*A[r][c]);
    cout<<"\n";
    A[r][c]=1/A[r][c];
    printd(A,n,m);
}
int check(double A[][10], int n, int m)
{
    int i,j,k=0;
    for(i=1;i<m;i++)
    {
        if(A[i][n]<0)
            k++;    
    }
    return k;
}
void swap(double A[][10], int n, int m)
{
    double temp;
    temp=A[0][c];
    A[0][c]=A[r][0];
    A[r][0]=temp;
}
void print(double a[][10], int n, int m)
{
    int i,j;
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++)
            {
                cout.width(5);
                cout<<setprecision(5)<<a[i][j]<<" ";
    }
        cout<<"\n";
    }
}
void fdpv(double a[][10],int n,int m)
{
    r=1;c=1;
    int i,j;
    double b[m][1],k;
    k=a[m][1];
    for(i=2;i<n;i++)
    {
        if(k>a[m][i])
        {
            k=a[m][i];
            c=i;
        }
    }
    k=10000;
    l=0;
    for(i=1;i<m;i++)
    {
        if(a[i][n]/a[i][c]<0)
            l++;
        else
            {
                k=a[i][n]/a[i][c];
                r=i;
            }
    }
    if(l==m-1)
    {   cout<<"\nThe system is unbounded and it has no solution";
        return;
    }
    for(i=1;i<m;i++)
    {
        if(k>=a[i][n]/a[i][c] && a[i][n]/a[i][c]>0)
        {
            k=a[i][n]/a[i][c];
            r=i;
        }
    }
    cout<<"\npivot element:"<<a[r][c]<<" ";
}
void tab(double a[][10],int n,int m)
{
    int i,j,k;
    for(i=1;i<=m;i++)
        if(i!=r)
            for(j=1;j<=n;j++)
                if(j!=c)
                    a[i][j]=((a[i][j]*a[r][c])-(a[r][j]*a[i][c]))/a[r][c];
    for(i=1;i<=n;i++)
        if(i!=c)
        a[r][i]=a[r][i]/a[r][c];
    for(i=1;i<=m;i++)
        if(i!=r)
        a[i][c]=a[i][c]/(-1*a[r][c]);
    cout<<"\n";
    a[r][c]=1/a[r][c];
    print(a,n,m);
}
void swap(int x1[], int x2[], int n, int m)
{
    int temp;
    temp = x2[r];
    x2[r] = x1[c];
    x1[c] = temp;
}
int main()
{
    int i,j,k=1,n,m,z=0,ch,x1[10],x2[10],piv;
    double a[10][10],b[10][10],f[10],frac=0.0,A[10][10],x[10],ch1,z1[10];
    cout<<"Enter the No. of variable and No. of equation: ";
    cin>>n>>m;
    for(i=1;i<=m;i++)
    for(j=1;j<=n+1;j++)
        cin>>a[i][j];
    cout<<"1.Maximization\n2.Minimization\n";
    cin>>ch;
    cout<<"Enter coefficient of z: ";
    for(i=1;i<=n;i++)
    {
        cin>>a[m+1][i];
        if(ch==1)
        a[m+1][i]=(-1)*a[m+1][i];
        x1[i]=i;
        x2[i]=0;
    }
    for(i=1;i<=n+m+1;i++)
        if(i<=n)
            x1[i]=i;
        else
            x2[i-n]=i;
    a[m+1][n+1]=0;
    print(a,n+1,m+1);
    for(i=1;i<=n;i++)
        cout<<" "<<x1[i];
    cout<<"\n";
    for(i=1;i<=m;i++)
            cout<<" "<<x2[i];                                                                                                                                                                                               
    while(1)
    {
        if(k==0)
            break;
        fdpv(a,n+1,m+1);
        if(l!=m)
        {
            tab(a,n+1,m+1);
            swap(x1,x2,n,m);
            for(i=1;i<=m;i++)
                if(x2[i]!=0)
                    cout<<"x"<<x2[i]<<"="<<a[i][n+1]<<" ";              
            k=0;
            for(i=1;i<=n;i++)
                if(a[m+1][i]<0)
                k++;                                                    
            z=0;
            for(i=1;i<=n;i++)
                if((a[m+1][i]==0 && a[m+1][i]==-0) && k==0)
                        z++;
            if(z!=0)
            {
                fdpv(a,n+1,m+1);
                tab(a,n+1,m+1);
                swap(x1,x2,n,m);
                break;
            }
        }
        else break;
    }
    cout<<"\n";
    for(i=1;i<=m;i++)
        if(frac<a[n+1][i]-int(a[n+1][i]))
            {frac=a[n+1][i]-int(a[n+1][i]); piv=i;}
    for(i=1;i<=n;i++)
        f[i]=-1*(a[m+1][i]-int(a[m+1][i]));
    f[i]=-frac;
    cout<<"\n\n";
    for(i=1;i<=m+1;i++)
    for(j=1;j<=n+1;j++)
        {
            if(i!=m+1)
                b[i][j]=a[i][j];
            if(i==m+1)
                {b[i][j]=f[j]; b[i+1][j]=a[i][j];}
        }
    m=m+1;
    for(i=1;i<=n;i++)
        A[0][i]=x1[i];
    for(i=1;i<=m;i++)
        A[i][0]=x2[i];
    for(i=1;i<=m+1;i++)
    for(j=1;j<=n+1;j++)
        A[i][j]=b[i][j];
    A[m+1][n+1]=13.6667; A[0][n+1]=0;
    A[m+1][0]=0; A[0][0]=0; //A[m][n+1]=13.6667;
    printd(A,n+1,m+1);
    while(1)
    {
        fdpvd(A,n+1,m+1);
        swap(A,n+1,m+1);
        tabd(A,n+1,m+1);
        ch=check(A,n+1,m+1);
        if(ch==0)
            break;
        else
            {   
                fdpvd(A,n+1,m+1);
                swap(A,n+1,m+1);
                tabd(A,n+1,m+1);
                ch=check(A,n+1,m+1);
                if(ch==0)
                    break;
            }
    }
    for(i=1;i<=n;i++)
        cout<<"x"<<x2[i]<<"="<<A[i][n+1]<<" ";
    if(ch1==2)
        A[m+1][n+1]*=-1;
    cout<<"\nThe Optimal solution is: "<<A[m+1][n+1];
}
