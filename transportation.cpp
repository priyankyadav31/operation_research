#include <iostream>
#include<iomanip>
#include<limits>
#include<cmath>

using namespace std;

void copy(int A[][20],int B[][20],int row,int column)
{
     for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            B[i][j]=A[i][j];
}

void printmat(int A[][20],int row,int column)
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

int check(int A[][20],int B[][20],int X[],int Y[],int row,int column)
{
    int i,j;
    for(i=0;i<row;i++)
    {
    	for(j=0;j<column;j++)
    		if(B[i][j]==0)
    		{
    			//cout<<X[i]<<" "<<Y[j];
    			if(X[i]+Y[j] > A[i][j])
    				break;
    		}
    	if(j<column) break;
    }
    if(i!=row) return 0;
    else return 1;
}

int value(int A[][20],int B[][20],int row,int column)
{
    int i,j,v=0;
    for(i=0;i<row;i++)
        for(j=0;j<column;j++)
        {
            if(B[i][j]!=0)
                v+=A[i][j]*B[i][j];
        }
    return v;
}
void NWCR(int A[][20],int B[][20],int S[],int D[],int X[],int Y[],int m,int n)
{
    int temp=0,i,j,k=0,l=0;
    for(i=0;i<m;i++)
        for(j=temp;j<n;j++)
        {
            if(S[i]<=D[j])
            {
                B[i][j]=S[i];
                D[j]-=S[i];
                S[i]=0;
                //cout<<S[i]<<" "<<D[j]<<endl;
                break;
            }
            else if(D[j]<=S[i])
            {
                    temp=temp+1;
                    B[i][j]=D[j];
                    S[i]-=D[j];
                    D[j]=0;
                    //cout<<S[i]<<" "<<D[j]<<endl;
            } 
        }
     printmat(A,m,n);
     printmat(B,m,n);
     X[0]=0; Y[0]=A[0][0];
     i=0; j=0;
     while(i<=m && j<=n){
		if(B[i][j+1]==0 || (j+1)>n){
			i++;
			X[i] = A[i][j] - Y[j];
		}else{
			j++;
			Y[j] = A[i][j] - X[i];
		}
	}
}

int maximum(int a,int b)
{
    if(a>b) return a;
    else return b;
}

int main()
{
	int m,n,i,j,p,q,l=0,r=0,u=0,d=0,temp=0,A[20][20],B[20][20],C[20][20],S[20],D[20],X[20],Y[20],V,UC[20][20],flag,max=0;
	cout<<"Enter the number of sources\n";
	cin>>m;
	cout<<"Enter the number of destination\n";
	cin>>n;
	for(i=0;i<20;i++)
        for(j=0;j<20;j++)
            A[i][j]=B[i][j]=C[i][j]=0;
    for(i=0;i<20;i++)
    	X[i]=Y[i]=0;
    cout<<"Enter the matrix\n";
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            cin>>A[i][j];
    cout<<"Enter the sources\n";
    for(i=0;i<m;i++)
    	cin>>S[i];
    cout<<"Enter the destination\n";
    for(i=0;i<n;i++)
    	cin>>D[i];
    NWCR(A,B,S,D,X,Y,m,n);
    cout<<"X[i] =  ";
    for(i=0;i<m;i++) cout<<X[i]<<" ";
    cout<<endl;
    cout<<"Y[i] =  ";
    for(i=0;i<n;i++) cout<<Y[i]<<" ";
    cout<<endl;
    V=value(A,B,m,n);
    cout<<"value= "<<V<<endl;
    flag=check(A,B,X,Y,m,n);
    if(flag==1)
    {
        cout<<"This is the optimal solution";
    }
    else
    {
        cout<<"This is not the optimal solution";
    }
     return 0;
}
