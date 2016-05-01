#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

void getMat(int a[][10],int rows,int cols){
	for(int i=1; i<=rows; i++){
		for(int j=1; j<=cols; j++){
			cin >> a[i][j];
		}
	}
}
void getArr(int a[],int len){
	for(int i=1; i<=len; i++){
		cin >> a[i];
	}
}

void printMat(int a[][10],int rows,int cols){
	for(int i=1; i<=rows; i++){
		for(int j=1; j<=cols; j++){
			cout.width(5);
			cout << a[i][j] << "\t";
		}cout << endl;
	}
}
void printArr(int a[],int len){
	for(int i=1; i<=len; i++){
		cout << a[i] << " ";
	}cout << endl;
}

int nwcr(int x[][10],int c[][10],int u[],int v[],int a[],int b[],int rows,int cols){
	int i=1,j=1;
	
	while(i<=rows && j<=cols){
		if(a[i]>b[j]){
			x[i][j] = b[j];
			a[i] = a[i] - b[j];
			b[j] = 0;
			j++;
		}else{
			x[i][j] = a[i];
			b[j] = b[j] - a[i];
			a[i] = 0;
			i++;
		}
	}
	//soling for u[] and v[]
	//when goes right solve for v[j] when go down solve for u[i]
	i=1, j=1;
	u[1] = 0;
	v[1] = c[i][j] - u[1];
	while(i<=rows && j<=cols){
		if(x[i][j+1]==0 || (j+1)>cols){
			i++;
			u[i] = c[i][j] - v[j];
		}else{
			j++;
			v[j] = c[i][j] - u[i];
		}
	}
	//checking whether solution is optimal or not reurn 1 for optimal and c[mi][mj] for not optimal
	int t=0,cnt=0,mt=0,mi=-1,mj=-1;
	for(int i=1; i<=rows; i++){
		for(int j=1; j<=cols; j++){
			if(x[i][j]==0){
				t = u[i] + v[j] - c[i][j];
				if(t>=0){
					if(cnt==0){
						mt = t;
						mi = i;
						mj = j;
						cnt++;
					}else{
						if(t>=mt){
							mt = t;
							mi = i;
							mj = j;
						}
					}
				}
			}
		}
	}
	if(mi!=-1 && mj!=-1){
		return 10*mi+mj;
	}else{
		return 1;
	}
	
}
void initMat(int x[][10],int rows,int cols){
	for(int i=1; i<=rows; i++){
		for(int j=1; j<=cols; j++){
			x[i][j] = 0;
		}
	}
}
int findCost(int c[][10],int x[][10],int rows,int cols){
	int sum=0;
	for(int i=1; i<=rows; i++){
		for(int j=1; j<=cols; j++){
			sum += c[i][j]*x[i][j];
		}
	}
	return sum;
}

void printcxMat(int c[][10],int x[][10],int rows,int cols){
	for(int i=1; i<=rows; i++){
		for(int j=1; j<=cols; j++){
			cout.width(5);
			cout << "["<<c[i][j] <<"]/{" << x[i][j] << "}\t";
		}cout << endl;
	}
}

int main(){
	int c[10][10],x[10][10],a[10],b[10],u[10],v[10],rows,cols;			//a is column vector and b is row vector
	
	cout << "Give the no of rows = #source and cols = #destination: ";
	cin >> rows >> cols;
	cout << "Enter the C matrix: \n";
	getMat(c,rows,cols);
	cout << "Enter a[] = ";
	getArr(a,rows);
	cout << "Enter b[] = ";
	getArr(b,cols);
	
	initMat(x,rows,cols);
	int tst = nwcr(x,c,u,v,a,b,rows,cols);
	
	cout << "nwcr matrix = c[][],x[][] \n";
	printcxMat(c,x,rows,cols);
	cout << "\nu[] = ";
	printArr(u,rows);
	cout << "\nv[] = ";
	printArr(v,cols);
	cout << "Cost = " << findCost(c,x,rows,cols);
	if(tst!=1){
		cout << "\nNot optimal! and starting index of Q loop = " << tst/10 << "," << tst%10 << endl;
	}else{
		cout << "optimal!\n";
	}


	return 0;
}

