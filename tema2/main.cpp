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
    /// declaram un vector de smart pointeri la clasa de baza Proces
    /// folosesc shared_ptr pentru a stoca obiecte de tipul Proces în vectorul procese
    /// cand nu mai sunt necesare obiectele o sa se distruga automat fara sa fie nevoie sa apelam automat delete
    std::vector<std::shared_ptr<Proces>> procese;

/// citire procese civile
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
        /// am folosit make_shared deorece creeaza un obiect de tip Proces_civil si ii aloca direct new, astfel incat nu mai trebuie sa o fac manual
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
        std::cout<<"-------------------------------------------------------------------------\n";
        std::cout << "1. Afisare procese civile\n";
        std::cout<<std::endl;
        std::cout<<"-------------------------------------------------------------------------\n";
        std::cout << "2. Afisare procese penale\n";
        std::cout<<std::endl;
        std::cout<<"-------------------------------------------------------------------------\n";
        std::cout << "3. Modificare stadiu proces\n";
        std::cout<<std::endl;
        std::cout<<"-------------------------------------------------------------------------\n";
        std::cout << "4. Calcul taxa timbru pentru fiecare proces\n";
        std::cout<<std::endl;
        std::cout<<"-------------------------------------------------------------------------\n";
        std::cout << "5. Adaugare proces civil\n";
        std::cout<<std::endl;
        std::cout<<"-------------------------------------------------------------------------\n";
        std::cout << "6. Adaugare proces penal\n";
        std::cout<<std::endl;
        std::cout<<"-------------------------------------------------------------------------\n";
        std::cout << "7. Iesire\n";
        std::cout<<std::endl;
        std::cout<<"-------------------------------------------------------------------------\n";
        std::cout << "Optiunea dvs.: ";
        std::cout<<std::endl;
        std::cin >> optiune;
        std::cout<<"-------------------------------------------------------------------------\n";
        std::cout<<std::endl;

        bool gasit = false;
        switch (optiune)
        {
        case 1:
            std::cout << "\nProcese civile introduse: \n";
            /// parcurgem lista procese in care avem salvate procesele civile si penale
            for (auto& p : procese)
            {
                /// facem o conversie dinamica a pointerului catre clasa Proces_civil
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
            int nrProces;
            bool stadiuNou;
            std::cout << "Introduceti numarul de proces pentru care doriti sa modificati stadiul: ";
            std::cin >> nrProces;
            std::cout << "Introduceti noul stadiu (0 - in asteptare, 1 - in curs): ";
            std::cin >> stadiuNou;


            for (auto& proc : procese)
            {
                if (proc->get_nrProces() == nrProces)
                {
                    proc->setStadiu(stadiuNou);
                    gasit = true;
                    std::cout << "\nStadiul procesului cu numarul " << proc->get_nrProces() << " a fost actualizat cu succes!\n";
                    break;
                }
            }

            if (!gasit)
            {
                std::cout << "\nNumarul de proces introdus nu exista!\n";
            }

            break;

        case 4:
            std::cout << "\nCalcul taxa timbru pentru fiecare proces:\n";
            for (auto& p : procese)
            {
                /// facem downcast la un obiect de tipul Proces_civil, si il salveaza in pointerul proces_civil_ptr
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
            std::cout << "\nAti ales sa iesiti din program. Pa Pa!\n";
            break;
        default:
            std::cout << "\nOptiunea introdusa nu exista. Va rugam sa alegeti alta optiune.\n";
            break;
        }
    }
    return 0;
}

