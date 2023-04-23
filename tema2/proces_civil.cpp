#include "proces_civil.h"
#include <iostream>

Proces_civil::Proces_civil() : Proces(), dauneMorale(0), dauneMateriale(0), nrMartori(0), stadiu(0) {}

Proces_civil::Proces_civil(int nrProces, std::string reclamant, std::string reclamat, double dauneMorale, double dauneMateriale, int nrMartori, bool stadiu) : Proces(nrProces, reclamant, reclamat), dauneMorale(dauneMorale), dauneMateriale(dauneMateriale), nrMartori(nrMartori), stadiu(stadiu) {
    if (nrMartori > 5) {
        this->stadiu = 1;
    }
    else
        this->stadiu=0;
}


Proces_civil::Proces_civil(const Proces_civil& other) : Proces(other), dauneMorale(other.dauneMorale), dauneMateriale(other.dauneMateriale), nrMartori(other.nrMartori), stadiu(other.stadiu) {}

Proces_civil& Proces_civil::operator=(const Proces_civil& other) {

    if(this!=&other)
    {
        Proces::operator=(other);
        this->dauneMorale=other.dauneMorale;
        this->dauneMateriale=other.dauneMateriale;
        this->nrMartori=other.nrMartori;
        this->stadiu=other.stadiu;
    }
    return *this;

}

void Proces_civil::citire(std::istream& is) {
    Proces::citire(is);
    try {
        std::cout << "Introduceti daunele morale: ";
        is >> this->dauneMorale;
        if (this->dauneMorale < 0) {
            throw std::invalid_argument("Daunele morale trebuie sa fie pozitive!");
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        this->dauneMorale = 0;
    }

    try {
        std::cout << "Introduceti daunele materiale: ";
        is >> this->dauneMateriale;
        if (this->dauneMateriale < 0) {
            throw std::invalid_argument("Daunele materiale trebuie sa fie pozitive!");
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        this->dauneMateriale = 0;
    }

    try {
        std::cout << "Introduceti numarul de martori: ";
        is >> this->nrMartori;
        if (this->nrMartori < 0) {
            throw std::invalid_argument("Numarul de martori trebuie sa fie pozitiv!");
        }
        if(this->nrMartori > 5)
            this->stadiu=1;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        this->nrMartori = 0;
    }
}

std::istream& operator>>(std::istream& in, Proces_civil& pc)
{
    pc.citire(in);
    return in;
}

void Proces_civil::afisare(std::ostream& os) const
{
    Proces::afisare(os);
    os<<"Daune morale: "<<dauneMorale<<std::endl;
    os<<"Daune materiale: "<<dauneMateriale<<std::endl;
    os<<"Nr. martori: "<<nrMartori<<std::endl;
    os<<"Stadiu: "<< (stadiu ? "Incheiat" : "Neincheiat")<< std::endl;
    os<<"Taxa de timbru: "<<calculTaxaTimbru()<<std::endl;


}

std::ostream& operator<<(std::ostream& os,const Proces_civil& pc)
{
    pc.afisare(os);
    return os;
}

double Proces_civil::getdauneMorale() const
{
    return dauneMorale;
}

double Proces_civil::getdauneMateriale() const
{
    return dauneMateriale;
}

int Proces_civil::getnrMartori() const {
    return nrMartori;
}

bool Proces_civil::getstadiu() const {
    return stadiu;
}

void Proces_civil::setStadiu(bool stadiu) {
    this->stadiu = stadiu;
}

double Proces_civil::calculTaxaTimbru() const {
    return 0.1*dauneMorale + 0.1*dauneMateriale;
}

Proces_civil::~Proces_civil() {}



