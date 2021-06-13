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

class bit_vect
{
	int max_val;
	int v_size;

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

	vector<bool> vect;

	bit_vect()
	{
		v_size = 0;
		max_val = 0;
	}

	bit_vect(int size)
	{
		this->v_size = size;
		vect.resize(size, true);
		max_val = bin_to_int_v(vect);
		clear();
	}

	bit_vect(string str)
	{
		vect.resize(str.size());
		max_val = bin_to_int_v(vect);
		clear();
		string_to_bin(str);
	}

	void clear()
	{
		vect.clear();
		vect.resize(v_size);
	}

	void resize(int size)
	{
		this->v_size = size;
		vect.resize(size, true);
		max_val = bin_to_int_v(vect);
		clear();
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

	int size()
	{
		return v_size;
	}
};


class coordinate
{
	bit_vect x, y;

public:

	bit_vect x_res, y_res;

	coordinate(bit_vect X, bit_vect Y) : x(X), y(Y) {};

	void setbv(bit_vect X, bit_vect Y)
	{
		x = X;
		y = Y;
	}

	void seti(int X, int Y)
	{
		x.int_to_bin(X);
		y.int_to_bin(Y);
	}

	//φε υσινÿ
	void recalc(vector<int> rx, vector<int> ry)
	{
		x_res.resize(rx.size());
		y_res.resize(ry.size());

		for (int i = 0; i < rx.size(); i++)
		{
			if (rx[i] <= (x.size() - 1))
			{
				x_res.vect[i] = x.vect[rx[i]];
			}
			else
			{
				x_res.vect[i] = y.vect[rx[i] - x.size()];
			}
		}

		for (int i = 0; i < ry.size(); i++)
		{
			int pos;
			if (ry[i] <= (x.size() - 1))
			{
				pos = ry[i];
				y_res.vect[i] = x.vect[pos];
			}
			else
			{
				pos = ry[i] - x.size();
				y_res.vect[i] = y.vect[pos];
			}
		}
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
		vector<int> x_dems, y_dems;
		bool is_x = true;
		for (auto& c : str)
		{
			if (is_x)
			{
				if (c == ';')
				{
					is_x = false;
				}
				else
				{
					if (c != ',')
					{
						if (isalnum(c))
							x_dems.push_back(c - 49);
					}
				}

			}
			else
			{
				if (c == ';')
				{
					break;
				}
				else
				{
					if (c != ',')
					{
						if (isalnum(c))
							y_dems.push_back(c - 49);
					}
				}
			}
		}

		int x_res_size = pow(2, x_dems.size());
		int y_res_size = pow(2, y_dems.size());
		result.resize(x_res_size, vector<char>(y_res_size, ' '));

		bit_vect a(xs_size);
		bit_vect b(ys_size);
		coordinate cc(a, b);
		int newx, newy;

		for (int i = 0; i < pow(2, ys_size); i++)
		{
			for (int j = 0; j < pow(2, xs_size); j++) 
			{
				cc.seti(i, j);
				cc.recalc(x_dems, y_dems);
				newx = cc.x_res.bin_to_int();
				newy = cc.y_res.bin_to_int();
				result[newx][newy] = matrix[j][i];
			}
		}

		for (int i = 0; i < y_res_size; i++)
		{
			for (int j = 0; j < x_res_size; j++)
			{
				cout << result[j][i] << ";";
			}
			cout << endl;
		}
		
		
	}

};


int main()
{
	/*bit_vect A(8);
	A.int_to_bin(251);
	A.string_to_bin("0111");
	A.vect[5] = true;
	cout << A.bin_to_int() << endl;
	A.clear();
	cout << A.bin_to_int() << endl;*/


	/*bit_vect a(4);
	bit_vect b(4);
	a.string_to_bin("0111");
	b.string_to_bin("0110");

	coordinate C(a, b);

	vector<int> aa = { 2,3,4 };
	vector<int> bb = { 5,6,7,0,1 };

	C.recalc(aa, bb);

	C.x_res.clear();
	C.y_res.clear();*/

	string filename;
	cout << "Filename: ";
	cin >> filename;

	matrix_reshape m(filename);
	m.print_src();
	string reshape_str;
	cout << "Input sequence: ";
	cin >> reshape_str;
	m.reshape(reshape_str);
}