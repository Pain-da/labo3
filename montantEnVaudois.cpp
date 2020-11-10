/*
-----------------------------------------------------------------------------------
Nom du fichier : labo3.cpp
Auteur(s) : Dimitri De Bleser, Léo Meli, Stefano Pontarolo
Date creation : 27.10.2020
Description : Convertie un montant en toutes lettres.
Remarque(s) :
Compilateur : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/

#include <string>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

string montantEnVaudois(long double montant);
//converti un nombre en toutes lettres
string nombreEnVaudois(unsigned long long nombre);
unsigned long long grandeureEnVaudois(unsigned grandeur, string& sortie, bool pluriel = false, const string& SEPARATEUR = "-", const string& PLURIEL = "s");

string montantEnVaudois(long double montant){
    const string DEVISE = "franc",
            NOM_DECIMAUX = "centime",
            ET_EN_VAUDOIS = "et",
            DE_EN_VAUDOIS = "de",
            PLURIEL = "s",
            ESPACE = " ";
    //nombres de chiffres apres la virgule
    const unsigned PRECISION = 2;
    const auto CENTIME_EGALE_FRANC = (unsigned) pow(10, PRECISION);
    const long double MONTANT_MAX = 999999999999999.99;
    string montantEnVaudois;

    if(montant > MONTANT_MAX){
        montantEnVaudois = "erreur : montant trop grand";
    }else if(montant < 0){
        montantEnVaudois = "erreur : montant negatif";
    }else {
        auto centimes = (unsigned) round((montant - trunc(montant)) * pow(10, PRECISION));
        if (centimes >= CENTIME_EGALE_FRANC) {
            centimes = 0;
            ++montant;
        }
        //nombre de franc
        if (montant >= 1 || centimes == 0) {
            //ajout zero si zero francs, zero centimes, le nombre de francs sinon
            montantEnVaudois = montant < 1 ? "zero" : nombreEnVaudois((unsigned long long) montant);
            montantEnVaudois += ESPACE;
            //ajout du "de" si le nombre de comporte pas de chiffres a la fin
            montantEnVaudois += (unsigned long long) montant % 100000 == 0 && montant >= 1000000 ? DE_EN_VAUDOIS + ESPACE : "";
            montantEnVaudois += DEVISE;
            montantEnVaudois += montant >= 2 ? PLURIEL : "";
            montantEnVaudois += centimes > 0 ? ESPACE : "";
        }
        //nombre de centimes
        if (centimes > 0) {
            montantEnVaudois += montant >= 1 ? ET_EN_VAUDOIS + ESPACE: "";
            montantEnVaudois += nombreEnVaudois(centimes) + ESPACE + NOM_DECIMAUX;
            montantEnVaudois += centimes > 1 ? PLURIEL : "";
        }
    }
    return montantEnVaudois;
}

string nombreEnVaudois(unsigned long long nombre){
    const string DIZAINE_EN_VAUDOIS[] = {"dix", "vingt", "trente", "quarante", "cinquante", "soixante", "septante",
                                         "huitante", "nonante"};
    string casParticulier[] = {"onze", "douze", "treize", "quatorze", "quinze", "seize"};
    enum CasParticulierMinMax {MIN = 11, MAX = 16} casParticulierMin = MIN, casParticulierMax = MAX;

    const string CHIFFRES_EN_VAUDOIS[] = {"zero", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit",
                                          "neuf"};
    const string GRANDEURE_EN_VAUDOIS[] = {"mille", "million", "milliard", "billion"};
    const string ET_EN_VAUDOIS = "et",
            PLURIEL = "s",
            SEPARATEUR = "-",
            ESPACE = " ",
            CENT = "cent";

    //decomposition du nombre en centaines
    string sortie;
    unsigned grandeur = 0;
    while (nombre >= 1) {
        const unsigned CENTAINE = nombre % 1000;
        const unsigned VALEUR_CENTAINE = CENTAINE / 100;
        const unsigned DIZAINE = nombre % 100;
        const unsigned VALEURE_DIZAINE = DIZAINE / 10;
        const unsigned CHIFFRE = nombre % 10;
        string nombreEnVaudois;

        // [nombre] ajout de cent[s]
        nombreEnVaudois += VALEUR_CENTAINE > 1 ? CHIFFRES_EN_VAUDOIS[VALEUR_CENTAINE] + SEPARATEUR : "";
        nombreEnVaudois += VALEUR_CENTAINE > 0 ? CENT : "";
        nombreEnVaudois += VALEUR_CENTAINE > 1 && DIZAINE == 0 && grandeur != 1 ? PLURIEL : "";
        nombreEnVaudois += VALEUR_CENTAINE > 0 ? SEPARATEUR : "";

        // ajout dizaine avec verification de cas particulier
        if(DIZAINE >= casParticulierMin && DIZAINE <= casParticulierMax){
            nombreEnVaudois += casParticulier[DIZAINE - casParticulierMin] + SEPARATEUR;
        }else{
            nombreEnVaudois += VALEURE_DIZAINE > 0 ? DIZAINE_EN_VAUDOIS[VALEURE_DIZAINE - 1] + SEPARATEUR : "";
            //ajout du "et" pour les nombre tel que 21, ajout du chiffre avant les dizaine
            nombreEnVaudois += CHIFFRE == 1 && VALEURE_DIZAINE > 1 ? ET_EN_VAUDOIS + SEPARATEUR : "";
            nombreEnVaudois += CHIFFRE > 0 && (CENTAINE > 1 || grandeur != 1) ? CHIFFRES_EN_VAUDOIS[CHIFFRE] + SEPARATEUR : "";
        }
        //ajout de la grandeure
        if(CENTAINE > 0 && grandeur > 0) {
            nombreEnVaudois += GRANDEURE_EN_VAUDOIS[grandeur - 1] ;
            nombreEnVaudois += CENTAINE > 1 && grandeur != 1 ? PLURIEL : "";
            nombreEnVaudois += SEPARATEUR;
        }

        // ajout du nombre actuelle dans le nombre final
        sortie.insert(0, nombreEnVaudois);
        nombre /= 1000;
        ++grandeur;
    }
    //supression du premier SEPARATEUR en trop
    sortie = sortie.substr(0, sortie.size() - 1);
    return sortie;
}
