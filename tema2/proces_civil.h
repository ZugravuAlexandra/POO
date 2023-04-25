#pragma once
#include "proces.h"

class Proces_civil : public Proces{

private:
    double dauneMorale;
    double dauneMateriale;
    int nrMartori;
    bool stadiu;

public:

    Proces_civil();
    Proces_civil(int nrProces, std::string reclamant, std::string reclamat, double dauneMorale, double dauneMateriale, int nrMartori, bool stadiu);
    Proces_civil(const Proces_civil& other);
    Proces_civil& operator=(const Proces_civil& other);

    /// override indica faptul ca functia citire suprascrie functia virtuala citire din clasa de baza Proces
    void citire(std::istream& is) override;
    void afisare(std::ostream& os) const;

    friend std::istream& operator>>(std::istream& in, Proces_civil& pc);
    friend std::ostream& operator<<(std::ostream& os, const Proces_civil& pc);

    double getdauneMorale() const;
    double getdauneMateriale() const;
    int getnrMartori() const;
    bool getstadiu() const;


    void setStadiu(bool stadiuNou) override ;
    double calculTaxaTimbru() const;

    ~Proces_civil();
};
