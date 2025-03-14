#include "Polynomial.hpp"

void Polynomial::print(bool ascending) const {
    if (!ascending) {
        int degree = -1;
        for (auto coefficient: m_coefficients) {
            degree++;
            if (degree == 0 && coefficient != 0) {
                std::cout << coefficient;
                continue;
            }
            if (coefficient == 0) {
                continue;
            }
            std::cout << ' ';
            if (coefficient > 0) std::cout << "+";
            if (coefficient != 1) std::cout << coefficient;
            std::cout << "x";
            if (degree == 1) continue;
            std::cout << '^' << degree;
        }
    }
    std::cout << '\n';
}

Polynomial Polynomial::derivative(int order) const {
    std::vector<double> coefficients(m_coefficients.size()-1, 0); 
    for (size_t i = 1; i<=coefficients.size(); i++) {
        coefficients[i-1] = i*m_coefficients[i];
    }

    return Polynomial(coefficients);
}

Polynomial Polynomial::integral(int order, double constant) const {
    std::vector<double> coefficients(m_coefficients.size()+1, 0); 

    coefficients[0] = constant;

    for (int i = 1; i<coefficients.size(); i++) {
        coefficients[i] = m_coefficients[i-1]/(i);
    }

    return Polynomial(coefficients);
}

double Polynomial::value_at_point(double x) const {
    double val = 0;
    for (int i = 0; i < m_coefficients.size(); i++) {
        val += m_coefficients[i] * std::pow(x, i);
    }
    return val;
}
double Polynomial::derivative_definition(double x, double dx) const {
    // calculated by definition of derivative ( lim_{h->0} { { f(x+h) - f(x) } / h } )
    double der = 0;  
    double y1 = value_at_point(x);
    double y2 = value_at_point(x+dx);

    der = ((y2-y1)/dx);
    return der;
}

double Polynomial::definite_integral(double x1, double x2) const {
    // could do this by definition but would be horribly slow compared to 
    // the derivative so i won't bother
    // instead, it is calculated using..
    // Second Fundamental Theorem of Calculus
    double val = 0;

    Polynomial integ = integral();

    val = integ.value_at_point(x2) - integ.value_at_point(x1);

    return val;
}

//////////////////////////////////////////////
///                                         //
///                 ZEROES                  //
///                                         //
//////////////////////////////////////////////


double Polynomial::bisection(double a, double b, double epsilon) const {
    double f_a = value_at_point(a);
    double f_b = value_at_point(b);
    if (f_a == 0) return f_a;
    if (f_b == 0) return f_b;
    if (f_a*f_b > 0) return b+1; // this does not imply that a zero does not exist in the interval
    double bisection = (a+b)/2;
    double val = value_at_point(bisection);
    while (std::fabs(val) > epsilon) {
        if (val < 0) {
            if (f_a > 0) {
                b = bisection;
                f_b = value_at_point(b);
            } else {
                a = bisection;
                f_a = value_at_point(a);
            }
        } else {
            if (f_a > 0) {
                a = bisection;
                f_a = value_at_point(a);
            } else {
                b = bisection;
                f_b = value_at_point(b);
            }
        }

        bisection = (a+b)/2;
        val = value_at_point(bisection);
    }

    return bisection;
}


