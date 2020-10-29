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
// test
#include<iostream>

using namespace std;

string unite[]={"", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf",
                "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"};
string dizaine[]={"", "", "vingt", "trente", "quarante", "cinquante", "soixante",
                  "septante", "huitante", "nonante"};

static const string sep= "-";
const string BILLION="billion";
const string MILIARD="miliard";
const string MILLION="million";
const string MILLE="mille";
const string CENT="cent";
string str;

string nombreEnMots(int n,const string& s){
str = "";

if(n>99){
str += (n / 100 > 1 ? unite[n / 100] + sep : "") + CENT + (n / 100 > 1 ? "s" : "");
}
if(n>19){
str += sep + dizaine[(n % 100) / 10] + sep + unite[n % 10];
}else{
str += unite[n];
}

if(n){
str += (!s.empty() ? sep : "") + s + ((n > 1 && s != "mille" && !s.empty()) ? "s" : "") +
       (!s.empty() ? sep : "");
}

return str;
}

string montantEnVaudois(long double montant){

	string out;
	long unsigned entier=(int)((montant/100)*100);
	unsigned decimale=((int)montant*100)%100;

	out+=nombreEnMots((entier/1000000000000),BILLION);

	out+=nombreEnMots((entier/1000000000)%1000,MILIARD);

	out+=nombreEnMots((entier/1000000)%1000,MILLION);

	out+=nombreEnMots((entier/1000)%1000,MILLE);

	out+=nombreEnMots(entier%1000,"");


	return out;

}