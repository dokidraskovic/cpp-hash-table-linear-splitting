#ifndef _HashTable_h_
#define _HashTable_h_
#include "SplitSequenceLinearHashing.h"

class HashTable {
public:
	struct Elem {
		unsigned int indeks;
		string ime;
		struct ListaP {
			string sifra;
			ListaP* next;
			ListaP(string s, ListaP* n = nullptr) : sifra(s), next(n) {};
		};
		ListaP* prvi = nullptr;
		void brisiL()
		{
			if (prvi == nullptr) return;
			while (prvi)
			{
				ListaP* stari = prvi;
				prvi = prvi->next;
				delete stari;
			}
			prvi = nullptr;
		}
		friend ostream& operator<<(ostream& os, const Elem& elem)
		{
			os << elem.indeks << " " << elem.ime << " ";
			ListaP* pom = elem.prvi;
			while (pom)
			{
				os << pom->sifra << " ";
				pom = pom->next;
			}
			return os;
		}
	};
private:
	struct Baket {
		Elem** elem;
		int mb;
		int b;
		Baket(int m, int ba) {
			b = ba;
			elem = new Elem * [mb = m];
			for (int i = 0; i < mb; i++)
				elem[i] = nullptr;
		}
		bool dodaj(Elem* elem)
		{
			int pom;
			pom = this->nadjiM(elem);
			if (pom == -1)
				return false;
			else
			{
				this->elem[pom] = elem;
				return true;
			}
		}
		bool isti(Elem* info)
		{
			for (int i = 0; i < mb; i++)
			{
				if (elem[i] == nullptr)
					break;
				if (elem[i]->indeks == info->indeks && elem[i]->ime.compare("deleted")) return true;
			}
			return false;
		}
		bool pun()
		{
			if (elem == nullptr)
				return false;
			for (int i = 0; i < mb; i++)
				if (elem[i] == nullptr)
					return false;
			return true;
		}
		int nadjiK(unsigned int key)
		{
			if (this->pun())
			{
				int i = 0;
				while (i < mb)
				{
					if (elem[i]->indeks == key && !elem[i]->ime.compare("deleted"))
						return -2;
					if (elem[i]->indeks == key && elem[i]->ime.compare("deleted"))
						return i;
					i++;
				}
				return -1;
			}
			else
			{
				int i = 0;
				while (i < mb)
				{
					if (elem == nullptr)break;
					if (elem[i] == nullptr)break;
					if (elem[i]->indeks == key && elem[i]->ime.compare("deleted"))
						return i;
					i++;
				}
				return -2;

			}
		}
		int nadjiM(Elem* info)
		{
			int pom = 0;
			int br = -1;
			for (int i = 0; i < mb; i++)
			{
				if (elem[i] == nullptr) break;
				else br = i;
				if (elem[i]->indeks == info->indeks && elem[i]->ime.compare("deleted")) return -2;
				if (elem[i]->indeks < info->indeks)
					pom = i;
				if (!elem[i]->ime.compare("deleted"))
				{
					pom = i;
					break;
				}
			}
			if (br == mb - 1)
				return -1;
			else if (br != -1 && elem[pom]->ime.compare("deleted"))
			{
				int j = 0;
				while (elem[j])
					j++;
				for (int i = j + 1; i > pom; i--)
					elem[i] = elem[i - 1];
			}
			return pom;
		}
	};
	Baket** tabela;
	int n;
	int m;
	int b;
	int p;
	int pp;
	AddressFunction* adr;
public:
	HashTable(int pa, int ba, int s11, int s22)
	{
		adr = new SplitSequenceLinearHashing(s11, s22);
		n = pow(2, p = pa);
		pp = pa;
		tabela = new Baket * [n];
		for (int i = 0; i < n; i++)
			tabela[i] = new Baket(b = ba, pa);
		m = 0;
	}
	void formiraj(ifstream& is);
	void formiraj(istream& is);
	bool insertKey(unsigned int key, Elem& info);
	Elem* findKey(unsigned int key);
	void findKey(unsigned int key, int& x, int& ad);
	bool deleteKey(unsigned int key);
	void clear();
	int keyCount();
	int tableSize();
	friend ostream& operator<<(ostream& os, const HashTable& h);
	double fillRatio();
	void dodajIspit(unsigned int key, string s);
	void brisiIspit(unsigned int key, string s);
	~HashTable();
};

#endif
