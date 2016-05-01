#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

void getGameMat(double a[][10],int row,int col){
	for (int i = 1; i <= row; ++i)
	{
		for (int j = 1; j <= col; ++j)
		{
			if(j<=col-1)
				cin >> a[i][j];
			else
				a[i][j] = 1;
		}
	}
}
//printing matrix
void printMat(double a[][10],int row,int col){
	cout << "\n___________________________________________________\n";
	for (int i = 1; i <= row; ++i)
	{
		for (int j = 1; j <= col; ++j)
		{
			cout.width(5);
			cout << setprecision(3) << a[i][j] << "\t";
		}
		cout << endl;
	}
}
void getcol(double a[][10],double c[],int row,int cn){
	for(int i=1; i<=row; i++){
		c[i] = a[i][cn];
	}
}

void getrow(double a[][10],double r[],int col,int rn){
	for(int i=1; i<=col-1; i++){
		r[i] = a[rn][i];
	}
}
int findp(double a[],int len){
	int pci = -1;
	double min;
	int count = 0;
	
	for (int i = 1; i <= len; ++i)
	{
		if (a[i] < 0)
		{
			count++;
			if(count == 1){
				min = a[i];
				pci = i;
			}
			else {
				if (a[i] < min){
					min = a[i];
					pci = i;
				}
			}	
		}
	}
	return pci;
}

int findsimq(double a[][10],int row,int col,int pci){
	int cnt = 0;
	int pri = -1;
	double ratio,minr;
	for (int i = 1; i <= row-1; ++i)
	{
		ratio = a[i][col]/a[i][pci];
		if (ratio > 0 && a[i][pci] > 0)
		{
			cnt++;
			if (cnt==1){
				minr = ratio;
				pri = i;
			}
			else {
				if(ratio < minr){
					minr = ratio;
					pri = i;
				}
			}
		}
	}
	return pri;
}

void copyMat(double a[][10],double b[][10],int row,int col){
	for(int i=1; i<=row; i++){
		for(int j=1; j<=col; j++){
			a[i][j] = b[i][j];
		}
	}
}

int max(int a,int b){
	return (a>b?a:b);
}

void printarr(double a[],int len){
	for(int i=1; i<=len; i++){
		cout << a[i] << " ";
	}
	cout << endl;
}

void updateSimplexTab(double a[][10],int row,int col,int p,int q){
	//update pth row
	double t[10][10];
	copyMat(t,a,row+1,col);

	for (int j = 1; j <= col; ++j)
	{
		if (j!=q)
			a[p][j] = a[p][j]/a[p][q];
	}
	//update qth col
	for (int i = 1; i <= row+1; ++i)
	{
		if (i!=p)
			a[i][q] = -a[i][q]/a[p][q];
	}

	a[p][q] = 1/a[p][q];

	for (int i = 1; i <= row+1; ++i) {
		for (int j = 1; j <= col; ++j) {
			if( i != p && j !=q ){
				a[i][j] = (t[i][j]*t[p][q] - t[p][j]*t[i][q])/t[p][q];
			}	
		}
	}
}

void setSimplexTab(double a[][10],double cb[],double cn[],int row,int col){
	double sum = 0;
	for(int i=1; i<=col; i++){
		for(int j=1; j<=row; j++){
			sum += a[j][i]*cb[j];
		}
		if(i<=col-1){
			a[row+1][i] = sum - cn[i];
			sum = 0;
		}
		else{
			a[row+1][i] = sum;
		}
	}
}

void solveSimplex(double a[][10],double cb[],double cn[],int bv[],int nbv[],int row,int col){
	double z[10];
	getrow(a,z,col,row+1);
	int pc = findp(z,col-1);
	while(pc!=-1){

		int pr = findsimq(a,row+1,col,pc);
		cout << "pc = " << pc  << ", pr = " << pr << endl;
		swap(bv[pr],nbv[pc]);
		swap(cb[pr],cn[pc]);
		updateSimplexTab(a,row,col,pr,pc);
		printMat(a,row+1,col);

		cout << "cb[] = ";
		printarr(cb,row);

		cout << "cn[] = ";
		printarr(cn,col-1);

		getrow(a,z,col,row+1);
		pc = findp(z,col-1);
	
	}
}

/*==========Dual Simplex===============*/

int findualsimq(double a[][10],double cb[],int row,int col,int pci){
	int cnt = 0;
	int pri = -1;
	double ratio,minr;
	for (int i = 1; i <= col-1; ++i){
		if(a[pci][i] < 0){
			cnt++;
			ratio = abs((a[row+1][i]-cb[pci])/a[pci][i]);
			if(cnt==1){
				minr = ratio;
				pri = i;
			}
			else {
				if(ratio < minr){
					minr = ratio;
					pri = i;
				}
			}
		}
	}		
	return pri;
}

void solveDaulSimplex(double a[][10],double cb[],double cn[],int bv[],int nbv[],int row,int col){

	double xb[10];
	getcol(a,xb,row,col);
	int p = findp(xb,row);
	while(p!=-1){

		int q = findualsimq(a,cb,row,col,p);
		cout << "p = " << p  << ", q = " << q << endl;
		swap(bv[p],nbv[q]);
		swap(cb[p],cn[q]);
		updateSimplexTab(a,row,col,p,q);
		printMat(a,row+1,col);

		cout << "cb[] = ";
		printarr(cb,row);

		cout << "cn[] = ";
		printarr(cn,col-1);
		
		getcol(a,xb,row,col);
		//cout << "disp xb : ";
		//printarr(xb,row);
		p = findp(xb,row);
	
	}
}
void ntranspose(double t[][10],double a[][10],int rows,int cols){
	//size for t matrix = (cols-1)X(rows+1)
	for(int i=1; i<=cols-1; i++){
		for(int j=1; j<=rows; j++){
			t[i][j] = -a[j][i];
			if(t[i][j]==-0){
				t[i][j] = 0;
			}
		}
	}
	for(int i=0; i<=cols-1; i++){
		t[i][rows+1] = -1;
	}
}


int main(){
	double a[10][10],xb[10],z[10],cf[10],cb[10],cn[10];
	int nbv[10],bv[10];
	int row,col;
	cout << "Enter row = #strategy of Player A, colm = #strategy of Player B : ";
	cin >> row >> col;
	//cout << "Type the coefficeient of function: ";
	for(int j=1; j<=col; j++){
		cf[j] = 1;
	}
	cout << "Enter the game matrix (rows for player A) & (cols for player B):\n";
	col++;
	getGameMat(a,row,col);
	//initialize cb, cn, nbv, bv
	int tl = max(row,col);
	for(int i=1; i<=tl; i++){
		if(i<=row){
			cb[i] = 0;
			bv[i] = -i;
		}
		cn[i] = cf[i];
		nbv[i] = i;
	}
	/*===========solving for player B================*/

	cout <<"\n===========Solution for Plyaer B=================\n";


	setSimplexTab(a,cb,cn,row,col);
	double tmp[10][10];
	copyMat(tmp,a,row+1,col);

	printMat(a,row+1,col);
	cout << "cb[] = ";
	printarr(cb,row);
	cout << "cn[] = ";
	printarr(cn,col-1);

	solveSimplex(a,cb,cn,bv,nbv,row,col);

	double nubar = 1/a[row+1][col];
	cout << endl;
	for(int i=1; i<=row; i++){
		if(bv[i]>0){
			cout << "P(B[" << bv[i] << "]) = y[" << bv[i] <<"] = " << a[i][col]*nubar << ", ";
		}
	}cout << endl;
	cout << "\nExpectation for player B = " << nubar << endl;

	cout <<"\n===========Solution for Plyaer A=================\n";

	/*===========solving for player A================*/
	double t[10][10],cbp[10],cnp[10];
	int bvp[10],nbvp[10];

	ntranspose(t,tmp,row,col);
	printMat(t,col-1,row+1);

	int nrow = col-1, ncol = row+1;
	int ntl = max(nrow,ncol);
	for(int i=1; i<=ntl; i++){
		if(i<=nrow){
			cbp[i] = 0;
			bvp[i] = -i;
		}
		cnp[i] = -1;
		nbvp[i] = i;
	}

	printarr(cbp,nrow);
	printarr(cnp,ncol-1);
	setSimplexTab(t,cbp,cnp,nrow,ncol);
	printMat(t,nrow+1,ncol);
	solveDaulSimplex(t,cbp,cnp,bvp,nbvp,nrow,ncol);

	double barnu = -1/t[nrow+1][ncol];
	cout << endl;
	for(int i=1; i<=nrow; i++){
		if(bvp[i]>0){
			cout << "P(A[" << bvp[i] << "]) = X[" << bvp[i] <<"] = " << t[i][ncol]*barnu << ", ";
		}
	}cout << endl;
	cout << "\nExpectation of player A = " << barnu << endl;
	cout <<"___________________________________________________\n";


	return 0;
}