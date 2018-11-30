#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#include "RC4_Array.h"

int main() {
	string key = "55586753090210",
		   plainText = "";

	bool validMessage = false;
	int failCount = 0,
		plainTextLen = 0;

	while (!validMessage && failCount < 10) {
		cout << "Enter the plaintext message (must be 16 hexidecimal characters long): ";
		cin >> plainText;

		if (plainText.length() == 16)
		{
			validMessage = true;
			plainTextLen = 16;
		}
		else
		{
			cout << "Invalid message length, try again:\n";
			failCount++;
		}
	}

	RC4_Array<int> RC4(plainText, plainTextLen, key, key.length());

	RC4.PopulateK();
	RC4.PopulateT();
	RC4.PermuteS();
	RC4.StreamGeneration();
	RC4.Encrypt();
	RC4.Decrypt();

	system("pause");
	return 0; 
}

/*
Encryption Input: 8 byte hex as the plaintext, one 7-byte hex as the key
Encryption Output: 8 bytes hex

Decryption Input: 8 bytes hex as the cipher text, one 7-byte hex as the key
Decryption Output: 8 byte hex characters
*/