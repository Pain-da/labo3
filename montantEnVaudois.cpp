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

const string LABELS_UNITES[21] = {
        "", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix",
        "onze", "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"
};
const string LABELS_DIZAINES[10] = {
        "", "", "vingt", "trente", "quarante", "cinquante",
        "soixante", "septante", "huitante", "nonante"
};

const string SEPARATEUR             = "-";
const string LABEL_BILLION          = "billion";
const string LABEL_MILIARD          = "miliard";
const string LABEL_MILLION          = "million";
const string LABEL_MILLIER          = "mille";
const string LABEL_CENTAINE         = "cent";

string dizaineEnMot(long long _nombre);

string nombreEnMot(long long _nombre);

string centaineEnMot(long long _nombre);

string montantEnVaudois(long double _montant);

string grandNombreEnMot(long long _nombre, int _exposant, string _label);

string montantEnVaudois(long double _montant) {
    auto nombre = (long long) _montant;
    auto centime = (long long)(round((_montant - nombre)*100));

    string montantEnMot{};

    if (_montant == 0){
        return "zero franc";
    }

    if(nombre){
        montantEnMot = nombreEnMot(nombre)  + " franc";
        if(nombre > 1){
            montantEnMot += "s";
        }
    }

    if(centime && nombre){
        montantEnMot += " et ";
    }

    if(centime){
        montantEnMot += nombreEnMot(centime) + " centime";
        if (centime > 1){
            montantEnMot += "s";
        }
    }
    return montantEnMot;

}

string centaineEnMot(long long _nombre){
    string montantEnMot{};
    long long nombreSignicatif = _nombre / 100;
    if (nombreSignicatif > 1) {
        montantEnMot = LABELS_UNITES[nombreSignicatif] + SEPARATEUR;
    }
    montantEnMot += LABEL_CENTAINE;
    long long dizaine = _nombre%100;
    if(dizaine){
        montantEnMot += SEPARATEUR + nombreEnMot(dizaine);
    }

    return montantEnMot;
}

string grandNombreEnMot(long long _nombre, int _exposant, string _label){

    auto nombreSignifiacatif = _nombre/(long long)pow(10,_exposant);
    string MontantEnMot{};

        if (nombreSignifiacatif == 1 && _label == LABEL_MILLIER){
            MontantEnMot = _label;
        }

    long long nombreDePoidsFaible = _nombre%(long long)pow(10,_exposant);
    if(nombreDePoidsFaible){
        MontantEnMot += nombreEnMot(nombreSignifiacatif) + SEPARATEUR + _label + SEPARATEUR + nombreEnMot(nombreDePoidsFaible);
    } else {
        MontantEnMot += nombreEnMot(nombreSignifiacatif) + " " + _label;
        if(nombreSignifiacatif > 1 && _label != LABEL_MILLIER){
            MontantEnMot += "s";
        }
        MontantEnMot +=  " de";
    }
    return MontantEnMot;
}

string dizaineEnMot (long long _nombre){
    string montantEnMot = LABELS_DIZAINES[_nombre / 10];
    long long unite = _nombre%10;
    if(unite){
        if(unite == 1){
            montantEnMot += "-et";
        }

        montantEnMot+= SEPARATEUR + LABELS_UNITES[unite];
    }

    return  montantEnMot;
}

string nombreEnMot(long long _nombre) {

    string montantEnMots{};

    if (_nombre < 20) {
        montantEnMots += LABELS_UNITES[_nombre];
    } else if (_nombre < 1e2) {
        montantEnMots += dizaineEnMot(_nombre);
    } else if (_nombre < 1e3) {
        montantEnMots += centaineEnMot(_nombre);
    } else if (_nombre < 1e6) {
        montantEnMots += grandNombreEnMot(_nombre, 3, LABEL_MILLIER);
    } else if (_nombre < 1e9) {
        montantEnMots += grandNombreEnMot(_nombre, 6, LABEL_MILLION);
    } else if (_nombre < 1e12) {
        montantEnMots += grandNombreEnMot(_nombre, 9, LABEL_MILIARD);
    } else if (_nombre < 1e15) {
        montantEnMots += grandNombreEnMot(_nombre, 12, LABEL_BILLION);
    }
    return montantEnMots;
}
