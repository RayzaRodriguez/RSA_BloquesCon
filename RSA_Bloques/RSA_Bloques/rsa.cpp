#include "rsa.h"

rsa::rsa(int nBits)
{
	this->nBits = nBits;
	generatePrimerNumbers();
	n = p * q;
	phiN = (p-1) * (q-1);
	generarE();
}

rsa::rsa(ZZ e_, ZZ n_)
{
	e = e_;
	n = n_;
}

void rsa::generatePrimerNumbers()
{
	RC4 r(nBits);
	mathLib p;
	string binario;
	vector <string> a;
	binario = r.generateRandomNumber();
	//string temp = r.zToString(r.convertirBinaryToZZ(binario));
	
	int count = 0;
	ZZ number;
	
	for (int i = 0; i < binario.size() - nBits - 1; i++)
	{
		string tem = binario.substr(i, nBits);
		tem[tem.size()-1] = '1';
		tem[(nBits / 2)] = '1';
		tem[(nBits / 2)+1] = '1';
		number = r.convertirBinaryToZZ(tem);
		//cout << tem << endl;
		if (number == 0) {
			continue;
		}

		if (p.fermatTest(10, number))
		{
			if (count == 0) 
			{
				this->p = number;
				++count;
				continue;
			}
			else if(count == 1) 
			{
				this->q = number;
				++count;
				break;
			}
			break;
		}
	}
}

void rsa::mostrar()
{
	cout << "PhiN: " << phiN << endl;
	cout << "N: " << n << endl;
	cout << "p: " << p << endl;
	cout << "q: " << q << endl;
	cout << "e: " << e << endl;
	cout << "d: " << d << endl;

}

void rsa::generarE()
{
	srand(time(NULL));
	mathLib r;
	ZZ t;
	t = rand();
	//cout << "T = " << t << endl;
	t = r.modulo((t * t) + phiN,phiN);
	//t = r.getMod(phiN,t);
	//cout << "T*T - phi = " << t << endl;
	if (r.algEuclides(t, phiN) == 1)
	{
		e = t;
		d=r.algEuclidesExt(e, phiN);
		d = r.getMod(d, phiN);
	}
	else
		generarE();
}

string rsa::cifrar(string _mensaje)
{
	mathLib x;
	mensaje = _mensaje;
	_mensaje = toNumbers(_mensaje);
	string rub, fd;
	string rubtmp, fdtmp;

	//Ndig = zToString(n).length();
	Ndig = x.zz_a_string(n).length();
	k = Ndig - 1;
	
	//NdigB = zzToString(n).length();
	NdigB = x.zz_a_string(n).length();
	kB = NdigB - 1;
	string resTemp = toBloques(_mensaje, Ndig);
	string res;
	ZZ opera;
	int nBloques = resTemp.length() / k;
	for (int i=0;i<nBloques;++i)
	{
		opera = x.string_a_zz(resTemp.substr(i * k, k).c_str());
		opera = x.expoMB(opera, e, n);
		res += formatZZ(opera, Ndig);
	}
	return res;
}

string rsa::toNumbers(string _mensaje)
{
	string res, digAct;
	int digsizAlf = to_string(alfabeto.size()).length();
	for (int i = 0; i < _mensaje.size(); ++i)
	{
		digAct = _mensaje[i];
		res += formatInt(alfabeto.find(digAct), digsizAlf);
	}
	return res;
}

string rsa::formatInt(int num, int dig)
{
	string res;
	res = to_string(num);
	int difeSize = dig - res.length();
	while (difeSize > 0)
	{
		res = '0' + res;
		difeSize--;
	}
	return res;
}

string rsa::toBloques(string _mensaje, int sizN)
{
	mathLib x;
	string fill = to_string(22);
	int k = sizN - 1;
	int ite = x.Modulo(_mensaje.length(), k);
	if (ite == 0)
		return _mensaje;
	ite = k - ite;
	int i = 0;
	while (i < ite)
	{
		_mensaje += fill[x.Modulo(i, fill.length())];
		i++;
	}
	return _mensaje;
}

string rsa::formatZZ(ZZ num, int dig)
{
	string res;
	mathLib x;
	//res += zzToString(num);
	res += x.zz_a_string(num);
	int difeSize = dig - res.length();
	while (difeSize > 0)
	{
		res = '0' + res;
		difeSize--;
	}
	return res;
}

string rsa::descifrar(string _mensaje)
{
	string res;
	ZZ opera;
	mathLib x;
	int nBloques = _mensaje.length() / Ndig;
	for (int i = 0; i < nBloques; i++)
	{
		//opera = Stringtozz(_mensaje.substr(i * Ndig, Ndig));
		opera = x.string_a_zz(_mensaje.substr(i * Ndig, Ndig));
		ap = x.expoMB(opera, dp, p);
		aq = x.expoMB(opera, dq, q);
		vector<ZZ>a = { ap,aq };
		vector<ZZ>P = { p,q };
		opera = x.resch(a, P);
		res += formatZZ(opera, k);
	}
	return res;
}

string rsa::descifra(string msn)
{
	string res;
	string resTemp, fdtmp, rubtmp;
	mathLib x;
	//Ndig = zzToString(N).length();
	Ndig = x.zz_a_string(n).length();
	k = Ndig - 1;

	//NdigB = zzToString(N).length();
	NdigB = x.zz_a_string(n).length();
	kB = Ndig - 1;

	//firmadigital

	//rsa
	resTemp = descifrar(msn);

	//Convertir a mensaje
	res = fromBloques(resTemp, alfabeto.length());

	return res;
}

string rsa::fromBloques(string msn, int sizAlf)
{
	string res, digAct;
	int digsizAlf = to_string(sizAlf).length();
	int pos;

	int ite = msn.length() / digsizAlf;
	for (int i = 0; i < ite; i++) 
	{
		pos = stoi(msn.substr(i * digsizAlf, digsizAlf));
		res += alfabeto[pos];
	}
	return res;
}