#include <iostream>
#include <vector>
#include "proces.h"
#include "proces_civil.h"
#include "proces_penal.h"
#include <memory>
#include <algorithm>

using namespace std;

int main()
{
    std::vector<std::shared_ptr<Proces>> procese;
// citire procese civile
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout << "----------------------------------Buna ziua---------------------------"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    int n_civile, m_penale;
    std::cout << "Va rugam, introduceti numarul de procese civile: ";
    std::cin >> n_civile;


    for (int i = 0; i < n_civile; i++)
    {
        std::shared_ptr<Proces> pc = std::make_shared<Proces_civil>();
        std::cin >> *pc;
        procese.push_back(pc);
    }

    std::cout << "Va rugam, introduceti numarul de procese penale: ";
    std::cin >> m_penale;

    for (int i = 0; i < m_penale; i++)
    {
        std::shared_ptr<Proces> pp = std::make_shared<Proces_penal>();
        std::cin >> *pp;
        procese.push_back(pp);
    }


// meniu interactiv
    int optiune = 0;
    while (optiune != 7)
    {
        std::cout<<"-------------------------------------------------------------------------";
        std::cout<<std::endl;
        std::cout<<"                                       Meniu                                  ";
        std::cout << "\nAlegeti o optiune:\n";
        std::cout<<std::endl;
        std::cout << "1. Afisare procese civile\n";
        std::cout<<std::endl;
        std::cout << "2. Afisare procese penale\n";
        std::cout<<std::endl;
        std::cout << "3. Modificare stadiu proces\n";
        std::cout<<std::endl;
        std::cout << "4. Calcul taxa timbru pentru fiecare proces\n";
        std::cout<<std::endl;
        std::cout << "5. Adaugare proces civil\n";
        std::cout<<std::endl;
        std::cout << "6. Adaugare proces penal\n";
        std::cout<<std::endl;
        std::cout << "7. Iesire\n";
        std::cout<<std::endl;
        std::cout << "Optiunea dvs.: ";
        std::cout<<std::endl;
        std::cin >> optiune;
        std::cout<<"-------------------------------------------------------------------------";
        std::cout<<std::endl;

        switch (optiune)
        {
        case 1:
            std::cout << "\nProcese civile introduse: \n";
            for (auto& p : procese)
            {
                if (std::dynamic_pointer_cast<Proces_civil>(p) != nullptr)
                {
                    std::cout << *p << std::endl;
                }
            }
            break;

        case 2:
            std::cout << "\nProcese penale introduse: \n";
            for (auto& p : procese)
            {
                if (std::dynamic_pointer_cast<Proces_penal>(p) != nullptr)
                {
                    std::cout << *p << std::endl;
                }
            }
            break;

        case 3:
            int nr_proces;
            bool stadiu_nou;
            std::cout << "\nIntroduceti numarul procesului: ";
            std::cin >> nr_proces;
            std::cout << "Introduceti noul stadiu (0 - in asteptare, 1 - in curs): ";
            std::cin >> stadiu_nou;
            if (nr_proces >= 0 && nr_proces < procese.size())
            {
                procese[nr_proces]->setStadiu(stadiu_nou);
                std::cout << "\nStadiul procesului a fost modificat cu succes!\n";
            }
            else
            {
                std::cout << "\nNumarul procesului introdus nu exista!\n";
            }
            break;


        case 4:
            std::cout << "\nCalcul taxa timbru pentru fiecare proces:\n";
            for (auto& p : procese)
            {
                auto proces_civil_ptr = dynamic_cast<Proces_civil*>(p.get());
                if (proces_civil_ptr != nullptr)
                {
                    std::cout << "\nProcesul cu numarul " << p->get_nrProces() << " are taxa de timbru de " << proces_civil_ptr->calculTaxaTimbru() << " lei.\n";
                }
            }
            break;


        case 5:
        {
            std::shared_ptr<Proces_civil> pc = std::make_shared<Proces_civil>();
            std::cin >> *pc;
            procese.push_back(pc);
            std::cout << "\nProces civil adaugat cu succes!\n";
            break;
        }
        case 6:
        {
            std::shared_ptr<Proces_penal> pp = std::make_shared<Proces_penal>();
            std::cin >> *pp;
            procese.push_back(pp);
            std::cout << "\nProces penal adaugat cu succes!\n";
            break;
        }
        case 7:
            std::cout << "\nAti ales sa iesiti din program. La revedere!\n";
            break;
        default:
            std::cout << "\nOptiunea introdusa nu exista. Va rugam sa alegeti alta optiune.\n";
            break;
        }
    }
    return 0;
}

