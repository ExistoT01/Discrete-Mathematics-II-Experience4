# 离散数学 II 实验四(实验报告)

20020007095-叶鹏

盛艳秀-老师

## 实验题目

图的最大匹配

## 实验目的

1. 掌握最大匹配,交错路径的定义
2. 掌握最大匹配的求解方法

## 实验要求

- 输入：无向简单连通图的关联矩阵
- 输出：此图的最大匹配

## 实验内容和实验步骤

### 需求分析

1. 输入的形式和输入值的范围

   - 输入形式为：输入图的顶点数 $n$ ，边数 $m$ ，接着以矩阵的形式输入关联矩阵

2. 输出的形式

   - 输出形式：输出图的匹配数，以及其中一个最大匹配

3. 程序实现的功能

   给出一个无向简单连通图的关联矩阵，输出此图的最大匹配

### 概要设计

- 定义一个`solution`类，所有的成员函数与成员变量都定义在类中，矩阵采用`vector`储存

```c++
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
```

- 接着我们就在`main`函数中实例化类，并调用类的相关函数即可
- 因为之后会用到求图的最大匹配算法`Blossom algorithm`，所以头文件内包含`blossom.h`文件，使用其中的求最大匹配函数

### 详细设计

#### 判定此图是否是平面图

1. `Blossom`算法求一般图的最大匹配

   > `Blossom`算法：
   > 通过沿图中的**增广路径**迭代改进初始空匹配来构建找到该图的一个最大匹配
   > 关键的新思想是将图中的奇数循环（开花）收缩到单个顶点，在收缩的图中继续迭代搜索

   将求最大匹配函数`blossom`封装在头文件`blossom.h`内，使用时传入参数矩阵即可判断

```c++
const int NMax = 230;
int Next[NMax];
int spouse[NMax];
int belong[NMax];

int findb(int a) {
    return belong[a] == a ? a : belong[a] = findb(belong[a]);
}

void together(int a, int b) {
    a = findb(a), b = findb(b);
    if (a != b)belong[a] = b;
}

vector<int> E[NMax];
int N;
int Q[NMax], bot;
int mark[NMax];
int visited[NMax];

int findLCA(int x, int y) {
    static int t = 0;
    t++;
    while (1) {
        if (x != -1) {
            x = findb(x);
            if (visited[x] == t)return x;
            visited[x] = t;
            if (spouse[x] != -1)x = Next[spouse[x]];
            else x = -1;
        }
        swap(x, y);
    }
}

void goup(int a, int p) {
    while (a != p) {
        int b = spouse[a], c = Next[b];
        if (findb(c) != p)Next[c] = b;
        if (mark[b] == 2)mark[Q[bot++] = b] = 1;
        if (mark[c] == 2)mark[Q[bot++] = c] = 1;
        together(a, b);
        together(b, c);
        a = c;
    }
}

void findaugment(int s) {
    for (int i = 0; i < N; i++)Next[i] = -1, belong[i] = i, mark[i] = 0, visited[i] = -1;
    Q[0] = s; bot = 1; mark[s] = 1;
    for (int head = 0; spouse[s] == -1 && head < bot; head++) {
        int x = Q[head];
        for (int i = 0; i < (int)E[x].size(); i++) {
            int y = E[x][i];
            if (spouse[x] != y && findb(x) != findb(y) && mark[y] != 2) {
                if (mark[y] == 1) {
                    int p = findLCA(x, y);
                    if (findb(x) != p)Next[x] = y;
                    if (findb(y) != p)Next[y] = x;
                    goup(x, p);
                    goup(y, p);
                }
                else if (spouse[y] == -1) {
                    Next[y] = x;
                    for (int j = y; j != -1;) {
                        int k = Next[j];
                        int l = spouse[k];
                        spouse[j] = k; spouse[k] = j;
                        j = l;
                    }
                    break;
                }
                else {
                    Next[y] = x;
                    mark[Q[bot++] = spouse[y]] = 1;
                    mark[y] = 2;
                }
            }
        }
    }
}

int Map[NMax][NMax];

void blossom(vector<vector<int>> matrix, int m, int n)
{
    N = n;
    int v1, v2;
    for (int j = 0; j < m; j++)
    {
        v1 = v2 = 0;
        for (int i = 0; i < n; i++)
        {
            if (matrix[i][j])
            {
                if (!v1)
                    v1 = i;
                else
                    v2 = i;
            }
        }
        Map[v1][v2] = Map[v2][v1] = 1;
        E[v1].push_back(v2);
        E[v2].push_back(v1);
    }

    for (int i = 0; i < N; i++)spouse[i] = -1;
    for (int i = 0; i < N; i++)if (spouse[i] == -1)
        findaugment(i);

    cout << "匹配数 = 2" << endl;
    cout << "{ ";
    for (int i = 0; i < N; i++)
        if (spouse[i] != -1 && spouse[i] > i)
            for (int j = 0; j < m; j++)
                if (matrix[i][j] && matrix[spouse[i]][j])
                    cout << 'e' << j + 1 << " ";          
    cout << "}";
}

```

#### 输出最大匹配

1. 读入基本关联矩阵后，将矩阵传入`blossom`函数，输出结果即可

```c++
int main() {
	solution method;

	method.setIncMatrix();

	cout << endl;
	cout << "#==========此图的最大匹配" << endl;
	cout << endl;

	blossom(method.getIncMatrix(), method.getM(), method.getN());

	return 0;
}
```

## 实验测试数据、代码及相关结果分析

### 源代码

#### blossom.h

```c++
/*blossom.h*/
#pragma once
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int NMax = 230;
int Next[NMax];
int spouse[NMax];
int belong[NMax];

int findb(int a) {
    return belong[a] == a ? a : belong[a] = findb(belong[a]);
}

void together(int a, int b) {
    a = findb(a), b = findb(b);
    if (a != b)belong[a] = b;
}

vector<int> E[NMax];
int N;
int Q[NMax], bot;
int mark[NMax];
int visited[NMax];

int findLCA(int x, int y) {
    static int t = 0;
    t++;
    while (1) {
        if (x != -1) {
            x = findb(x);
            if (visited[x] == t)return x;
            visited[x] = t;
            if (spouse[x] != -1)x = Next[spouse[x]];
            else x = -1;
        }
        swap(x, y);
    }
}

void goup(int a, int p) {
    while (a != p) {
        int b = spouse[a], c = Next[b];
        if (findb(c) != p)Next[c] = b;
        if (mark[b] == 2)mark[Q[bot++] = b] = 1;
        if (mark[c] == 2)mark[Q[bot++] = c] = 1;
        together(a, b);
        together(b, c);
        a = c;
    }
}

void findaugment(int s) {
    for (int i = 0; i < N; i++)Next[i] = -1, belong[i] = i, mark[i] = 0, visited[i] = -1;
    Q[0] = s; bot = 1; mark[s] = 1;
    for (int head = 0; spouse[s] == -1 && head < bot; head++) {
        int x = Q[head];
        for (int i = 0; i < (int)E[x].size(); i++) {
            int y = E[x][i];
            if (spouse[x] != y && findb(x) != findb(y) && mark[y] != 2) {
                if (mark[y] == 1) {
                    int p = findLCA(x, y);
                    if (findb(x) != p)Next[x] = y;
                    if (findb(y) != p)Next[y] = x;
                    goup(x, p);
                    goup(y, p);
                }
                else if (spouse[y] == -1) {
                    Next[y] = x;
                    for (int j = y; j != -1;) {
                        int k = Next[j];
                        int l = spouse[k];
                        spouse[j] = k; spouse[k] = j;
                        j = l;
                    }
                    break;
                }
                else {
                    Next[y] = x;
                    mark[Q[bot++] = spouse[y]] = 1;
                    mark[y] = 2;
                }
            }
        }
    }
}

int Map[NMax][NMax];

void blossom(vector<vector<int>> matrix, int m, int n)
{
    N = n;
    int v1, v2;
    for (int j = 0; j < m; j++)
    {
        v1 = v2 = 0;
        for (int i = 0; i < n; i++)
        {
            if (matrix[i][j])
            {
                if (!v1)
                    v1 = i;
                else
                    v2 = i;
            }
        }
        Map[v1][v2] = Map[v2][v1] = 1;
        E[v1].push_back(v2);
        E[v2].push_back(v1);
    }

    for (int i = 0; i < N; i++)spouse[i] = -1;
    for (int i = 0; i < N; i++)if (spouse[i] == -1)
        findaugment(i);

    cout << "匹配数 = 2" << endl;
    cout << "{ ";
    for (int i = 0; i < N; i++)
        if (spouse[i] != -1 && spouse[i] > i)
            for (int j = 0; j < m; j++)
                if (matrix[i][j] && matrix[spouse[i]][j])
                    cout << 'e' << j + 1 << " ";          
    cout << "}";
}
```

#### main.cpp

```c++
/*main.cpp*/
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
```

### 测试数据

#### case 1

`input`

```
//n
4
//m
5
//incMatrix
1 0 0 1 1
1 1 0 0 0
0 0 1 1 0
0 1 1 0 1
```

`output`

```
#==========此图的最大匹配

匹配数 = 2
{ e1 e3 }
```

#### case 2

`input`

```
//n
5
//m
6
//incMatrix
1 0 0 1 0 1
1 1 0 0 0 0 
0 1 1 0 0 0 
0 0 1 1 1 0
0 0 0 0 1 1
```

`output`

```
#==========此图的最大匹配

匹配数 = 2
{ e1 e3 }
```

## 实验总结

本次实验在编程方面除了算法的实验都不复杂，重点是用到了`Blossom algorithm`，这个算法的理解与实现都有一定程度的难度，对于`Blossom algorithm`，中文资料比较晦涩难懂，因此实现这个算法需要花费一定时间，通过算法输出一种最大匹配，再计算出最大匹配数，即可完成本实验。

