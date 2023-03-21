/*
Cerinte comune tuturor temelor:

x	implementare in C++ folosind clase
x	datele membre private
x	constructori de initializare (cu si fara parametri), constructor de copiere, destructor, operator de atribuire
x	get, set pentru toate datele membre
•	ATENTIE: functiile pe care le-am numit mai jos metode (fie ca sunt supraincarcari de operatori, fie altfel de functii),
pot fi implementate ca functii prieten in loc de metode ale claselor respective, daca se considera ca aceasta alegere este mai naturala;
x	supraincarcarea operatorilor << si >> pentru iesiri si intrari de obiecte, dupa indicatiile de mai jos, astfel incat sa fie permise
(si ilustrate in program);
x	sa existe metode publice prin care se realizeaza citirea si afisarea informațiilor complete a n obiecte, memorarea și afisarea
acestora.
x	programul sa aiba un meniu interactiv

Necesar: programul sa nu contina erori de compilare si sa ruleze in CodeBlocks

Tema 16.
D10 Clasa "individ", avand:     // mediu spre greu
    - membrii privati:   i (intreg) = pozitia (dintr-un tablou unidimensional de 30 de elemente declarat static in main);
                         tip (char) = „numele” speciei ('+' sau '0');
                         varsta (intreg) = varsta (de la 0 la o valoare maxima fixa aleasa de programator);
                         energie (double) = energia;
                         viu (unsigned char) = este 1 daca e viu si 0 daca e mort;

    - constructor care primeste ca parametrii pozitia si tipul si initializeaza corespunzator membrii respectivi; varsta se initializeaza
cu 0, energia cu o valoare fixa aleasa de programator,  viu cu 1;

    - metode private:
hraneste = creste energia proprie cu o valoare random intre 1 si 10;
inmulteste = adauga un fiu in stanga sau in dreapta individului daca pozitia este libera (fiul are acelasi tip, varsta este 0, iar energia
este de doua ori mai mare fata de cea a parintelui)
ataca = pentru fiecare individ x invecinat si de alt tip, daca energia proprie este mai mare decat energia lui x, din energia proprie se
scade energia lui x iar x este omorat (i se aplica metoda "moare");
imbatraneste = creste varsta cu 1; scade energie cu o valoare constanta aleasa de programator; daca a atins o varsta maxima aleasa de
programator sau daca energia sa a devenit <=0, individul curent este omorat (i se aplica metoda "moare");
moare = viu devine 0;

    - metode publice:
actualizare = aplica succesiv metodele: hraneste, inmulteste, ataca, imbatraneste;
esteviu = returneaza 1 daca viu==1 si 0 altfel;
gettip = returneaza tipul.
    Se citesc maxim 30 de indivizi (supraincarcare pentru >> si <<).
    Realizare meniu cu functia de: citire indivizi (se citeste si numarul de indivizi aici), actualizare, este viu, get tip.
*/

#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

class individ {
    char tip;
    unsigned char viu;
    int i, varsta;
    double energie;

public:
//constructor de initializare fara parametri:
    individ() {
        tip = '\0';
        i = -1;
        setvarsta(0);
        setenergie(50);
        setviu('1');
    }
//constructor de initializare cu parametri:
    individ(int I, char Tip);
//constructor de initializare cu toti parametri:
    individ(int I, char Tip, unsigned char viu, int varsta, double energie);
//constructor de copiere
    individ(const individ& ob);
//destructor
    ~individ() {}
//operator de atribuire
    individ& operator=(const individ& ob);
    individ& operator=(const char tip);
    individ& operator=(const int i);

    void actualizare() {
        hraneste();
        inmulteste();
        ataca();
        imbatraneste();
    }

    int esteviu() {
        if (viu == '1')
            return 1;
        else return 0;
    }
//get pentru tip:
    char gettip() {
        return this->tip;
    }
//supraincarcare pentru >> si <<:
    friend istream& operator>> (istream&, individ&);
    friend ostream& operator<< (ostream&, const individ&);

private:
//getteri pentru restul datelor membre:
    unsigned char getviu() {
        return this->viu;
    }

    int geti() {
        return this->i;
    }

    int getvarsta() {
        return this->varsta;
    }

    double getenergie() {
        return this->energie;
    }
//setteri pentru toate datele membre:
    void settip(const char tip) {
        this->tip = tip;
    }

    void setviu(const unsigned char viu) {
        this->viu = viu;
    }

    void seti(const int i) {
        this->i = i;
    }

    void setvarsta(const int varsta) {
        this->varsta = varsta;
    }

    void setenergie(const double energie) {
        this->energie = energie;
    }

    void hraneste() {
        energie += 1 + (rand() % 10);
    }

    void inmulteste();

    void imbatraneste();

    void moare() {
        energie = 0;
        viu = '0';
    }

    void ataca();

    friend class populatie;
};

class populatie {
    individ v[30];
public:
    void meniu();
    void citire();
    void actualizeaza();
    void esteviumeniu();
    void gettipmeniu();
    void afisare();
    bool verificaviata();
    void actualizeazameniu();
};

individ::individ(int I, char Tip) : i(I), tip(Tip) {
    setvarsta(0);
    setenergie(50);
    setviu('1');
}

individ::individ(int I, char Tip, unsigned char viu, int varsta, double energie) : i(I), tip(Tip) {
    setvarsta(varsta);
    setenergie(energie);
    setviu(viu);
}

individ::individ(const individ & ob) {
    seti(ob.i);
    settip(ob.tip);
    setvarsta(ob.varsta);
    setenergie(ob.energie);
    setviu(ob.viu);
}

individ& individ::operator=(const individ& ob) {
    if (this == &ob)
        return *this;
    else {
        seti(ob.i);
        settip(ob.tip);
        setvarsta(ob.varsta);
        setenergie(ob.energie);
        setviu(ob.viu);
    }
    return *this;
}

individ& individ::operator=(const char tip) {
    if (this->tip == tip)
        return *this;
    else
        settip(tip);
    return *this;
}

individ& individ::operator=(const int i) {
    if (this->i == i)
        return *this;
    else
        seti(i);
    return *this;
}

void individ::inmulteste() {
    if (i == 0) {
        if ((*(this + 1)).geti() == -1) {
            individ aux(i + 1, this->tip);
            aux.setenergie(this->energie * 2);
            *(this + 1) = aux;
        }
    }
    else
        if (i == 29) {
            if ((*(this - 1)).geti() == -1) {
                individ aux(i - 1, this->tip);
                aux.setenergie(this->energie * 2);
                *(this - 1) = aux;
            }
        }
        else
            if ((*(this - 1)).geti() == -1) {
                individ aux(i - 1, this->tip);
                aux.setenergie(this->energie * 2);
                *(this - 1) = aux;
            }
            else
                if ((*(this + 1)).geti() == -1) {
                    individ aux(i + 1, this->tip);
                    aux.setenergie(this->energie * 2);
                    *(this + 1) = aux;
                }
}

void individ::imbatraneste() {
    varsta++;
    energie -= 20;
    if (varsta > 50 || energie <= 0) {
        moare();
    }
}

void individ::ataca() {
    if (this->i != 0 && (this - 1)->tip != '\0' && (this - 1)->tip != this->tip && (this - 1)->energie > this->energie) {
        (*(this - 1)).setenergie((this - 1)->energie - this->energie);
        moare();
    }
    else if (this->i != 29 && (this + 1)->tip != '\0' && (this + 1)->tip != this->tip && (this + 1)->energie > this->energie) {
        (*(this + 1)).setenergie((this + 1)->energie - this->energie);
        moare();
    }
}

istream& operator>> (istream& in, individ& ob) {
    in >> ob.i >> ob.tip;
    return in;
}

ostream& operator<< (ostream& out, const individ& ob) {
    out << "-----------------------------------------------------------\n";
    out << "Pozitia individului: " << ob.i << "\n";
    out << "Numele speciei: " << ob.tip << "\n";
    out << "-----------------------------------------------------------\n";
    return out;
}
//citirea a n obiecte:
void populatie::citire() {
    int n;
    cout << "Numar de indivizi: ";
    cin >> n;
    string rasp;
    cout << "Doriti sa introduceti manual pozitiile? DA/NU\n";
    cin >> rasp;
    if (rasp == "DA") {
        cout << "Pozitie individ (de la 0 la 29) urmata de specie individ (0 sau +):\n";
        for (int i = 0; i < n; i++) {
            individ aux;
            cin >> aux;
            v[aux.geti()] = aux;
        }
    }
    else {
        int random[30];
        for (int i = 0; i < 30; i++)
            random[i] = i;
        random_shuffle(random, random + 30);
        cout << "Speciile indivizilor (0 sau +):\n";
        for (int poz = 0; poz < n; poz++) {
            char tip;
            cin >> tip;
            individ aux(random[poz], tip);
            v[aux.i] = aux;
        }
    }
}
//afisarea a n obiecte:
void populatie::afisare() {
    HANDLE  hConsole;
    int k;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 30; i++) {
        if (v[i].viu == '1')
            k = 10;
        else
            k = 12;
        SetConsoleTextAttribute(hConsole, k);
        if (v[i].i != -1)
            cout << "    Individul " << v[i].i << ", specia " << v[i].tip << ", viu " << v[i].viu << ", varsta " << v[i].varsta << ", energie " << v[i].energie << endl;
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void populatie::actualizeaza() {
    int aux[30];
    for (int i = 0; i < 30; i++) {
        aux[i] = v[i].i;
    }
    for (int i = 0; i < 30; i++) {
        if (aux[i] != -1)
            v[i].actualizare();
    }
}

void populatie::actualizeazameniu() {
    int nr;
    cout << "Cate actualizari doriti sa efectuati? ";
    cin >> nr;
    for (int i = 0; i < nr; i++)
        actualizeaza();
    cout << "Indivizii au fost actualizati. Populatia este: \n";
    afisare();
}

void populatie::esteviumeniu() {
    int i;
    cout << "Pozitia individului: ";
    cin >> i;
    if (v[i].i == -1)
        cout << "INDIVIDUL NU EXISTA\n";
    else
        if (v[i].esteviu())
            cout << "DA\n";
        else
            cout << "NU\n";
}

void populatie::gettipmeniu() {
    int i;
    cout << "Pentru ce individ doriti sa stiti tipul? ";
    cin >> i;
    if (v[i].i == -1)
        cout << "INDIVIDUL NU EXISTA\n";
    else
        cout << "Tipul individului " << i << " este " << v[i].gettip() << ".\n";
}

bool populatie::verificaviata() {
    int i = 0;
    while (i < 30 && v[i].viu == '0')
        i++;
    if (i == 30)
        return false;
    else
        return true;
}

//meniu interactiv:
void populatie::meniu() {
    int optiune;
    cout << endl;
    cout << "--------JOCUL VIETII------------------------------------------------------------------------------\n" << endl;
    while (verificaviata())
    {
        cout << "Optiunile sunt:\n" << "   0 -> Renuntare la populatia curenta\n" << "   1 -> Citire indivizi\n" << "   2 -> Actualizare\n" << "   3 -> Este viu?\n" << "   4 -> Get tip\n" << "   5 -> Afiseaza situatia curenta\n";
        cout << "--------------------------------------------------------------------------------------------------\nIntroduceti optiunea: ";
        cin >> optiune;
        switch (optiune)
        {
        case 0: return;
        case 1: citire();
            break;
        case 2: actualizeazameniu();
            break;
        case 3: esteviumeniu();
            break;
        case 4: gettipmeniu();
            break;
        case 5: afisare();
        }
        cout << "--------------------------------------------------------------------------------------------------\n";
    }
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 79);
    cout << "                                               Populatia este moarta. 'Jocul vietii' s-a incheiat.";
    SetConsoleTextAttribute(hConsole, 7);
    cout << endl;
}

    int main() {
       populatie Populatie;
        Populatie.meniu();
        cout << "--------------------------------------------------------------------------------------------------\n";
        cout << "Doriti sa aplicati citire, stocare si afisare a 'Jocului vietii' pentru mai multe populatii? DA/NU\n";
        string rasp;
        cin >> rasp;
        if (rasp == "DA") {
            populatie P[20];
            int n;
            cout << "Cate populatii? ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                P[i].meniu();
            }
        }
        else {
            HANDLE  hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 160);
            cout << "Sesiune de joc incheiata.                                                                           ";
            SetConsoleTextAttribute(hConsole, 7);
        }
    }