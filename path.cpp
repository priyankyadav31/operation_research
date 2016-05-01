#include <iostream>
#include<iomanip>
#include<limits>
#include <math.h>
#include <cmath> 

using namespace std;

int count=0;

void path(int A[][20],int i,int j,int m,int n)
{
	if(i==m-1 && j==n-1)
	{
       ++count;
    }
	else
	{
		if(i+1 !=m )
		{
			if(A[i+1][j]==1) path(A,i+1,j,m,n);
		}
		if(j+1 != n)
		{
			if(A[i][j+1]==1) path(A,i,j+1,m,n);
		}
	}
}

int main()
{
	int i=0,j=0,m,n,A[20][20];
	cout<<"Enter the number of rows \n";
	cin>>m;
	cout<<"Enter the number of column\n";
	cin>>n;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			{
				cin>>A[i][j];
		    } 
    path(A,0,0,m,n);
    cout<<"count = "<<count;

}