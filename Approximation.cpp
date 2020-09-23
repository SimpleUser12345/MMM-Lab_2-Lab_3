#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

typedef long double extended;
typedef unsigned char byte;
typedef extended** Matrix;
typedef extended* Vector;

bool WithGauss(Matrix M, Vector A, int n){
    int l;
    int bi,r,c,i;
    Vector Temp;
    extended a1,b1,sum;
    extended el;
    bool Result;

    Temp=0;
    Result=false;
    if (n==0) return Result;
	l=n+1;

	for (i=0;i<n;i++){
	  bi=i;
	  for (r=i;r<n;r++)
		if (fabsl(M[r][i])>fabsl(M[bi][i])) bi=r;
		  Temp=M[bi];
		  M[bi]=M[i];
		  M[i]=Temp;
		  if (M[i][i]==0.0l) return Result;
		  el=M[i][i];
		  M[i][i]=1;
		  for(c=i+1;c<l;c++)
			if (M[i][c]==0) M[i][c]=0;
			else M[i][c]=M[i][c]/el;
		  for(r=i+1;r<n;r++){
			if (M[r][i]==0) M[r][i]=0;
			else {
			  el=M[r][i];
			  M[r][i]=0;
			  for(c=i+1;c<l;c++){
				if (M[r][c]==0) a1=0;
				else a1=M[r][c];
				if (M[i][c]==0) b1=0;
				else b1=M[i][c]*el;
				M[r][c]=a1-b1;
			  }
			}
		  }
	}

	for(i=n-1;i>=0;i--){
	  a1=0;
	  for(c=i+1;c<n;c++)
		a1=a1+M[i][c]*A[c];
	  if (a1==0) a1=0;
	  if (M[i][n]==0) A[i]=-a1;
	  else A[i]=M[i][n]-a1;
	}
	Result=true;
	return Result;
}

double FindNumber(string line, int k){
	int count=0;
	int i=0;
	while (count<k){
		if (line[i]==',') {
			count++;
		}
		i++;
	}
	int i1=i;
	while (line[i]!=',') i++;
	string v=line.substr(i1,i-i1);
	return atof(v.c_str());
}

int main (int argc, char **argv) {
	vector<double> x;
	vector<double> y;

	string line;
	ifstream file;
	file.open("surgut.csv");
	getline(file,line);
	for (int i = 0; i < 10; i++) {
		getline(file,line);
	}
	getline(file,line);
	while (getline(file,line)){
		double v=FindNumber(line,3);
		//cout << v << endl;
		y.push_back(v);
	}
	file.close();

	cout<<"Input data"<<endl;

	double h=0.1;
	int n=6;
	for (int i=0;i<n;i++){
		x.push_back(h*i);
		cout << x[i] << " " << y[i] << endl;
	}

	cout<<endl;

	cout<<"Formulas"<<endl;

	int maxp=6;

	int count=51;
	vector<vector<double>> ans(maxp+1,vector<double>(count,0));

	for (int p = 1; p <= maxp; p++) {
		int k=2*p-1;
		vector<double> s(k,0);
		vector<double> b(p,0);
		for (int i = 0; i < n; i++) {
			double t=x[i];
			double r=1;
			for (int j = 0; j < k; j++) {
				s[j]+=r;
				r*=t;
			}
			r=1;
			for (int j = 0; j < p; j++) {
				b[j]+=r*y[i];
				r*=t;
			}
		}
		cout<<endl;

		Matrix m=new extended*[p];
		for (int i = 0; i < p; i++) {
			m[i]=new extended[p+1];
			for (int j = 0; j < p; j++) {
				m[i][j]=s[i+j];
			}
			m[i][p]=b[i];
		}
		Vector a=new extended[p];
		WithGauss(m,a,p);

		cout<<a[0];
		for (int i = 1; i < p; i++) {
			cout<<"+("<<a[i]<<")*x^"<<i;
		}
		cout<<endl;

		for (int i = 0; i < count; i++) {
			double xx=x[0]+(x[n-1]-x[0])*i/(count-1);
			double r=1;
			double sum=0;
			for (int j = 0; j < p; j++) {
				sum+=a[j]*r;
				r*=xx;
			}
			ans[p][i]=sum;
		}

		for (int i = 0; i < p; i++) {
			delete [] m[i];
		}
		delete [] m;
		delete [] a;
	}

	cout<<endl;

	cout<<"51 points"<<endl;

	cout<<endl;

	for (int i = 0; i < count; i++) {
		double xx=x[0]+(x[n-1]-x[0])*i/(count-1);

		cout<<xx<<" ";
		for (int j = 0; j < maxp; j++) {
			cout<<ans[j+1][i]<<" ";
		}
		cout<<endl;
	}
	//system("Pause");
    char s;
	cin>>s;

	return 0;
}
