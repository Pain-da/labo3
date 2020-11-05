/*
-----------------------------------------------------------------------------------
Nom du fichier : labo3.cpp
Auteur(s) : Dimitri De Bleser, Léo Meli, Stefano Pontarolo
Date creation : 27.10.2020
Description : Convertie un nombre en toutes lettres.
Remarque(s) :
Compilateur : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <string>
#include <iostream>
#include <cmath>

using namespace std;

string montantEnVaudois(long double montant);
string obtientDecimal(unsigned chiffre, unsigned long long montantActuel, const string& SEPARATEUR);
string obtientDizaine(unsigned chiffre);
string obtientCasParticulier(unsigned chiffre);
string obtientGrandeure(int puissanceDix, unsigned chiffre, unsigned long long montant, const string& SEPARATEUR);


string montantEnVaudois(long double montant) {
    const unsigned CENTIMES = 100;
    const string SEPARATEUR = "-";
    const string ESPACE = " ";

    auto montantEnCentimes = (unsigned long long) round(montant * CENTIMES);
    int puissanceDix = -2;
    string montantEnVaudois;

    do {
        unsigned chiffreActuel = montantEnCentimes % 10;
        montantEnVaudois.insert(0, obtientGrandeure(puissanceDix, chiffreActuel, montantEnCentimes, SEPARATEUR));

        bool pasUnCent = puissanceDix == 0 || (puissanceDix + 1 ) % 3 != 0;
        bool pasUnMille = puissanceDix != 3 || montantEnCentimes % 100 > 9;
        bool afficheQuelquechose;

        if ((afficheQuelquechose = ((abs(puissanceDix) - 1) % 3 == 0))) {
            montantEnVaudois.insert(0, obtientDizaine(chiffreActuel));
        } else if ((afficheQuelquechose = (chiffreActuel > 1 || (chiffreActuel > 0 && pasUnCent && pasUnMille)))) {

            bool pasUnCasParticulier = montantEnCentimes % 100 <= 10 || montantEnCentimes % 100 >= 17 || puissanceDix % 3 != 0;

            if (pasUnCasParticulier) {
                montantEnVaudois.insert(0, obtientDecimal(chiffreActuel, montantEnCentimes, SEPARATEUR));
            } else {
                montantEnVaudois.insert(0, obtientCasParticulier(montantEnCentimes % 100));
                montantEnCentimes /= 10;
                ++puissanceDix;
            }
        }

        montantEnCentimes /= 10;
        ++puissanceDix;

        if(afficheQuelquechose && chiffreActuel > 0 && montantEnCentimes >= 1 && puissanceDix != 0){
            montantEnVaudois.insert(0, SEPARATEUR);
        }

        if (puissanceDix == 0 && montantEnCentimes > 0) {

            string franc = ESPACE + "franc";
            if(montant >= 1000000){
                franc.insert(0, ESPACE + "de");
            }
            if(montant > 1){
                franc.insert(franc.length(), "s");
            }
            if((long long unsigned) round(montant * 100) % 100 > 0){
                franc.insert(franc.length(), ESPACE + "et" + ESPACE);
            }
            montantEnVaudois.insert(0, franc);
        }
    } while (montantEnCentimes >= 1);

    return montantEnVaudois;
}

string obtientDecimal(unsigned chiffre, unsigned long long montantActuel, const string& SEPARATEUR) {
    string et;
    if(chiffre == 1 && montantActuel % 100 >= 20){
        et = "et" + SEPARATEUR;
    }

    string conversion[] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix"};
    return et + conversion[chiffre];
}

string obtientDizaine(unsigned chiffre) {
    string conversion[] = {"", "dix", "vingt", "trante", "quarante", "cinquante", "soixante", "septante",
                           "huitante","nonante"};
    return conversion[chiffre];
}

string obtientCasParticulier(unsigned chiffre) {
    string casParticulierDisaine[] = {"onze", "douze", "treize", "quatorze", "quinze", "seize"};
    return casParticulierDisaine[chiffre - 11];
}

string obtientGrandeure(int puissanceDix, unsigned chiffre, unsigned long long montantActuel, const string& SEPARATEUR) {

    enum Grandeures {CENTIMES = -2, CENT = 2, MILLE = 3, MILLION = 6, MILLIARD = 9, BILLION = 12, BILLIARD = 15};

    string grandeure;
    if(puissanceDix == Grandeures::CENTIMES && montantActuel % 100 > 0){
        grandeure = "centime";
        if(montantActuel % 100 > 1){
            grandeure += "s";
        }
    }

    if (puissanceDix > 0 && montantActuel % 1000 > 0) {

        if(puissanceDix > 0 && (puissanceDix + 1) % 3 == 0 && chiffre > 0){
            grandeure += "cent";
        }

        switch(puissanceDix){
            case Grandeures::MILLE :
                grandeure += "mille";
                break;
            case Grandeures::MILLION :
                grandeure += "million";
                break;
            case Grandeures::MILLIARD :
                grandeure += "milliard";
                break;
            case Grandeures::BILLION :
                grandeure += "million";
                break;
            case Grandeures::BILLIARD :
                grandeure += "billiard";
                break;
        }
    }

    if(grandeure.length() > 0) {
        if(montantActuel > 1 || (montantActuel > 0 && (puissanceDix + 1) % 3 != 0 && puissanceDix != Grandeures::MILLE)){
            grandeure.insert(0, SEPARATEUR);
        }
        if (puissanceDix >= Grandeures::MILLION && montantActuel % 1000 > 1) {
            grandeure += "s";
        }
    }

    return grandeure;
}


