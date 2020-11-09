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

string nombreEnMots(long long n, long long reste, const string &s) {

	const string unite[] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix", "onze",
	                        "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};
	const string dizaine[] = {"", "", "vingt", "trente", "quarante", "cinquante", "soixante", "septante", "huitante",
	                          "nonante"};

	const string sep = "-",
		CENT = "cent",
		PLURIEL = "s";
	string str;

	if (n > 99) {
		str += (n / 100 > 1 ? unite[n / 100] + sep : "") + CENT + (s != "mille" && n / 100 > 1 && !(n % 100) ? PLURIEL :
		                                                           !(n % 100) ? "" : sep);
	}
	if (n % 100 > 19) {
		str += (dizaine[(n % 100) / 10].empty() ? "" : dizaine[(n % 100) / 10]) + (unite[n % 10].empty() ? "" : sep) +
		       (unite[n % 10] == "un" ? "et" + sep : "") + unite[n % 10];
	} else {
		str += (s == "mille" && unite[n % 100] == "un" ? "" : unite[n % 100]);
	}


	if (n || s == "franc") {
		if (str.empty()) {

		} else{
			str += (s != "franc" && s != "centime" && (unite[n % 10] != "un" || s != "billion") ? sep : " ");
		}

		if(n){
			str += s + ((n > 1 && s != "mille") ? PLURIEL : "") + ((s != "franc" && s != "centime" && reste) ? sep : " ");

			if (!reste) {
				str += (s == "mille" || s == "franc" || s == "centime" ? "" : "de francs");
			}
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
		montant = round(montant * 100) / 100;
		long long entier = montant;
		// conversion pour garder la partie décimale
		long long decimale = ((long long) (montant * 100)) % 100;


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


			out += nombreEnMots((entier / diviseur_billion), entier % diviseur_billion, BILLION);

			out += nombreEnMots((entier / diviseur_milliard) % diviseur_mille, entier % diviseur_milliard, MILLIARD);

			out += nombreEnMots((entier / diviseur_million) % diviseur_mille, entier % diviseur_million, MILLION);

			out += nombreEnMots((entier / diviseur_mille) % diviseur_mille, entier % diviseur_mille, MILLE);

			out += nombreEnMots(entier % diviseur_mille, entier % diviseur_mille, VALUE);

			if (entier && decimale) {
				out += "et ";
			}

			out += nombreEnMots(decimale, 1, CENTIME);

		}

		return out;
	}
}