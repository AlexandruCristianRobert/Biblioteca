#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Carte  //definirea obiectului carte
{
	int nr_carte;//  nr de identificare al cartii
	bool inchirie_zi[366];// varianta adevarat sau fals daca e inchiriata , pe zile.
	string nume;// numele cartii
	int zile_inchiriate;// numarul total de zile inchiriate a unei arti
	static int urmatoarea_carte;// incrementam, adunam, nr de indentificare al cartii
public:

	bool get_inchiriere_zi(int zi)// variabilele de mai sus sunt variabile private, nu pot fi accesate in afara clasei , deci pentru a le accesa in afara de ex in biblioteca sau in int main folosim functii private, cum e functia asta get care returneaza valoarea de adevar
	{
		return  inchirie_zi[zi];
	}
	int get_zile_inchiriare()// returneaza  valoarea din variabila zile_inchiriate
	{
		return zile_inchiriate;
	}
	int get_nr_carte()// returneaza nr cartii
	{
		return nr_carte;
	}
	Carte()// constructorul
	{
		urmatoarea_carte++;// incrementam variabila statica( o variabila statica apartine clasei, nu unei instante) De ex oricate carti ai crea, asta e o singura variabila pentru toate.
		nume = "Fara nume";// ii un nume implicit
		nr_carte = urmatoarea_carte;// ii dam nr cartii, pentru ca urmatoarea_carte e o variabila a clasei , se pastreaza. Ex creezi o carte urm_carte =1 , nr_carte = 1, creezi alta carte urm_carte++ adica 2, nr_carte =2 si tot asa
		for (int i = 0;i < 367;i++)
		{
			inchirie_zi[i] = false;// declar cartea ca fiind  disponibila pentru toate zilele 
		}
		zile_inchiriate = 0;// declar 0 zile inchiriate
	}
	void Inchiriere(int zi)// functie "set"care seteaza o zi inchiriata
	{
		inchirie_zi[zi] = true;// setam ziua respectiva inchiriata
		zile_inchiriate++;// adunam zilele inchiriate ale functiei
	}
	friend istream& operator >>(istream& intrare, Carte& c)// suprascrierea citirii
	{
		cout << "Nume carte:";
		intrare >> c.nume;
		return  intrare;
	}
	friend ostream& operator <<(ostream& iesire, Carte& c)// suprascrierea afisarii
	{
		iesire << "Nr carte:" << c.nr_carte << endl;
		iesire << "Nume carte:" << c.nume << endl;
		return iesire;
	}
};
int Carte::urmatoarea_carte = 0;//initializarea variabilei statice cu valoarea 0
template <typename T> class Biblioteca// clasa Template, ne permite sa facem un vector de obiecte de orice tip, tipul e specificat in int main
{
	vector<T> carti;//  declararea vectorului
	int total_carti_inchiriate[366];// variabila care tine nr de carti inchiriate pe zile
public:

	void Inchiriere_carte(int nr_carte)// vector de inchiriere a u  unei carti
	{
		bool procesare;//  o folosim sa verificam daca o carte e disponibila intr-o perioada sau nu
		int zi_inchiriere;
		int zi_returnare;
		for (auto i = carti.begin();i != carti.end();++i)// asa se parcurge vectorul
			{
			if ((*i).get_nr_carte() == nr_carte)// un pointer i este echivalentul unui obiect din vector. Fiind un vector de carti putem folosi functiile publice ale clasei Carte
			{
				do// daca am gasit cartea , introducem ziua inchirierii si ziua returnarii
				{
					procesare = true;
					cout << "Introduceti ziua inchirierii: ";
					cin >> zi_inchiriere;
					cout << "Introduceti ziua returnarii: ";
					cin >> zi_returnare;
					for (int j = zi_inchiriere;j <= zi_returnare;j++)//  poti inlocui <= cu < daca vrei sa nu verifice si ziua returnarii
					{
						cout << (*i).get_inchiriere_zi(j) << endl;
						if ((*i).get_inchiriere_zi(j) == true)// verificam daca toate zilele sunt libere, Daca gasim una ocupata = intervalul nu e disponibil
						{
							procesare = false;
							break;// pentru ca am gasit una ocupata, nu mai are rost sa parcurgem intervalul pana la capat
						}

					}

					if (procesare == false)
					{
						cout << "Cartea este deja inchiriata in perioada selectata, va rugam sa introduceti alta perioada." << endl;

					}
					else// pentru ca toate zilele sunt disponibile atunci o seteaza ca ocupata
					{
						for (int j = zi_inchiriere;j <= zi_returnare;j++)
						{
							(*i).Inchiriere(j);
							total_carti_inchiriate[j]++;

						}
						cout << "Cartea a fost inchiriata";
					}
				} while (procesare == false);
			}
			}
	}
	Carte selectare_carte(int nr_carte)// selectam o carte pe baza nr_cartii
	{
		for (auto i = carti.begin();i != carti.end();++i)
			if ((*i).get_nr_carte() == nr_carte)
				return (*i);
		Carte c;
		return c;
	}
	void Adauga_carte(T c)// adauga cartea
	{
		cin >> c;
		carti.push_back(c);// functie din stl-ul algorithm
	}
	
	void afisare_carte(int nr_carte)// afisarea
	{
		for (auto i = carti.begin();i != carti.end();++i)
			if ((*i).get_nr_carte() == nr_carte)
				cout << (*i);//  pentru ca am suprascris afisarea, putem sa o facem asa
	}
	int get_total_carti_inchiriare(int zi)// returnam nr de carti inchiriate intr-o zi anume
	{
		return total_carti_inchiriate[zi];
	}
};
int main()
{
	Biblioteca<Carte> biblioteca;//  declararea vectorului si specificarea tipului sau
	int a = 0;
	while (a != 7)
	{
		cout << endl;
		cout << "1 Adauga carte" << endl;
		cout << "2 Afisare carte" << endl;
		cout << "3 Inchiriere carte" << endl;
		cout << "4 Afisare stare carte intr-o zi" << endl;
		cout << "5 Afisare total zile inchiriate carte" << endl;
		cout << "6 Afisare total carti inchiriate intr-o zi" << endl;
		cout << "7 Inchidere proogram" << endl;
		cin >> a;
		switch (a)// switch, in functie de ce valoare are a ruleaza un cod
		{
		case 1:// daca a=1 atunci
		{
			Carte carte;
			biblioteca.Adauga_carte(carte);
		}
		break;// opreste cazul, daca nu era break intra in urmatorul caz, chit ca nu are valoarea 2, si rula si ce e acolo pana gasea un break, daca nu gasea intra si in cazul 3 si tot asa
		case 2:
		{
			cout << "Introduceti numarul cartii: ";
			int nr_carte;
			cin >> nr_carte;
			biblioteca.afisare_carte(nr_carte);
		}
		break;
		case 3:
		{
			cout << "Introduceti numarul cartii: ";
			int nr_carte;
			cin >> nr_carte;
			biblioteca.afisare_carte(nr_carte);
			cout << endl;
			biblioteca.Inchiriere_carte(nr_carte);
		}
		break;
		case 4:
		{
			cout << "Introduceti numarul cartii: ";
			int nr_carte;
			cin >> nr_carte;
			cout << "introduceti ziua: ";
			int zi;
			cin >> zi;
			if (biblioteca.selectare_carte(nr_carte).get_inchiriere_zi(zi) == 1)
				cout << "Cartea este inchiriata in ziua " << zi;
			else
				cout << "Cartea este disponibila in ziua " << zi << endl;
		}
		break;
		case 5:
		{
			cout << "Introduceti numarul cartii: ";
			int nr_carte;
			cin >> nr_carte;
			cout << "Cartea a fost inchiriata " << biblioteca.selectare_carte(nr_carte).get_zile_inchiriare() << " zile" << endl;
		}
		break;
		case 6:
		{
			cout << "introduceti ziua: ";
			int zi;
			cin >> zi;
			cout << "In ziua " << zi << " bibilioteca a inchiriat " << biblioteca.get_total_carti_inchiriare(zi) << " carti" << endl;

		}
		break;

		}

	}
}
