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

// prototypes des deux fonctions
string montantEnVaudois(long double montant);

string nombreEnMots(unsigned long long nombre, unsigned long long reste, const string &grandeurActuelle, string str);

// fonction qui prend deux nombres, une chaîne de caracteres constante et une chaine de caracteres et qui renvoie une
// chaine de caracteres
string nombreEnMots(unsigned long long nombre, unsigned long long reste, const string &grandeurActuelle, string str) {

	const string unite[] = {"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix", "onze",
	                        "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};
	const string dizaine[] = {"", "", "vingt", "trente", "quarante", "cinquante", "soixante", "septante", "huitante",
	                          "nonante"};
	const string grandeur[] = {"mille", "million", "milliard", "billion"};
	enum Grandeur {
		MILLE, MILLION, MILLIARD, BILLION
	}
		mille = MILLE, million = MILLION, milliard = MILLIARD, billion = BILLION;

	const string sep = "-",
		CENT = "cent",
		PLURIEL = "s",
		DE = "de",
		ET = "et",
		ESPACE = " ",
		DEVISE = "franc";

	// si le nombre est superieur a 99, il doit verifier s'il est supérieur a 199 afin de saisir correctement la valeur
	// des centaines
	if (nombre > 99) {
		str += (nombre > 199 ? unite[nombre / 100] + sep : "") + CENT;
		str += (grandeurActuelle != grandeur[mille] && nombre > 199 && !(nombre % 100) ? PLURIEL : !(nombre % 100) ? ""
		                                                                                                           : sep);
	}
	// si le reste de la division avec 100 est superieur a 19, le nombre doit etre divise en dizaines et en unites.
	if (nombre % 100 > 19) {
		str += (dizaine[(nombre % 100) / 10].empty() ? "" : dizaine[(nombre % 100) / 10]) +
		       (unite[nombre % 10].empty() ? "" : sep) +
		       (unite[nombre % 10] == unite[1] ? ET + sep : "") + unite[nombre % 10];
	} else { // Sinon le nombre se situe entre 1 et 19.
		str += (grandeurActuelle == grandeur[mille] && unite[nombre % 100] == unite[1] ? "" : unite[nombre % 100]);
	}
	// Si le nombre est different de 0 ou si la grandeur est franc
	if (nombre || grandeurActuelle == DEVISE) {
		// Si la grandeur est egale a billion ou milliard ou million
		if (grandeurActuelle == grandeur[billion] || grandeurActuelle == grandeur[milliard] || grandeurActuelle ==
		                                                                                       grandeur[million]) {
			str += (unite[nombre % 10] == unite[1] ? ESPACE : sep) + grandeurActuelle + (nombre > 1 ? PLURIEL : "") +
			       (reste ? sep : ESPACE + DE + ESPACE + DEVISE + PLURIEL);
			// Sinon si la grandeur est egale a mille
		} else if (grandeurActuelle == grandeur[mille]) {
			str += (unite[nombre % 10] == unite[1] ? "" : sep) + grandeurActuelle + (reste ? sep : "");
			// Sinon, si la grandeur est franc et que la chaine ne est pas vide
		} else if (grandeurActuelle == DEVISE && !str.empty()) {
			str += ESPACE + (nombre == 1 ? grandeurActuelle + ESPACE : grandeurActuelle + PLURIEL + ESPACE);
		} else { // Sinon, nous sommes dans le cas ou la grandeur est centime.
			str += ESPACE + (nombre == 1 ? grandeurActuelle + ESPACE : grandeurActuelle + PLURIEL);
		}
	}

	return str;
}

// Fonction principale qui prend un nombre entre 0 et 999999999999999.99 et le transforme en mots
string montantEnVaudois(long double montant) {

	const long double max = 999999999999999.99;

	// Si le nombre est negatif, une erreur est renvoyee
	if (montant < 0) {
		return "erreur : montant negatif";
	} else if (montant > max) { // Si le nombre est superieur au maximum, une erreur est renvoyee
		return "erreur : montant trop grand";
	} else { // Sinon il peut demarrer la conversion

		string out;
		// Arrondi a deux chiffres apres la virgule
		montant = round(montant * 100) / 100;
		// Conversion pour enlever la partie décimale
		auto entier = (unsigned long long) montant;
		// Conversion pour garder la partie décimale
		auto decimale = ((unsigned long long) (montant * 100)) % 100;

		// Si la partie entiere et la partie decimale sont 0, alors le nombre est 0 et il sorte de la fonction
		if (!entier && !decimale) {
			return "zero franc";
		} else { // Sinon il peut faire la conversion

			const string BILLION = "billion",
				MILLIARD = "milliard",
				MILLION = "million",
				MILLE = "mille",
				CENTIME = "centime",
				DEVISE = "franc";
			const long long diviseur_billion = 1000000000000,
				diviseur_milliard = 1000000000,
				diviseur_million = 1000000,
				diviseur_mille = 1000;

			// Commence la decomposition du nombre en partant de la plus grande partie jusqua aux unites
			out = nombreEnMots((entier / diviseur_billion), entier % diviseur_billion, BILLION, out);
			// Si le reste entre la partie entiere et un billion est different de 0, il est necessaire de poursuivre la decomposition du nombre
			if (entier % diviseur_billion) {
				out = nombreEnMots((entier / diviseur_milliard) % diviseur_mille, entier % diviseur_milliard, MILLIARD,
				                   out);
				// Si le reste entre la partie entiere et un milliard est different de 0, il est necessaire de poursuivre la decomposition du nombre
				if (entier % diviseur_milliard) {
					out = nombreEnMots((entier / diviseur_million) % diviseur_mille, entier % diviseur_million, MILLION,
					                   out);
					// Si le reste entre la partie entiere et un million est different de 0, il est necessaire de poursuivre la decomposition du nombre
					if (entier % diviseur_million) {
						out = nombreEnMots((entier / diviseur_mille) % diviseur_mille, entier % diviseur_mille, MILLE, out);
						out = nombreEnMots(entier % diviseur_mille, entier % diviseur_mille, DEVISE, out);
					}
				}
			}
			// Si la partie entier et la partie decimale sont differents de 0
			if (entier && decimale) {
				out += "et ";

			}
			// Si la partie decimale est different de 0
			if (decimale) {
				out = nombreEnMots(decimale, 0, CENTIME, out);
			}

		}

		return out;
	}
}