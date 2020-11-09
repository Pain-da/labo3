/*
-----------------------------------------------------------------------------------
Nom du fichier : montantEnVaudois.cpp
Auteur(s) : Dimitri De Bleser, Léo Meli, Stefano Pontarolo
Date creation : 27.10.2020
Description :
Remarque(s) :
Compilateur : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include<iostream>
#include <cmath>

using namespace std;

string nombreEnMots(unsigned long long nombre, unsigned long long reste, const string &grandeurActuelle, string str) {

    const string unite[] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix", "onze",
                            "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};
    const string dizaine[] = {"", "", "vingt", "trente", "quarante", "cinquante", "soixante", "septante", "huitante",
                              "nonante"};
    const string grandeur[] = {"mille", "million", "milliard", "billion"};
    enum Grandeur{MILLE, MILLION, MILLIARD, BILLION} mille = MILLE, million = MILLION, milliard = MILLIARD, bilion = BILLION;

    const string sep = "-",
            CENT = "cent",
            PLURIEL = "s",
            DE = "de",
            ET = "et",
            ESPACE = " ",
            DEVISE = "franc";

    if (nombre > 99) {
        str += (nombre > 100 ? unite[nombre / 100] + sep : "") + CENT;
        str += (grandeurActuelle != grandeur[mille] && nombre > 100 && !(nombre % 100) ? PLURIEL : !(nombre % 100) ? "" : sep);
    }
    if (nombre % 100 > 19) {
        str += (dizaine[(nombre % 100) / 10].empty() ? "" : dizaine[(nombre % 100) / 10]) + (unite[nombre % 10].empty() ? "" : sep) +
               (unite[nombre % 10] == unite[1] ? ET + sep : "") + unite[nombre % 10];
    } else {
        str += (grandeurActuelle == grandeur[mille] && unite[nombre % 100] == unite[1] ? "" : unite[nombre % 100]);
    }

    if (nombre || grandeurActuelle == DEVISE) {
        if (grandeurActuelle == grandeur[bilion] || grandeurActuelle == grandeur[milliard] || grandeurActuelle == grandeur[million]) {
            str += (unite[nombre % 10] == unite[1] ? ESPACE : sep) + grandeurActuelle + (nombre > 1 ? PLURIEL : "") + (reste ? sep : ESPACE + DE + ESPACE + DEVISE);
        } else if (grandeurActuelle == grandeur[mille]) {
            str += (unite[nombre % 10] == unite[1] ? "" : sep) + grandeurActuelle + (reste ? sep : "");
        } else if (grandeurActuelle == DEVISE && !str.empty()) {
            str += ESPACE + (nombre == 1 ? grandeurActuelle + ESPACE : grandeurActuelle + PLURIEL + ESPACE);
        } else {
            str += ESPACE + (nombre == 1 ? grandeurActuelle + ESPACE : grandeurActuelle + PLURIEL);
        }
    }

    return str;
}


string montantEnVaudois(long double montant) {

    const long double max = 999999999999999.99;

    if (montant < 0) {
        return "erreur : montant negatif";
    } else if (montant > max) {
        return "erreur : montant trop grand";
    } else {

        string out;
        // conversion pour enlever la partie décimale
        auto entier = (unsigned long long) round(montant * 100) / 100;;
        // conversion pour garder la partie décimale
        auto decimale = ((unsigned long long) (montant * 100)) % 100; //todo a verifier pour la perte de precision


        if (!entier && !decimale) {
            out += "zero franc";
        } else {

            const string BILLION = "billion",
                    MILLIARD = "milliard",
                    MILLION = "million",
                    MILLE = "mille",
                    CENTIME = "centime",
                    VALUE = "franc";
            const long long diviseur_billion = 1000000000000,
                    diviseur_milliard = 1000000000,
                    diviseur_million = 1000000,
                    diviseur_mille = 1000;

            out = nombreEnMots((entier / diviseur_billion), entier % diviseur_billion, BILLION, out);
            if (entier % diviseur_billion) {
                out = nombreEnMots((entier / diviseur_milliard) % diviseur_mille, entier % diviseur_milliard, MILLIARD,
                                   out);
                if (entier % diviseur_milliard) {
                    out = nombreEnMots((entier / diviseur_million) % diviseur_mille, entier % diviseur_million, MILLION,
                                       out);
                    if (entier % diviseur_million) {
                        out = nombreEnMots((entier / diviseur_mille) % diviseur_mille, entier % diviseur_mille, MILLE, out);
                        out = nombreEnMots(entier % diviseur_mille, entier % diviseur_mille, VALUE, out);
                    }
                }
            }

            if (entier && decimale) {
                out += "et ";

            }
            out = nombreEnMots(decimale, 1, CENTIME, out);

        }

        return out;
    }
}

int main(){
    cout << montantEnVaudois(1234.21);
    return EXIT_SUCCESS;
}
