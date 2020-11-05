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


string nombreEnMots(long long n, const string &s) {

	const string unite[] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix", "onze",
	                        "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};
	const string dizaine[] = {"", "", "vingt", "trente", "quarante", "cinquante", "soixante", "septante", "huitante",
	                          "nonante"};

	const string sep = "-",
		CENT = "cent";
	string str;

	if (n > 99) {
		str += (n / 100 > 1 ? unite[n / 100] + sep : "") + CENT + (s != "mille" && n / 100 > 1 && !(n % 100) ? "s" :
		                                                           !(n % 100) ? "" : sep);
	}
	if (n%100 > 19) {
		str += (dizaine[(n % 100) / 10].empty() ? "" : dizaine[(n % 100) / 10])+ (unite[n % 10].empty() ? "" : sep) +
			(unite[n % 10] ==  "un" ? "et" +	sep: "") + unite[n % 10];
	} else {
		str += unite[n%100];
	}

	if (n) {
		str += (s != "franc" && s != "centime" ? sep : " ") + s + ((n > 1 && !s.empty() && s != "mille") ? "s" : "")
		+((s != "franc" && s != "centime") ? sep : " ");
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






			out += nombreEnMots((entier / 1000000000000), BILLION);

			out += nombreEnMots((entier / 1000000000) % 1000, MILLIARD);

			out += nombreEnMots((entier / 1000000) % 1000, MILLION);

			out += nombreEnMots((entier / 1000) % 1000, MILLE);

			out += nombreEnMots(entier % 1000, VALUE);

			if (entier && decimale) {
				out += "et ";
			}

			out += nombreEnMots(decimale, CENTIME);

		}

		return out;
	}
}