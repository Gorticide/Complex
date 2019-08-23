/*
 g++ -g solve_complex_QQ.cpp fraction.cpp -std=c++11 -o solve_complex_QQ
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
#include <string>
#include "fraction.h"

using std::cout;
using std::cin;
using std::pair;
using std::string;


// invented complex a + bi where a,b in Rational [EXPERIMENTAL]
typedef pair<Fraction, Fraction>  COR;  // complex over Rationals

typedef pair<COR, COR> QQ;

// Takes two integers and transforms each to Fraction object
// then stores as REAL and IMAGINARY parts of COR object
std::istream& operator>> (std::istream& is, COR &w) {
  int value;
  is >> value;
  Fraction real_part = Fraction(value, 1);
  w.first = real_part;
  is >> value;
  Fraction imag_part = Fraction(value, 1);
  w.second = imag_part;
  return is;
}


QQ getEquation();

QQ solveRationals(Fraction a, Fraction b, QQ eqn);
    // returns QQ sol where sol.first is x and sol.second is y

QQ eqn_Integers(int a, int b, int c, int d);

char show_ystr(QQ eqn);
bool show_work(QQ eqn, string eqn_str);
std::string xyi(COR z);
COR x_solutions_only(QQ eqn);
COR y_solutions_only(QQ eqn);
void show_x(Fraction a, Fraction c, Fraction d, string eqn_str);
void show_y(Fraction b, Fraction c, Fraction d, string eqn_str);
string equation = "";

int main()  {

 QQ eqn = getEquation();  // eqn.first is LHS, eqn.second is RHS

 cout << "\nFind all pairs of complex numbers x and y for which " << equation
      << "\nSince x and y are complex numbers, we can write x = a + bi when a, b in Integers,\n"
      << "and y = c + di when c, d in Integers.\n\n";

 if (show_work(eqn, equation))   {  // return bool, then true: solutions for both x and y exist
                                   // if false: then show_work calls x or y solutions_only(eqn)

    cout << "\nAt this point we are free to assign any (real) Rational values to a and b.\n\n";
    char substitute = 'y';
    while (  (substitute == 'y') || (substitute == 'Y')  )   {
        Fraction a, b;
        cout << "Let fraction a = ";
        cin >> a;
        cout << "\nLet fraction b = ";
        cin >> b;
        QQ Q = solveRationals(a, b, eqn);
        cout << "\nx = " << xyi(Q.first) << " and y = " << xyi(Q.second) << "\n\n";
        cout << "Do you want to find another pair? <y/n> : ";
        cin >> substitute;
    }
}

}

QQ getEquation()   {

    COR x, y;
    char sign;
    std::string val;

    cout << "\nEnter equation of complex numbers where: ax + by i = cx + dy i\n\n";
	  cout << "\nand a, b, c, and d are Intgers\n ";

	  cout << "\n\nEnter BOTH components of left member (a and b) as INTEGERS\n"
         << "(to become Fractions) <'real part'> <'imaginary part'>: ";
    cin >> x;

    val = std::to_string(x.first.getNum());
    if (abs(x.first.getNum()) != 1) equation.append(val);
    //if (x.first.getNum() != 0)
    equation += 'x';

    if (x.second < 0) {
      sign = '-';
      val = std::to_string(-x.second.getNum());
    }
    else  {
      sign = '+';
      val = std::to_string(x.second.getNum());
    }
    equation += ' ';
    equation += sign;
    equation += ' ';

    if (abs(x.second.getNum()) != 1)  {
      equation.append(val);
    }
    //if (x.second.getNum() != 0)
    equation += 'y';
    //if (x.second.getNum() != 0)
    equation.append(" i == ");
    //else equation.append(" == ");

    cout << "\n\nEnter BOTH components of right member (c and d) as INTEGERS\n"
         << "(to become Fractions) <'real part'> <'imaginary part'>: ";
    cin >> y;

    val = std::to_string(y.first.getNum());
    equation.append(val);

    if (y.second < 0) {
      sign = '-';
      val = std::to_string(-y.second.getNum());
    }
    else  {
      sign = '+';
      val = std::to_string(y.second.getNum());
    }
    equation += ' ';
    equation += sign;

    if (abs(y.second.getNum()) != 1) {
      equation += ' ';
      equation.append(val);
    }
    //if (y.second.getNum() != 0)
    equation.append(" i");

    QQ eqn(x, y);
    return eqn;
}


QQ solveRationals(Fraction a, Fraction b, QQ eqn)   {

   COR x, y;

   x.first = a;
   x.second = b;
   y.first = (eqn.second.second - eqn.first.first*b)/eqn.first.second;
   y.second = (eqn.first.first*a - eqn.second.first)/eqn.first.second;

   QQ solution(x,y);
   return solution;

}

char show_ystr(QQ eqn)   {

   COR LHS = eqn.first;
   COR RHS = eqn.second;
   Fraction re1 = LHS.first;
   Fraction im1 = LHS.second;
   Fraction re2 = RHS.first;
   Fraction im2 = RHS.second;

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
     Fraction a = re1;
     Fraction b = im1;
     Fraction c = re2;
     Fraction d = im2;

     if ( (a == 0) && (b == 0) )  {
       if ( (c == 0)  && (d == 0) ) {
         cout << "\nFor all values x, y in Complex, 0x + 0y i = 0 + 0 i = 0\n\n";
         info = 'z';
       }
       else  {
         cout << "\nThe solution set is empty: {} since no values exist for which 0x + 0y i = "
              << xyi(COR(c, d)) << std::endl;
         info = 'e';
     }
   }
   else {
     if (a == 0)  {   // b != 0
       if (c == 0)  {
         show_y(b, Fraction(0, 1), d, equation);
         info = 'y';
       }
       else  {
         show_y(b, c, d, equation);
         info = 'y';
       }
     }
     else {   // b must equal 0
       if (d == 0) {
         show_x(a, c, Fraction(0, 1), equation);
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


bool show_work(QQ eqn, string eqn_str)  {
// 3 cases: show_ystr(), show_x(), show_y()
    bool status;
    cout << "\nSubstituting x = a + bi and y = c + di into " << eqn_str << ", we obtain:\n";
    char filter = show_ystr(eqn);

    switch(filter)  {
      case 's':
         cout << "\nTherefore, {(x,y) | x = a + bi and y = c + di; a, b in Rational}\n"
              << "is the solution set of the equation  " << eqn_str << " and x,y in 'My Complex'\n\n";
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

std::string xyi(COR z)  {

  std::string a = "";   // 'a' for Algebraic Form
	Fraction REAL = z.first;
	Fraction IMAG = z.second;

    a.append(std::to_string(REAL.getNum()));
    if (REAL.getDen() != 1) {
      //if (REAL.getDen() == 0) cout << "Division by zero!\n\n";
        a += '/';
        a.append(std::to_string(REAL.getDen()));
    }

	if (IMAG < 0)   {
        a.append(" - i ");
        a.append(std::to_string(-IMAG.getNum()));
    }
	else {
       a.append(" + i ");
       a.append(std::to_string(IMAG.getNum()));
    }

    if (IMAG.getDen() != 1)  {
       a += '/';
       a.append(std::to_string(IMAG.getDen()));
    }

	return a;
}   // END xyi(z)

COR x_solutions_only(QQ eqn)   {
  COR x;

  if (eqn.first.second == 0)  {
    if (eqn.second.second == 0)  {
      x.first = (eqn.second.first)/(eqn.first.first);
      x.second = 0;
    }
    else {
      x.first = (eqn.second.first)/(eqn.first.first);
      x.second = (eqn.second.second)/(eqn.first.first);
    }
  }
   else cout << "\ny_solutions should have been called!\n\n";

   return x;
}

COR y_solutions_only(QQ eqn)   {

   COR y;
   if (eqn.first.first == 0)  {
     if (eqn.second.first == 0)  {
       y.first = (eqn.second.second)/(eqn.first.second);
       y.second = 0;
     }
     else {
       y.first = (eqn.second.second)/(eqn.first.second);
       y.second = -(eqn.second.first)/(eqn.first.second);
     }
   }
   else cout << "\nx_solutions should have been called!\n\n";

   return y;

}

void show_x(Fraction a, Fraction c, Fraction d, string eqn_str)  {
    if (d == 0)  {
      COR x = COR(c/a, 0);

      cout << a << "(a + bi) + " << 0 << "(c + di)i = " << c << " + " << 0 << "i\n";
      cout << a << "a + " << a << "bi  = " << c << " + " << 0 << "i\n";
      cout << "(" << a << "a) + (" << a << "bi) = " << c << " + " << 0 << "i\n";
      cout << a << "a = " << c << " and b = " << 0 << std::endl;
      cout << "a = (" << c << ")/(" << a << ") and b = " << 0 << std::endl;

      cout << "\nTherefore, {x | x = " << xyi(x) << " }\n"
           << "is the only solution of the equation  " << eqn_str << " and x in 'My Complex'\n\n";
    }
    else {
      COR x = COR(c/a, d/a);
      cout << a << "(a + bi) + " << 0 << "(c + di)i = " << c << " + " << d << "i\n";
      cout << a << "a + " << a << "bi = " << c << " + " << d << "i\n";
      cout << a << "a + " << a << "bi = " << c << " + " << d << "i\n";
      cout << a << "a = " << c << " and " << a << "b = " << d << std::endl;

      cout << "\n\na = " << c << '/' << a << " and b = " << d << '/' << a << std::endl;

      cout << "\nTherefore, {x | x = " << xyi(x) << " }\n"
           << "is the only solution of the equation  " << eqn_str << " and x in 'My Complex'\n\n";
    }

}

void show_y(Fraction b, Fraction c, Fraction d, string eqn_str)  {
    if (c == 0)  {
      COR y = COR(d/b, 0);

      cout << 0 << "(a + bi) + " << b << "(c + di)i = " << 0 << " + " << d << "i\n";
      cout << b << "ci + " << b << "d i^2 = " << 0 << " + " << d << "i\n";
      cout << "(- " << b << "d) + " << b << "ci = " << c << " + " << d << "i\n";

      cout << "- " << b << "d = " << 0 << " and " << b << "c = "
           << d << std::endl;

      cout << "\n\nd = (-" << 0 << ")/" << b << " and c = " << d
           << "/" << b << std::endl;

      cout << "\nTherefore, {y | y = " << xyi(y) << " }\n"
           << "is the only solution of the equation  " << eqn_str << " and y in 'My Complex'\n\n";

    }
    else {
      COR y = COR(d/b, -c/b);
      cout << 0 << "(a + bi) + " << b << "(c + di)i = " << c << " + " << d << "i\n";
      cout << b << "ci + " << b << "d i^2 = " << c << " + " << d << "i\n";
      cout << "(-" << b << "d) + " << b << "ci = " << c << " + " << d << "i\n";

      cout << '-' << b << "d = " << c << " and " << b << " c = " << d << std::endl;

      cout << "\n\nd = (-" << c << ")/" << b << " and c = " << d << "/" << b << std::endl;

      cout << "\nTherefore, {y | y = " << xyi(y) << " }\n"
           << "is the only solution of the equation  " << eqn_str << " and y in 'My Complex'\n\n";
    }
}
