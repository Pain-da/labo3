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
#include <iomanip>

using namespace std;

extern string montantEnVaudois(long double montant);

int main() {

	long double d;

	while (cin >> d) { // finir par EOF (Ctrl-D) ou autre chose qu'un nombre
			cout << fixed << (d ? setprecision(2) : setprecision(0)) << d << endl // arrondi different de celui de la
			// fonction demandee
			     << montantEnVaudois(d) << endl;

	}


	return 0;
}
