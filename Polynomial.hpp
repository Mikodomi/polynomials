#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class Polynomial {
    std::vector<double> m_coefficients; // starting from constant, to linear, quadratic etc.

public:
    Polynomial(std::vector<double> coefficients) : m_coefficients { coefficients } {}

    void print(bool ascending = false) const;

    Polynomial derivative(int order = 1) const;
    Polynomial integral(int order = 1, double constant = 0) const;

    double value_at_point(double x) const;
    double derivative_definition(double x, double dx = 0.000001) const;
    double definite_integral(double x1, double x2) const;

    // root-finding
    
    //this method relies on the user supplying an interval [a,b] such that f(a) and f(b)
    //have opposite signs. if they do not, the function returns b+1
    double bisection(double lower, double higher, double epsilon = 0.000001) const;
};
