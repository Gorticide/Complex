//  g++ -g complex2.cpp -std=c++11 -o complex2
// Michael William Hentrich
// September 2018

#include <iostream>
#include <cmath>
#include <complex>
#include <iomanip>
#include <cstdio>
#include <string>
#include <sstream>   // for std::string to_string_with_precision

#include <istream>  // to use cin.get() so as to use function "pause"

//static constexpr auto PI = acos(-1);   // must compile with -std=c++11 to use this
//const double PI = 3.1415926535897932384626433832795;   // if no c++11, use this

static constexpr auto PI = acos(-1);
const double radians = PI/180.0;
const double degrees = 180.0/PI;
const double tol = 0.0000001;

using std::cout;
using std::cin;
using std::endl;
using std::setw;
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
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 4)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

int irrational();
complex<double> getz();
complex<double> conjugate();
int angle_theta(complex<double> z);
int Modulus(complex<double> z);
int convert_tri(complex<double> z);
int convert_pol(complex<double> z);
int convert_expon(complex<double> z);
complex<double> power(complex<double> z, int n);
void Roots_of_Unity(int Nth);
int roots(complex<double> z, int n);
std::string cis(complex<double> z);
std::string xyi(complex<double> z);
void clearScreen();
void setCursorPosition(short row , short col);
std::string printQuadrant_reals(double abscissa, double ordinate, double eps);
int getQuadrant_reals(double abscissa, double ordinate, double eps);
bool gt(double LHS, double RHS);
bool lt(double LHS, double RHS);
int pause();

char choice;
int op;
bool binary_operation = false;
bool current_values = false;
complex<double> z, w;

int main ()    {
	clearScreen();
	cout << endl;
	cout << setw(53) << "A Complex Numbers Calculator\n" << endl;
	cout << setw(53) << "Using C++ STL:  <complex>\n\n\n";
	irrational();
	return 0;
}

int irrational()       {

    complex<double> result;

	cout <<"\n" << setw(57) << "  * C O M P L E X   N U M B E R S * \n\n"
	          << setw(61) << "######################################\n\n\n\n";

	do   {
		z = getz();
		do      {
menu:	   clearScreen();
		   cout << endl << setw(45) << "\"MAIN MENU\"\n";

		cout << setw(45) << "===========\n";
		cout << "\n\t1) Addition" << setw(36) << "2) Subtraction\n";
		cout << "\n\t3) Multiplication" << setw(27) << "4) Division\n";
		cout << "\n\t5) Conjugate" << setw(35) << "6) Phase Angle\n";
		cout << "\n\t7) Modulus" << setw(57) << "8) Transform to trigonometric form\n";
		cout << "\n\t9) Transform to polar form" << setw(40) << "10) Transform to Exponential form\n";
		cout << "\n\t11) List N Nth roots" << setw(33) << "12) Raise to power n\n";

		cout << "\n\n\tYour choice = ";
		cin >> op;
		clearScreen();

      if ( (op == 1) || (op == 2) || (op == 3) || (op ==4) )  {
		      cout << "\nYour first complex number is: " << xyi(z);
			  if (  (!current_values) || (!binary_operation)  ) {
				  cout << "\n\nEnter your second complex number:\n";
                  w = getz();
			  }
			  else cout << "\nYour second complex number is: " << xyi(w);
	 }

			switch(op)    	{

			case 1://Addition
				cout << endl << setw(45) << "\"Addition\"\n\n";
				result = z + w;
				break;

			case 2://Subtraction
				cout << endl << setw(46) << "\"Subtraction\"\n\n";
				result = z - w;
				break;

			case 3://Multiplication
				cout << endl << setw(48) << "\"Multiplication\"\n\n";
				result = z*w;
				break;

			case 4://Division
				cout << endl << setw(45) << "\"Division\"\n\n";
				result = z/w;
				break;

			case 5://Conjugate
				cout << endl << setw(45) << "\"Conjugate\"\n\n";
				result = conj(z);
				break;

			case 6://Angle(theta)
				cout << endl << setw(47) << "\"Phase Angle (theta)\"\n\n";
                angle_theta(z);
				break;

			case 7://Modulus
				cout << endl << setw(45) << "\"Modulus (r)\"\n\n";
				Modulus(z);
				break;

			case 8://Transform to trigonometric form
				cout << endl << setw(56)
				          << "\"Transform to trigonometric form\"\n\n";
			    convert_tri(z);
				break;

			case 9://Transform to polar form
				cout << endl << setw(52) << "\"Transform to polar form\"\n\n";
				convert_pol(z);
				break;

			case 10://Transform to Exponential form
				cout << endl << setw(55) << "\"Transform to Exponential form\"\n\n";
				convert_expon(z);
				break;

			case 11:  // List N Nth roots
				int N;
				cout << endl << setw(55) << "\"List N Nth roots\"\n\n";
			    cout << "Enter integer N: ";
				cin >> N;
				roots(z, N);
				break;

			case 12:  // Raise complex number to a power
				 int n;
                 cout << endl << setw(55) << "\"Raise to a Power\"\n\n";
				 cout << "To find (" << xyi(z) << ")^n, enter integer n: ";
				 cin >> n;
				 result = power(z, n);
				 break;

			default :     //when the user enter anumber more than 10 .

				cout << setw(46) << "\"Out of Menu\"\n\n";
				cout << "\t\tError  ! enter from 1 to 12 only \n\n";
				goto menu;
			}  // END first switch(op)

			if ( (op == 1) || (op == 2) || (op == 3) || (op ==4) )  {
				binary_operation = true;
				cout << "\n\nThe result of the ";
				switch(op)  {
				case 1:  cout << "addition: \n\n(" << xyi(z) << ") + ("
					          << xyi(w) << ") = " << xyi(result);
				         break;

				case 2:  cout << "subtraction:\n\n(" << xyi(z) << ") - ("
					          << xyi(w) << ") = " << xyi(result);
 					      break;

			    case 3:  cout << "multiplication: \n\n(" << xyi(z) << ") * ("
					          << xyi(w) << ") = " << xyi(result);
	 					 break;

			    case 4:  cout << "division: \n\n(" << xyi(z) << ") / ("
					          << xyi(w) << ") = " << xyi(result);
 					      break;

				}
			}  // END second switch(op)

			if ( (op < 6) || (op == 12) ) {
			cout << "\n\nPolar form: " << cis(result);
			cout << "\n\nAlgebraic form: " << xyi(result);
		    }
			if (binary_operation)
			  cout << "\n\nDo you want to perform another operation on these numbers? (y/n) ";
			else cout << "\n\nDo you want to perform another operation on this number? (y/n) ";
			cin >> choice;   //to do another operation or not.
			if (choice == 'y' || choice == 'Y')  {
				current_values = true;
				goto menu;
			}
			if (choice == 'n' || choice == 'N')  {
				current_values = false;
				cout << "\n\nDo you want to save this result and operate on it? (y/n) ";
				cin >> choice;
				if (choice == 'y' || choice == 'Y')  {
					if ( (binary_operation) || (op == 12) ) z = result;
					choice = 'N';
					goto menu;
				}
	    	}
	  }  // END Inner Do-While Loop
	  while(choice=='y'||choice=='Y');

	cout << "\n\nDo you want to enter new numbers? (y/n) ";
	cin >> choice;      //to enter new numbers or not.
	clearScreen();
	cout << endl << endl;

 }  // END Outer Do-While Loop
	while(choice=='y'||choice=='Y');
    return(0);

}  // END function irrational()

// NOTES about my adjustment for arg(z) range (−π, π)  to range (0, 2*π)
/************************************************************************
Return value of arg is same as atan2
Principal arc tangent of y/x, in the interval (−π, π) radians.
complex ---> std::arg
Calculates the phase angle (in radians) of the complex number z in the interval (−π, π).
Errors and special cases are handled as if the function is implemented as
std::atan2(std::imag(z), std::real(z)).
One radian is equivalent to 180/PI degrees.

I wish to have return values in the interval (0, 2*π)
This means that return values in interval (0, π) remain as is,
but return values in interval (-π, 0) must be adjusted:
IF arg(z) < 0, then I will want to add 2*π to the result,
for example, when z = 3 - 2i, arg(z) returns atan2(-2 , 3) = -0.58800 ...
We add 2*π which gives 5.69518 ... (radians)
which, when multiplied by 180/π, gives us about 326.31 degrees.
***************************************************************************/

std::string cis(complex<double> z)  {

	std::string p = "";  // 'p' for Polar Form
	double theta = arg(z);
	if (theta < 0) theta += 2*PI;   // see above note
	else if (std::fabs(theta) < tol)  theta = 0; // if theta is zero
	theta *= degrees;
	p.append(to_string_with_precision(abs(z)) + "(COS " + to_string_with_precision(theta));
	p.append(" + i SIN " + to_string_with_precision(theta) + ")");
	return p;
}   // END cis(z)

std::string xyi(complex<double> z)  {

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

complex<double> getz()  {
	int terms = 1;

	cout << "\n\nComplex Number in" << setw(35) << " (1) algebraic terms x + yi\n "
	          << "\t\t\t" << setw(49)
			  << "(2) polar terms r(cos t + i sin t)\n\nEnter 1 or 2: ";
	cin >> terms;

    switch(terms)   {
	case 1:
		{
			complex<double> C;
			cout << "\n\nEnter BOTH components <real part> <imaginary part>: ";
		    cin >> C;
			return C;
	    }

	case 2:
		{
			double rho, theta;
			cout << "\n\nEnter magnitude (absolute value RHO): ";
			cin >> rho;
			cout << "\nEnter direction in degrees (phase angle THETA): ";
			cin >> theta;
			if (std::fabs(theta) < tol)  theta = 0; // if theta is zero
			complex<double> C(std::polar(rho, theta*radians));
			return C;
		}
	}

}    // END getz()

int angle_theta(complex<double> z)   {
	double theta = arg(z);
	if (theta < 0) theta += 2*PI;   // see note above cis(z) definition
	else if (std::fabs(theta) < tol)  theta = 0; // if theta is zero
	cout << "phase angle in degress on interval (0, 360]: " << theta * degrees;
	return(0);
}

int Modulus(complex<double> z)   {
      cout << "\n|" << xyi(z) << "| = " << abs(z);
	  return(0);
}

int convert_tri(complex<double> z)   {
       cout << endl << "  " << cis(z);
	   return 0;
}

int convert_pol(complex<double> z)   {
	double theta = arg(z);
	if (theta < 0) theta += 2*PI;   // see note above cis(z) definition
	else if (std::fabs(theta) < tol)  theta = 0; // if theta is zero
    cout << endl << "(" << abs(z) << ", " << theta * degrees << ")";
	cout << "\n\nThat is, modulus (absolute value) =====> | " << xyi(z) << " | = "
	          << abs(z) << "\nnorm (squared absolute value) =====> | " << xyi(z) << " |^2 = "
		      << norm(z) << "\nPhase angle: " << arg(z)*degrees;
	  return(0);
}

int convert_expon(complex<double> z)   {
	double theta = arg(z);
	if (theta < 0) theta += 2*PI;   // see note above cis(z) definition
	else if (std::fabs(theta) < tol)  theta = 0; // if theta is zero
    cout << endl << abs(z) << " e^(" << theta << ")";
	return(0);
}

complex<double> power(complex<double> z, int n)   {
      complex<double> p = pow(z, n);
	  return p;
}

void Roots_of_Unity(int Nth)    {
	int K;  // to calculate 2*PI*k/n in degrees: 360*k/n
    int j = 1;
    for (int k = 0; k < Nth; ++k)  {
	  cout << "root " << j << ": ";
	  K = 360*k/(Nth);
      cout << cis(std::polar(1.0, K*radians)) << " = "
	            << xyi(std::polar(1.0, K*radians));
	  cout << endl;
	  j++;
	  }
}

// Note that I made this function far more robust than simply spitting put results
// The extra work that went into explaining how to find roots of complex numbers
// will surely be useful to the end user (me in the future when I forget how!)
int roots(complex<double> z, int n)   {
	   if (std::fabs(abs(z)) < tol)  {
		   cout << "\n Since modulus | " << xyi(z)
		        << " | = 0, the only root of 0 is 0 itself.";
		   return(0);
	   }

       if ( (std::fabs(z.real() - 1) <=  tol) && (z.imag() <= tol) ) Roots_of_Unity(n);
	   else {
		   double angle, phi;
		   // The very first thing we must check for are "vertical vectors".
		   // If the vector is vertical, then x == 0, so we cannot use atan(y/x):

		   if ( (std::fabs(z.real()) < tol) ) angle = PI/2.0;
		   else angle = atan(std::fabs(z.imag()/z.real()));

		   cout << "\nFirst we put " << xyi(z) << " in polar (trigonometric) form.\n\n";
		   cout << " Note that | " << xyi(z) << " | = " << abs(z) << ",\n cos(t) = "
		        << std::setprecision(4) << z.real()/abs(z) << ", and angle t is "
				<< printQuadrant_reals(z.real(), z.imag(), tol);
		   cout << " So, the reference angle = arccos(" << std::fabs(z.real()/abs(z))
		        << ") = " << acos(std::fabs(z.real()/abs(z)))*degrees;

		   cout << "\n The degree measure of angle t = ";
		   int quadrant = getQuadrant_reals(z.real(), z.imag(), tol);

		   switch(quadrant)  {
		   case 1:
			   cout << "arccos(" << std::fabs(z.real()/abs(z)) << ") = ";
			   phi = angle;
			   break;

		   case 2:
			   cout << "180 - arccos(" << std::fabs(z.real()/abs(z)) << ") = ";
			   phi = PI - angle;
			   break;

		   case 3:
			   cout << "180 + arccos(" << std::fabs(z.real()/abs(z)) << ") = ";
			   phi = PI + angle;
			   break;

		   case 4:
			   cout << "360 - arccos(" << std::fabs(z.real()/abs(z)) << ") = ";
			   phi = 2*PI - angle;
			   break;

		   }  // End switch(quadrant)
		   cout << phi * degrees;

		   cout << "\n\n We now have " << xyi(z) << " = " << cis(z);
		   cout << "\n Now, let z = r[cos(t) + i sin(t)] be the " << n
		        << "-ROOT of " << xyi(z);
		   cout << "\n Then, z^(" << n << ") = " << xyi(z) << ", or, "
		        << "by De Moivre's theorem,\n r^(" << n << ")*[cos("
				<< n << "*t) + i sin(" << n << "*t)] = " << cis(z)
				<< "\n\n From this equation, r^(" << n << ") = "
				<< abs(z) << "  <---->  r = " << pow(abs(z), 1.0/n);
		  cout << "\n\n Also, cos(" << n << "*t) = " << std::setprecision(4)
		       << phi*degrees << " and sin(" << n << "*t) = "
			   << std::setprecision(4) << phi*degrees;
	      pause();
		  cout << "\n Thus " << n << "*t differs from " << phi*degrees
			   << " by an integral multiple of 360:\n\n";

		   cout << n << "*t = " << phi*degrees << " + k*360, k any integer\n"
		        << "  t = " << phi*degrees/n << " + k*" << 360.0/n
				<< ", k any integer.\n\n Letting k = ";
		   for (int i = 0; i < n; ++i) cout << i << ", ";
		   cout << "we have t = ";
		    for (int i = 0; i < n; ++i) {
				cout << phi*degrees/n + i*360.0/n;
				if ( i != (n - 1) ) cout << ", ";
			}
			cout << "\n\n Thus, " << xyi(z) << " has " << n << " " << n << "-ROOTS:\n\n";
			double r = pow(abs(z), 1.0/n);
			int j = 1;
			for (int k = 0; k < n; ++k)  {
			  cout << "root " << j << ": ";
			  cout << cis(std::polar(r , phi/n + k*2.0*PI/n)) << " = "
						<< xyi(std::polar(r , phi/n + k*2.0*PI/n));
			  cout << endl;
			  j++;
			  }

	   }  // End else
	   return(0);
}

void clearScreen()      {
  system("clear");
  setCursorPosition(0, 0);
}

void setCursorPosition(short row , short col)   {
  printf("%c[%d;%df",0x1B, col , row);
}

std::string printQuadrant_reals(double abscissa, double ordinate, double eps)  {
  double x = abscissa;
  double y = ordinate;

  // if x == 0
  if (std::fabs(x) < eps) {
    if (std::fabs(y) < eps) return std::string("at the origin.");
    if ( gt(y, 0.0) ) return std::string("on the positive side of the y-axis.\n\n");
    if ( lt(y, 0.0) ) return std::string("on the negative side of the y-axis.\n\n");
  }
  else  {
     if (x > 0)  {
		 // if y == 0
        if (std::fabs(y) < eps) return std::string("on the positive side of the x-axis.\n\n");
        if ( gt(y, 0.0) ) return std::string("in the first quadrant.\n\n");
        if ( lt(y, 0.0) ) return std::string("in the fourth quadrant.\n\n");
     }
     if ( lt(x, 0.0) ) {
		// if y == 0
        if (std::fabs(y) < eps) return std::string("on the negative side of the x-axis.\n\n");
        if ( gt(y, 0.0) )  return std::string("in the second quadrant.\n\n");
        if ( lt(y, 0.0) )  return std::string("in the third quadrant.\n\n");
      }
    }
}

int getQuadrant_reals(double abscissa, double ordinate, double eps)  {
  double x = abscissa;
  double y = ordinate;

  // if x == 0
  if (std::fabs(x) < eps) {
    if (std::fabs(y) < eps) return(0);
    if ( gt(y, 0.0) ) return 1;  // angle is simply 90 degrees [PI/2 radian]
    if ( lt(y, 0.0) ) return 3;  // angle is 270 degrees, so 180 + arccos(angle)
  }
  else  {
     if ( gt(x, 0.0) )  {
		 // if y == 0
        if (std::fabs(y) < eps) return 1;  // angle is 0
        if ( gt(y, 0.0) ) return 1;        // Quadrant I (reference angel)
        if ( lt(y, 0.0) ) return 4;        // Quadrant IV (360 - reference angle)
     }
     if ( lt(x, 0.0) ) {
		// if y == 0
        if (std::fabs(y) < eps) return 2;  // angle is simply 180 [PI]
        if ( gt(y, 0.0) )  return 2;     // Quadrant II (180 - reference angle)
        if ( lt(y, 0.0) )  return 3;     // Quadrant III (180 + reference angle)
      }
    }
}

bool gt(double LHS, double RHS)    {
	if (std::isgreater(LHS, RHS)) return true;
    else return false;
}

bool lt(double LHS, double RHS)    {
  if (std::isless(LHS, RHS))  return true;
  else return false;
}


int pause ()  {

   do  {
       std::cout << std::endl << std::endl;
       std::cout << "\n\t Press ENTER [ <-----||| ] to continue.";
	   std::cin.get();
      } while (std::cin.get() != '\n');

   return 0;
}
