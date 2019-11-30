#include "headMathLib.h"

mathLib::mathLib() 
{
}

int mathLib::Modulo(int a, int n) 
{
	int res = a - n * (a / n);
	if (res < 0)
		res += n;
	return res;
}

ZZ mathLib::getMod(ZZ d, ZZ a)
{
	ZZ q = d / a;
	ZZ r = d - (q * a);
	if (r < 0) {
		r += a;
	}
	return r;
}

string mathLib:: zz_a_string(const ZZ& z) 
{
	std::stringstream buffer;
	buffer << z;
	return buffer.str();
}

ZZ mathLib::string_a_zz(string message) 
{
	NTL::ZZ number(NTL::INIT_VAL, message.c_str());
	return number;
}

ZZ mathLib::modulo(ZZ a, ZZ n)
{
	ZZ res = a - n * (a / n);
	if (res < 0)
		res += n;
	return res;
}
ZZ mathLib::algEuclides(ZZ a, ZZ b) {
	ZZ m;
	m = getMod(a, b);
	while (m != 0) {
		a = b;
		b = m;
		m = getMod(a, b);
	}
	return b;
}

ZZ mathLib::algEuclidesExt(ZZ a, ZZ b) {
	ZZ x, y, x2, x1, y2, y1, q, r;
	if (b == 0) {
		x2 = 1;
	}
	else {
		x = 0;
		y = 0;
		x1 = 0;
		x2 = 1;
		y2 = 0;
		y1 = 1;
		q = 0;
		r = 0;
		while (b != 0) {
			q = a / b;
			r = getMod(a, b);
			x = x2 - q * x1;
			y = y2 - q * y1;
			a = b;
			b = r;
			x2 = x1;
			x1 = x;
			y2 = y1;
			y1 = y;
		}
	}
	return x2;

}

ZZ mathLib::Inversa(ZZ a, ZZ l) {
	a = algEuclidesExt(a, l);
	if (a < 0) {
		a = a + l;
	}
	else if (a >= l) {
		a = getMod(a, l);
	}
	//cout<<"Inversa: "<<a<<endl;
	return a;
}
int mathLib::getModInt(int d, int a) {
	int q = d / a;
	int r = d - (q * a);
	if (r < 0) {
		r += a;
	}
	return r;
}
void shiftLeft(vector<bool>& a, int inicio, int fin) {
	bool val;
	val = a[inicio];
	a.erase(a.begin());
	a.insert(a.begin() + fin, val);
}
void shiftRight(vector<bool>& a, int inicio, int fin) {
	bool val;
	val = a[fin];
	a.erase(a.begin() + fin);
	a.insert(a.begin() + inicio, val);
}
ZZ mathLib::genetareRandom(int sizeSeed, int sizeNumber, int numPar, int loops) {
	vector<bool> seed;
	bool control = 1;
	int ini, increment, fin;
	ZZ res;
	ini = 0;
	long n = 0;
	res = 0;
	int l = 2;
	increment = sizeNumber / numPar;
	if (getModInt(sizeNumber, numPar) != 0) {
		increment += 1;
	}
	fin = increment - 1;

	for (int i = 0; i < sizeSeed; i++) {
		int* foo;
		foo = new  int[1];
		int val = getModInt((*foo) + (time(0)), 2);
		seed.push_back(val);
		delete[] foo;

	}
	for (int i = 0; i < sizeNumber; i++) {
		int temp;
		temp = seed[i] + seed[i + 1];
		if (temp >= 2) {
			temp = getModInt(temp, l);
		}
		seed.push_back(temp);
	}
	for (int j = 0; j < numPar; j++) {
		for (int k = 0; k < loops; k++) {
			if (control) {
				shiftLeft(seed, ini, fin);
			}
			else {
				shiftRight(seed, ini, fin);
			}
			control = !control;
		}

		ini += increment;
		fin += increment;
		if (fin >= seed.size()) {
			fin = seed.size() - 1;
		}
	}
	seed[sizeNumber - 1] = 1;
	for (int i = sizeNumber; i >= 1; i--) {
		if (seed[i - 1]) {
			res += power2_ZZ(n);
		}
		n = n + 1;
	}
	//cout<<res<<endl;
	return res;

}

ZZ mathLib::resch(vector<ZZ> a, vector<ZZ> p) {
	ZZ qInv = euclext(p[1], p[0]);
	ZZ tam = to_ZZ(a.size());
	for (int i = 0; i < tam; i++) {
		a[i] = modulo(a[i], p[i]);
	}
	ZZ h = modulo(qInv * modulo(a[0] - a[1], p[0]), p[0]);
	ZZ m = a[1] + h * p[1];
	return m;
}

ZZ mathLib::euclext(ZZ a, ZZ b) 
{
	ZZ d, x, y, q, r;
	ZZ x2 = ZZ(1);
	ZZ x1 = ZZ(0);
	ZZ y2 = ZZ(0);
	ZZ y1 = ZZ(1);
	if (b == 0) {
		d = a;
		x = ZZ(1);
		y = ZZ(1);
	}
	while (b > 0) {
		q = a / b;
		r = a - q * b;
		x = x2 - q * x1;
		y = y2 - q * y1;
		a = b;
		b = r;
		x2 = x1;
		x1 = x;
		y2 = y1;
		y1 = y;
	}
	d = a;
	x = x2;
	y = y2;
	return x;
}

ZZ mathLib::MulMod(ZZ a, ZZ b, ZZ mod) 
{
	ZZ x, y, c;
	c = 2;
	x = 0;
	y = getMod(a, mod);
	while (b > 0)
	{
		if (getMod(b, c) == 1)
		{
			x = getMod((x + y), mod);
		}
		y = getMod((y * c), mod);
		b = b / c;
	}
	return getMod(x, mod);
}
bool mathLib::testMiller(ZZ pseudoPrime, int iteration) {
	ZZ s, a, temp, mod, c;
	c = 2;
	if (pseudoPrime < c)
	{
		return false;
	}
	if (pseudoPrime != c && getMod(pseudoPrime, c) == 0)
	{
		return false;
	}
	s = pseudoPrime - 1;
	while (getMod(s, c) == 0)
	{
		s /= 2;
	}
	for (int i = 0; i < iteration; i++)
	{
		a = getMod(genetareRandom(16, 1024, 16, 8), (pseudoPrime - 1)) + 1;
		temp = s;
		mod = modularExpo(a, temp, pseudoPrime);
		while (temp != pseudoPrime - 1 && mod != 1 && mod != pseudoPrime - 1)
		{
			mod = MulMod(mod, mod, pseudoPrime);
			temp *= 2;
		}
		if (mod != pseudoPrime - 1 && getMod(temp, c) == 0)
		{
			return false;
		}
	}
	return true;

}

ZZ mathLib::modularExpo(ZZ a, ZZ b, ZZ m) {
	ZZ ans, c;
	ans = 1;
	c = 2;
	while (b != 0) {
		if (getMod(b, c) == 1) {
			ans = getMod(ans * a, m);
		}
		a = getMod(a * a, m);
		b = b / 2;
	}
	return ans;
}

ZZ mathLib::expoM(ZZ a, ZZ e, ZZ N) 
{
	ZZ exp = ZZ(1);
	ZZ x = modulo(a, N);
	while (e > ZZ(0)) {
		if (modulo(e, ZZ(2)) == ZZ(1))
			exp = modulo(exp * x, N);
		x = modulo(x * x, N);
		e = e / ZZ(2);
	}
	return exp;
}

ZZ mathLib::expoMB(ZZ a, ZZ e, ZZ N) 
{
	int k = NumBits(e);
	ZZ c;
	if (bit(e, k - 1) == 1)
		c = a;
	else
		c = ZZ(1);
	for (int i = k - 2; i >= 0; i--) {
		c = modulo(c * c, N);
		if (bit(e, i) == 1)
			c = modulo(c * a, N);
	}
	return c;
}

bool mathLib::fermatTest(int numTests, ZZ pseudoPrime) {
	mathLib m;
	ZZ a, c;
	c = 1;
	if (pseudoPrime == 2) {
		return 1;
	}
	for (int i = 0; i < numTests; i++) {
		a = m.genetareRandom(16, 1024, 16, 8);
		if (a >= pseudoPrime) {
			a = m.getMod(a, pseudoPrime);
		}
		if (m.modularExpo(a, (pseudoPrime - c), pseudoPrime) == 1) {
			return 1;
		}
	}
	return 0;
}
ZZ mathLib::chineseReminder(vector<ZZ> ai, vector<ZZ> pi, ZZ n, ZZ k) {
	mathLib m;
	ZZ p, mi, inv, res, temp;
	res = 0;
	p = 1;
	long i = 0;
	for (i = 0; i < pi.size(); i++) {
		p *= pi[i];
	}
	for (i = 0; i < pi.size(); i++) {
		mi = p / pi[i];
		inv = m.Inversa(mi, pi[i]);
		temp = ai[i] * inv;/**mi*/
		if (temp >= p) {
			temp = m.getMod(temp, p);
		}
		temp = temp * mi;
		if (temp >= p) {
			temp = m.getMod(temp, p);
		}
		if (temp >= p) {
			temp = m.getMod(temp, p);
		}
		res += temp;
		if (res >= p) {
			res = m.getMod(res, p);
		}
	}
	res = res + n * k;
	return res;
}
ZZ mathLib::fingGen(ZZ p) {
	ZZ g, c, q;
	q = (p - 1) / 2;
	c = 2;
	for (int i = 1; i < p - 1; i++) {
		g = i;
		if ((modularExpo(g, c, p) != 1) && (modularExpo(g, q, p) != 1)) {
			return g;
		}
	}
	return g;
}

vector<ZZ>mathLib::RndNumber() {
	int pc1[] = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };
	int pc2[] = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32 };
	int vueltas[] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
	bitset<64> k;
	bitset<56> k1;
	bitset<28> c;
	bitset<28> d;
	bitset<48> num;
	vector<ZZ>res;
	long n = 0;
	ZZ result(0);

	for (int i = 0; i < 64; i++) {
		int* foo;
		foo = new  int[1];
		int val = getModInt((*foo) * time(0), 2);
		k[i] = val;
		delete[] foo;
	}

	for (int i = 55; i >= 0; i--) {
		k1[i] = k[pc1[i]];
	}

	for (int i = 0; i < 28; i++) {
		c[i] = k1[i];
		d[i] = k1[i + 28];
	}

	int first;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < vueltas[i]; j++) {
			first = c[0];
			c << 1;
			c[27] = first;
			first = d[0];
			d << 1;
			d[27] = first;
			for (int p = 28; p >= 0; p--) {
				k1[p] = c[p];
				k1[p + 28] = d[p];
			}

			for (int l = 47; l >= 0; l--) {
				num[l] = k1[pc2[l]];
			}
			num[0] = 1;
			unsigned long long t = num.to_ullong();
			//cout << t <<endl;
			for (int i = 47; i >= 0; i--) {
				if (num[i]) {
					result += power2_ZZ(n);
				}
				n = n + 1;
			}
			res.push_back(result);
		}
		cout << i << ": " << result << endl;
	}
	return res;
}

