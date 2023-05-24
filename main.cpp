#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>


template <typename T>
class Locuinta
{
protected:
    std::string numeClient;
    int suprafataUtila;
    double discount;
public:
    Locuinta(const std::string& nume, int suprafata, double disc) : numeClient(nume), suprafataUtila(suprafata), discount(disc)
{
    if (suprafataUtila < 0)
    {
        throw std::invalid_argument("Suprafata trebuie sa fie un numar pozitiv.");
    }
}
    virtual T calculeazaChirie() const = 0;
    virtual void afiseaza() const = 0;
    virtual void citeste(std::istream& is)
{
    std::cout << "Numele clientului: ";
    is >> this->numeClient;
    std::cout << "Suprafata utila: ";
    is >> this->suprafataUtila;
    if (this->suprafataUtila < 0)
    {
        throw std::invalid_argument("Suprafata trebuie sa fie un numar pozitiv.");
    }
    std::cout << "Discountul: ";
    is >> this->discount;
}



     virtual ~Locuinta() {}
    friend std::ostream& operator<<(std::ostream& os, const Locuinta& locuinta)
    {
        locuinta.afiseaza();
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Locuinta& locuinta)
    {
        locuinta.citeste(is);
        return is;
    }
};





class Apartament : public Locuinta<double>
{
    int etaj;
public:
    Apartament(const std::string& nume, int suprafata, double disc, int et) : Locuinta(nume, suprafata, disc), etaj(et)
{
    if (suprafataUtila < 0)
    {
        throw std::invalid_argument("Suprafata trebuie sa fie un numar pozitiv.");
    }
}

    double calculeazaChirie() const override
    {
        return suprafataUtila * 10 - discount;
    }
    void afiseaza() const override
    {
        std::cout << "Apartament:\n";
        std::cout << "Nume client: " << numeClient << "\n";
        std::cout << "Suprafata utila: " << suprafataUtila << " mp\n";
        std::cout << "Discount: " << discount << "\n";
        std::cout << "Etaj: " << etaj << "\n";
        std::cout << "Chirie: " << calculeazaChirie() << "\n";
    }
    void citeste(std::istream& is) override
{
    try {
        Locuinta<double>::citeste(is);
        std::cout << "Etaj: ";
        is >> etaj;
    } catch (const std::exception& e) {
        std::cerr << "Eroare la citirea datelor: " << e.what() << std::endl;
        throw;
    }
}

    friend std::ostream& operator<<(std::ostream& os, const Apartament& apartament)
    {
        os << "Apartament:\n";
        os << "Nume client: " << apartament.numeClient << "\n";
        os << "Suprafata utila: " << apartament.suprafataUtila << " mp\n";
        os << "Discount: " << apartament.discount << "\n";
        os << "Etaj: " << apartament.etaj << "\n";
        os << "Chirie: " << apartament.calculeazaChirie() << "\n";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Apartament& apartament)
    {
        apartament.citeste(is);
        return is;
    }
};




template<typename T>
class Casa : public Locuinta<double>
{
    T curte;
public:
    Casa(const std::string& nume, int suprafata, double disc, T ct) : Locuinta(nume, suprafata, disc), curte(ct) {


    if (suprafataUtila < 0)
    {
        throw std::invalid_argument("Suprafata trebuie sa fie un numar pozitiv.");
    }

}
    double calculeazaChirie() const override
    {
        return suprafataUtila * 10 - discount;
    }
    void afiseaza() const override
    {
        std::cout << "Casa:\n";
        std::cout << "Nume client: " << numeClient << "\n";
        std::cout << "Suprafata utila: " << suprafataUtila << " mp\n";
        std::cout << "Discount: " << discount << "\n";
        std::cout << "Suprafata curtii: " << curte << " mp\n";
        std::cout << "Chirie: " << calculeazaChirie() << "\n";
    }
    void citeste(std::istream& is) override
    {
        try {
            Locuinta<double>::citeste(is);  // Apelăm funcția din clasa de bază pentru a citi numele, suprafața utilă și discountul
            std::cout << "Suprafata curtii: ";
            is >> curte;
        } catch (const std::exception& e) {
            std::cerr << "Eroare la citirea datelor: " << e.what() << std::endl;
            throw;
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Casa& casa)
    {
        os << "Casa:\n";
        os << "Nume client: " << casa.numeClient << "\n";
        os << "Suprafata utila: " << casa.suprafataUtila << " mp\n";
        os << "Discount: " << casa.discount << "\n";
        os << "Suprafata curtii: " << casa.curte << " mp\n";
        os << "Chirie: " << casa.calculeazaChirie() << "\n";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Casa& casa)
    {
        casa.citeste(is);
        return is;
    }
};




class LocuintaFactory
{
public:
    /// cream obiecte de tip Locuinta<double>
    virtual std::shared_ptr<Locuinta<double>> creazaLocuinta(const std::string& nume, int suprafata, double disc) = 0;
    virtual ~LocuintaFactory() {}
};

// Subclasa Factory pentru crearea Apartamentelor
class ApartamentFactory : public LocuintaFactory
{
public:
    std::shared_ptr<Locuinta<double>> creazaLocuinta(const std::string& nume, int suprafata, double disc) override
    {
        int etaj;
        std::cout << "Etaj: ";
        std::cin >> etaj;
        /// cream un obiect de tip Apartament
        return std::make_shared<Apartament>(nume, suprafata, disc, etaj);
    }
};



// Subclasa Factory pentru crearea Caselor
class CasaFactory : public LocuintaFactory
{
public:
    std::shared_ptr<Locuinta<double>> creazaLocuinta(const std::string& nume, int suprafata, double disc) override
    {
        int suprafataCurte;
        std::cout << "Suprafata curtii: ";
        std::cin >> suprafataCurte;
        return std::make_shared<Casa<int>>(nume, suprafata, disc, suprafataCurte);
    }
};



// Clasa abstractă Observator pentru Observer
class Observator
{
public:
    /// la fiecare adaugare de locuinta o sa primesc o notificare
    virtual void notificare(const std::shared_ptr<Locuinta<double>>& locuinta) = 0;
    virtual ~Observator() {}
};



// Observatorii Apartament și Casa care se înregistrează în AgentieImobiliara
class ApartamentObservator : public Observator
{
public:
    /// functia pentru notificare
    void notificare(const std::shared_ptr<Locuinta<double>>& locuinta) override
    {
        std::cout << "\n================================\n";
        std::cout << "Notificare pentru Apartament: O noua locuinta a fost adaugata:\n";
        std::cout << *locuinta << "\n";
    }
};



class CasaObservator : public Observator
{
public:
    void notificare(const std::shared_ptr<Locuinta<double>>& locuinta) override
    {
        std::cout << "\n================================\n";
        std::cout << "Notificare pentru Casa: O noua locuinta a fost adaugata:\n";
        std::cout << *locuinta << "\n";
    }
};



class AgentieImobiliara
{
    /// vector de pointeri cu lista de locuinte
    std::vector<std::shared_ptr<Locuinta<double>>> locuinte;
    /// vector de pointeri la observator cu lista de observatori
    std::vector<std::shared_ptr<Observator>> observatori;

public:

    /// metoda template
    /// adaugam pointerul de la observator in lista
    template<typename ObsT>
    void adaugaObservator(const std::shared_ptr<ObsT>& observator)
    {
        observatori.push_back(observator);
    }


    /// facem un pointer la locuinta si apoi cu un dynamic_cast verificam tipul locuintei pentru a apela functia de notificare potrivita
    void notificaObservatori(const std::shared_ptr<Locuinta<double>>& locuinta)
    {
        if (dynamic_cast<Apartament*>(locuinta.get()))
        {
            for (const auto& observator : observatori)
            {
                if (dynamic_cast<ApartamentObservator*>(observator.get()))
                {
                    observator->notificare(locuinta);
                }
            }
        }
        else if (dynamic_cast<Casa<int>*>(locuinta.get()))
        {
            for (const auto& observator : observatori)
            {
                if (dynamic_cast<CasaObservator*>(observator.get()))
                {
                    observator->notificare(locuinta);
                }
            }
        }
    }

    /// facem un pointer la locuinta si o adaugam in vectorul locuinte, iar apoi apelam
    /// functia de notificare pentru a ne spune ca a fost adaugat cu succes si detalii despre adaugare
    void adaugaLocuinta(const std::shared_ptr<Locuinta<double>>& loc)
    {
        locuinte.push_back(loc);
        notificaObservatori(loc);
    }

    /// facem un pointer la un factory de locuinte si apeleaza functia creazaLocuinta

template<typename LocuintaFactoryType>
    void adaugaLocuinta(const std::shared_ptr<LocuintaFactoryType>& factory)

    {
        std::string nume;
        int suprafata;
        double disc;

        std::cout << "Nume client: ";
        std::cin >> nume;

        do {
            std::cout << "Suprafata: ";
            std::cin >> suprafata;
            if (suprafata <= 0) {
                std::cout << "Suprafata trebuie sa fie un numar pozitiv. Introduceti o valoare valida.\n";
            }
        } while (suprafata <= 0);

        std::cout << "Discount: ";
        std::cin >> disc;


        auto locuinta = factory->creazaLocuinta(nume, suprafata, disc);

        adaugaLocuinta(locuinta);
    }

    void afiseazaLocuinte(std::function<bool(const std::shared_ptr<Locuinta<double>>&, const std::shared_ptr<Locuinta<double>>&)> criteriuSortare = nullptr)
    {


            std::sort(locuinte.begin(), locuinte.end(), criteriuSortare);


        for (const auto& locuinta : locuinte)
        {
            std::cout << *locuinta << "\n";
        }
    }

};

auto criteriuSortare = [](const std::shared_ptr<Locuinta<double>>& loc1, const std::shared_ptr<Locuinta<double>>& loc2) {
    return loc1->calculeazaChirie() < loc2->calculeazaChirie();
};




int main()
{
    AgentieImobiliara agentie;

    std::shared_ptr<Observator> apartamentObservator = std::make_shared<ApartamentObservator>();
    std::shared_ptr<Observator> casaObservator = std::make_shared<CasaObservator>();

    agentie.adaugaObservator(apartamentObservator);
    agentie.adaugaObservator(casaObservator);

    int optiune;
    do
    {
        std::cout << "\n=========== Meniu ===========\n";
        std::cout << "1. Adauga apartament\n";
        std::cout << "2. Adauga casa\n";
        std::cout << "3. Afiseaza locuinte in ordine crescatoare in functie de chirie\n";
        std::cout << "4. Iesire\n";
        std::cout << "Optiune: ";
        std::cin >> optiune;
        std::cout << "\n================================\n";

        switch (optiune)
        {
        case 1:
            agentie.adaugaLocuinta(std::make_shared<ApartamentFactory>());
            break;
        case 2:
            agentie.adaugaLocuinta(std::make_shared<CasaFactory>());
            break;
        case 3:
            agentie.afiseazaLocuinte(criteriuSortare);
            break;
        case 4:
            std::cout << "La revedere!\n";
            break;
        default:
            std::cout << "Optiune invalida!\n";
            break;
        }
    }
    while (optiune != 4);

    return 0;
}
