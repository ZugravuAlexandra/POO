/*

Nr. 6
	Se considera urmatoarele clase:
Materie ce contine atributele: denumire(sir de caractere de lungime fixa 50), optional(true=1/false=0)
Student ce contine atributele: nrMatricol(int), nume(sir de caractere de lungime variabila), grupa(int).
Curs ce contine atributele: mat(Materie), nrStudenti(int), St(vector de obiecte de tip Student).

Definiti clasele si completati-le cu metode si supraincarcari de operatori pentru a permite in functia main() urmatoarele operatii:
	Materie m1(“POO”,0), m2(“Pedagogie”,1),m3;
	if (m1==m2) cout<<”Cursuri identice”;
	else cout<<”Denumiri diferite”;
Student s1(12,“Ionescu”,133), s2;
cin>>s2; cout<<s1<<s2;
Curs c1(m1);
c1+=s1;//adauga student s1 in lista studentilor cursului c1
c1 = c1 + s2; //adauga student s2 in lista studentilor cursului c1
Curs c2 = c1;
cout<<c2;
m3 = c2.materie(); cout<<m3;

*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Materie
{
private:

    string denumire;
    bool optional;

public:

    /// constructor default
    Materie() {}
    /// constructor cu parametrii
    Materie (const string& den, bool op) {
        denumire=den;
        optional=op;
    }
    /// operator de supraincarcare pentru egalitate

    bool operator==(const Materie&);

    /// getter
    string getDenumire() const
    {
        return denumire;
    }
    /// getter

    bool getOptional() const
    {
        return optional;
    }
    /// operator de supraincarcare pentru afisare

    friend ostream& operator<<(ostream&, const Materie&);

    /// destructor
    ~Materie(){}

};
ostream& operator<<(ostream& out, const Materie& ma)
{
        out<<ma.denumire;
        return out;
}
bool Materie::operator==(const Materie& comp)
{
        return (denumire==comp.denumire && optional==comp.optional);
}
class Student
{
private:

    int nrMatricol;
    string nume;
    int grupa;

public:
    /// constructor default
    Student() {}
    /// constructor cu parametrii
    Student(int nrMat, string numeStu, int grp)  {
        nrMatricol=nrMat;
        nume=numeStu;
        grupa=grp;
    }
    ///getter
    int getnrMatricol() const
    {
        return nrMatricol;
    }
    string getnume() const
    {
        return nume;
    }
    int getgrupa() const
    {
        return grupa;
    }
    /// operator de supraincarcare pentru citire
    friend istream& operator>>(istream&, Student&);

    /// operator de supraincarcare pentru afisare
    friend ostream& operator<<(ostream&, const Student&);

    /// destructor
    ~Student() {}

};
istream& operator>>(istream& is, Student& s)
{
    cout<<"Numar matricol: ";
    is>>s.nrMatricol;
    cout<<"Nume elev: ";
    is>>s.nume;
    cout<<"Grupa: ";
    is>>s.grupa;
    return is;
}
ostream& operator<<(ostream& out, const Student& s)
{
    out<<s.nrMatricol<<" "<<s.nume<<" "<<s.grupa;
    return out;
}

class Curs
{
private:
    Materie mat;
    int nrStudenti;
    vector <Student> St;

public:
    /// constructor default
    Curs() {}
    /// constructor cu parametru de tip Materie
    /// initial. mat cu materia primita ca param si nrStudenti cu 0
    Curs(const Materie& materie) {
        mat=materie;
        nrStudenti=0;
    }
    /// constructor de copiere
    Curs(const Curs& copie)
    {
        mat=copie.mat;
        St=copie.St;
        nrStudenti=copie.nrStudenti;
    }
    ///operator de supraincarcare pentru +=
    ///punem in vector noul student, iar apoi nrStudenti creste

    Curs& operator+=(const Student&);

    ///operator de supraincarcare pentru +
    Curs operator+(const Student&);

    ///operator de supraincarcare pentru =
    Curs& operator=(const Curs&);

    ///operator de supraincarcare pentru afisare
    friend ostream& operator<<(ostream& out, const Curs& curs);

    /// returneaza materia cursului curent (functie publica)
    Materie materie() const
    {
        return mat;
    }

    /// destructor
    ~Curs() {}
};
Curs& Curs::operator+=(const Student& s)
{
    St.push_back(s);
    nrStudenti++;
    return *this;
}
Curs Curs::operator+(const Student& s)
{
    *this+=s;
    return *this;
}
Curs& Curs::operator=(const Curs& c)
{
    mat=c.mat;
    nrStudenti=c.nrStudenti;
    St=c.St;
    return *this;
}
ostream& operator<<(ostream& out, const Curs& curs)
{
    out<<"Materia: "<<curs.mat.getDenumire()<<endl;
    out<<"Numar Studenti: "<<curs.nrStudenti<<endl;
    out<<"Studenti: ";
    for(int i=0; i<curs.nrStudenti; i++)
        out<<curs.St[i]<<" ";
    out<<endl;
    return out;
}


int main()
{
    Materie m1("POO", 0), m2("Pedagogie", 1), m3;

    if (m1 == m2)
        cout << "Cursuri identice" << endl;
    else
        cout << "Denumiri diferite" << endl;

    Student s1(12, "Ionescu", 133), s2;
    cin >> s2;
    cout << s1 << endl << s2 << endl;
    Curs c1(m2);
    c1 +=s1;
    c1 = c1 + s2;
    Curs c2 = c1;
    cout<<c2;
    m3 = c2.materie();
    cout<<m3;

    return 0;
}
