/* test
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
#include <cmath>

using namespace std;

extern string montantEnVaudois(long double _montant);

int main() {
    long double nombre = 0.;
    cout << "Veuillez entrer un nombre."
         << endl;
    cin >> nombre;

    cout << montantEnVaudois(nombre) << endl;

    return 0;
}