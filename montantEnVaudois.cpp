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
unsigned centaineEnvaudois(unsigned nombre, vector<string>& sortie, unsigned grandeur = 0);
//ajoute les dizaines en toutes lettres
unsigned dizaineEnVaudois(unsigned nombre, vector<string>& sortie);
//ajoute les chiffres en toutes lettres
unsigned chiffreEnVaudois(unsigned nombre, vector<string>& sortie, bool afficheZero = true);
//ajoute les grandeures en toutes lettres
unsigned long long grandeureEnVaudois(unsigned grandeur, vector<string>& sortie, bool pluriel = false);

string montantEnVaudois(long double montant){
    const string DEVISE = "franc";
    const string NOM_DECIMAUX = "centime";
    const string ET_EN_VAUDOIS = "et";
    const string DE_EN_VAUDOIS = "de";
    const string PLURIEL = "s";
    const string SEPARATEUR = "-";
    const string ESPACE = " ";
    const unsigned PRECISION = 2; //nombres de chiffres apres la virgule
    string montantEnVaudois;
    vector<string> sortie;

    if(montant > 999999999999999.99){
        montantEnVaudois = "erreur : montant trop grand";
    }else if(montant < 0){
        montantEnVaudois = "erreur : montant negatif";
    }else {
        auto centimes = (unsigned) round((montant - trunc(montant)) * pow(10, PRECISION));//todo verification d'arondi
        if (centimes >= 100) {
            centimes = 0;
            ++montant;
        }
        //nombre de francs
        montantEnVaudois = nombreEnVaudois((unsigned long long) montant); //todo verification d'arondi
        //ajout franc
        if (montant >= 1 || centimes == 0) {
            //ajout zero si zero francs, zero centimes
            if (montant < 1) {
                chiffreEnVaudois(0, sortie), montantEnVaudois += sortie.back();
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
    const string SEPARATEUR = "-";
    string nombreEnVaudois;
    vector<string> sortie;
    unsigned grandeur = 0;
    while (nombre >= 1) {
        unsigned centaine = nombre % 1000;
        //ajout de la grandeure
        if (centaine > 0) {
            grandeureEnVaudois(grandeur, sortie, centaine > 1);
        }
        //decomposition du nombre en centaines
        if (centaine > 1 || grandeur != 1){
            centaineEnvaudois(centaine, sortie, grandeur);
        }
        nombre /= 1000;
        ++grandeur;
    }
    //ajout des sorties dans le string
    for(auto i = sortie.begin(); i != sortie.end(); ++i) {
        nombreEnVaudois += *i;
        if(i != sortie.end() - 1){
            nombreEnVaudois += SEPARATEUR;
        }
    }
    return nombreEnVaudois;
}

unsigned centaineEnvaudois(unsigned nombre, vector<string>& sortie,  unsigned grandeur){
    string cent = "cent";
    const string CENT_PLURIEL = "s";
    const unsigned  CENTAINE = nombre % 1000;
    const unsigned VALEUR_CENTAINE = CENTAINE / 100;
    //ajout des dizaines avant les centaines
    const unsigned DIZAINE = dizaineEnVaudois(nombre, sortie);
    //ajout de cent(s)
    if (VALEUR_CENTAINE > 0) {
        if(VALEUR_CENTAINE > 1 && DIZAINE == 0 && grandeur != 1){
            cent += CENT_PLURIEL;
        }
        sortie.insert(sortie.begin(), cent);
    }
    //ajout du nombre de centaine si plus grand que 1 pour ne pas avoir "un-cent"
    if(VALEUR_CENTAINE > 1) {
        chiffreEnVaudois(VALEUR_CENTAINE, sortie);
    }
    return VALEUR_CENTAINE;
}

unsigned dizaineEnVaudois(unsigned nombre, vector<string>& sortie){
    //decomposition du nombre en dizaine
    const unsigned DIZAINE = nombre % 100;
    const unsigned VALEURE_DIZAINE = DIZAINE / 10;
    const string DIZAINE_ET = "et";
    const string DIZAINE_EN_VAUDOIS[] = {"dix", "vingt", "trente", "quarante", "cinquante", "soixante", "septante",
                                         "huitante", "nonante"};

    //si cas particulier, traduction de la dizaine
    enum CasParticulierMinMax {MIN = 11, MAX = 16} casParticulierMin = MIN, casParticulierMax = MAX;
    string casParticulier[] = {"onze", "douze", "treize", "quatorze", "quinze", "seize"};

    if(DIZAINE >= casParticulierMin && DIZAINE <= casParticulierMax){
        //verifie si une valeur a ete ajoutee
        sortie.insert(sortie.begin(), casParticulier[DIZAINE - casParticulierMin]);
    }//sinon decomposition du nombre
    else{
        //ajout du "et" pour les nombre tel que 21, ajout du chiffre avant les dizaine
        if(chiffreEnVaudois(nombre,sortie, false) == 1 && VALEURE_DIZAINE > 1){
            sortie.insert(sortie.begin(), DIZAINE_ET);
        }
        if(VALEURE_DIZAINE > 0) {
            sortie.insert(sortie.begin(), DIZAINE_EN_VAUDOIS[VALEURE_DIZAINE - 1]);
        }
    }
    return DIZAINE;
}

unsigned chiffreEnVaudois(unsigned nombre, vector<string>& sortie, bool afficheZero) {
    const string CHIFFRES_EN_VAUDOIS[] = {"zero", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit",
                                          "neuf"};
    //decomposition du nombre en chiffre
    const unsigned CHIFFRE = nombre % 10;
    if (afficheZero || CHIFFRE != 0){
        sortie.insert(sortie.begin(), CHIFFRES_EN_VAUDOIS[CHIFFRE]);
    }
    return CHIFFRE;
}

unsigned long long grandeureEnVaudois(unsigned grandeur, vector<string>& sortie, bool pluriel){
    const string GRANDEURE_EN_VAUDOIS[] = {"mille", "million", "milliard", "billion", "billiard"};
    const string PLURIEL_GRANDEUR = "s";
    if(grandeur > 0 && grandeur <= 5) {
        string grandeurEnVaudois = GRANDEURE_EN_VAUDOIS[grandeur - 1];
        if(pluriel && grandeur > 1){
            grandeurEnVaudois += PLURIEL_GRANDEUR;
        }
        sortie.insert(sortie.begin(), grandeurEnVaudois);
        return (unsigned long long) pow(10,grandeur * 3);
    }
    return 0;
}
