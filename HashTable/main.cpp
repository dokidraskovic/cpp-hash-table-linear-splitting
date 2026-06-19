#include "HashTable.h"

int main()
{
	bool kraj = false;
	cout << "Unesite parametar b i k" << endl;
	int b, k;
	cin >> b >> k;
	HashTable hash(b, k, 0, 0);
	cout << "Pre pocetka rada sa hash tabelom izaberite na koji nacin cete je formirati:" << endl;
	cout << "1.Citaj iz datoteke" << endl;
	cout << "2.Citaj sa standardnog ulaza" << endl;
	int opcija;
	cin >> opcija;
	if (opcija == 1)
	{
		cout << "Unesite naziv datoteke" << endl;
		ifstream ulaz;
		string pom;
		cin >> pom;
		ulaz.open(pom);
		hash.formiraj(ulaz);
		ulaz.close();
	}
	if (opcija == 2)
		hash.formiraj(cin);
	while (!kraj)
	{
		cout << "U ovo programu imate sledece opcije" << endl;
		cout << "1.Pretraga kljuca" << endl;
		cout << "2.Umetanje kljuca" << endl;
		cout << "3.Brisanje kljuca" << endl;
		cout << "4.Brisanje svih kljuceva" << endl;
		cout << "5.Broj umetnutih kljuceva" << endl;
		cout << "6.Velicina tabele" << endl;
		cout << "7.Ispis tabele" << endl;
		cout << "8.Popunjenost tabele" << endl;
		cout << "9.Dodajte ispit studentu" << endl;
		cout << "10.Izbrisite ispit studentu" << endl;
		cout << "0.Prekid programa" << endl;
		cin >> opcija;
		switch (opcija)
		{
		case 1:
		{
			cout << "Unesite vrednost kljuca" << endl;
			unsigned int key;
			cin >> key;
			HashTable::Elem* pom = hash.findKey(key);
			if (pom == nullptr)
				cout << "Kljuc nije pronadjen" << endl;
			else
				cout << *pom;
			break;
		}
		case 2:
		{
			cout << "Unesite u novom redu sve podatke potrebne za formiranje jednog zapisa tabele" << endl;
			string s;
			HashTable::Elem* novi = new HashTable::Elem();
			getline(cin, s, ',');
			novi->indeks = (unsigned int)(stoi(s));
			getline(cin, s, ',');
			novi->ime = s;
			getline(cin, s);
			while (s.find(' ') != s.npos)
			{
				string ps;
				int poz = s.find(' ');
				ps = s.substr(0, poz);
				HashTable::Elem::ListaP* novip = new HashTable::Elem::ListaP(ps, novi->prvi);
				novi->prvi = novip;
				s.erase(0, poz + 1);
			}
			HashTable::Elem::ListaP* novip = new HashTable::Elem::ListaP(s, novi->prvi);
			novi->prvi = novip;
			s.erase();
			hash.insertKey(novi->indeks, *novi);
			break;
		}
		case 3:
		{
			cout << "Unesite kljuc koji zelite da izbrisete" << endl;
			unsigned int key;
			cin >> key;
			bool t = hash.deleteKey(key);
			if (t)
				cout << "Kljuc je uspesno izbrisan" << endl;
			else
				cout << "Kljuc ne postoji u tabeli" << endl;
			break;
		}
		case 4:
		{
			hash.clear();
			break;
		}
		case 5:
		{
			cout << "Broj umetnutih kljuceva je " << hash.keyCount();
			break;
		}
		case 6:
		{
			cout << "Tabela sadrzi " << hash.tableSize() << " baketa" << endl;
			break;
		}
		case 7:
		{
			cout << hash;
			break;
		}
		case 8:
		{
			cout << "Popunjenost tabele je" << hash.fillRatio();
			break;
		}
		case 9:
		{
			cout << "Unesite indeks studenta i sifru ispita koji se dodaje" << endl;
			unsigned int key;
			string s;
			cin >> key >> s;
			hash.dodajIspit(key, s);
			break;
		}
		case 10:
		{
			cout << "Unesite indeks studenta i sifru ispita koji se izbacuje" << endl;
			unsigned int key;
			string s;
			cin >> key >> s;
			hash.brisiIspit(key, s);
			break;
		}
		case 0:
		{
			kraj = true;
			break;
		}
		}
	}

}