#include "proces.h"
#include <iostream>
#include <string>
#include <cctype>


Proces::Proces()
{
    nrProces=0;
    reclamant = "";
    reclamat = "";
}

Proces::Proces(int nrProces,const std::string reclamant,const std::string reclamat) : nrProces(nrProces), reclamant(reclamant), reclamat(reclamat) {};

Proces::Proces(const Proces& other)
{
    this->nrProces = other.nrProces;
    this->reclamant = other.reclamant;
    this->reclamat = other.reclamat;

}

Proces& Proces::operator=(const Proces& other)
{
    this->nrProces=other.nrProces;
    this->reclamant=other.reclamant;
    this->reclamat=other.reclamat;
}

void Proces::citire(std::istream& is)
{
    try
    {
        std::cout << "Va rugam, introduceti numarul de proces: ";
        is >> this->nrProces;
        if (this->nrProces<0)
        {
            throw std::invalid_argument("Numarul de proces trebuie sa fie un numar pozitiv!");
        }
    }
    catch (std::exception& e)
    {
        std::cerr<<e.what()<<std::endl;
        this->nrProces=0;
        throw;
    }

    try
    {
        std::cout << "Va rugam, introduceti numele reclamantului: ";
        is >> this->reclamant;
        for (char const& c : this->reclamant)
        {
            if (std::isdigit(c))
            {
                throw std::invalid_argument("Numele reclamantului nu poate fi un numar!");
            }
        }
        if (this->reclamant.empty())
        {
            throw std::invalid_argument("Numele reclamantului nu poate fi gol!");
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }

    try
    {
        std::cout << "Va rugam, introduceti numele reclamatului: ";
        is >> this->reclamat;
        for (char const& c : this->reclamat)
        {
            if (std::isdigit(c))
            {
                throw std::invalid_argument("Numele reclamatului nu poate fi un numar!");
            }
        }
        if (this->reclamat.empty())
        {
            throw std::invalid_argument("Numele reclamatului nu poate fi gol!");
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }

}



void Proces::afisare(std::ostream& os) const
{
    os<<"Procesul cu numarul: "<<nrProces<<" a fost initiat de "<<reclamant<<" impotriva lui "<<reclamat<<std::endl;

}

std::istream& operator>>(std::istream& is, Proces& proces)
{
    proces.citire(is);
    return is;
}

std::ostream& operator<<(std::ostream& os,const Proces& proces)
{
    proces.afisare(os);
    return os;
}



int Proces::get_nrProces() const
{
    return nrProces;
}

std::string Proces::get_reclamant() const
{
    return reclamant;
}

std::string Proces::get_reclamat() const
{
    return reclamat;
}

bool Proces::getstadiu() const {
    return stadiu;
}

void Proces::set_reclamant(const std::string& reclamant)
{
    this->reclamant=reclamant;
}
void Proces::set_reclamat(const std::string& reclamat)
{
    this->reclamat=reclamat;
}

void Proces::setStadiu(bool stadiuNou) {
    this->stadiu = stadiuNou;
}

Proces::~Proces() {}
