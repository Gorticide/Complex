/*
 g++ -g solve_complex_RR.cpp fraction.cpp -std=c++11 -o solve_complex_RR
 Michael William Hentrich
 4 November 2018

          D I V I D E   A N D   C O N Q U O R
Split into two different programs, one for actual <complex> from STl where a, b, c, d are Reals
another for experimental complex where a, b, c, d are Integers and solution in Fractions

 Example of what this program solves:
 Find all pairs of complex numbers x and y for which 3x + 5y i = 6 + 30 i
 Since x and y are complex numbers, we can write x = a + bi when a, b in Real,
 and y = c + di when c, d in Real.

 Substituting in 3x + 5y i = 6 + 30i, we obtain
   3(a + bi) + 5(c + di)i = 6 + 30i
   3a + 3bi + 5ci + 5d i^2 = 6 + 30i
   (3a - 5d) + (3b + 5c)i = 6 + 30i

   3a - 5d = 6 and 3b + 5c = 30

   d = (3a-6)/5 and c = (30 - 3b)/5

   Therefore, {(x,y) | x = a + bi and y = (30 - 3b)/5 + [(3a-6)/5]i; a, b in Real}
   is the solution set of the equation  3x + 5y i = 6 + 30i and x,y in Complex

At this point we are free to assign any real values to a and b.
I may make two versions, one using Rationals (Fraction), the other using reals.
We may even wish to experiment with <complex>.  Explore and tinker!
*/


#include <iostream>
#include <cmath>
#include <utility>  // for std::pair
#include <complex>
#include <string>
#include <sstream>   // for std::string to_string_with_precision  (also need <iomanip>)
#include <iomanip>

using std::cout;
using std::cin;
using std::pair;
using std::string;
using std::complex;

typedef pair< complex<double>, complex<double> > RR;

// For dealing with cin
template<class T>
std::istream& operator>> (std::istream& is, complex<T>& z) {
  T value;
  is >> value;
  z.real(value);
  is >> value;
  z.imag(value);
  return is;
}

// For setting precision in std::to_string(number), where number is type double
// needs <sstream> and <iomanip>
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 4)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

RR getEquation();
complex<double> getComplex();
RR solveReals(double a, double b, RR eqn);
   // returns RR sol where sol.first is x and sol.second is y

char show_ystr(RR eqn);
bool show_work(RR eqn, string eqn_str);
complex<double> x_solutions_only(RR eqn);
complex<double> y_solutions_only(RR eqn);
void show_x(double a, double c, double d, string eqn_str);
void show_y(double b, double c, double d, string eqn_str);
std::string xyi(complex<double> z);

string equation = "";

int main()  {

 RR eqn = getEquation();   // eqn.first is LHS, eqn.second is RHS
 string y_str = "";

 cout << "\nFind all pairs of complex numbers x and y for which " << equation
      << "\nSince x and y are complex numbers, we can write x = a + bi when a, b in Real,\n"
      << "and y = c + di when c, d in Real.\n\n";

if (show_work(eqn, equation))   {  // return bool, then true: solutions for both x and y exist
                                  // if false: then show_work calls x or y solutions_only(eqn)

   cout << "\nAt this point we are free to assign any real values to a and b.\n\n";
   char substitute = 'y';
   while (  (substitute == 'y') || (substitute == 'Y')  )   {
       double a, b;
       cout << "Let real a = ";
       cin >> a;
       cout << "\nLet real b = ";
       cin >> b;
       RR R = solveReals(a, b, eqn);
       cout << "\nx = " << xyi(R.first) << " and y = " << xyi(R.second) << "\n\n";
       cout << "Do you want to find another pair? <y/n> : ";
       cin >> substitute;
   }
 }

}

RR getEquation()   {
    char sign;
    std::string val;
    double tol = 0.00001;

    cout << "\nEnter equation of complex numbers where: ax + by i = c + d i\n\n";
	  cout << "\nand a, b, c, and d are Real\n ";
    cout << "\n\nEnter BOTH components of left member (a and b of ax + by i).\n";
    complex<double> x = getComplex();

    val = to_string_with_precision(x.real());
    if (!(std::fabs(x.real()) - 1.0 < tol)) equation.append(val);
    //if (std::fabs(x.real() - 0.0) > tol)
    equation += 'x';

    if (x.imag() < 0) {
      sign = '-';
      val = to_string_with_precision(-x.imag());
    }
    else  {
      sign = '+';
      val = to_string_with_precision(x.imag());
    }
    equation += ' ';
    //if (std::fabs(x.imag() - 0.0) > tol)
    equation += sign;
    equation += ' ';
    if (!(std::fabs(x.imag()) - 1.0 < tol)) equation.append(val);
    //if (std::fabs(x.imag() - 0.0) > tol)
    equation += 'y';
    //if (std::fabs(x.imag() - 0.0) > tol)
    equation.append(" i == ");
    //else equation.append(" == ");

    cout << "\n\nEnter BOTH components of right member (c and d of c + di).\n";
    complex<double> y = getComplex();

    val = to_string_with_precision(y.real());
    equation.append(val);

    if (y.imag() < 0) {
      sign = '-';
      val = to_string_with_precision(-y.imag());
    }
    else  {
      sign = '+';
      val = to_string_with_precision(y.imag());
    }
    equation += ' ';
    //if (std::fabs(y.imag() - 0.0) > tol)
    equation += sign;

    if (std::fabs(y.imag()) - 1.0 > tol)   {
      equation += ' ';
      equation.append(val);
    }

    //if (std::fabs(y.imag() - 0.0) > tol)
    equation.append(" i");

    RR eqn(x, y);
    return eqn;
}

complex<double> getComplex()  {
	complex<double> C;
	cout << "\n\nEnter BOTH components as REAL (decimal) numbers <real part> <imaginary part>: ";
    cin >> C;
	return C;
}

RR solveReals(double a, double b, RR eqn)  {
   complex<double> x, y;

   x.real(a);
   x.imag(b);
   y.real((eqn.second.imag() - eqn.first.real()*b)/eqn.first.imag());
   y.imag((eqn.first.real()*a - eqn.second.real())/eqn.first.imag());

   RR solution(x,y);
   return solution;

}

char show_ystr(RR eqn)   {
   complex<double> LHS = eqn.first;
   complex<double> RHS = eqn.second;
   double re1 = LHS.real();
   double im1 = LHS.imag();
   double re2 = RHS.real();
   double im2 = RHS.imag();

   char info;

// We will screen the data here and send back a char which will be used in a switch
// 's': solutions for both x and y exist, so a and b can have any real values
//      In this case, show_ystr() displays work, then show_work() returns TRUE
//      and main() will call solveRationals()
//
// 'x': y is not considered, so show_ystr calls show_x()
//      which will call x_solution_only()
//
// 'y': x is not considered, so show_ystr calls show_y()
//     which will call y_solutions_only()
//
// 'z': For all values x, y in Complex, 0x + 0y i = 0 + 0 i = 0
//      In this case, display 'If a + bi = 0, then a = 0 and b = 0'
//
// 'e' : Therefore, no solutions are ever possible.

if ( (re1 != 0) && (im1 != 0) )   {
     cout << re1 << "(a + bi) + " << im1 << "(c + di)i = " << re2 << " + " << im2 << "i\n";
     cout << re1 << "a + " << re1 << "bi + " << im1 << "ci + " << im1 << "d i^2 = "
          << re2 << " + " << im2 << "i\n";
     cout << "(" << re1 << "a - " << im1 << "d) + (" << re1 << "b + " << im1 << "c)i = "
          << re2 << " + " << im2 << "i\n";

     cout << re1 << "a - " << im1 << "d = " << re2 << " and " << re1 << " + " << im1 << " = "
          << im2 << std::endl;

     cout << "\n\nd = (" << re1 << "a - " << re2 << ")/" << im1 << " and c = (" << im2
          << " - " << re1 << "b)/" << im1 << std::endl;

     info = 's';
  }
  else {
    double a = re1;
    double b = im1;
    double c = re2;
    double d = im2;

    if ( (a == 0) && (b == 0) )  {
      if ( (c == 0)  && (d == 0) ) {
        cout << "\nFor all values x, y in Complex, 0x + 0y i = 0 + 0 i = 0\n\n";
        info = 'z';
      }
      else  {
        cout << "\nThe solution set is empty: {} since no values exist for which 0x + 0y i = "
             << xyi(complex<double>(c, d)) << std::endl;
        info = 'e';
    }
  }
  else {
    if (a == 0)  {   // b != 0
      if (c == 0)  {
        show_y(b, 0, d, equation);
        info = 'y';
      }
      else  {
        show_y(b, c, d, equation);
        info = 'y';
      }
    }
    else {   // b must equal 0
      if (d == 0) {
        show_x(a, c, 0, equation);
        info = 'x';
      }
      else {
        show_x(a, c, d, equation);
        info = 'x';
      }
    }
  }
 }
 return info;
}

bool show_work(RR eqn, string eqn_str)  {
    // 3 cases: show_ystr(), show_x(), show_y()
    bool status;
    cout << "\nSubstituting x and y into " << eqn_str << ", we obtain:\n";
    char filter = show_ystr(eqn);

    switch(filter)  {
     case 's':
        cout << "\nTherefore, {(x,y) | x = a + bi and y = c + di; a, b in Rational}\n"
             << "is the solution set of the equation  " << eqn_str << " and x,y in Complex\n\n";
        status = true;
        break;

     case 'x':
        x_solutions_only(eqn);
        status = false;
        break;

     case 'y':
        y_solutions_only(eqn);
        status = false;
        break;

     case 'z':
       cout << "If a + bi = 0, then a = 0 and b = 0\n\n";
       status = false;
       break;

     case 'e':
       cout << "\nTherefore, no solutions are ever possible.\n\n";
       status = false;
       break;

     default:
       cout << "\n Status has not been set and is meaningless: status = " << status;
       cout << std::endl;
       break;

    }
    return status;
}

std::string xyi(complex<double> z)  {
  double tol = 0.000001;
  std::string a = "";   // 'a' for Algebraic Form
	double REAL = z.real();
	double IMAG = z.imag();

	if (std::fabs(REAL) < tol) REAL = 0;
	if (std::fabs(IMAG) < tol) IMAG = 0;

    a.append(to_string_with_precision(REAL));
	if (z.imag() < 0) a.append(" - i " + to_string_with_precision(-IMAG));
	else a.append(" + i " + to_string_with_precision(IMAG));
	return a;
}   // END xyi(z)

complex<double> x_solutions_only(RR eqn)  {
   complex<double> x;
   if (eqn.first.imag() == 0)  {
     if (eqn.second.imag() == 0)  {
       x.real( (eqn.second.real())/(eqn.first.real()) );
       x.imag(0);
     }
     else {
       x.real( (eqn.second.real())/(eqn.first.real()) );
       x.imag( (eqn.second.imag())/(eqn.first.real()) );
     }
   }
    else cout << "\ny_solutions should have been called!\n\n";

    return x;
}

complex<double> y_solutions_only(RR eqn)  {

   complex<double> y;
   if (eqn.first.real() == 0)  {
     if (eqn.second.real() == 0)  {
       y.real( (eqn.second.imag())/(eqn.first.imag()) );
       y.imag(0);
     }
     else {
       y.real( (eqn.second.imag())/(eqn.first.imag()) );
       y.imag( -(eqn.second.real())/(eqn.first.imag()) );
     }
   }
   else cout << "\nx_solutions should have been called!\n\n";

   return y;
}

void show_x(double a, double c, double d, string eqn_str)  {
  if (d == 0)  {
    complex<double> x = complex<double>(c/a, 0);

    cout << a << "(a + bi) + " << 0 << "(c + di)i = " << c << " + " << 0 << "i\n";
    cout << a << "a + " << a << "bi  = " << c << " + " << 0 << "i\n";
    cout << "(" << a << "a) + (" << a << "bi) = " << c << " + " << 0 << "i\n";
    cout << a << "a = " << c << " and b = " << 0 << std::endl;
    cout << "a = (" << c << ")/(" << a << ") and b = " << 0 << std::endl;

    cout << "\nTherefore, {x | x = " << xyi(x) << " }\n"
         << "is the only solution of the equation  " << eqn_str << " and x in Complex\n\n";
  }
  else {
    complex<double> x = complex<double>(c/a, d/a);
    cout << a << "(a + bi) + " << 0 << "(c + di)i = " << c << " + " << d << "i\n";
    cout << a << "a + " << a << "bi = " << c << " + " << d << "i\n";
    cout << a << "a + " << a << "bi = " << c << " + " << d << "i\n";
    cout << a << "a = " << c << " and " << a << "b = " << d << std::endl;

    cout << "\n\na = " << c << '/' << a << " and b = " << d << '/' << a << std::endl;

    cout << "\nTherefore, {x | x = " << xyi(x) << " }\n"
         << "is the only solution of the equation  " << eqn_str << " and x in Complex\n\n";
  }

}

void show_y(double b, double c, double d, string eqn_str)  {
  if (c == 0)  {
    complex<double> y = complex<double>(d/b, 0);

    cout << 0 << "(a + bi) + " << b << "(c + di)i = " << 0 << " + " << d << "i\n";
    cout << b << "ci + " << b << "d i^2 = " << 0 << " + " << d << "i\n";
    cout << "(- " << b << "d) + " << b << "ci = " << c << " + " << d << "i\n";

    cout << "- " << b << "d = " << 0 << " and " << b << "c = "
         << d << std::endl;

    cout << "\n\nd = (-" << 0 << ")/" << b << " and c = " << d
         << "/" << b << std::endl;

    cout << "\nTherefore, {y | y = " << xyi(y) << " }\n"
         << "is the only solution of the equation  " << eqn_str << " and y in Complex\n\n";

  }
  else {
    complex<double> y = complex<double>(d/b, -c/b);
    cout << 0 << "(a + bi) + " << b << "(c + di)i = " << c << " + " << d << "i\n";
    cout << b << "ci + " << b << "d i^2 = " << c << " + " << d << "i\n";
    cout << "(-" << b << "d) + " << b << "ci = " << c << " + " << d << "i\n";

    cout << '-' << b << "d = " << c << " and " << b << " c = " << d << std::endl;

    cout << "\n\nd = (-" << c << ")/" << b << " and c = " << d << "/" << b << std::endl;

    cout << "\nTherefore, {y | y = " << xyi(y) << " }\n"
         << "is the only solution of the equation  " << eqn_str << " and y in Complex\n\n";
  }

}
