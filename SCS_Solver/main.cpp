#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

string string_revert(string str)
{
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

	int bin_to_int_v(vector<bool> v)
	{
		int result = 0;

		for (int i = 0; i < v.size(); i++)
		{
			result += v[i] * pow(2, i);
		}

		return result;
	}
public:
	bin_vect(int size)
	{
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
		for (auto i : vect)
		{
			i = false;
		}
	}
	void int_to_bin(int val)
	{
		clear();
		if (val > max_val || val < 0)
		{
			throw invalid_argument("R U rTARD?");
			return;
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
			return;
		}

		for (int i = 0; i < str.size(); i++)
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


int main()
{
	bin_vect A(8);
	A.int_to_bin(251);
	A.string_to_bin("0111");
	cout << A.bin_to_int() << endl;
	A.clear();
	cout << A.bin_to_int() << endl;

	/*string filename;
	cout << "Filename: ";
	cin >> filename;
	ifstream file(filename);
	char ch;
	while (!file.eof())
	{
		file.read(&ch, 1);
		cout << ch;
	}
	file.close();
	cout << endl;*/
}