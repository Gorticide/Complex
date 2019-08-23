// Using C++14 : 1i = sqrt(-1)

#include <iostream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>   // for std::string to_string_with_precision  (also need <iomanip>)
#include <iomanip>
#include "dcomplex.h"

using std::cout;
using std::cin;
using std::string;
using std::complex;


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

int main()
{
    using namespace std::complex_literals;
    std::cout << std::fixed << std::setprecision(1);
 
    std::complex<double> z1 = 1i * 1i;     // imaginary unit squared
    std::cout << "i * i = " << z1 << '\n';
 
    std::complex<double> z2 = std::pow(1i, 2); // imaginary unit squared
    std::cout << "pow(i, 2) = " << z2 << '\n';
 
    double PI = std::acos(-1);
    std::complex<double> z3 = std::exp(1i * PI); // Euler's formula
    std::cout << "exp(i * pi) = " << z3 << '\n';
 
    std::complex<double> z4 = 1. + 2i, z5 = 1. - 2i; // conjugates
    std::cout << "(1+2i)*(1-2i) = " << z4*z5 << '\n';

    std::cout << "Square root of -4 is "
              << std::sqrt(std::complex<double>(-4, 0)) << '\n'
              << "Square root of (-4,-0), the other side of the cut, is "
              << std::sqrt(std::complex<double>(-4, -0.0)) << '\n';

    std::cout << "\nsqrt(-1) = " << std::sqrt(std::complex<double>(-1, 0)) << '\n'
              << "Square root of (-1,-0), the other side of the cut, is "
              << std::sqrt(std::complex<double>(-1, -0.0)) << '\n';

    std::cout << "\n\n\nNow, using my own xyi() function to print complex numbers:\n\n";

    //std::complex<double> z1 = 1i * 1i;     // imaginary unit squared
    std::cout << "i * i = " << xyi(z1) << '\n';
 
    //std::complex<double> z2 = std::pow(1i, 2); // imaginary unit squared
    std::cout << "pow(i, 2) = " <<xyi(z2) << '\n';
 
    //double PI = std::acos(-1);
    //std::complex<double> z3 = std::exp(1i * PI); // Euler's formula
    std::cout << "exp(i * pi) = " << xyi(z3) << '\n';
 
    //std::complex<double> z4 = 1. + 2i, z5 = 1. - 2i; // conjugates
    std::cout << "(1+2i)*(1-2i) = " << xyi(z4*z5) << '\n';

    std::cout << "Square root of -4 is "
              << xyi(std::sqrt(std::complex<double>(-4, 0))) << '\n'
              << "Square root of (-4,-0), the other side of the cut, is "
              << xyi(std::sqrt(std::complex<double>(-4, -0.0))) << '\n';

    std::cout << "\nsqrt(-1) = " << xyi(std::sqrt(std::complex<double>(-1, 0))) << '\n'
              << "Square root of (-1,-0), the other side of the cut, is "
              << xyi(std::sqrt(std::complex<double>(-1, -0.0))) << '\n';

    std::cout << "\n\n" << "1i = " << 1i << " = " << xyi(1i) << '\n'
              << "1i * 1i = " << 1i*1i << " = pow(1i, 2) = " << pow(1i, 2) << " = "
              << xyi(pow(1i, 2)) << '\n'
              << "pow(i1, 3) = " << pow(1i, 3) << " = " << xyi(pow(1i, 3)) << '\n';

    std::cout << "\n\nUsing J: typedef std::complex<double> dcomplex\n\t"
              << "#define J dcomplex(0.0,1.0)\n\n";

    std::cout << "\n\n" << "J = " << J << " = " << xyi(J) << '\n'
              << "J * J = " << J*J << " = pow(J, 2) = " << pow(J, 2) << " = "
              << xyi(pow(J, 2)) << '\n'
              << "pow(J, 3) = " << pow(J, 3) << " = " << xyi(pow(J, 3)) << '\n';
    std::complex<double> z7 = 1. + 2.*J, z8 = 1. - 2.*J; // conjugates
    std::cout << "(1+2*J)*(1-2*J) = " << xyi(z7*z8) << '\n';
}
/*

    std::cout << "Square root of -4 is "
              << std::sqrt(std::complex<double>(-4, 0)) << '\n'
              << "Square root of (-4,-0), the other side of the cut, is "
              << std::sqrt(std::complex<double>(-4, -0.0)) << '\n';
*/