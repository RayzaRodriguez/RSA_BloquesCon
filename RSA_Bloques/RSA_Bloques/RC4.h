#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <NTL/ZZ.h>
#include <intrin.h>
#include <bitset>
#include "headMathLib.h"
using namespace std;
using namespace NTL;

class RC4
{
private:
	vector<ZZ> Si;
	vector<ZZ> Ki;
	string binario;
	int nBits;
public:
	RC4(int nBits);
	string zToString(const ZZ z);
	ZZ getModule(ZZ a, ZZ b);
	ZZ getCPUCicles();
	void swapPositions(ZZ a, ZZ b);
	string generateRandomNumber();
	string convertirBits(vector <string> a);
	ZZ convertirBinaryToZZ(string binary);
};

