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
//ajoute les centaines en toutes lettres
unsigned centaineEnvaudois(unsigned nombre, string& sortie, unsigned grandeur = 0, const string& SERPARATEUR = "-", const string& PLURIEL = "s");
//ajoute les dizaines en toutes lettres
unsigned dizaineEnVaudois(unsigned nombre, string& sortie, const string& SEPARATEUR = "-", const string& ET = "et");
//ajoute les chiffres en toutes lettres
unsigned chiffreEnVaudois(unsigned nombre, string& sortie, bool afficheZero = true, const string& SEPARATEUR = "-");
//ajoute les grandeures en toutes lettres
unsigned long long grandeureEnVaudois(unsigned grandeur, string& sortie, bool pluriel = false, const string& SEPARATEUR = "-", const string& PLURIEL = "s");

int main(){
    cout << montantEnVaudois(1000000) << endl;

    return EXIT_SUCCESS;
}
string montantEnVaudois(long double montant){
    const string DEVISE = "franc",
        NOM_DECIMAUX = "centime",
        ET_EN_VAUDOIS = "et",
        DE_EN_VAUDOIS = "de",
        PLURIEL = "s",
        SEPARATEUR = "-",
        ESPACE = " ";
    //nombres de chiffres apres la virgule
    const unsigned PRECISION = 2,
        CENTIME_EGALE_FRANC = (unsigned) pow(10, PRECISION);
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
        //nombre de francs
        montantEnVaudois = nombreEnVaudois((unsigned long long) montant);
        //ajout franc
        if (montant >= 1 || centimes == 0) {
            //ajout zero si zero francs, zero centimes
            if (montant < 1) {
                chiffreEnVaudois(0, montantEnVaudois);
            }
            montantEnVaudois += ESPACE;
            if ((unsigned long long) montant % 100000 == 0 && montant >= 1000000) {
                montantEnVaudois += DE_EN_VAUDOIS + ESPACE;
            }
            montantEnVaudois += DEVISE;
            if (montant >= 2) {
                montantEnVaudois += PLURIEL;
            }
        }
        //nombre de centimes
        if (centimes > 0) {
            if (montant >= 1) {
                montantEnVaudois += ESPACE + ET_EN_VAUDOIS;
            }
            montantEnVaudois += ESPACE + nombreEnVaudois(centimes) + ESPACE + NOM_DECIMAUX;
            if (centimes > 1) {
                montantEnVaudois += PLURIEL;
            }
        }
    }
    return montantEnVaudois;
}

string nombreEnVaudois(unsigned long long nombre){
    string nombreEnVaudois;
    unsigned grandeur = 0;
    while (nombre >= 1) {
        unsigned centaine = nombre % 1000;
        //ajout de la grandeure
        if (centaine > 0) {
            grandeureEnVaudois(grandeur, nombreEnVaudois, centaine > 1);
        }
        //decomposition du nombre en centaines
        if (centaine > 1 || grandeur != 1){
            centaineEnvaudois(nombre, nombreEnVaudois, grandeur);
        }
        nombre /= 1000;
        ++grandeur;
    }
    //supression du premier SEPARATEUR en trop
    nombreEnVaudois = nombreEnVaudois.substr(0, nombreEnVaudois.size()-1);
    return nombreEnVaudois;
}

unsigned centaineEnvaudois(unsigned nombre, string& sortie,  unsigned grandeur, const string& SEPARATEUR, const string& PLURIEL){
    string cent = "cent";
    const unsigned  CENTAINE = nombre % 1000;
    const unsigned VALEUR_CENTAINE = CENTAINE / 100;
    //ajout des dizaines avant les centaines
    const unsigned DIZAINE = dizaineEnVaudois(nombre, sortie);
    //ajout de cent(s)
    if (VALEUR_CENTAINE > 0) {
        if(VALEUR_CENTAINE > 1 && DIZAINE == 0 && grandeur != 1){
            cent += PLURIEL;
        }
        sortie.insert(0, cent + SEPARATEUR);
    }
    //ajout du nombre de centaine si plus grand que 1 pour ne pas avoir "un-cent"
    if(VALEUR_CENTAINE > 1) {
        chiffreEnVaudois(VALEUR_CENTAINE, sortie);
    }
    return CENTAINE;
}

unsigned dizaineEnVaudois(unsigned nombre, string& sortie, const string& SEPARATEUR, const string& ET){
    const unsigned DIZAINE = nombre % 100;
    const unsigned VALEURE_DIZAINE = DIZAINE / 10;
    const string DIZAINE_EN_VAUDOIS[] = {"dix", "vingt", "trente", "quarante", "cinquante", "soixante", "septante",
                                         "huitante", "nonante"};

    //si cas particulier, traduction de la dizaine
    enum CasParticulierMinMax {MIN = 11, MAX = 16} casParticulierMin = MIN, casParticulierMax = MAX;
    string casParticulier[] = {"onze", "douze", "treize", "quatorze", "quinze", "seize"};

    if(DIZAINE >= casParticulierMin && DIZAINE <= casParticulierMax){
        //verifie si une valeur a ete ajoutee
        sortie.insert(0, casParticulier[DIZAINE - casParticulierMin] + SEPARATEUR);
    }//sinon decomposition du nombre
    else{
        //ajout du "et" pour les nombre tel que 21, ajout du chiffre avant les dizaine
        if(chiffreEnVaudois(nombre,sortie, false) == 1 && VALEURE_DIZAINE > 1){
            sortie.insert(0, ET + SEPARATEUR);
        }
        if(VALEURE_DIZAINE > 0) {
            sortie.insert(0, DIZAINE_EN_VAUDOIS[VALEURE_DIZAINE - 1] + SEPARATEUR);
        }
    }
    return DIZAINE;
}

unsigned chiffreEnVaudois(unsigned nombre, string& sortie, bool afficheZero, const string& SEPARATEUR) {
    const string CHIFFRES_EN_VAUDOIS[] = {"zero", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit",
                                          "neuf"};
    const unsigned CHIFFRE = nombre % 10;
    if (afficheZero || CHIFFRE != 0){
        sortie.insert(0, CHIFFRES_EN_VAUDOIS[CHIFFRE] + SEPARATEUR);
    }
    return CHIFFRE;
}

unsigned long long grandeureEnVaudois(unsigned grandeur, string& sortie, bool pluriel, const string& SEPARATEUR, const string& PLURIEL){
    const string GRANDEURE_EN_VAUDOIS[] = {"mille", "million", "milliard", "billion"};
    if(grandeur > 0 && grandeur <= 4) {
        string grandeurEnVaudois = GRANDEURE_EN_VAUDOIS[grandeur - 1];
        if(pluriel && grandeur > 1){
            grandeurEnVaudois += PLURIEL;
        }
        grandeurEnVaudois += SEPARATEUR;
        sortie.insert(0, grandeurEnVaudois);
    }
    return (unsigned long long) pow(10,grandeur * 3);
}
