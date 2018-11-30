#ifndef RC4_ARRAY_H
#define RC4_ARRAY_H

template <class D>
class RC4_Array {
	private:
		string msgString;
		string keyString;
		string cipherText;
		string plainText;
		int msgLength;
		int keyLength;
		int indexArraySize;
		D *K;
		D *S;
		D *T;
		string *bitStream;

	public:
		RC4_Array();
		RC4_Array(string, int, string, int);
		~RC4_Array();
		void ErrorMessage(string) const;
		int Power(int, int);
		char BinToHex(string);
		int HexToDec(char);
		string HexToBin(char);
		string AnyDecToBin(int);
		void PrintArrays() const;
		void PrintK() const;
		void PrintS() const;
		void PrintT() const;
		void PopulateK();
		void PopulateT();
		void PermuteS();
		void Swap(D &, D &);
		void StreamGeneration();
		void Encrypt();
		void Decrypt();
};

#include "RC4_Array.hpp"

#endif