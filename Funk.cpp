#include "Funk.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

EquationSolver::EquationSolver(std::function<double(double)> f_ /*= nullptr*/) : f(f_) {}

void EquationSolver::setParameters(double a_, double b_, double eps_) {
    if (a_ >= b_) {
        throw std::invalid_argument("Помилка: a повинно бути менше b.");
    }
    a = a_;
    b = b_;
    eps = eps_;
    iterations = 0;
}

double EquationSolver::evaluateFunction(double x) const {
    if (!f) {
        throw std::runtime_error("Помилка: Функція f не встановлена.");
    }
    return f(x);
}

double EquationSolver::derivative(double x) const {
    if (!f) {
        throw std::runtime_error("Помилка: Функція f не встановлена.");
    }
    double h = 1e-6;
    return (evaluateFunction(x + h) - evaluateFunction(x - h)) / (2 * h);
}

void EquationSolver::bisectionMethod() const {
    iterations = 0;
    double left = a, right = b;

    if (evaluateFunction(left) * evaluateFunction(right) >= 0) {
        cout << "На інтервалі [" << a << ", " << b << "] немає кореня або він не єдиний.\n";
        return;
    }

    while ((right - left) / 2 > eps) {
        double c = (left + right) / 2;
        if (evaluateFunction(left) * evaluateFunction(c) < 0)
            right = c;
        else
            left = c;
        iterations++;
    }

    double result = (left + right) / 2;
    cout << "Корінь: " << result << " (ітерацій: " << iterations << ")\n";
}

void EquationSolver::newtonMethod() const {
    iterations = 0;
    double x = (a + b) / 2.0;
    double dx;

    do {
        double f_val = evaluateFunction(x);
        double df = derivative(x);

        if (fabs(df) < 1e-12) {
            cout << "Похідна близька до нуля. Метод Ньютона не працює.\n";
            return;
        }

        dx = f_val / df;
        x = x - dx;
        iterations++;

        if (x < a || x > b) {
            cout << "Вихід за межі проміжку. Метод Ньютона не збігається.\n";
            return;
        }
    } while (fabs(dx) > eps);

    cout << "Корінь: " << x << " (ітерацій: " << iterations << ")\n";
}