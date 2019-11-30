#pragma once
#include <iostream>
#include <sstream>
#include "RC4.h"
#include "headMathLib.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace NTL;
class rsa
{
private:
	string alfabeto = "abcdefghijklamnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
	string mensaje;
	int nBits;
	ZZ p;
	ZZ q;
	ZZ n;
	ZZ phiN;
	ZZ e;
	ZZ d;
	ZZ eB;
	ZZ NB;
	int Ndig;
	int k;
	int NdigB;
	int kB;
	ZZ ap;
	ZZ aq;
	ZZ dq;
	ZZ dp;
public:
	rsa(int);
	rsa(ZZ , ZZ);
	void generatePrimerNumbers();
	void mostrar();
	void generarE();
	string cifrar(string);
	string toNumbers(string);
	string formatInt(int, int);
	string toBloques(string, int);
	string formatZZ(ZZ, int);
	string descifrar(string);
	string descifra(string);
	string fromBloques(string, int);
};

