#include <iostream>
#include <cmath>
#include <vector>
#include "Polynomial.hpp"

int main() {
    Polynomial pol = Polynomial({-2, 1, -1, 1, -1, 1});

    std::cout << "Polynomial to be analised:\n";
    pol.print();

    double x = 1;
    std::cout << "\nValue at point: " << x << ":\n";
    std::cout << pol.value_at_point(x);

    std::cout << "\n\nDerivative in general form:\n";
    Polynomial der = pol.derivative();
    der.print();

    std::cout << "\nValue of the derivative at point: " << x << ":\n";
    std::cout << pol.derivative_definition(x);


    std::cout << "\n\nIntegral in general form:\n";
    Polynomial integ = pol.integral();
    integ.print();


    double a = 0, b = 1;
    std::cout << "\nDefinite integral over interval: " << a << " " << b << ":\n";
    
    std::cout << pol.definite_integral(a, b);

    std::cout << "\n\nZeroes:";

    std::cout << "\nBy bisection (\"binary search\"): ";
    double lower = 3, upper = 5;
    std::cout << "\ntrying interval [" << lower << ", " << upper << "] (no zero): " << pol.bisection(lower, upper);
    lower = 1; upper = 2;
    std::cout << "\ntrying interval [" << lower << ", " << upper << "] (yes zero): " << pol.bisection(lower, upper);
    std::cout << '\n';
    return 0;
}
