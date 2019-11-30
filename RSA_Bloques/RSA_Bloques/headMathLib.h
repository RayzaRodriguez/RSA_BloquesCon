#pragma once
#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <sstream>
#include <time.h>
#include <math.h>
#include <bitset>
using namespace std;
using namespace NTL;
class mathLib {
public:
	mathLib();
	ZZ modulo(ZZ a, ZZ n);
	int Modulo(int a, int n);
	ZZ getMod(ZZ d, ZZ a);
	string zz_a_string(const ZZ& z);
	ZZ string_a_zz(string message);
	int getModInt(int a, int b);
	ZZ algEuclides(ZZ a, ZZ b);
	ZZ algEuclidesExt(ZZ a, ZZ b);
	ZZ MulMod(ZZ a, ZZ b, ZZ mod);
	ZZ Inversa(ZZ a, ZZ l);
	ZZ genetareRandom(int tamSeed, int tamNum, int numPart, int loops);
	ZZ resch(vector<ZZ> a, vector<ZZ> p);
	ZZ euclext(ZZ a, ZZ b);
	bool testMiller(ZZ pseudoPrime, int numTest);
	ZZ modularExpo(ZZ a, ZZ b, ZZ m);
	ZZ expoM(ZZ a, ZZ e, ZZ N);
	ZZ expoMB(ZZ a, ZZ e, ZZ N);
	bool fermatTest(int numTests, ZZ pseudoPrime);
	ZZ chineseReminder(vector<ZZ> ai, vector<ZZ> pi, ZZ n, ZZ i);
	ZZ fingGen(ZZ p);
	vector<ZZ> RndNumber();
};