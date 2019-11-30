#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include<fstream>
#include <sstream>
#include <vector>
#include <sstream>
#include "rsa.h"

using namespace std;
using namespace NTL;

int main()
{
	rsa r(20);
	r.mostrar();
	//    Emisor.eB=receptor.e;
	//    Emisor.NB=receptor.N;



	int op;
	do {
		cout << " ELIGE UNA OPCION: " << endl;
		cout << " 1. ENCRIPTAR " << endl;
		cout << " 2. DESENCRIPTAR " << endl;
		cout << " 3. SALIR " << endl;
		cin >> op;
		switch (op)
		{
		case 1: {

			string linea;
			string message;
			ifstream MSJ("plaintext.txt");
			if (MSJ.is_open())
			{
				while (!MSJ.eof())
				{
					getline(MSJ, linea);
					message += linea;
				}
				MSJ.close();
			}

			string Cipher = r.cifrar(message);
			cout << "MSJ Cifrado: " << endl << Cipher << endl;
			ofstream ciphertext;
			ciphertext.open("ciphertext.txt");
			ciphertext << Cipher;
			break; 
		}

		case 2: 
		{

			string Cipher;
			string linea;
			ifstream CIPHER("ciphertext.txt");
			if (CIPHER.is_open())
			{
				while (!CIPHER.eof())
				{
					getline(CIPHER, linea);//lee linea a linea reconociendo el enter
					Cipher += linea;
				}
				CIPHER.close();
			}
			//
			cout << Cipher << endl;
			string Descipher;
			Descipher = r.descifrar(Cipher);
			cout << "MSJ Descifrado: " << endl;
			cout << Descipher << endl;


			break; }
		}
	} while (op != 3);

	system("pause");
	return 0;

}
