#include <cmath>  
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <string>
using namespace std;

double GetOneGaussianByBoxMuller()//������̬�ֲ��������
{
	double result;
	double x;
	double y;
	double sizeSquared;
	do
	{
		x = 2.0*rand() / static_cast<double>(RAND_MAX) - 1;
		y = 2.0*rand() / static_cast<double>(RAND_MAX) - 1;
		sizeSquared = x*x + y*y;
	} while
		(sizeSquared >= 1.0);
	result = x*sqrt(-2 * log(sizeSquared) / sizeSquared);
	return result;
}


double* priceroad(double s0, int T, double miu, double sigma) //����һ��·�������������������ʼ�ɼ�s0,����T������miu,������sigma
{
	double *b,*s;
	miu = miu / 250;//���껯��miuת��Ϊÿ���miu
	sigma = sigma / sqrt(250);//���껯��sigmaת��Ϊÿ���sigma
	s = new double[T + 1];
	*s = s0;
	for (int i = 0; i < T; i++) {
		*(s + i + 1) = *(s + i)*exp((miu - 0.5*sigma*sigma) + sigma* GetOneGaussianByBoxMuller());
	}//�����s�ɼ۰���ÿ����ƣ�����i+1��Ĺɼ۰��յ�i��Ĺɼ��Ƴ���
	return s;
}


int main() 
{
	double *price[100];//ָ�������������100��·��
	double s0, miu, sigma;
	int T;
	cout << "Please input T:" << endl;//��������T
	cin >> T;
	cout << "Please input s0:" << endl;//�����ʼ�ɼ�s0
	cin >> s0;
	cout << "Please input miu:" << endl;//��������miu
	cin >> miu;
	cout << "Please input sigma:" << endl;//���벨����sigma
	cin >> sigma;
	for (int j = 0; j < 100; j++) {
		srand(j);
		price[j] = priceroad(s0, T, miu, sigma);
	}
	ofstream outfile;
	string InitialFileName("priceroad(T="+to_string(T)+",s0="+ to_string(s0) + ",miu=" + to_string(miu) + ",sigma=" + to_string(sigma) + ")"+".txt");
	outfile.open(InitialFileName, ostream::app);//���·��Ϊtxt���ļ�������������������Ϣ
	for (int j = 0; j < 100; j++) {
		for (int i = 0; i<T + 1; i++) {
			outfile << price[j][i];
			if (i != T) {
				outfile << ',';
			}
		}
		outfile << endl;
	}
	outfile.close();
	system("pause");
}