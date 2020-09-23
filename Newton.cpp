#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

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
	return  atof(v.c_str());
}

int main (int argc, char **argv) {
	vector<double> x;
	vector<double> y;

	cout<<"Input Data"<<endl;

	string line;
	ifstream file;
	file.open("surgut.csv");
	getline(file,line);
	getline(file,line);
	while (getline(file,line)){
		double v=FindNumber(line,2);
		y.push_back(v);
	}
	file.close();

	double h=0.1;

	cout<<endl;
	int n=6;
	for (int i=0;i<n;i++){
		x.push_back(h*i);
		cout<<x[i]<<" "<<y[i]<<endl;
	}
	vector<vector<double>> d(n - 1,vector<double>(n - 1,0));
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (i==0) {
				d[i][j]=(y[j+1]-y[j]);
			} else {
				d[i][j]=(d[i-1][j+1]-d[i-1][j]);
			}
		}
	}

	cout<<endl;

	cout<<"Formulas"<<endl;

	cout<<endl;

	cout<<"q = (x-"<<x[0]<<")/"<<h<<endl;

	cout<<y[0]<<"+"<<endl;

	double r = 1;

	string s="q";
	for (int i=0;i<n-1;i++){
		r/=(i+1);
		if (i>0) {
			s+="*(q - ";
			s+=to_string(i);
			s+=")";
		}
		cout<<d[i][0]*r<<"*"<<s;
		if (i<n-2) {
			cout<<"+"<<endl;
		} else {
			cout<<endl;
		}
	}

	cout<<endl;
	cout<<"q = (x+"<<x[n-1]<<")/"<<h<<endl;
	cout<<y[n-1]<<"+"<<endl;
	s="q";
	r = 1;
	for (int i=0;i<n-1;i++){
		r/=(i+1);
		if (i>0) {
			s+="*(q - ";
			s+=to_string(i);
			s+=")";
		}
		cout<<d[i][n-2-i]*r<<"*"<<s;
		if (i<n-2) {
			cout<<"+"<<endl;
		} else {
			cout<<endl;
		}
	}

	cout<<endl;
	cout<<"51 points"<<endl;
	cout<<endl;

	int count=51;
	for (int i = 0; i < count; i++) {
		double xx=x[0]+(x[n-1]-x[0])*i/(count-1);
		double r=1;
		double q=(xx-x[0])/h;
		double sum1=y[0];
		r = 1;
		for (int i=0;i<n-1;i++){
			r*=(q-i)/(i+1);
			sum1+=d[i][0]*r;
		}
		q=(xx-x[n-1])/h;
		double sum2=y[n-1];
		r = 1;
		for (int i=0;i<n-1;i++){
			r*=(q+i)/(i+1);
			sum2+=d[i][n-2-i]*r;
		}
		cout<<xx<<" "<<sum1<<" "<<sum2<<endl;
	}

	system("Pause");
//	char cc;
//	cin>>cc;	
	
	return 0;
}
