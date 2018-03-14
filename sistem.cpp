#include <iostream>
#define N 2
#include "fractie.h"

using namespace std;

inline void afiseazaEcuatie(const fractie& f1, fractie& f2, const fractie& f3)
{
	cout<<f1<<'X';
	if(f2.getNumarator() >= 0) cout<<'+';
	cout<<f2<<'Y'<<'='<<f3<<'\n';
}
inline void afiseazaEcuatie(fractie& f1, const fractie& f2)
{
	if(f1.getNumarator() >= 0) cout<<'+';
	cout<<f1<<'Y'<<'='<<f2<<'\n';
}
inline void afiseazaRezultat(fractie& f1, fractie& f2)
{
	if(f1.getNumarator() >= 0) cout<<"Y="<<f1;
		else cout<<"Y="<<'('<<f1<<')';
	if(f2.getNumarator() >= 0) cout<<'*'<<f2<<'\n';
		else cout<<'*'<<'('<<f2<<')'<<'\n';
}
inline void afiseazaRezultat(fractie& f1, fractie& f2, fractie& f3)
{
	if(f1.getNumarator() >= 0) cout<<"X="<<'('<<f1;
		else cout<<"x="<<'('<<'('<<f1<<')';
	if(f2.getNumarator() >= 0) cout<<'+'<<f2<<')';
		else cout<<f2<<')';
	if(f3.getNumarator() >= 0) cout<<'*'<<f3<<'\n';
		else cout<<'*'<<'('<<f3<<')'<<'\n';
}
inline void afiseazaEcuatiePartiala(const fractie& f1, fractie& f2, const fractie& f3)
{
	cout<<f1<<'X';
	if(f2.getNumarator() >= 0) cout<<'+';
	cout<<f2<<'='<<f3<<'\n';
}
inline void swapFractie(fractie& f1, fractie& f2)
{
	fractie auxiliar;
	auxiliar = f1; f1 = f2; f2 = auxiliar;
}
int main()
{
	int x, y;
	fractie *coeficienti = new fractie[N * 3];
	for(int i = 0; i < N * 3; ++i)
	{
		fin >> x >> y;
		coeficienti[i].setNumarator(x);
		coeficienti[i].setNumitor(y);
	}

	cout<<"Afiseaza ecuatiile sistemului\n";
	for(int i = 0; i < N * 3; i += 3)
			afiseazaEcuatie(coeficienti[i], coeficienti[i + 1],coeficienti[i + 2]);

	for(int i = 0; i < N * 3; ++i)
		if(coeficienti[i].getNumarator() == 0 || coeficienti[i].getNumitor() == 0)
			{cout<<"Date invalide! Sistemul utilizeaza coeficinti diferiti de 0!\n"; return 0;}


	//Generare Matrice Coeficienti
	fractie **matrice = new fractie* [N];
	for(int i = 0; i < N; ++i)
		matrice[i] = new fractie [N + 1];

	int k = 0;
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N + 1; ++j)
			{
				matrice[i][j] = coeficienti[k]; 
				++k;
			}

	bool ok = false;
	for(int j = 0; j < N + 1; ++j)
		if(matrice[0][j] != matrice[1][j]) ok = true;

	if(ok == false) {cout<<"Sistemul este incompatibil\n"; return 0; }

	cout<<"Afiseaza matricea coeficientilor:\n";
	for(int i = 0; i < N; ++i)
	{	
		for(int j = 0; j < N + 1; ++j)
			matrice[i][j].afiseaza();
		cout<<'\n';
	}


	//Se memoreaza prima ecuatie pentru inlocuirea necunoscutei y
	fractie *ecuatie = new fractie[N + 1];
	for(int i = 0; i < N + 1; ++i)
		ecuatie[i] = matrice[0][i];

	//Se utilizeaza un vector auxiliar pentru memorarea variabilelor cu care vor fi inmultite ecuatile
	fractie *aux = new fractie [N];
	for(int i = 0 ; i < N; ++i)
		if(i % 2 == 0 ) 
			{ 
				matrice[i][0].negatie(); 
				aux[i] = matrice[i][0]; 
				matrice[i][0].negatie();
			}
		else 
				aux[i] = matrice[i][0];


	swapFractie(aux[0], aux[1]);
	cout<<"Afisare vector auxiliar cu care se vor inmulti ecuatiile\n";
	for(int i = 0; i < N; ++i)
		cout<<aux[i]<<' ';
	cout<<'\n';

	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N + 1; ++j)
			matrice[i][j] *= aux[i];				

	cout<<"Afiseaza matricea coeficientilor dupa inmultire:\n";
	for(int i = 0; i < N; ++i)
	{	
		for(int j = 0; j < N + 1; ++j)
			matrice[i][j].afiseaza();
		cout<<'\n';
	}

	cout<<"Afiseaza noul sistem de ecuatii\n";
	for(int i = 0; i < N; ++i)
		afiseazaEcuatie(matrice[i][0], matrice[i][1], matrice[i][2]);


	//Se realizeaza adunarea celor doua ecuatii
	aux[0] = matrice[0][1] + matrice[1][1];
	aux[1] = matrice[0][2] + matrice[1][2];


	cout<<"Afiseaza vectorul rezultat din adunarea celor doua ecuatii\n";
	for(int i = 0; i < N; ++i)
		cout<<aux[i]<<' ';
	cout<<'\n';

	cout<<"Ecuatia obtinuta dupa adunarea \n";
	afiseazaEcuatie(aux[0], aux[1]);

	cout<<"Inmultim cu inversul lui "<<aux[0]<<'\n';
	aux[0].invers();
	cout<<"Acesta fiind: "<<aux[0]<<'\n';
	cout<<"Sistemul devine: \n";
	afiseazaRezultat(aux[1], aux[0]);

	cout<<"Primul rezultat final este Y = ";
	fractie rezultat = aux[1] * aux[0];
	cout<<rezultat<<' '<<'\n';

	cout<<"Revenim la prima ecuatie initiala:\n";
	afiseazaEcuatie(ecuatie[0], ecuatie[1], ecuatie[2]);

	cout<<"Inlocuim pe Y in ecuatie\n";
	fractie rezultatAuxiliar = ecuatie[1] * rezultat;
	afiseazaEcuatiePartiala(ecuatie[0], rezultatAuxiliar, ecuatie[2]);
	rezultatAuxiliar.negatie();
	ecuatie[0].invers();
	cout<<"Scoatem pe X \n";
	afiseazaRezultat(ecuatie[2], rezultatAuxiliar, ecuatie[0]);
	
	rezultatAuxiliar = ecuatie[2] + rezultatAuxiliar;
	rezultatAuxiliar = ecuatie[0] * rezultatAuxiliar;
	cout<<"Al doilea rezultat final este X = "<<rezultatAuxiliar<<'\n';

	delete[] aux;
	delete[] matrice[N];
	delete[] ecuatie;

	fin.close();

}  