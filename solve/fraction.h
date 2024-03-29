// Added rat_0_1 to approximate decimal (between 0 and 1) to fraction
// to assist constructor Fraction::Fraction(double)
// enhanced in November 2018, merging with rational.h for sorting capabilities
// and then added instream >> capabilities

#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <string>

class Fraction
{
    private:
        int num, den;
        void normalize();
        int gcf(int a, int b);
        int lcm(int a, int b);

	public:
    int MAX_DENOMINATOR = 500;  // used in Fraction(double) constructor
    double tol = 0.001;        // used for comparing floating point numbers
    Fraction(double);           // Uses rat_0_1
		Fraction() {set(0, 1);}
		Fraction(int n, int d) {set(n, d);}
		Fraction(int n) {set(n, 1);}
		Fraction (const Fraction &src);
		Fraction (std::string);

		void set(int n, int d) {num = n; den = d; normalize();}

		int getNum() const {return num;}
		int getDen() const {return den;}
    double asDecimal() {
      return double((double)num/(double)den);
    }
    Fraction rat_0_1(double x, int N);
		Fraction add(const Fraction &other);
    Fraction sub(const Fraction &other);
		Fraction mult(const Fraction &other);
    Fraction div(const Fraction &other);
		Fraction operator+(const Fraction &other) {return add(other);}
    Fraction operator-(const Fraction &other) {return sub(other);}
		Fraction operator*(const Fraction &other) {return mult(other);}
    Fraction operator/(const Fraction &other) {return div(other);}

    Fraction& operator = (const Fraction& r);
    Fraction operator - ()const;//unary minus
    Fraction operator +=(const Fraction &r);
    Fraction	operator -=(const Fraction &r);
    Fraction operator /=(const Fraction &r);
    Fraction operator *=(const Fraction &r);
    int less (const Fraction & )const;
    int equal (const Fraction & )const;
    int lessEqual (const Fraction & )const;
    int greater (const Fraction & )const;
    int greaterEqual (const Fraction &)const;
    int notEqual (const Fraction & )const;
    std::istream& read(std::istream &is);

		//int operator==(const Fraction &other);
		friend std::ostream &operator<<(std::ostream &os, Fraction &fr);
    friend std::istream &operator >> (std::istream &is, Fraction&fr);
    	
};
int operator < (const Fraction & r, const Fraction & s);
int operator == (const Fraction & r, const Fraction & s);
int operator <= (const Fraction & r, const Fraction & s);
int operator > (const Fraction & r, const Fraction & s);
int operator >= (const Fraction & r, const Fraction & s);
int operator != (const Fraction & r, const Fraction & s);
#endif
