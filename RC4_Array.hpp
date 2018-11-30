#ifndef RC4_ARRAY_HPP
#define RC4_ARRAY_HPP

const int MAXBITS = 8;

//============================================Constructors/Destructor//
template <class D>
RC4_Array<D>::RC4_Array()
{
	msgString		= "";
	keyString		= "";
	cipherText		= "";
	plainText		= "";
	msgLength		= 0;
	keyLength		= 0;
	indexArraySize	= 0;
	K				= NULL;
	S				= NULL;
	T				= NULL;
	bitStream		= NULL;
}


template <class D>
RC4_Array<D>::RC4_Array(string msg, int mLen, string key, int kLen)
{
	msgString		= msg;
	keyString		= key;
	cipherText		= "";
	plainText		= "";
	msgLength		= mLen;
	keyLength		= kLen;
	indexArraySize	= 256;

	K = new D[keyLength];
	if(K != NULL)
		for(int i = 0; i < keyLength; i++)
			K[i] = 0;
	else
		ErrorMessage("Invalid memory allocation -- @ K[] paramaterized constructor");

	S = new D[indexArraySize];
	T = new D[indexArraySize];
	if(S != NULL && T != NULL) {
		for(int i = 0; i < indexArraySize; i++) {
			S[i] = i;
			T[i] = 0;
		}
	}
	else
		ErrorMessage("Invalid memory allocation -- @ S[] or T[] paramaterized constructor");

	bitStream = new string[msgLength];
	if(bitStream != NULL)
		for(int i = 0; i < msgLength; i++)
			bitStream[i] = "";
	else
		ErrorMessage("Invalid memory allocation -- @ bitStream[] paramaterized constructor");
}


template <class D>
RC4_Array<D>::~RC4_Array()
{
	delete [] K;
	delete [] S;
	delete [] T;
	delete [] bitStream;
}


template <class D>
void RC4_Array<D>::ErrorMessage(string s) const
{
	cout << "ERROR -- " << s << "\n\n";
	system("pause");
	exit(EXIT_SUCCESS);
}



//============================================Conversion functions//
template <class D>
int RC4_Array<D>::Power(int a, int b) // Raises int a to the power of int b
{
	int c = a;

	if(b != 0)
		for(int i = 0; i < (b - 1); i++)
			c *= a;
	else
		c = 1;

	return c;
}


// Convert a 4-bit binary string to hex char
template <class D>
char RC4_Array<D>::BinToHex(string s)
{
	char c = ' ';
	char cArr[4] = { s[0], s[1], s[2], s[3] };

	if(s[0] == '0' && s[1] == '0' && s[2] == '0' && s[3] == '0') { c = '0'; }
	else if(s[0] == '0' && s[1] == '0' && s[2] == '0' && s[3] == '1') { c = '1'; }
	else if(s[0] == '0' && s[1] == '0' && s[2] == '1' && s[3] == '0') { c = '2'; }
	else if(s[0] == '0' && s[1] == '0' && s[2] == '1' && s[3] == '1') { c = '3'; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '0' && s[3] == '0') { c = '4'; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '0' && s[3] == '1') { c = '5'; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '1' && s[3] == '0') { c = '6'; }
	else if(s[0] == '0' && s[1] == '1' && s[2] == '1' && s[3] == '1') { c = '7'; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '0' && s[3] == '0') { c = '8'; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '0' && s[3] == '1') { c = '9'; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '1' && s[3] == '0') { c = 'A'; }
	else if(s[0] == '1' && s[1] == '0' && s[2] == '1' && s[3] == '1') { c = 'B'; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '0' && s[3] == '0') { c = 'C'; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '0' && s[3] == '1') { c = 'D'; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '1' && s[3] == '0') { c = 'E'; }
	else if(s[0] == '1' && s[1] == '1' && s[2] == '1' && s[3] == '1') { c = 'F'; }
	else { ErrorMessage("Incorrect bit sqeuence -- [@BinToHex]"); }

	return c;
}


// Convert a hex char to a 4-bit binary string
template <class D>
int RC4_Array<D>::HexToDec(char c)
{
	int n = -1;
	
	switch(c) {
		case '0': { n = 0;  break; }
		case '1': { n = 1;  break; }
		case '2': { n = 2;  break; }
		case '3': { n = 3;  break; }
		case '4': { n = 4;  break; }
		case '5': { n = 5;  break; }
		case '6': { n = 6;  break; }
		case '7': { n = 7;  break; }
		case '8': { n = 8;  break; }
		case '9': { n = 9;  break; }
		case 'A': { n = 10; break; }
		case 'B': { n = 11; break; }
		case 'C': { n = 12; break; }
		case 'D': { n = 13; break; }
		case 'E': { n = 14; break; }
		case 'F': { n = 15; break; }
	}

	if (n == -1)
		ErrorMessage("Incorrect hex char -- [@HexToDec]");

	return n;
}


// Convert a hex char to a 4-bit binary string
template <class D>
string RC4_Array<D>::HexToBin(char c)
{
	string s = " ";
	
	switch(c) {
		case '0': { s = "0000"; break; }
		case '1': { s = "0001"; break; }
		case '2': { s = "0010"; break; }
		case '3': { s = "0011"; break; }
		case '4': { s = "0100"; break; }
		case '5': { s = "0101"; break; }
		case '6': { s = "0110"; break; }
		case '7': { s = "0111"; break; }
		case '8': { s = "1000"; break; }
		case '9': { s = "1001"; break; }
		case 'A': { s = "1010"; break; }
		case 'B': { s = "1011"; break; }
		case 'C': { s = "1100"; break; }
		case 'D': { s = "1101"; break; }
		case 'E': { s = "1110"; break; }
		case 'F': { s = "1111"; break; }
	}

	if (s == " ")
		ErrorMessage("Incorrect hex char -- [@HexToBin]");

	return s;
}


// Convert an int to a MAXBITS-sized binary string
template <class D>
string RC4_Array<D>::AnyDecToBin(int n)
{
	int x = n;
	char a[MAXBITS];
	string result = "";

	for(int i = MAXBITS - 1; i >= 0; i--)
	{
		if (x - Power(2, i) >= 0)
		{
			a[i] = '1';
			x = x - Power(2, i);
		}
		else
			a[i] = '0';
	}

	for(int i = MAXBITS - 1; i >= 0; i--)
		result += a[i];

	return result;
}


//============================================Permutation functions//
template <class D>
void RC4_Array<D>::PrintArrays() const
{
	PrintK();
	PrintS();
	PrintT();
}


template <class D>
void RC4_Array<D>::PrintK() const
{
	cout << "K:\n";
	for(int i = 0; i < keyLength; i++)
	{
		cout << K[i] << " ";
		if((i + 1) % 20 == 0)
			cout << "\n";
	}
	cout << "\n\n";
}


template <class D>
void RC4_Array<D>::PrintS() const
{
	cout << "S:\n";
	for(int i = 0; i < indexArraySize; i++)
	{
		cout << S[i] << " ";
		if((i+1) % 20 == 0)
			cout << "\n";
	}
	cout << "\n\n";
}


template <class D>
void RC4_Array<D>::PrintT() const
{
	cout << "T:\n";
	for(int i = 0; i < indexArraySize; i++)
	{
		cout << T[i] << " ";
		if((i+1) % 20 == 0)
			cout << "\n";
	}
	cout << "\n\n";
}


template <class D>
void RC4_Array<D>::PopulateK()
{
	for(int i = 0; i < keyLength; i++)
		K[i] = HexToDec(keyString[i]);
}


template <class D>
void RC4_Array<D>::PopulateT()
{
	for(int i = 0; i < indexArraySize; i++)
		T[i] = K[i % keyLength];
}


template <class D>
void RC4_Array<D>::Swap(D &a, D &b)
{
	D temp;
	temp = a;
	a = b;
	b = temp;
}


template <class D>
void RC4_Array<D>::PermuteS()
{
	int j = 0, temp = 0;

	for(int i = 0; i < indexArraySize; i++)
	{
		j = (j + S[i] + T[i]) % indexArraySize;
		Swap(S[i], S[j]);
	}
}


template <class D>
void RC4_Array<D>::StreamGeneration()
{
	int j = 0;
	string tempStr;

	for(int i = 0, k = 0; i < (msgLength / 2); i = ((i + 1) % indexArraySize), k += 2)
	{
		tempStr = "";
		j = (j + S[i]) % indexArraySize;

		Swap(S[i], S[j]);

		tempStr = AnyDecToBin(S[(S[i] + S[j]) % indexArraySize]);

		for(int n = 0; n < 4; n++)
		{
			bitStream[k] += tempStr[n];
			bitStream[k + 1] += tempStr[n + 4];
		}
	}
}


template <class D>
void RC4_Array<D>::Encrypt()
{
	string cipherByte = "", msgByte = "";

	cout << "\nEncrypting . . .\n\n";

	for(int i = 0; i < msgLength; i++)
	{ 
		cipherByte = bitStream[i];

		msgByte = HexToBin(msgString[i]);

		for(int j = 0; j < 4; j++)
			cipherByte[j] = (msgByte[j] ^ cipherByte[j]) ? '1' : '0';

		cipherText += BinToHex(cipherByte);
	}

	cout << "Ciphertext: " << cipherText << "\n\n";
}


template <class D>
void RC4_Array<D>::Decrypt()
{
	string cipherByte = "", msgByte = "";

	cout << "\nDecrypting . . .\n\n";

	for(int i = 0; i < msgLength; i++)
	{ 
		cipherByte = bitStream[i];

		msgByte = HexToBin(cipherText[i]);

		for(int j = 0; j < 4; j++)
			cipherByte[j] = (msgByte[j] ^ cipherByte[j]) ? '1' : '0';

		plainText += BinToHex(cipherByte);
	}

	cout << "Plaintext: " << plainText << "\n\n\n";
}

#endif