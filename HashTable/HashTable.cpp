#include "HashTable.h"

void HashTable::formiraj(ifstream& is)
{
	if (is.eof()) return;
	string s;
	getline(is, s);
	while (!is.eof())
	{
		Elem* novi = new Elem();
		getline(is, s, ',');
		novi->indeks = (unsigned int)(stoi(s));
		getline(is, s, ',');
		novi->ime = s;
		getline(is, s);
		while (s.find(' ') != s.npos)
		{
			string ps;
			int poz = s.find(' ');
			ps = s.substr(0, poz);
			Elem::ListaP* novip = new Elem::ListaP(ps, novi->prvi);
			novi->prvi = novip;
			s.erase(0, poz + 1);
		}
		Elem::ListaP* novip = new Elem::ListaP(s, novi->prvi);
		novi->prvi = novip;
		s.erase();
		this->insertKey(novi->indeks, *novi);
	}
}

void HashTable::formiraj(istream& is)
{
	char c = is.get();
	c = is.get();
	if (c == '\n') return;
	string s;
	while (c != '\n')
	{
		Elem* novi = new Elem();
		string pom;
		pom += c;
		getline(is, s, ',');
		s.insert(0, pom);
		novi->indeks = (unsigned int)(stoi(s));
		getline(is, s, ',');
		novi->ime = s;
		getline(is, s);
		while (s.find(' ') != s.npos)
		{
			string ps;
			int poz = s.find(' ');
			ps = s.substr(0, poz);
			Elem::ListaP* novip = new Elem::ListaP(ps, novi->prvi);
			novi->prvi = novip;
			s.erase(0, poz + 1);
		}
		Elem::ListaP* novip = new Elem::ListaP(s, novi->prvi);
		novi->prvi = novip;
		s.erase();
		this->insertKey(novi->indeks, *novi);
		c = is.get();
	}
}

bool HashTable::insertKey(unsigned int key, Elem& info)
{
	unsigned int maska;
	maska = (1 << pp) - 1;  //odlucio sam da se podsetim bitskih operacija i zato sam koristio masku za ovaj problem gde je postojalo jednostavnije
	int h = key & maska;	//resenje
	int i = 1;
	int a = h;
	if (tabela[h]->isti(&info)) return false;
	if (tabela[h]->dodaj(&info) == false)
	{
		p++;
		tabela[h]->b++;
		int n1 = pow(2, p);
		Baket** pomb = new Baket * [n1];
		int i = 0;
		while (i < pow(2, p - 1))
		{
			int j = i << 1;
			pomb[j] = tabela[i];
			pomb[j + 1] = tabela[i];
			i++;
		}
		Baket* novi = new Baket(b, p);
		novi->elem[0] = &info;
		if (novi->elem[0]->indeks > tabela[h]->elem[0]->indeks)
		{
			pomb[h << 1] = tabela[h];
			pomb[(h << 1) + 1] = novi;
		}
		else
		{
			pomb[h << 1] = novi;
			pomb[(h << 1) + 1] = tabela[h];
		}
		delete tabela;
		tabela = pomb;
	}
	m++;
	n = pow(2, p);
	return true;
}

HashTable::Elem* HashTable::findKey(unsigned int key)
{
	unsigned int maska;
	maska = (1 << pp) - 1;
	int h = key & maska;
	int p;
	while (h < n)
	{
		p = tabela[h]->nadjiK(key);
		if (p != -1 && p != -2)return tabela[h]->elem[p];
		if (h + 1 < n)
			p = tabela[h + 1]->nadjiK(key);
		if (p != -1 && p != -2)return tabela[h + 1]->elem[p];
		h = h << 1;
	}

	return nullptr;;
}

void HashTable::findKey(unsigned int key, int& x, int& ad)
{
	unsigned int maska;
	maska = (1 << pp) - 1;
	int h = key & maska;
	int p;
	while (h < n)
	{
		p = tabela[h]->nadjiK(key);
		if (p != -1 && p != -2)
		{
			ad = h;
			x = p;
			return;
		}
		if (h + 1 < n)
			p = tabela[h + 1]->nadjiK(key);
		if (p != -1 && p != -2)
		{
			ad = h;
			x = p;
			return;
		}
		h = h << 1;
	}
	ad = -1;
	x = -1;
}

bool HashTable::deleteKey(unsigned int key)
{
	int x;
	int ad;
	this->findKey(key, x, ad);
	if (x == -1 || x == -2) return false;
	tabela[ad]->elem[x]->brisiL();
	tabela[ad]->elem[x]->ime = "deleted";
	m--;
	return true;
}

void HashTable::clear()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < b; j++)
			if (tabela[i]->elem[j] != nullptr && tabela[i]->elem[j]->ime != "deleted")
			{
				tabela[i]->elem[j]->brisiL();
				tabela[i]->elem[j]->ime = "deleted";
			}
	m = 0;
}

int HashTable::keyCount()
{
	return m;
}

int HashTable::tableSize()
{
	return n;
}

double HashTable::fillRatio()
{
	return 1.0 * m / (n * b);
}

void HashTable::dodajIspit(unsigned int key, string s)
{
	Elem* pom = findKey(key);
	if (pom != nullptr)
		pom->prvi = new Elem::ListaP(s, pom->prvi);
}

void HashTable::brisiIspit(unsigned int key, string s)
{
	Elem* pom = findKey(key);
	if (pom != nullptr)
	{
		Elem::ListaP* pret = nullptr;
		Elem::ListaP* tren = pom->prvi;
		if (!tren) return;
		while (tren && tren->sifra.compare(s))
		{
			pret = tren;
			tren = tren->next;
		}
		if (tren)
		{
			if (!pret)
				pom->prvi = pom->prvi->next;
			else
				pret->next = tren->next;
			delete tren;
		}
	}
}

HashTable::~HashTable()
{
	for (int i = 0; i < n; i++)
	{
		if (tabela[i] != nullptr)
		{
			for (int j = 0; j < b; j++)
			{
				if (tabela[i]->elem[j] != nullptr)
				{
					tabela[i]->elem[j]->brisiL();
					delete tabela[i]->elem[j];
				}
			}
			delete tabela[i];
			int j = i + 1;
			while (tabela[i] == tabela[j])
			{
				tabela[j] = nullptr;
				j++;
			}
		}
	}
	delete tabela;
}

ostream& operator<<(ostream& os, const HashTable& h)
{
	for (int i = 0; i < h.n; i++)
	{
		for (int j = 0; j < h.b; j++)
		{
			if (h.tabela[i]->elem[j] == nullptr)
				os << "EMPTY ";
			else if (h.tabela[i]->elem[j]->ime == "deleted")
				os << "DELETED ";
			else
			{
				os << *h.tabela[i]->elem[j];
			}
			os << "  ";
		}
		os << endl;
	}
	os << endl;
	return os;
}
