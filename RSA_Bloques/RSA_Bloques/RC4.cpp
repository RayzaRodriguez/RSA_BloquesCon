#include "RC4.h"

RC4::RC4(int nBits)
{
	this->nBits = nBits;
}

string RC4::zToString(const ZZ z)
{
	stringstream buffer;
	buffer << z;
	return buffer.str();
}

ZZ RC4::getModule(ZZ a, ZZ b)
{
	ZZ res, q, r;
	q = a / b;
	r = a - q * b;
	if (r < 0)
	{
		r += b;
	}
	return r;
}

ZZ RC4::getCPUCicles()
{
	ZZ n(__rdtsc());
	return n;
}

void RC4::swapPositions(ZZ a, ZZ b)
{
	long a1, b1;
	conv(a1, a);
	conv(b1, b);
	ZZ temp = Si[a1];
	Si[a1] = Si[b1];
	Si[b1] = temp;
}

string RC4::generateRandomNumber()
{
	vector<string> res;
	for (int i = 0; i < this->nBits; ++i) {
		Si.push_back(conv<ZZ>(i));
		Ki.push_back(getCPUCicles());
	}

	ZZ f;
	ZZ c;
	f = 0;
	c = 0;
	for (int i = 0; i < this->nBits; ++i) {
		f = getModule(c + Si[i] + Ki[i], conv<ZZ>(this->nBits));
		swapPositions(f, c);
		++c;
	}
	c = 0;
	f = 0;
	long index;
	ZZ t;
	for (int i = 0; i < this->nBits; ++i) {
		c = getModule(c + 1, conv<ZZ>(this->nBits));
		f = getModule(f + Si[i], conv<ZZ>(this->nBits));
		conv(index, f);
		swapPositions(c, f);
		t = getModule(Si[i] + Si[index], conv<ZZ>(this->nBits));
		conv(index, t);
		res.push_back(zToString(Si[index]));
	}
	Si.clear();
	Ki.clear();
	string r = convertirBits(res);
	return r;
}

string RC4::convertirBits(vector<string> a)
{
	int num;
	for (int i = 0; i < a.size(); i++)
	{
		num = stoi(a[i]);
		string cad;
		if (num > 0)
		{
			while (num > 0)
			{
				if (num % 2 == 0)
					cad = "0" + cad;
				else
					cad = "1" + cad;
				num = num / 2;
			}
			binario += cad;
		}
	}
	return binario;
}

ZZ RC4::convertirBinaryToZZ(string binary)
{
	ZZ res;
	ZZ base;
	base = 2;
	res = 0;
	long exp = 0;
	for (long i = binary.size()-1; i >= 0; --i) {
		if (binary[i] == '1') {
			res += power(base, exp);
		}
		++exp;
	}

	return res;
}
