#include <iostream>

using namespace std;

struct Carte
{
    int cod;
    string nume;
    string autor;
    int an_publicatie = 0;
    bool stare = false;
};

struct Biblioteca
{
    int nr_carti;
    Carte* carti = new Carte;
};

struct Persoana
{
    string nume;
    string *carte;

};

void adaugaCarte(Biblioteca biblioteca)
{
    for(int i = 0; i < biblioteca.nr_carti; i++)
    {
        if(biblioteca.carti[i].nume == "")
        {
            cout << "Introduceti numele cartii: \n";
            cin >> biblioteca.carti[i].nume;
            cout << "Introduceti numele autorului: \n";
            cin >> biblioteca.carti[i].autor;
            cout << "Introduceti anul publicatiei: \n";
            cin >> biblioteca.carti[i].an_publicatie;
            cout << "Introduceti codul de identificare al cartii: \n";
            cin >> biblioteca.carti[i].cod;
            break;
        }

    }
}

void listareCarti(Biblioteca biblioteca)
{
    cout << "Cartile existente in biblioteca sunt: \n";
    for(int i = 0; i < biblioteca.nr_carti; i++)
    {
        if(biblioteca.carti[i].stare == false && biblioteca.carti[i].nume != "")
        {
            cout << biblioteca.carti[i].nume << "\n";
        }
    }
    cout << '\n';
}

void reseteazaElement(Biblioteca biblioteca, int i)
{
    biblioteca.carti[i].nume.clear();
    biblioteca.carti[i].autor.clear();
    biblioteca.carti[i].an_publicatie = 0;
    biblioteca.carti[i].stare = 0;
    biblioteca.carti[i].cod = 0;
}

void eliminaCarte(Biblioteca biblioteca)
{
    int id;
    cout << "Introduceti codul cartii pe care vreti sa o eliminati:\n";
    cin >> id;

    for(int i = 0; i < biblioteca.nr_carti; i++)
    {
        if(biblioteca.carti[i].cod == id)
        {
            reseteazaElement(biblioteca, i);
            break;
        }
    }
}

void listareInformatiiCarte(Biblioteca biblioteca)
{
    int id;
    cout << "Introduceti id-ul cartii despre care vreti informatii:\n";
    cin >> id;

    for(int i = 0; i < biblioteca.nr_carti; i++)
    {
        if(biblioteca.carti[i].cod == id)
        {
            cout << biblioteca.carti[i].nume << " scrisa de " << biblioteca.carti[i].autor << " publicata in anul " <<
                 biblioteca.carti[i].an_publicatie << " are codul " << biblioteca.carti[i].cod << " si este " <<
                 ((biblioteca.carti[i].stare == true) ? "imprumutata." : "in biblioteca.\n");
            break;
        }
    }
}

void adaugaPersoana(Biblioteca biblioteca, Persoana *persoane, string numePersoana, string numeCarte)
{
    for(int i = 0; i < biblioteca.nr_carti; i++)
    {
        if(persoane[i].nume == "")
        {
            persoane[i].nume = numePersoana;
            persoane[i].carte[0] = numeCarte;
            break;
        }
    }
}

void imprumutaCarte(Biblioteca biblioteca, Persoana *persoane)
{
    int id;
    string nume;
    int var = 0;        //verifica daca s-a gasit persoana cu numele dat

    cout << "Introduceti numele persoanei care va imprumuta cartea:\n";
    cin >> nume;
    cout << "Introduceti codul cartii pe care o va imprumuta:\n";
    cin >> id;

    for(int i = 0; i < biblioteca.nr_carti; i++)       //iterez prin carti
    {

        if(biblioteca.carti[i].cod == id)              //daca id-ul corespunde
        {

            if(biblioteca.carti[i].stare == false)     //daca nu este deja imprumutata
            {

                for(int j = 0; j < biblioteca.nr_carti; j++)       //iterez prin persoane
                {
                    if(persoane[j].nume == nume)                     //daca persoana exista deja
                    {
                        var = 1;                                   //am gasit persoana cu numele dat
                        for(int k = 0; k < biblioteca.nr_carti; k++)   //iterez prin carti
                        {
                            if(persoane[j].carte[k] == "")              //gasesc un loc liber
                            {
                                persoane[j].carte[k] = biblioteca.carti[i].nume;       //carte = nume
                                biblioteca.carti[i].stare = true;     //starea cartii devine imprumutata
                                break;
                            }
                        }
                    }
                }
                if(var == 0)                        //daca nu s-a gasit persoana o adaugam
                {
                    adaugaPersoana(biblioteca, persoane, nume, biblioteca.carti[i].nume); //adaug persoana
                    biblioteca.carti[i].stare = true;
                    break;
                }

            }
            else
            {
                cout << "Cartea este deja imprumutata.\n";
            }

            break;
        }

    }
}

void listeazaInformatiiPersoana(Persoana *persoane, Biblioteca biblioteca)
{
    string nume;
    cout << "Introduceti numele persoanei despre care vreti informatii:\n";
    cin >> nume;

    for(int i = 0; i < biblioteca.nr_carti; i++)
    {
        if(persoane[i].nume == nume)
        {
            cout << "Persoana " << persoane[i].nume << " a imprumutat cartile: ";
            for(int j = 0; j < biblioteca.nr_carti; j++)
            {
                if(persoane[i].carte[j] != "")
                {
                    cout << persoane[i].carte[j] << " ";
                }
            }
        }
    }
}

void Meniu()
{
    cout << "Introduceti operatia pe care vreti sa o efectuati: \n";
    cout << " A - Adauga carte in biblioteca;\n";
    cout << " L - Listare carti din biblioteca;\n";
    cout << " E - Elimina carte din biblioteca;\n";
    cout << " I - Imprumuta carte;\n";
    cout << " C - Listare informatii despre o carte;\n";
    cout << " P - Listare informatii despre o persoana;\n";
    cout << " Q - Inchidere biblioteca.\n";
}

int main()
{
    int n;
    cout << "Introduceti numarul maxim de carti din biblioteca:\n";
    cin >> n;

    Biblioteca biblioteca;
    Persoana *persoane = new Persoana[n];
    persoane->carte = new string[n];                        ///o persoana poate imprumuta toate cartile din biblioteca = n

    biblioteca.nr_carti = n;
    biblioteca.carti = new Carte[n];                       ///am alocat dinamic fiecare carte in parte


    char op;
    do
    {
        Meniu();
        cin >> op;

        switch(op)
        {
        case 'A':
            cout << "Adauga carte: \n";
            adaugaCarte(biblioteca);
            cout << "\n";
            break;
        case 'L':
            cout << "Listare carti: \n";
            listareCarti(biblioteca);
            cout << "\n";
            break;
        case 'E':
            cout << "Elimina carte: \n";
            eliminaCarte(biblioteca);
            cout << "\n";
            break;
        case 'I':
            cout << "Imprumuta carte: \n";
            imprumutaCarte(biblioteca, persoane);
            cout << "\n";
            break;
        case 'C':
            cout << "Listeaza informatii carte: \n";
            listareInformatiiCarte(biblioteca);
            cout << "\n";
            break;
        case 'P':
            cout << "Listeaza informatii persoana: \n";
            listeazaInformatiiPersoana(persoane, biblioteca);
            cout << "\n";
            break;
        case 'Q':
            cout << "La revedere!\n";
            cout << "\n";
            break;
        default:
            cout << "Operatie invalida!\n";
            cout << "\n";
            break;
        }
    }
    while(op != 'Q');

    delete[] biblioteca.carti;

}
