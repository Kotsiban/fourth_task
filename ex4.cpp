#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;

void print_vector(const vector<int>& data);
void repack_fast(vector<int>& data);
void repack_slow(vector<int>& data);
void vector_create(vector<int>& data,const int& N);
unsigned int algorithm_count(vector<int>& data, int N, int algo);

int main()
{

	vector<int> data;
	vector_create(data,8);
	repack_fast(data);
	cout << "Fast algorithm result: ";
	print_vector(data);

	vector_create(data, 8);
	repack_slow(data);

	cout << "Slow algorithm result: ";
	print_vector(data);
	cout << endl;

	cout.setf(ios::fixed);
	cout << "Numbers of elements:" << setw(10) << 10000 << setw(10) << 100000 << endl;
	cout <<setw(20)<< "Fast algorithm time:" << setw(8) << algorithm_count(data, 1000, 1) << "ms";
	cout << setw(8) << algorithm_count(data, 10000, 1)<<"ms"<<endl;

	cout << setw(20)<< "Slow algorithm time:" << setw(8) << algorithm_count(data, 1000, 2)<<"ms";
	cout << setw(8) << algorithm_count(data, 10000, 2)<<"ms"<<endl;

	cout << "Complexity of Fast algorithm : o(N)" << endl;
	cout << "Complexity of Slow algorithm : o(N^2)" << endl;

	system("pause");
	return 0;
}

void print_vector(const vector<int>& data)

{
	for (const int& n : data)
		cout << n << " ";
	cout << endl;
}

void repack_fast(vector<int>& data)
{
	vector<int> data2 = data;
	vector<int> data3 = data;
	reverse(data2.begin(), data2.end());
	int step = 0;
	for (int i = 0; i < data.size(); ++i) {
		if (i % 2) {
			data3[i] = data2[step];
			++step;
		}
		else {
			data3[i] = data[step];
		}
	}
	data = data3;
}

void repack_slow(vector<int>& data)
{
	int step = 0;
	for (int i = 0; i < data.size(); ++i) {
		if (i % 2) {
			int last = data[data.size()-1];
			for (int j = data.size()-1; j > i; --j) {
				data[j] = data[j - 1];
			}
			data[i] = last;
		}
	}
}

void vector_create(vector<int>& data, const int & N)
{
	data.clear();
	for (int i = 1; i <= N; ++i) {
		data.push_back(i);
	}
}

unsigned int algorithm_count(vector<int>& data, int N, int algo)
{

	unsigned int start_time;
	unsigned int end_time;

	vector_create(data, N);
	if (algo == 1) {
		start_time = clock();
		repack_fast(data);
		end_time = clock();
	}
	else {
		start_time = clock();
		repack_slow(data);
		end_time = clock();
	}

	return end_time - start_time;
}