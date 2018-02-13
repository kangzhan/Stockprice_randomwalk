#include <cmath>  
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <string>
using namespace std;

double GetOneGaussianByBoxMuller()//生成正态分布的随机数
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


double* priceroad(double s0, int T, double miu, double sigma) //生成一条路径，输入参数包括：初始股价s0,期限T，收益miu,波动率sigma
{
	double *b,*s;
	miu = miu / 250;//将年化的miu转化为每天的miu
	sigma = sigma / sqrt(250);//将年化的sigma转化为每天的sigma
	s = new double[T + 1];
	*s = s0;
	for (int i = 0; i < T; i++) {
		*(s + i + 1) = *(s + i)*exp((miu - 0.5*sigma*sigma) + sigma* GetOneGaussianByBoxMuller());
	}//这里的s股价按照每天递推，即第i+1天的股价按照第i天的股价推出来
	return s;
}


int main() 
{
	double *price[100];//指针数组用来存放100条路径
	double s0, miu, sigma;
	int T;
	cout << "Please input T:" << endl;//输入期限T
	cin >> T;
	cout << "Please input s0:" << endl;//输入初始股价s0
	cin >> s0;
	cout << "Please input miu:" << endl;//输入收益miu
	cin >> miu;
	cout << "Please input sigma:" << endl;//输入波动率sigma
	cin >> sigma;
	for (int j = 0; j < 100; j++) {
		srand(j);
		price[j] = priceroad(s0, T, miu, sigma);
	}
	ofstream outfile;
	string InitialFileName("priceroad(T="+to_string(T)+",s0="+ to_string(s0) + ",miu=" + to_string(miu) + ",sigma=" + to_string(sigma) + ")"+".txt");
	outfile.open(InitialFileName, ostream::app);//输出路径为txt，文件名包含了输入数据信息
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