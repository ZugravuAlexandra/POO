/***

Tema 14. Se dau clasele:
-	Proces (int nrProces, string reclamant, string reclamat)
-	Proces_civil (double dauneMorale, double dauneMateriale, int nrMartori, bool stadiu)
-	Proces_penal (int dovezi, bool stadiu).
Sa se faca verificarile in constructori si la citire astfel: daca nrMartori > 5 automat stadiul este 1, altfel este 0.
Daca la un proces penal numarul dovezilor > 25 atunci stadiul este 1.
Sa se poata modifica stadiul unui proces si sa se creeze o metoda de calculare a taxei de timbru pentru fiecare proces civil.
Taxa de timbru = 10/100 * dauneMorale + 10% * dauneMateriale.
Sa se afle procesul care are taxa de timbru cea mai mare.

***/
#pragma once
#include <iostream>
#include <string>

class Proces {

protected:
    int nrProces;
    std::string reclamant;
    std::string reclamat;
    bool stadiu;

public:
    /// constructor de initializare
    Proces();
    /// constructor parametrizat
    Proces(int nrProces,const std::string reclamant,const std::string reclamat);
    /// constructor de copiere
    Proces(const Proces& other);
    /// functii virtuale
    virtual void citire(std::istream& is);
    virtual void afisare(std::ostream& os) const;
     /// operator de citire
    friend std::istream& operator>>(std::istream& is, Proces& proces);
    /// operator de afisare
    friend std::ostream& operator<<(std::ostream& os,const Proces& proces);
    /// operator de atribuire
    Proces& operator=(const Proces& other);
    /// seter si geter
    int get_nrProces() const;
    std::string get_reclamant() const;
    std::string get_reclamat() const;
    bool getstadiu() const;
    void set_reclamat(const std::string& reclamat);
    void set_reclamant(const std::string& reclamant);
    void setStadiu(bool stadiu);
    ///destructor
    virtual ~Proces();

};


