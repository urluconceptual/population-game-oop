#include <iostream>
#include <windows.h>
#include <algorithm>

using namespace std;

class Individ {
    char tip;
    unsigned char viu;
    int i, varsta;
    double energie;

public:
    //constructor de initializare fara parametri:
    Individ() {
        tip = '\0';
        i = -1;
        setvarsta(0);
        setenergie(50);
        setviu('1');
    }
    //constructor de initializare cu parametri:
    Individ(int I, char Tip);
    //constructor de initializare cu toti parametri:
    Individ(int I, char Tip, unsigned char viu, int varsta, double energie);
    //constructor de copiere
    Individ(const Individ& ob);
    //destructor
    ~Individ() {}
    //operator de atribuire
    Individ& operator=(const Individ& ob);
    Individ& operator=(const char tip);
    Individ& operator=(const int i);

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
    friend istream& operator>> (istream&, Individ&);
    friend ostream& operator<< (ostream&, const Individ&);

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

    friend class Populatie;
};

class Populatie {
    Individ v[30];
protected:
    void citire();
    void actualizeaza();
    void esteViuMeniu();
    void getTipMeniu();
    void afisare();
    bool verificaViata();
    void actualizeazaMeniu();

    friend class Meniu;
};

class Meniu {
    static Meniu* instanta;
    Populatie* p;
    Meniu() {
        p = new Populatie;
    }
public:
    static Meniu* getInstanta() {
        if (instanta == nullptr)
            instanta = new Meniu;
        return instanta;
    }
    void meniu();
    void restart();
};

Meniu* Meniu::instanta = nullptr;

Individ::Individ(int I, char Tip) : i(I), tip(Tip) {
    setvarsta(0);
    setenergie(50);
    setviu('1');
}

Individ::Individ(int I, char Tip, unsigned char viu, int varsta, double energie) : i(I), tip(Tip) {
    setvarsta(varsta);
    setenergie(energie);
    setviu(viu);
}

Individ::Individ(const Individ& ob) {
    seti(ob.i);
    settip(ob.tip);
    setvarsta(ob.varsta);
    setenergie(ob.energie);
    setviu(ob.viu);
}

Individ& Individ::operator=(const Individ& ob) {
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

Individ& Individ::operator=(const char tip) {
    if (this->tip == tip)
        return *this;
    else
        settip(tip);
    return *this;
}

Individ& Individ::operator=(const int i) {
    if (this->i == i)
        return *this;
    else
        seti(i);
    return *this;
}

void Individ::inmulteste() {
    if (i == 0) {
        if ((*(this + 1)).geti() == -1) {
            Individ aux(i + 1, this->tip);
            aux.setenergie(this->energie * 2);
            *(this + 1) = aux;
        }
    }
    else
        if (i == 29) {
            if ((*(this - 1)).geti() == -1) {
                Individ aux(i - 1, this->tip);
                aux.setenergie(this->energie * 2);
                *(this - 1) = aux;
            }
        }
        else
            if ((*(this - 1)).geti() == -1) {
                Individ aux(i - 1, this->tip);
                aux.setenergie(this->energie * 2);
                *(this - 1) = aux;
            }
            else
                if ((*(this + 1)).geti() == -1) {
                    Individ aux(i + 1, this->tip);
                    aux.setenergie(this->energie * 2);
                    *(this + 1) = aux;
                }
}

void Individ::imbatraneste() {
    varsta++;
    energie -= 20;
    if (varsta > 50 || energie <= 0) {
        moare();
    }
}

void Individ::ataca() {
    if (this->i != 0 && (this - 1)->tip != '\0' && (this - 1)->tip != this->tip && (this - 1)->energie > this->energie) {
        (*(this - 1)).setenergie((this - 1)->energie - this->energie);
        moare();
    }
    else if (this->i != 29 && (this + 1)->tip != '\0' && (this + 1)->tip != this->tip && (this + 1)->energie > this->energie) {
        (*(this + 1)).setenergie((this + 1)->energie - this->energie);
        moare();
    }
}

istream& operator>> (istream& in, Individ& ob) {
    in >> ob.i >> ob.tip;
    return in;
}

ostream& operator<< (ostream& out, const Individ& ob) {
    out << "-----------------------------------------------------------\n";
    out << "Pozitia individului: " << ob.i << "\n";
    out << "Numele speciei: " << ob.tip << "\n";
    out << "-----------------------------------------------------------\n";
    return out;
}
//citirea a n obiecte:
void Populatie::citire() {
    int n;
    cout << "Numar de indivizi: ";
    cin >> n;
    string rasp;
    cout << "Doriti sa introduceti manual pozitiile? DA/NU\n";
    cin >> rasp;
    if (rasp == "DA") {
        cout << "Pozitie individ (de la 0 la 29) urmata de specie individ (0 sau +):\n";
        for (int i = 0; i < n; i++) {
            Individ aux;
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
            Individ aux(random[poz], tip);
            v[aux.i] = aux;
        }
    }
}
//afisarea a n obiecte:
void Populatie::afisare() {
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

void Populatie::actualizeaza() {
    int aux[30];
    for (int i = 0; i < 30; i++) {
        aux[i] = v[i].i;
    }
    for (int i = 0; i < 30; i++) {
        if (aux[i] != -1)
            v[i].actualizare();
    }
}

void Populatie::actualizeazaMeniu() {
    int nr;
    cout << "Cate actualizari doriti sa efectuati? ";
    cin >> nr;
    for (int i = 0; i < nr; i++)
        actualizeaza();
    cout << "Indivizii au fost actualizati. Populatia este: \n";
    afisare();
}

void Populatie::esteViuMeniu() {
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

void Populatie::getTipMeniu() {
    int i;
    cout << "Pentru ce individ doriti sa stiti tipul? ";
    cin >> i;
    if (v[i].i == -1)
        cout << "INDIVIDUL NU EXISTA\n";
    else
        cout << "Tipul individului " << i << " este " << v[i].gettip() << ".\n";
}

bool Populatie::verificaViata() {
    int i = 0;
    while (i < 30 && v[i].viu == '0')
        i++;
    if (i == 30)
        return false;
    else
        return true;
}

//meniu interactiv:
void Meniu::meniu() {
    int optiune;
    cout << endl;
    cout << "--------JOCUL VIETII------------------------------------------------------------------------------\n" << endl;
    while (p->verificaViata())
    {
        cout << "Optiunile sunt:\n" << "   0 -> Renuntare la populatia curenta\n" << "   1 -> Citire indivizi\n" << "   2 -> Actualizare\n" << "   3 -> Este viu?\n" << "   4 -> Get tip\n" << "   5 -> Afiseaza situatia curenta\n";
        cout << "--------------------------------------------------------------------------------------------------\nIntroduceti optiunea: ";
        cin >> optiune;
        switch (optiune)
        {
        case 0: return;
        case 1: p->citire();
            break;
        case 2: p->actualizeazaMeniu();
            break;
        case 3: p->esteViuMeniu();
            break;
        case 4: p->getTipMeniu();
            break;
        case 5: p->afisare();
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

void Meniu::restart() {
    delete p;
    p = new Populatie;
}

int main() {
    Meniu* M = Meniu::getInstanta();
    M->meniu();
    cout << "--------------------------------------------------------------------------------------------------\n";
    cout << "Doriti sa aplicati citire, stocare si afisare a 'Jocului vietii' pentru mai multe populatii? DA/NU\n";
    string rasp;
    cin >> rasp;
    if (rasp == "DA") {
        int n;
        cout << "Cate populatii? ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            M->restart();
            M->meniu();
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