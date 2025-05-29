#include <iostream>
#include <iomanip>
#include "Funk.h"
#include <functional>
#include <cmath>
#include <limits>

void solveQuadraticDirectly(double a, double b, double c) {
    std::cout << "--- Прямий розв'язок квадратного рівняння " << a << "x^2 + " << b << "x + " << c << " = 0 ---\n";
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                std::cout << "Рівняння має безліч розв'язків (0x + 0 = 0).\n";
            } else {
                std::cout << "Рівняння не має розв'язків (" << c << " = 0 є хибним).\n";
            }
        } else {
            double x = -c / b;
            std::cout << "Це лінійне рівняння. Корінь: x = " << x << std::endl;
        }
        return;
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double x1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double x2 = (-b - std::sqrt(discriminant)) / (2 * a);
        std::cout << "Два дійсних корені: x1 = " << x1 << ", x2 = " << x2 << std::endl;
    } else if (discriminant == 0) {
        double x = -b / (2 * a);
        std::cout << "Один дійсний корінь (два однакових): x = " << x << std::endl;
    } else {
        std::cout << "Немає дійсних коренів (дискримінант < 0).\n";
    }
    std::cout << "---------------------------------------------------------\n";
}


int main() {
    std::cout << "========= РОЗВ'ЯЗАННЯ НЕЛІНІЙНОГО РІВНЯННЯ =========\n";
    auto f_lambda_nonlinear = [](double x) -> double {
        if (x < 0) return std::numeric_limits<double>::quiet_NaN();
        return x + std::sqrt(x) + std::cbrt(x) - 2.5;
    };

    double a_nl = 0.4;
    double b_nl = 1.0;
    double eps_nl = 1e-5;

    EquationSolver* solver_nonlinear = new EquationSolver(f_lambda_nonlinear);
    try {
        solver_nonlinear->setParameters(a_nl, b_nl, eps_nl);

        std::cout << std::fixed << std::setprecision(7);

        std::cout << "Рівняння: x + sqrt(x) + cbrt(x) - 2.5 = 0\n";
        std::cout << "Інтервал: [" << a_nl << ", " << b_nl << "], Точність: " << eps_nl << "\n\n";

        std::cout << "===  Метод бісекції (нелінійне)  ===\n";
        solver_nonlinear->bisectionMethod();
        std::cout << "Ітерацій: " << solver_nonlinear->getIterationCount() << std::endl;
        std::cout << std::endl;

        std::cout << "===  Метод Ньютона (нелінійне)  ===\n";
        solver_nonlinear->newtonMethod();
        std::cout << "Ітерацій: " << solver_nonlinear->getIterationCount() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Помилка при розв'язанні нелінійного рівняння: " << e.what() << std::endl;
    }
    delete solver_nonlinear;
    solver_nonlinear = nullptr;
    std::cout << "\n=========================================================\n\n";

    std::cout << "========== РОЗВ'ЯЗАННЯ КВАДРАТНОГО РІВНЯННЯ =========\n";

    double qa = 1.0;
    double qb = -3.0;
    double qc = 2.0;

    auto f_lambda_quadratic = [qa, qb, qc](double x) -> double {
        return qa * x * x + qb * x + qc;
    };

    std::cout << "Розв'язуємо квадратне рівняння: "
              << qa << "x^2 + (" << qb << ")x + (" << qc << ") = 0 "
              << "за допомогою методів для нелінійних рівнянь.\n\n";

    solveQuadraticDirectly(qa, qb, qc);


    EquationSolver* solver_quadratic = new EquationSolver(f_lambda_quadratic);
    double eps_q = 1e-5;

    std::cout << "\n--- Пошук першого кореня квадратного рівняння (очікується x=1) ---\n";
    double a1_q = 0.0;
    double b1_q = 1.5;
    try {
        solver_quadratic->setParameters(a1_q, b1_q, eps_q);
        std::cout << "Інтервал: [" << a1_q << ", " << b1_q << "], Точність: " << eps_q << "\n";

        std::cout << "===  Метод бісекції (квадратне, корінь 1)  ===\n";
        solver_quadratic->bisectionMethod();
        std::cout << "Ітерацій: " << solver_quadratic->getIterationCount() << std::endl;
        std::cout << std::endl;

        std::cout << "===  Метод Ньютона (квадратне, корінь 1)  ===\n";
        solver_quadratic->newtonMethod();
        std::cout << "Ітерацій: " << solver_quadratic->getIterationCount() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Помилка при пошуку першого кореня квадратного рівняння: " << e.what() << std::endl;
    }

    std::cout << "\n--- Пошук другого кореня квадратного рівняння (очікується x=2) ---\n";
    double a2_q = 1.5;
    double b2_q = 3.0;
    try {

        solver_quadratic->setParameters(a2_q, b2_q, eps_q);
        std::cout << "Інтервал: [" << a2_q << ", " << b2_q << "], Точність: " << eps_q << "\n";

        std::cout << "===  Метод бісекції (квадратне, корінь 2)  ===\n";
        solver_quadratic->bisectionMethod();
        std::cout << "Ітерацій: " << solver_quadratic->getIterationCount() << std::endl;
        std::cout << std::endl;

        std::cout << "===  Метод Ньютона (квадратне, корінь 2)  ===\n";
        solver_quadratic->newtonMethod();
        std::cout << "Ітерацій: " << solver_quadratic->getIterationCount() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Помилка при пошуку другого кореня квадратного рівняння: " << e.what() << std::endl;
    }

    delete solver_quadratic;
    solver_quadratic = nullptr;
    std::cout << "=========================================================\n";

    return 0;
}