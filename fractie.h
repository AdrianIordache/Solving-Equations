#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("fractie.in");
class fractie
{
 	private:
 		int numitor;
 		int numarator;

 	public:

 		inline int getNumarator() {return numarator;}
 		inline int getNumitor() {return numitor;}
 		inline void setNumarator(int x) {numarator = x;}
 		inline void setNumitor(int x) {numitor = x;}
 		inline void Amplifica(int x);
 		inline void Simplifica();
 		inline void citire();
 		inline void afiseaza();
 		inline void negatie();
 		inline void invers();

 		fractie(int x = 0, int y = 1);
 		fractie(const fractie&);
 		//~fractie();

 		fractie& operator= (const fractie&);
 		friend const fractie operator+ (const fractie&, const fractie&);
 		friend const fractie operator- (const fractie&, const fractie&);
 		friend const fractie operator* (const fractie&, const fractie&);
 		friend const fractie operator/ (const fractie&, const fractie&);
 		friend const fractie operator* (const fractie&, const int);

 		friend fractie& operator+= (fractie &, const fractie&);
		friend fractie& operator-= (fractie &, const fractie&);
		friend fractie& operator*= (fractie &, const fractie&);
		friend fractie& operator/= (fractie &, const fractie&);

		friend bool operator== (const fractie&, const fractie&);
		friend bool operator!= (const fractie&, const fractie&);

		friend bool operator<  (const fractie&, const fractie&);
		friend bool operator>  (const fractie&, const fractie&);
		friend bool operator>= (const fractie&, const fractie&);
		friend bool operator<= (const fractie&, const fractie&);

 		friend istream& operator>> (istream&, fractie&);
 		friend ostream& operator<< (ostream&, const fractie&);

 		fractie& operator++ ();
		fractie  operator++ (int fictiv);
		fractie& operator-- ();
		fractie  operator-- (int fictiv);

		operator double() const; 

};

fractie::fractie(int x, int y)
{
	numarator = x;
	numitor   = y;
}

fractie::fractie(const fractie &ob)
{
	numarator = ob.numarator;
	numitor   = ob.numitor;
}

/*fractie::~fractie()
{
	cout<<"Se apeleaza destructorul\n";
}*/

inline void fractie::Simplifica()
{
	int aux, x ,y;
	x = numarator;
	y = numitor;

	while(y) {aux = x % y; x = y; y = aux;}

	numarator/=x; numitor/=x;

	if(numitor < 0) {numarator = numarator * (-1); numitor = numitor * (-1);}
}

inline void fractie::negatie()
{
	numarator = numarator * (-1);
	numitor   = numitor;
}
inline void fractie::Amplifica(int x)
{
	numarator = numarator * x;
	numitor   = numitor * x;
}
inline void fractie::citire()
{
	fin >> numarator >> numitor;
}
inline void fractie::afiseaza()
{
	if(numitor != 1)
		cout<<numarator<<'/'<<numitor<<' ';
	else 
		cout<<numarator<<' ';
}
inline void fractie::invers()
{
	int aux;
	if(numarator > 0)
	{
		aux = numarator;
		numarator = numitor;
		numitor  = aux;
	}
	else 
	{
		numarator = (-1) * numarator;
		numitor   = (-1) * numitor;
		aux = numarator;
		numarator = numitor;
		numitor  = aux;
	}
}

fractie& fractie::operator= (const fractie& ob)
{
	if(this != &ob) {numarator = ob.numarator; numitor = ob.numitor;}
	return *this; 
} 

const fractie operator+ (const fractie& f1, const fractie& f2)
{
	fractie rez;
	rez.numarator = f1.numarator * f2.numitor + f1.numitor * f2.numarator;
	rez.numitor   = f1.numitor * f2.numitor;
	rez.Simplifica();
	return rez;
}

const fractie operator- (const fractie& f1, const fractie& f2)
{
	fractie rez;
	rez.numarator = f1.numarator * f2.numitor - f1.numitor * f2.numarator;
	rez.numitor   = f1.numitor * f2.numitor;
	rez.Simplifica();
	return rez;
}

const fractie operator* (const fractie& f1, const fractie& f2)
{
	fractie rez;
	rez.numarator = f1.numarator * f2.numarator;
	rez.numitor  = f1.numitor   * f2.numitor;
	rez.Simplifica();
	return rez;
}

const fractie operator/ (const fractie& f1, const fractie& f2)
{
	fractie rez;
	rez.numarator = f1.numarator * f2.numitor;
	rez.numitor  = f1.numitor   * f2.numarator;
	rez.Simplifica();
	return rez;
}

const fractie operator* (const fractie& f1, const int x)
{
	fractie rez;
	rez.numarator = f1.numarator * x;
	rez.numitor   = f1.numitor;
	rez.Simplifica();
	return rez;
}

istream & operator>> (std::istream & in, fractie & f)
{
	in >> f.numarator >> f.numitor;
	return in;
}

ostream & operator<< (std::ostream & out, const fractie & f)
{
	out << f.numarator << '/' << f.numitor;
	return out;
}
fractie& operator+= (fractie &f1, const fractie &f2)
{
	
	f1.numarator = f1.numarator * f2.numitor + f1.numitor * f2. numarator;
	f1.numitor   = f1.numitor * f2.numitor;
	f1.Simplifica();
	return f1;
}
fractie& operator-= (fractie& f1, const fractie& f2)
{
	f1.numarator = f1.numarator * f2.numitor - f1.numitor * f2. numarator;
	f1.numitor   = f1.numitor * f2.numitor;
	f1.Simplifica();
	return f1;
}
fractie& operator*= (fractie& f1, const fractie& f2)
{
	f1.numarator = f1.numarator * f2.numarator;
	f1.numitor   = f1.numitor * f2.numitor;
	f1.Simplifica();
	return f1;
}
fractie& operator/= (fractie& f1, const fractie& f2)
{
	f1.numarator = f1.numarator * f2.numitor;
	f1.numitor   = f1.numitor   * f2.numarator;
	f1.Simplifica();
	return f1;
}
bool operator== (const fractie & f1, const fractie & f2)
{
	return f1.numarator * f2.numitor - f1.numitor * f2.numarator == 0;
}
bool operator!= (const fractie & f1, const fractie & f2)
{
	return f1.numarator * f2.numitor - f1.numitor * f2.numarator;
}
bool operator< (const fractie & f1, const fractie & f2)
{
	return f1.numarator * f2.numitor < f1.numitor * f2.numarator;
}
bool operator> (const fractie & f1, const fractie & f2)
{
	return f2<f1;
}
bool operator<= (const fractie & f1, const fractie & f2)
{
	return !(f1>f2);
}
bool operator>= (const fractie & f1, const fractie & f2)
{
	return !(f1<f2);
}
fractie& fractie::operator++()
{
	numarator += numitor;
	return *this;
}
fractie& fractie::operator--()
{
	numarator -= numitor;
	return *this;
}
fractie fractie::operator++ (int fictiv)
{
	fractie temp(numarator, numitor);
	++(*this);
	return temp;
}
fractie fractie::operator-- (int fictiv)
{
	fractie temp(numarator, numitor);
	--(*this);
	return temp;
}
fractie::operator double() const
{
	return (double) numarator/numitor;
}




