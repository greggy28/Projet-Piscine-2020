#include <iostream>
#include "Graphe.h"
#include "Svgfile.h"
#include <string>

void menu()             //menu
{
    int fin=0;
    std::string nom = "vide", nom2 = "vide";
    int choix1;
    std::string choix2;

    do
    {
        std::cout << std::endl << "------- MENU -------" << std::endl;
        std::cout << std::endl << "1. Charger un graphe\n"
                  "2. Changer le systeme de ponderation d'un graphe\n"
                  "3. Calculer l'indice de centralite\n"
                  "4. Tester la vulnerabilite\n"
                  "5. Quitter le menu" << std::endl;

        std::cout << std::endl << "Choisissez une option !" << std::endl;               //choix de l'option

        std::cin >> choix1;                         //r�cup�ration du choix utilisateur

        while((choix1 > 5)|| (choix1 < 0))          //blindage
        {
            std::cout << "Ne correspond pas a un choix possible\n"
                      "Veuillez ressaisir votre choix" << std::endl;

            std::cin >> choix1;
        }

        if((nom == "vide")&&(nom2 == "vide"))                    //v�rification chargement de fichiers
        {
            std::cout << "Il n'y a pas de graphe deja charge\n"
                      "Veuillez en charger un avant toutes actions\n\n"
                      "Veuillez choisir le nom du fichier (topologie) en .txt " << std::endl;

            std::cin >> nom;
            Graphe g{nom,nom2};             //ouverture du fichier
        }

        Svgfile svgout;

        switch(choix1)
        {
        case 1:                         //choix 1 : chargement d'une pond�ration
        {
            std::cout << "Voulez-vous ouvrir un fichier de ponderation (OUI/NON) ?\n";
            std::cin >> choix2;

            while((choix2 != "OUI")&&(choix2 != "NON"))
            {
                std::cout << "Ne correspond pas a un choix possible\n"
                          "Veuillez ressaisir votre choix" << std::endl;

                std::cin >> choix2;
            }

            if(choix2 == "OUI")
            {
                std::cout << "Vous souhaitez charger une ponderation\n"
                          "Veuillez choisir le nom du fichier (ponderation) en .txt" << std::endl;
                std::cin >> nom2;
            }
            else
                nom2 = "vide";

            Graphe g{nom,nom2};     //ouverture du fichier
            g.afficher();
            g.afficherGrapheSvg(&svgout);
        }
        break;

        case 2:
        {
            std::cout << "Vous souhaitez charger une nouvelle ponderation\n"
                      "Veuillez choisir le nom du fichier (ponderation) en .txt" << std::endl;

            std::cin >> nom2;

            Graphe p{nom,nom2};
            p.afficherGrapheSvg(&svgout);
        }
        break;

        case 3:
        {
            double id1,id2;
            std::cout << std::endl << "PCC avec dji:";
            std::cout << std::endl << "Identifiant sommet de depart :";             //on demande le sommet de d�part
            std::cin >> id1;
            std::cout << std::endl << "Identifiant sommet d'arrivee :";             //on demande le sommet d'arriv�e
            std::cin >> id2;
            std::vector<int> arbre = g.rechercheDijkstra(id1);
            g.afficher_parcours(id1,id2,arbre);

            std::cout << std::endl << "PCC avec BFS";
            ///affichage du plus court chemin
            std::cout << std::endl << "parcours a partir du sommet " << id1 << " jusqu'au sommet " << id2 << std::endl;
            g.afficher_parcours(id1,id2,arbre);
        }
        break;

        case 4:
            std::cout << "4_OK" << std::endl;
            break;

        case 5:
            fin = 1;
            break;

        }
    }
    while(fin != 1);
}


int main()
{

    menu();         //appel du menu

    return 0;
}
