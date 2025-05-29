#pragma once
#ifndef FUNK_H
#define FUNK_H

#include <functional>

class EquationSolver {
private:
    double a, b, eps;
    mutable int iterations;
    std::function<double(double)> f;

public:
    EquationSolver(std::function<double(double)> f_ = nullptr);
    void setParameters(double a_, double b_, double eps_);
    double evaluateFunction(double x) const;
    double derivative(double x) const;

    void bisectionMethod() const;
    void newtonMethod() const;

    int getIterationCount() const { return iterations; }
};

#endif