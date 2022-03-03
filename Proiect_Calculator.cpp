#include <iostream>
#include <string.h>
#include <string>

using namespace std;


char* valInvalida;

class Operatie    //radica, punct, putere
{
private:
	char operatie;  //., #, ^
	double operand1;
	double operand2;
	static int impartirelaZero;

public:
	Operatie()
	{
		operatie = '+';
		operand1 = 0;
		operand2 = 0;
	}
	Operatie(char operatie, double operand1, double operand2)
	{
		this->operatie = operatie;
		this->operand1 = operand1;
		this->operand2 = operand2;
	}

	static int getImpartirelaZero()
	{
		return impartirelaZero;
	}
	static void setImpartirelaZero(int x)
	{
		if (x == 1 || x == 0)
		{
			impartirelaZero = x;
		}
		else
		{
			impartirelaZero = 0;
		}
	}

	void setOperatie(char operatie)
	{
		if (operatie == '+' || operatie == '-' || operatie == '*' || operatie == '/' || operatie == '^' || operatie == '#')
			this->operatie = operatie;
	}
	char getOperatie()
	{
		return operatie;
	}
	void setOperand1(double o1)
	{
		operand1 = o1;
	}
	double getOperand1()
	{
		return operand1;
	}
	void setOperand2(double o2)
	{
		operand2 = o2;
	}
	double getOperand2()
	{
		return operand2;
	}

	//double radical(double operand1, double operand2);
	static double putere(double operand1, double operand2)//op1 la puterea  op 2
	{
		if (operand1 == 0)
		{
			return 0;
		}
		if (operand2 == 0)
		{
			return 1;
		}
		if (operand2 < 0)
		{
			return 1 / putere(operand1, -operand2);  //rastorn fractia si pun la putere pozitiva
		}
		else if (operand2 > 0 && operand2 < 1)
		{
			return radical(operand1, 1 / operand2);
		}
		else if ((int)operand2 % 2 == 0)
		{
			double jumatate = putere(operand1, operand2 / 2);
			return jumatate * jumatate;
		}
		else
		{
			return operand1 * putere(operand1, operand2 - 1);
		}
	}
	static double radical(double operand1, double operand2)
	{
		const int k = 6;
		double x[k] = { 1 };
		for (int i = 0; i < k - 1; i++)
		{
			x[i + 1] = (1.0 / operand2) * ((operand2 - 1) * x[i] + operand1 / putere(x[i], operand2 - 1));
		}
		return x[k - 1];
	}

	double punct(double operand1, double operand2)
	{
		int nrCifre = 1;
		int copie = operand2;
		while (copie != 0)
		{
			copie /= 10;
			nrCifre *= 10;
		}
		double rezultat = operand1 + operand2 / nrCifre;
		return rezultat;
	}
	//calcul-2 operanzi si un simbol

	static double calcul(double operand1, char simbol, double operand2)
	{
		if (simbol == '+')
		{
			return operand1 + operand2;
		}
		if (simbol == '-')
		{
			return operand1 - operand2;
		}
		if (simbol == '*')
		{
			return operand1 * operand2;
		}
		if (simbol == '/')
		{
			if (operand2 != 0)
			{
				return operand1 / operand2;
			}
			else
			{
				impartirelaZero = 1;
				return 0;
			}
		}
		if (simbol == '^')
		{
			return putere(operand1, operand2);
		}
		if (simbol == '#')
		{
			return radical(operand1, operand2);
		}
	}


	//operatori
	//op ++
	Operatie operator++()
	{
		operand1++;
		return *this;
	}
	Operatie operator++(int i)
	{
		Operatie copie = *this;
		operand1++;
		return copie;
	}

	friend bool operator<=(const Operatie& o1, const Operatie& o2)
	{
		return o1.operand1 < o1.operand2;
	}

	friend istream& operator>>(istream& in, Operatie& op)
	{

		cout << "Operand 1: ";
		in >> op.operand1;
		cout << "Operatie: ";
		in >> op.operatie;
		cout << "Operand 2: ";
		in >> op.operand2;

		return in;
	}

	friend ostream& operator<<(ostream& out, Operatie op)
	{

		out << "Operand 1: " << op.operand1 << endl;
		out << "Operatie: " << op.operatie << endl;
		out << "Operand 2: " << op.operand2 << endl;

		return out;
	}


};

int Operatie::impartirelaZero = 0;




class Expresie    //calculez continutul parantezelor, nu va contine paranteze, //pot avea un double*pentru nuemerele din ecuatie
{
private:
	char* expresie;
	double* numere;
	int numarNumere;
	char* operatii;
	int numarOperatii;
	double rezultat;
	int prioritateMaxima;
	const int pi;

public:

	Expresie() :pi(3.14)
	{
		expresie = nullptr;
		numere = nullptr;
		numarNumere = 0;
		operatii = nullptr;
		numarOperatii = 0;
		rezultat = 0;
		prioritateMaxima = 1;
	}
	Expresie(char* expresie) :pi(3.14)
	{
		if (expresie != nullptr)
		{
			this->expresie = new char[strlen(expresie) + 1];
			strcpy_s(this->expresie, strlen(expresie) + 1, expresie);
		}
		else
		{
			this->expresie = nullptr;
		}
		numarNumere = 0;
		numarOperatii = 0;
		if (expresie != "")
		{
			numere = new double[strlen(expresie) + 1];
			operatii = new char[strlen(expresie) + 1];
		}
		rezultat = 0;
		prioritateMaxima = 1;
	}

	//constructor de copiere
	Expresie(const Expresie& e) :pi(e.pi)
	{

		numarNumere = e.numarNumere;
		numarOperatii = e.numarOperatii;
		rezultat = e.rezultat;
		prioritateMaxima = e.prioritateMaxima;
		if (e.expresie != nullptr)
		{
			expresie = new char[strlen(e.expresie) + 1];
			strcpy_s(expresie, strlen(e.expresie) + 1, e.expresie);
		}
		if (numarNumere > 0 && e.numere != nullptr)
		{
			numere = new double[numarNumere];
			for (int i = 0; i < numarNumere; i++)
			{
				numere[i] = e.numere[i];
			}
		}
		if (numarOperatii > 0 && e.operatii != nullptr)
		{
			operatii = new char[strlen(e.operatii) + 1];
			strcpy_s(operatii, strlen(e.operatii) + 1, e.operatii);
		}
	}

	//operator egal, de atribuire
	Expresie operator=(const Expresie& e)
	{
		if (numere != nullptr)
		{
			delete[] numere;
			numere = nullptr;
		}
		if (operatii != nullptr)
		{
			delete[] operatii;
			operatii = nullptr;
		}
		if (expresie != nullptr)
		{
			delete[] expresie;
			expresie = nullptr;
		}
		numarNumere = e.numarNumere;
		numarOperatii = e.numarOperatii;
		rezultat = e.rezultat;
		prioritateMaxima = e.prioritateMaxima;
		if (e.expresie != nullptr)
		{
			expresie = new char[strlen(e.expresie) + 1];
			strcpy_s(expresie, strlen(e.expresie) + 1, e.expresie);
		}
		if (numarNumere > 0 && e.numere != nullptr)
		{
			numere = new double[numarNumere];
			for (int i = 0; i < numarNumere; i++)
			{
				numere[i] = e.numere[i];
			}
		}
		if (numarOperatii > 0 && e.operatii != nullptr)
		{
			operatii = new char[strlen(e.operatii) + 1];
			strcpy_s(operatii, strlen(e.operatii) + 1, e.operatii);
		}
	}

	void setExpresie(char* expresie)
	{
		if (expresie != nullptr)
		{
			if (this->expresie != nullptr)
			{
				delete[] this->expresie;
			}
			this->expresie = new char[strlen(expresie) + 1];
			strcpy_s(this->expresie, strlen(expresie) + 1, expresie);
		}

	}
	char* getExpresie()
	{
		return expresie;
	}

	void setNumere(double* numere, int numarNumere)
	{
		if (numere != nullptr && numarNumere > 0)
		{
			if (this->numere != nullptr)
			{
				delete[] this->numere;
			}
			this->numere = new double[numarNumere];
			for (int i = 0; i <= numarNumere; i++)
			{
				this->numere[i] = numere[i];
			}
			this->numarNumere = numarNumere;
		}
	}

	double* getNumere()
	{
		if (numere != nullptr && numarNumere > 0)
		{
			double* copie = new double[numarNumere];
			for (int i = 0; i < numarNumere; i++)
			{
				copie[i] = numere[i];
			}
			return copie;
		}
		else
		{
			return nullptr;
		}
	}

	void setNumarNumere(int numarNumere)
	{
		if (numarNumere > 0)
		{
			this->numarNumere = numarNumere;
		}
		else
		{
			this->numarNumere = 0;
		}
	}

	void setOperatii(char* operatii, int numarOperatii)
	{
		if (operatii != nullptr && numarOperatii > 0)
		{
			if (this->operatii != nullptr)
			{
				delete[] this->operatii;
			}
			this->operatii = new char[numarOperatii];
			for (int i = 0; i < numarOperatii; i++)
			{
				this->operatii[i] = operatii[i];
			}
			this->numarOperatii = numarOperatii;
		}
	}

	char* getOperatii()
	{
		if (operatii != nullptr && numarOperatii > 0)
		{
			char* copie = new char[numarOperatii];
			for (int i = 0; i < numarOperatii; i++)
			{
				copie[i] = operatii[i];
			}
			return copie;
		}
		else
		{
			return nullptr;
		}
	}

	void setNumarOperatii(int numarOperatii)
	{
		if (numarOperatii > 0)
		{
			this->numarOperatii = numarOperatii;
		}
		else
		{
			this->numarOperatii = 0;
		}
	}

	int getNumaroperatii()
	{
		return numarOperatii;
	}
	int getNumarNumere()
	{
		return numarNumere;
	}

	void setRezultat(double rezultat)
	{
		this->rezultat = rezultat;
	}
	double getRezultat()
	{
		return rezultat;
	}

	void setPrioritateMaxima(int p)
	{
		if (p > 0 && p < 4)
		{
			this->prioritateMaxima = p;
		}
		else
		{
			this->prioritateMaxima = 1;
		}
	}
	int getPrioritateMaxima()
	{
		return prioritateMaxima;
	}



	//metoda calcul
	void prioritate()  //1-sume si scaderi   2-produs si raport   3- radical si putere
	{
		prioritateMaxima = 1;
		for (int i = 0; i < strlen(expresie); i++)
		{
			if (expresie[i] == '^' || expresie[i] == '#')
			{
				if (prioritateMaxima < 3)
				{
					prioritateMaxima = 3;
				}
			}
		}
		for (int i = 0; i < strlen(expresie); i++)
		{
			if (expresie[i] == '/' || expresie[i] == '*')
			{
				if (prioritateMaxima < 2)
				{
					prioritateMaxima = 2;
				}
			}
		}
		//return prioritateMaxima;
	}

	void transformareNumere()   //transforma expresia data in doi vectori alocati dinamici, unul pt numere, celalalt pentru operatii
	{
		numarNumere = -1;
		numarOperatii = -1;
		string numar;
		int i = 0;
		double nr;
		while (i < strlen(expresie))
		{
			numar.clear();
			bool formareNumar = false;
			while (i < strlen(expresie) && expresie[i] != '(' && expresie[i] != ')' && expresie[i] != '[' && expresie[i] != ']' && expresie[i] != '+'
				&& expresie[i] != '-' && expresie[i] != '*' && expresie[i] != '/' && expresie[i] != '^' && expresie[i] != '#')
			{
				numar += expresie[i]; //adaug cifrele si punctul
				i++;
				formareNumar = true;
			}
			if (formareNumar == true)
			{
				nr = stof(numar);  //formez un numar
				numarNumere++;
				numere[numarNumere] = nr;//adaug valoarea calculata
			}
			i++;
		}

		for (i = 0; i < strlen(expresie); i++)
		{
			if ((expresie[i] < 48 || expresie[i]>57) && expresie[i] != 46)  //nu e cifra si nu e punct
			{
				numarOperatii++;
				operatii[numarOperatii] = expresie[i];
			}
		}
		numarOperatii++;
		operatii[numarOperatii] = '\0';

	}

	double calculInteriorParanteza()
	{
		int i;
		this->prioritate();
		this->transformareNumere();
		while (prioritateMaxima != 0)
		{
			if (prioritateMaxima == 3)  //fac inati calculele cu radical si putere
			{
				for (int i = 0; i < numarOperatii; i++)
				{
					if (operatii[i] == '^' || operatii[i] == '#')
					{
						numere[i] = Operatie::calcul(numere[i], operatii[i], numere[i + 1]);
						for (int j = i + 1; j < numarNumere; j++)
						{
							numere[j] = numere[j + 1];
						}
						numarNumere--;
						for (int j = i; j < numarOperatii; j++)
						{
							operatii[j] = operatii[j + 1];
						}
						numarOperatii--;
					}
				}
				prioritateMaxima--;
			}

			if (prioritateMaxima == 2)  //fac  calculele cu * si /
			{
				for (int i = 0; i < numarOperatii; i++)
				{
					if (operatii[i] == '*' || operatii[i] == '/')
					{
						numere[i] = Operatie::calcul(numere[i], operatii[i], numere[i + 1]);
						for (int j = i + 1; j < numarNumere; j++)
						{
							numere[j] = numere[j + 1];
						}
						numarNumere--;
						for (int j = i; j < numarOperatii; j++)
						{
							operatii[j] = operatii[j + 1];
						}
						numarOperatii--;
					}
				}
				prioritateMaxima--;
			}
			if (prioritateMaxima == 1)  //fac  calculele cu + si -
			{
				while (numarOperatii > 0)
				{
					numere[0] = Operatie::calcul(numere[0], operatii[0], numere[1]);
					for (int j = 1; j < numarNumere; j++)
					{
						numere[j] = numere[j + 1];
					}
					numarNumere--;

					for (int j = 0; j < numarOperatii; j++)
					{
						operatii[j] = operatii[j + 1];
					}
					numarOperatii--;
				}
				prioritateMaxima--;
			}
		}
		rezultat = numere[0];
		return rezultat;
	}

	//operatori
	//op index
	int operator[](int index)
	{
		if (index >= 0 && index < numarNumere)
		{
			return numere[index];
		}
		else return 0;
	}

	operator double()
	{
		return rezultat;
	}

	~Expresie()
	{
		if (numere != nullptr)
		{
			//delete[] numere;
			numere = nullptr;
		}
		if (operatii != nullptr)
		{
			//delete[] operatii;
			operatii = nullptr;
		}
		if (expresie != nullptr)
		{
			//delete[] expresie;
			expresie = nullptr;
		}
	}



	friend istream& operator>>(istream& in, Expresie& ex)
	{
		string buffer;
		cout << "Expresie:";

		in >> buffer;
		char* buf = new char[buffer.length() + 1];
		strcpy_s(buf, buffer.length() + 1, buffer.c_str());
		ex.setExpresie(buf);
		return in;
	}

	friend ostream& operator<<(ostream& out, Expresie ex)
	{
		if (ex.expresie != nullptr)
		{
			out << "Expresie: " << ex.expresie << endl;
		}
		else
		{
			out << "Expresie: " << endl;
		}
		out << "Numar Numere: " << ex.numarNumere << endl;
		for (int i = 0; i < ex.numarNumere; i++)
		{
			cout << ex.numere[i] << " ";
		}
		out << "Numar Operatii: " << ex.numarOperatii << endl;
		for (int i = 0; i < ex.numarOperatii; i++)
		{
			cout << ex.operatii[i] << " ";
		}
		out << "Prioritate maxima: " << ex.prioritateMaxima << endl;
		out << "Rezultat: " << ex.rezultat << endl;
		return out;
	}


};






class Ecuatie    //primesc intreaga ecuatie  validare, stergere spatii
{
private:
	char* ecuatie;
	int numarElemente;
	bool parantezeDrepte;
	bool parantezeRotunde;
	int* pozitiiParanteze;
	int numarParanteze;
	double rezultat;
	int okParanteze;

public:

	Ecuatie()
	{
		ecuatie = nullptr;
		numarElemente = 0;
		parantezeDrepte = false;
		parantezeRotunde = false;
		pozitiiParanteze = nullptr;
		numarParanteze = 0;
		rezultat = 0;
		okParanteze = -1;

	}
	Ecuatie(char* ecuatie, int numarElemente)
	{
		this->numarElemente = numarElemente;
		this->ecuatie = new char[strlen(ecuatie) + 1];
		strcpy_s(this->ecuatie, strlen(ecuatie) + 1, ecuatie);
		parantezeDrepte = false;
		parantezeRotunde = false;
		pozitiiParanteze = nullptr;
		numarParanteze = 0;
		rezultat = 0;
		okParanteze = -1;
	}


	//constructor de copiere
	Ecuatie(const Ecuatie& e)
	{
		if (e.ecuatie != nullptr && e.numarElemente > 0)
		{
			ecuatie = new char[strlen(e.ecuatie) + 1];
			strcpy_s(ecuatie, strlen(e.ecuatie) + 1, e.ecuatie);
			numarElemente = e.numarElemente;
		}
		parantezeDrepte = e.parantezeDrepte;
		parantezeRotunde = e.parantezeRotunde;
		if (e.pozitiiParanteze != nullptr && numarParanteze > 0)
		{
			pozitiiParanteze = new int[numarParanteze];
			numarParanteze = e.numarParanteze;
			for (int i = 0; i < numarParanteze; i++)
			{
				pozitiiParanteze[i] = e.pozitiiParanteze[i];
			}
		}
	}

	//op egal
	Ecuatie operator=(const Ecuatie& e)
	{
		if (ecuatie != nullptr)
		{
			delete[] ecuatie;
			ecuatie = nullptr;
		}
		if (pozitiiParanteze != nullptr)
		{
			delete[] pozitiiParanteze;
			pozitiiParanteze = nullptr;
		}
		if (e.ecuatie != nullptr && e.numarElemente > 0)
		{
			ecuatie = new char[strlen(e.ecuatie) + 1];
			strcpy_s(ecuatie, strlen(e.ecuatie) + 1, e.ecuatie);
			numarElemente = e.numarElemente;
		}
		parantezeDrepte = e.parantezeDrepte;
		parantezeRotunde = e.parantezeRotunde;
		if (e.pozitiiParanteze != nullptr && numarParanteze > 0)
		{
			pozitiiParanteze = new int[numarParanteze];
			numarParanteze = e.numarParanteze;
			for (int i = 0; i < numarParanteze; i++)
			{
				pozitiiParanteze[i] = e.pozitiiParanteze[i];
			}
		}
	}

	void setEcuatie(char* ecuatie)
	{

		if (ecuatie != nullptr)
		{
			if (this->ecuatie) {
				//delete[] this->ecuatie;
				this->ecuatie = nullptr;
				this->ecuatie = new char[strlen(ecuatie)];
			}
			this->numarElemente = strlen(ecuatie);
			strcpy_s(this->ecuatie, strlen(ecuatie) + 1, ecuatie);
		}

	}
	char* getEcuatie()
	{
		return ecuatie;
	}

	bool getParantezeDrepte()
	{
		return parantezeDrepte;
	}
	bool getParantezeRotunde()
	{
		return parantezeRotunde;
	}
	int getNumarParanteze()
	{
		return numarParanteze;
	}

	void getPozitiiParanteze()     //AFISEAZA VECTORUL
	{
		for (int i = 0; i <= numarParanteze; i++)
		{
			cout << pozitiiParanteze[i] << " ";
		}
	}

	double getRezultat()
	{
		return rezultat;
	}
	int getokParanteze()
	{
		return okParanteze;
	}



	//metoda stergere spatii
	void stergereSpatii() //fac o noua variabila de tip string, copie, aici pun cu + toate elementele care nu sunt spatiu
	{
		int k = -1;
		char* copie = new char[strlen(ecuatie) + 1];
		for (int i = 0; i < strlen(ecuatie); i++)
		{
			if (ecuatie[i] != ' ')
			{
				k++;
				copie[k] = ecuatie[i];
			}
		}
		k++;
		copie[k] = '\0';
		delete[] ecuatie;
		ecuatie = new char[strlen(copie) + 1];
		strcpy_s(ecuatie, strlen(copie) + 1, copie);
		numarElemente = strlen(copie) + 1;
	}



	int validareEcuatie()
	{
		numarParanteze = -1;
		pozitiiParanteze = new int[strlen(ecuatie)];
		int parantezaRotunda = 0, parantezaDreapta = 0;
		string paranteze;

		int ok = 1;// cod de succes, ecuatie valida

		for (int i = 0; i < strlen(ecuatie); i++)
		{
			if (ecuatie[i] == '(' || ecuatie[i] == ')' || ecuatie[i] == '[' || ecuatie[i] == ']')
			{
				paranteze += ecuatie[i];
				numarParanteze++;
				pozitiiParanteze[numarParanteze] = i;
			}

		}

		for (int i = 0; i < paranteze.length(); i++)
		{
			if (paranteze[i] == '(')
			{
				parantezaRotunda++;
				if (parantezaRotunda > 1)
					ok = 0;
			}

			if (paranteze[i] == '[')
			{
				parantezaDreapta++;
				if (parantezaDreapta > 1) {
					ok = 0;
				}
			}
			if (paranteze[i] == ')')
			{
				parantezaRotunda--;
				if (parantezaRotunda < 0)
					ok = 0;
			}
			if (paranteze[i] == ']')
			{
				parantezaDreapta--;
				if (parantezeRotunde < 0) {
					ok = 0;
				}
			}
		}
		if (paranteze.length() > 0)
		{
			if (paranteze[0] == ')' || paranteze[0] == ']')
				ok = 0;
		}


		for (int i = 1; i < paranteze.length(); i++)
		{
			if (paranteze[i] == ')' && paranteze[i - 1] != '(')
				ok = 0;
			if (paranteze[i] == ']' && (paranteze[i - 1] == '[' || paranteze[i - 1] == '('))
				ok = 0;

		}

		if (ok == 1)
		{

			for (int i = 0; i < paranteze.length(); i++)
			{

				if (paranteze[i] == '(')
				{
					parantezeRotunde = true;
				}
				if (paranteze[i] == '[')
				{
					parantezeDrepte = true;
				}
			}
		}
		okParanteze = ok;
		return ok;
	}


	//operatori 
	//op+
	Ecuatie operator+(Ecuatie e)
	{
		Ecuatie copie = *this;
		copie.rezultat = rezultat + e.rezultat;
		return copie;
	}
	operator double()
	{
		return rezultat;
	}

	bool operator!()
	{
		return okParanteze;
	}



	void calculator()
	{
		int ordine = 1, i, j, io, in;
		int impartire0 = 0;

		Expresie sir(ecuatie);
		string interiorP = "";

		//stergereSpatii();
		//validareEcuatie();
		//sir.Ecuatie::stergereSpatii();
		if (validareEcuatie() == 1)
		{
			sir.transformareNumere();

			if (parantezeRotunde)
			{
				ordine++;
			}
			if (parantezeDrepte)
			{
				ordine++;
			}

			while (ordine > 1)
			{
				if (ordine == 3)// am ambele paranteze
				{
					i = 0;
					while (i < strlen(ecuatie))
					{
						while (i < strlen(ecuatie) && ecuatie[i] != '(')
						{
							i++;
						}
						j = i + 1;
						bool gasit = false;

						if (interiorP != "") {
							interiorP = "";
						}

						while (j < strlen(ecuatie))
						{
							interiorP += ecuatie[j];
							j++;
							if (ecuatie[j] == ')') {
								gasit = true;
								break;
							}
						}
						if (gasit) {
							char* c = new char[interiorP.length() + 1];
							strcpy_s(c, strlen(interiorP.c_str()) + 1, interiorP.c_str());
							Expresie continut(c);
							continut.transformareNumere();
							continut.calculInteriorParanteza();

							string rez = to_string(continut.getRezultat());
							string ec_veche(ecuatie);
							string interiorParanteza(c);
							interiorParanteza = '(' + interiorParanteza + ')';
							string ec_noua = ec_veche.replace(i, interiorParanteza.length(), rez);    //functie de inlocuire a parantezei

							char* ecuatieNoua = new char[ec_noua.length() + 1];
							strcpy_s(ecuatieNoua, ec_noua.length() + 1, ec_noua.c_str());

							sir.setExpresie(ecuatieNoua);
							this->setEcuatie(ecuatieNoua);
							sir.transformareNumere();

						}
						i = j + 1;
					}


					i = 0;
					while (i < strlen(ecuatie))
					{
						while (i < strlen(ecuatie) && ecuatie[i] != '[')
						{
							i++;
						}
						j = i + 1;
						bool gasit = false;

						if (interiorP != "") {
							interiorP = "";
						}

						while (j < strlen(ecuatie))
						{
							interiorP += ecuatie[j];
							j++;
							if (ecuatie[j] == ']') {
								gasit = true;
								break;
							}
						}
						if (gasit) {
							char* c = new char[interiorP.length() + 1];
							strcpy_s(c, strlen(interiorP.c_str()) + 1, interiorP.c_str());
							Expresie continut(c);
							continut.transformareNumere();
							continut.calculInteriorParanteza();

							string rez = to_string(continut.getRezultat());
							string ec_veche(ecuatie);
							string interiorParanteza(c);
							interiorParanteza = '[' + interiorParanteza + ']';
							string ec_noua = ec_veche.replace(i, interiorParanteza.length(), rez);    //functie de inlocuire a parantezei

							char* ecuatieNoua = new char[ec_noua.length() + 1];
							strcpy_s(ecuatieNoua, ec_noua.length() + 1, ec_noua.c_str());

							sir.setExpresie(ecuatieNoua);
							this->setEcuatie(ecuatieNoua);
							sir.transformareNumere();


						}
						i = j + 1;
					}
					ordine = 1;
				}



				if (ordine == 2)
				{
					i = 0;
					while (i < strlen(ecuatie))
					{
						while (i < strlen(ecuatie) && ecuatie[i] != '(')
						{
							i++;
						}
						j = i + 1;
						bool gasit = false;

						if (interiorP != "") {
							interiorP = "";
						}

						while (j < strlen(ecuatie))
						{
							interiorP += ecuatie[j];
							j++;
							if (ecuatie[j] == ')') {
								gasit = true;
								break;
							}
						}
						if (gasit) {
							char* c = new char[interiorP.length() + 1];
							strcpy_s(c, strlen(interiorP.c_str()) + 1, interiorP.c_str());
							Expresie continut(c);
							continut.transformareNumere();
							continut.calculInteriorParanteza();

							string rez = to_string(continut.getRezultat());
							string ec_veche(ecuatie);
							string interiorParanteza(c);
							interiorParanteza = '(' + interiorParanteza + ')';
							string ec_noua = ec_veche.replace(i, interiorParanteza.length(), rez);    //functie de inlocuire a parantezei

							char* ecuatieNoua = new char[ec_noua.length() + 1];
							strcpy_s(ecuatieNoua, ec_noua.length() + 1, ec_noua.c_str());

							sir.setExpresie(ecuatieNoua);
							this->setEcuatie(ecuatieNoua);
							sir.transformareNumere();
							ordine--;
						}
						i = j + 1;
					}
					ordine = 1;
				}
			}
			if (ordine == 1)
			{
				i = 0;
				sir.calculInteriorParanteza();
				this->rezultat = sir.getRezultat();
			}

			rezultat = sir.calculInteriorParanteza();
		}
		else
		{
			cout << "Parantezele nu sunt folosite corect";
		}

		if (Operatie::getImpartirelaZero() == 1)
		{
			cout << "impartire la 0";
		}
	}

	~Ecuatie()
	{
		if (ecuatie != nullptr)
		{
			//delete[] ecuatie;
			ecuatie = nullptr;
		}
		if (pozitiiParanteze != nullptr)
		{
			//delete[] pozitiiParanteze;
			pozitiiParanteze = nullptr;
		}
	}

	friend istream& operator>>(istream& in, Ecuatie& ec)
	{
		string buffer;
		cout << "Ecuatie:";

		in >> buffer;
		char* buf = new char[buffer.length() + 1];
		strcpy_s(buf, buffer.length() + 1, buffer.c_str());
		ec.setEcuatie(buf);
		return in;
	}

	friend ostream& operator<<(ostream& out, Ecuatie ec)
	{
		if (ec.ecuatie != nullptr)
		{
			out << "Ecuatie: " << ec.ecuatie << endl;
		}
		else
		{
			out << "Ecuatie: " << endl;
		}
		out << "Numar Elemente: " << ec.numarElemente << endl;
		out << "Paranteze drepte: " << ec.parantezeDrepte;
		out << "Paranteze rotunde: " << ec.parantezeRotunde;
		out << "Parantezele sunt asezate corect: " << ec.okParanteze;
		out << "Rezultat: " << ec.rezultat;

		return out;
	}
};


string stergereZeroParteZecimala(double x)
{

	string nr = to_string(x);
	nr.erase(nr.find_last_not_of('0')+1, string::npos);

	return nr;
}



int main()

{
	//cout << fixed;
	cout.precision(4);
	char s[100];
	cin.getline(s, 100);
	int dim = 0;
	double x;
	//int dim = strlen(s);

	while (strcmp(s, "exit") != 0)
	{
		dim = strlen(s);
		Ecuatie ec(s, dim);
		ec.stergereSpatii();
		ec.calculator();
		if (Operatie::getImpartirelaZero() != 1 || ec.getokParanteze() != 0)
		{
			x = ec.getRezultat();
			cout << fixed << x << endl;
		}
		cin.getline(s, 100);
		Operatie::setImpartirelaZero(0);
	}

}
