#pragma once
#include <iostream>
#include "proces.h"

class Proces_penal : public Proces {
private:
    int dovezi;
    bool stadiu;
public:
    Proces_penal();
    Proces_penal(int nrProces, std::string reclamant, std::string reclamat, int dovezi, bool stadiu);
    Proces_penal(const Proces_penal& p);
    Proces_penal& operator=(const Proces_penal& p);

    void citire(std::istream& is) override;
    void afisare(std::ostream& os) const;


    int getdovezi() const;
    bool getStadiu() const;
    void setStadiu(bool stadiuNou) override;

    friend std::istream& operator>>(std::istream& in, Proces_penal& pp);
    friend std::ostream& operator<<(std::ostream& os, const Proces_penal& pp);


    ~Proces_penal();



};
