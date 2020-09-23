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

double num(const vector<double>& x,int k,double arg){
	double r=1;
	for (int i = 0; i < x.size(); i++) {
		if (i!=k) {
			r*=(arg-x[i]);
		}
	}
    return r;
}

double den(const vector<double>& x,int k){
	double r=1;
	for (int i = 0; i < x.size(); i++) {
		if (i!=k) {
			r*=(x[k]-x[i]);
		}
	}
	return r;
}

double Lagrange(const vector<double>& x, const vector<double>& y, double arg){
	double r=0;
	for (int i = 0; i < x.size(); i++) {
		r+=y[i]*num(x,i,arg)/den(x,i);
	}
	return r;
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
	int n=12;
	for (int i=0;i<n;i++){
		x.push_back(h*i);
		cout<<x[i]<<" "<<y[i]<<endl;
	}

	cout<<endl;
	cout<<"50 points"<<endl;
	cout<<endl;

	int count=50;
	for (int i = 0; i < count; i++) {
		double arg=x[0]+(x[n-1]-x[0])*i/(count-1);
		cout<<arg<<" "<<Lagrange(x,y,arg)<<endl;
	}

	//system("Pause");
	char s;
	cin>>s;

	return 0;
}
