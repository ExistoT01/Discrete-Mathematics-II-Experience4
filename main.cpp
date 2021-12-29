#include <iostream>
#include <vector>
#include "blossom.h"
using namespace std;

class solution {
private:
	vector<vector<int>> incMatrix;
	int m;
	int n;
public:

	void setIncMatrix();
	vector<vector<int>> getIncMatrix();
	int getM() { return m; }
	int getN() { return n; }
	void showMatrix(vector<vector<int>> matrix, int row, int col, int type);

	solution() {
		this->m = 0;
		this->n = 0;
	}


};


int main() {
	solution method;

	method.setIncMatrix();

	cout << endl;
	cout << "#==========此图的最大匹配" << endl;
	cout << endl;

	blossom(method.getIncMatrix(), method.getM(), method.getN());

	return 0;
}

void solution::setIncMatrix()
{
	cout << endl;
	cout << "#==========读入定点数n与边数m" << endl;
	cout << endl;

	int input;

	cout << "n = ";
	cin >> input;
	this->n = input;

	cout << "m = ";
	cin >> input;
	this->m = input;

	cout << endl;
	cout << "#==========读入基本关联矩阵" << endl;
	cout << endl;

	vector<int> tem;

	for (int i = 0; i < n; i++)
	{
		vector<int>().swap(tem);
		for (int j = 0; j < m; j++)
		{
			cin >> input;
			tem.push_back(input);
		}
		this->incMatrix.push_back(tem);
	}

	//showMatrix(incMatrix, n, m, 1);
}

vector<vector<int>> solution::getIncMatrix()
{
	return this->incMatrix;
}

void solution::showMatrix(vector<vector<int>> matrix, int row, int col, int type)
{
	cout << endl;
	cout << "#==========输出";

	char ch_row = 't';
	char ch_col = 't';

	if (type == 0) {
		ch_row = 'v';
		ch_col = 'v';
		cout << "邻接矩阵" << endl;
	}
	else if (type == 1) {
		ch_row = 'v';
		ch_col = 'e';
		cout << "关联矩阵" << endl;
	}
	else if (type == 2) {
		ch_row = 'r';
		ch_col = 'e';
		cout << "面矩阵" << endl;
	}
	cout << endl;

	printf("%-5s\t", "index");
	for (int i = 0; i < col; i++)
		printf("%4c%d", ch_col, i + 1);
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		printf("%4c%d\t", ch_row, i + 1);
		for (int j = 0; j < col; j++)
			printf("%5d", matrix[i][j]);
		cout << endl;
	}
}
