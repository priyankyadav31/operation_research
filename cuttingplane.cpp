#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#define SIZE 20

using namespace std;


class fraction{
private:
	int lcm(int a,int b){
		return (a*b)/gcd(a,b);
	}

	int gcd(int a,int b){
		while(a!=b){
			if(a>b){
				a = a-b;
			}
			else{
				b = b-a;
			}
		}
		return a;
	}

	void reduce(){
		int n = this->p, d = this->q;
		if(n!=0){
			int hcf = gcd(abs(n),abs(d));
			this->p = n/hcf;
			this->q = d/hcf;
		}
		else {
			this->q = 1;
		}
	}

public:
	int p;
	int q;

	fraction(){
		this->p = 0;
		this->q = 1;
	}
	void print(){
		cout << this->p << "/" << this->q << endl;
	}
	fraction multiply(int m){
		fraction f;
		f.p = m * this->p;
		f.q = this->q;
		return f;
	}
	fraction inverse(){
		fraction f;
		if(this->p < 0){
			this->p = -1 * this->p;
			this->q = -1 * this->q;
		}
		f.p = this->q;
		f.q = this->p;
		return f;
	}
	fraction operator+(fraction& f){
		reduce();
		f.reduce();
		fraction ft;
		if(this->q == f.q){
			ft.p = this->p + f.p;
			ft.q = this->q;
		}
		else{
			ft.q = lcm(this->q,f.q);
			ft.p = (this->p)*((ft.q)/(this->q)) + (f.p)*((ft.q)/(f.q));
		}
		ft.reduce();
		return ft;
	}

	fraction operator-(fraction& f){
		reduce();
		f.reduce();
		fraction ft;
		if(this->q == f.q){
			ft.p = this->p - f.p;
			ft.q = this->q;
		}
		else{
			ft.q = lcm(this->q,f.q);
			ft.p = (this->p)*((ft.q)/(this->q)) - (f.p)*((ft.q)/(f.q));
		}
		ft.reduce();
		return ft;
	}

	fraction operator*(fraction& f){
		fraction ft;
		reduce();
		f.reduce();
		ft.p = this->p * f.p;
		ft.q = this->q * f.q;
		ft.reduce();
		return ft;
	}

	fraction operator/(fraction& f){
		fraction ft;
		reduce();
		f.reduce();
		ft.p = this->p * f.q;
		ft.q = this->q * f.p;

		if(ft.p<0 && ft.q<0){
			ft.p = -1 * ft.p;
			ft.q = -1 * ft.q;
		}
		if(ft.p>0 && ft.q<0){
			ft.p = -1*ft.p;
			ft.q = -1*ft.q;
		}
		ft.reduce();
		return ft;
	}

	bool operator>=(fraction& f){
		return (this->p)*(f.q) >= (this->q)*(f.p);
	}

	bool operator>(fraction& f){
		return (this->p)*(f.q) > (this->q)*(f.p);
	}

	bool operator<(fraction& f){
		return (this->p)*(f.q) < (this->q)*(f.p);
	}

	bool operator<=(fraction& f){
		return (this->p)*(f.q) <= (this->q)*(f.p);
	}

	bool operator==(fraction& f){
		return (this->p)*(f.q) == (this->q)*(f.p);
	}

	bool operator!=(fraction& f){
		return (this->p)*(f.q) != (this->q)*(f.p);
	}

	void operator=(const fraction& f){
		p = f.p;
		q = f.q;
	}

	friend ostream &operator<<(ostream &output, const fraction &f){
		output << f.p << "/" << f.q ; 
		return output;
	}

	friend istream &operator>>(istream &input, fraction &f){
		input >> f.p;
		//f.q = 1;
		return input;
	}
};
/*simplex and dual simplex code*/

void getMat(fraction a[][SIZE],int row,int col){
	for (int i = 1; i <= row; ++i)
	{
		for (int j = 1; j <= col; ++j)
		{
			cin >> a[i][j];
		}
	}
}
//printing matrix
void printMat(fraction a[][SIZE],int row,int col){
	cout << "\n___________________________________________________\n";
	for (int i = 1; i <= row; ++i)
	{
		for (int j = 1; j <= col; ++j)
		{
			cout.width(5);
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
}
void getcol(fraction a[][SIZE],fraction c[],int row,int cn){
	for(int i=1; i<=row; i++){
		c[i] = a[i][cn];
	}
}

void getrow(fraction a[][SIZE],fraction r[],int col,int rn){
	for(int i=1; i<=col-1; i++){
		r[i] = a[rn][i];
	}
}
int findp(fraction a[],int len){
	int pci = -1;
	fraction min;
	int count = 0;

	for (int i = 1; i <= len; ++i)
	{
		if (a[i].p < 0)
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

int findsimq(fraction a[][SIZE],int row,int col,int pci){
	int cnt = 0;
	int pri = -1;
	fraction ratio,minr;
	for (int i = 1; i <= row-1; ++i)
	{
		ratio = a[i][col]/a[i][pci];
		if (ratio.p > 0 && a[i][pci].p > 0)
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

void copyMat(fraction a[][SIZE],fraction b[][SIZE],int row,int col){
	for(int i=1; i<=row; i++){
		for(int j=1; j<=col; j++){
			a[i][j] = b[i][j];
		}
	}
}

int max(int a,int b){
	return (a>b?a:b);
}

void printarr(fraction a[],int len){
	for(int i=1; i<=len; i++){
		cout << a[i] << " ";
	}
	cout << endl;
}

void updateSimplexTab(fraction a[][SIZE],int row,int col,int p,int q){
	//update pth row
	//fraction t[SIZE][SIZE];
	//copyMat(t,a,row+1,col);
	fraction t1,t2,t3;
	for (int i = 1; i <= row+1; ++i) {
		for (int j = 1; j <= col; ++j) {
			if( i != p && j !=q ){
				t1 = a[i][j]*a[p][q];
				t2 = a[p][j]*a[i][q];
				t3 = t1-t2;
				a[i][j] = t3/a[p][q];
			}	
		}
	}

	for (int j = 1; j <= col; ++j)
	{
		if (j!=q)
			a[p][j] = a[p][j]/a[p][q];
	}
	//update qth col
	fraction f1;
	for (int i = 1; i <= row+1; ++i)
	{
		if (i!=p){
			f1 = a[i][q]/a[p][q];
			a[i][q] = f1.multiply(-1);
		}
	}

	a[p][q] = a[p][q].inverse();

	
}

void setSimplexTab(fraction a[][SIZE],fraction cb[],fraction cn[],int row,int col){
	fraction sum,t,zero;
	for(int i=1; i<=col; i++){
		for(int j=1; j<=row; j++){
			t = a[j][i]*cb[j];
			sum = sum + t;
		}
		if(i<=col-1){
			a[row+1][i] = sum - cn[i];
			sum = zero;
		}
		else{
			a[row+1][i] = sum;
		}
	}
}

void solveSimplex(fraction a[][SIZE],fraction cb[],fraction cn[],int bv[],int nbv[],int row,int col){
	fraction z[SIZE];
	getrow(a,z,col,row+1);
	int pc = findp(z,col-1);
	while(pc!=-1){

		int pr = findsimq(a,row+1,col,pc);
		cout << "p = " << pc  << ", q = " << pr << endl;
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
	cout << endl;
	//writing the solution
	for(int i=1; i<=row; i++){
		if(bv[i]>0){
			cout << "x[" << bv[i] << "] = " << a[i][col] << ", ";
		}
	}cout << endl;
}

/*==========Dual Simplex===============*/
fraction abs(fraction f){
	if(f.p < 0){
		f.p = -f.p;
	}
	return f;
}
int findualsimq(fraction a[][SIZE],fraction cb[],int row,int col,int pci){
	int cnt = 0;
	int pri = -1;
	fraction ratio,minr,f1,f2,f3,f4;
	for (int i = 1; i <= col-1; ++i){
		if(a[pci][i].p < 0){
			cnt++;
			f1 = a[row+1][i];
			f2 = cb[pci];
			f3 = f1 - f2;
			f4 = f3/a[pci][i];
			ratio = abs(f4);
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

void solveDaulSimplex(fraction a[][SIZE],fraction cb[],fraction cn[],int bv[],int nbv[],int row,int col){

	fraction xb[SIZE];
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
		p = findp(xb,row);
	
	}
	//writing the solution
	cout << endl;
	for(int i=1; i<=row; i++){
		if(bv[i]>0){
			cout << "x[" << bv[i] << "] = " << a[i][col] << ", ";
		}
	}cout << endl;
	//cout << "\nThe maximum value is: " << a[row+1][col] << endl;
}

int findgfi(fraction f[],int len){
	
	int gfi=-1,cnt=0;
	fraction gf,fr;
	for(int i=1; i<=len; i++){
		if(f[i].q == 1){
			continue;
		}else{
			if(f[i].p>0){
				int t1 = f[i].q, t2 = f[i].p;
				int r =  t2 % t1;
				fr.p = r , fr.q = f[i].q;
				if(cnt==0){
					gf = fr;
					gfi = i;
					cnt++;
				}else{
					if(fr > gf){
						gf = fr;
						gfi = i;
					}
				}
			}else{
				int t = f[i].q / f[i].p;
				t--;
				fraction ft;
				ft.p = -t;
				fr = ft + f[i];
				if(cnt==0){
					gf = fr;
					gfi = i;
					cnt++;
				}else{
					if(fr > gf){
						gf = fr;
						gfi = i;
					}
				}
			}
		}
	}
	return gfi;
}

fraction gif(fraction f){
	
	fraction tf;

	if(f.q == 1){
		return f;
	}else{
		if(f.p < 0){
			int d = f.p / f.q;
			d--;
			tf.p = d;
			return tf;
		}else{
			int t = f.p / f.q;
			tf.p = t;
			return tf;
		}
	}
}

fraction findf(fraction f){
	fraction f1,f2;
	f1 = gif(f);
	f2 = f - f1;
	return f2;
}
/*----------------------------------------------------------------------------------------------------------------------------*/

 int main(){

 	fraction a[SIZE][SIZE],xb[SIZE],z[SIZE],cf[SIZE],cb[SIZE],cn[SIZE];
 	int nbv[SIZE],bv[SIZE];
 	int row,col;
 	cout << "Enter row = #inequality, col = #variables: ";
 	cin >> row >> col;
 	cout << "Type the coefficeient of function: ";
 	for(int j=1; j<=col; j++){
 		cin >> cf[j];
 	}
 	cout << "Enter the constrain inequality (all <= type):\n";
 	col++;
 	getMat(a,row,col);
 	//initialize cb, cn, nbv, bv
 	int tl = max(row,col);
 	for(int i=1; i<=tl; i++){
 		if(i<=row){
 			cb[i].p = 0;
 			bv[i] = -i;
 		}
 		cn[i] = cf[i];
 		nbv[i] = i;
 	}
 	
 	setSimplexTab(a,cb,cn,row,col);
 	printMat(a,row+1,col);
 	cout << "cb[] = ";
 	printarr(cb,row);
 	cout << "cn[] = ";
 	printarr(cn,col-1);
 	
 	solveSimplex(a,cb,cn,bv,nbv,row,col);

 	fraction f[SIZE];
	getcol(a,f,row,col);
	printarr(f,row);
	int g = findgfi(f,row);
	cout << "g = " << g << endl;

	while(g!=-1){
			fraction zero;
			row++;
			cb[row] = zero;
			bv[row] = -row;
			/*copy the previous row entry to next row in a[][]*/ 	
			for(int i=1; i<=col; i++){
				a[row+1][i] = a[row][i];
			}
			printMat(a,row+1,col);
			cout << "cb[] = ";
		 	printarr(cb,row);
		 	cout << "cn[] = ";
		 	printarr(cn,col-1);
		 	/*writing row'th entry in a[][] from g'th row entry*/
		 	for(int i=1; i<=col; i++){
		 		a[row][i] = findf(a[g][i]);
		 		a[row][i] = a[row][i].multiply(-1);
		 	}
		 	printMat(a,row+1,col);

		 	solveDaulSimplex(a,cb,cn,bv,nbv,row,col);

		 	getcol(a,f,row,col);
		 	printarr(f,row);
		 	g = findgfi(f,row);
	}


	return 0;
}