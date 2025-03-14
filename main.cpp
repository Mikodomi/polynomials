#include <iostream>
#include <cmath>
#include <vector>

class Polynomial {
    std::vector<double> m_coefficients; // starting from constant, to linear, quadratic etc.

public:
    Polynomial(std::vector<double> coefficients) : m_coefficients { coefficients } {}

    void print(bool ascending = false) const {
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

    Polynomial derivative(int order = 1) {
        std::vector<double> coefficients(m_coefficients.size()-1, 0); 
        for (size_t i = 1; i<=coefficients.size(); i++) {
            coefficients[i-1] = i*m_coefficients[i];
        }

        return Polynomial(coefficients);
    }

    Polynomial integral(int order = 1, double constant = 0) {
        // WARNING: +C is ignored!
        std::vector<double> coefficients(m_coefficients.size()+1, 0); 
        
        coefficients[0] = constant;

        for (int i = 1; i<coefficients.size(); i++) {
            coefficients[i] = m_coefficients[i-1]/(i);
        }
        
        return Polynomial(coefficients);
    }

    double value_at_point(double x) {
        double val = 0;
        for (int i = 0; i < m_coefficients.size(); i++) {
            val += m_coefficients[i] * std::pow(x, i);
        }
        return val;
    }
    double derivative_definition(double x, double dx = 0.000001) {
        // calculated by definition of derivative ( lim_{h->0} { { f(x+h) - f(x) } / h } )
        double der = 0;  
        double y1 = value_at_point(x);
        double y2 = value_at_point(x+dx);

        der = ((y2-y1)/dx);
        return der;
    }

    double definite_integral(double x1, double x2) {
        // could do this by definition but would be horribly slow compared to 
        // the derivative so i won't bother
        // instead, it is calculated using..
        // Second Fundamental Theorem of Calculus
        double val = 0;

        Polynomial integ = integral();

        val = integ.value_at_point(x2) - integ.value_at_point(x1);

        return val;
    }
};

int main() {
    Polynomial pol = Polynomial({1, 2, -2, 4});

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

    std::cout << '\n';
    return 0;
}
