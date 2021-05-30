#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

string string_revert(string str)
{
	if (str.size() <= 1)
	{
		throw invalid_argument("R U rTARD?");
		exit(-1);
	}

	int str_size = str.size() - 1;
	for (int i = 0; i < (str_size + 1) / 2; i++)
	{
		char ch = str[i];
		str[i] = str[str_size - i];
		str[str_size - i] = ch;
	}

	return str;
}

class bin_vect
{
	vector<bool> vect;
	int max_val;
	int size;

	int bin_to_int_v(vector<bool> v)
	{
		int result = 0;

		for (size_t i = 0; i < v.size(); i++)
		{
			result += v[i] * pow(2, i);
		}

		return result;
	}
public:
	bin_vect(int size)
	{
		this->size = size;
		vect.resize(size, true);
		max_val = bin_to_int_v(vect);
		clear();
	}
	bin_vect(string str)
	{
		vect.resize(str.size());
		max_val = bin_to_int_v(vect);
		clear();
		string_to_bin(str);
	}
	void clear()
	{
		vect.clear();
		vect.resize(size);
	}
	void int_to_bin(int val)
	{
		clear();
		if (val > max_val || val < 0)
		{
			throw invalid_argument("R U rTARD?");
			exit(-1);
		}

		for (int i = vect.size() - 1; i >= 0; i--)
		{
			int powi = pow(2, i);
			if ((val - powi) >= 0)
			{
				val = val - powi;
				vect[i] = true;
			}
			else
			{
				vect[i] = false;
			}
		}
	}

	void string_to_bin(string str)
	{
		clear();
		str = string_revert(str);
		if(str.size() > vect.size())
		{
			throw invalid_argument("R U rTARD?");
			exit(-1);
		}

		for (size_t i = 0; i < str.size(); i++)
		{
			vect[i] = (bool)((int)str[i] - 48);
		}
	}

	int bin_to_int()
	{
		int result = bin_to_int_v(vect);
		return result;
	}
};


class matrix_reshape
{
	vector<vector<char>> matrix;
	vector<vector<char>> result;
	int xs_size, ys_size;
public:
	matrix_reshape(string filename)
	{
		ifstream file(filename);
		char ch;
		file.read(&ch, 1);
		xs_size = ch - 48;
		file.read(&ch, 1);
		file.read(&ch, 1);
		ys_size = ch - 48;

		int xs_pow = pow(2, xs_size);
		int ys_pow = pow(2, ys_size);
		matrix.resize(xs_pow, vector<char>(ys_pow, ' '));
		file.seekg(file.beg);
		file.seekg(2);
		string tmp_str;

		for (int j = 0; j < ys_pow + ys_size; j++)
		{
			if (j >= 4)
			{
				file >> tmp_str;
				for (int i = 0; i < 2 * (xs_pow + xs_size); i += 2)
				{
					if (i >= 2 * xs_size)
					{
						matrix[j - ys_size][i / 2 - xs_size] = tmp_str[i];
					}
				}
			}
			else
			{
				file >> tmp_str;
			}
		}
		file.close();
	}

	void print_src()
	{
		for (auto& s : matrix)
		{
			for (auto& i : s)
			{
				cout << i << ";";
			}
			cout << endl;
		}
	}

	void reshape(string str)
	{

	}

};


int main()
{
	bin_vect A(8);
	A.int_to_bin(251);
	A.string_to_bin("0111");
	cout << A.bin_to_int() << endl;
	A.clear();
	cout << A.bin_to_int() << endl;

	string filename;
	cout << "Filename: ";
	cin >> filename;
	
	matrix_reshape m(filename);
	m.print_src();
}