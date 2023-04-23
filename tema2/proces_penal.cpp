#include <iostream>
#include "proces_penal.h"

Proces_penal::Proces_penal() : Proces(), dovezi(0), stadiu(0) {}

Proces_penal::Proces_penal(int nrProces, std::string reclamant, std::string reclamat, int dovezi, bool stadiu) : Proces(nrProces, reclamant, reclamat), dovezi(dovezi), stadiu(stadiu)
{
    if (dovezi > 25)
        this->stadiu=1;
}

Proces_penal::Proces_penal(const Proces_penal& p) : Proces(p)
{
    dovezi=p.dovezi;
    stadiu=p.stadiu;

}

Proces_penal& Proces_penal::operator=(const Proces_penal& p)
{
    if(this!=&p)
    {
        Proces::operator=(p);
        dovezi = p.dovezi;
        stadiu = p.stadiu;
    }
    return *this;
}

void Proces_penal::citire(std::istream& is)
{
    try {
        Proces::citire(is);
        std::cout << "Numarul de dovezi: ";
        is>>this->dovezi;
        if(this->dovezi<0)
        {
            throw std::invalid_argument("Nr. dovezi trebuie sa fie un numar pozitiv! ");
        }
        if (this->dovezi > 25) {
            this->stadiu = 1;
        }
        else {
            this->stadiu = 0;
        }
    }
    catch (const std::exception& ex) { // prindem exceptiile derivate din std::exception
        std::cerr<< ex.what() << std::endl;
        this->dovezi=0;
        throw; // aruncam exceptia mai departe pentru a fi prinsa in blocurile try-catch superioare
    }
}

std::istream& operator>>(std::istream& in, Proces_penal& pp)
{
    pp.citire(in);
    return in;
}


int Proces_penal::getdovezi() const
{
    return dovezi;
}

bool Proces_penal::getStadiu() const
{
    return stadiu;
}

void Proces_penal::afisare(std::ostream& os) const
{
    Proces::afisare(os);
    os << "Dovezi: " << getdovezi() << '\n';
    os << "Stadiu: " << getStadiu() << '\n';
}

std::ostream& operator<<(std::ostream& os, const Proces_penal& pp) {

    pp.afisare(os);
    return os;
}




void Proces_penal::setStadiu(bool s)
{
    stadiu=s;
}

Proces_penal::~Proces_penal() {}
