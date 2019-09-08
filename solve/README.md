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
