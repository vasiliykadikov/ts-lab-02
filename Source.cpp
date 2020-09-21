#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <random>

double used_f(double x) {
    return ((1 - x) * (1 - x) + exp(x));
}

double used_g(double x) {
    return sin(5 * x) * used_f(x);
}

int search_N(double q, double P) {
    return (ceil(log(1 - P) / log(1 - q)));
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main() {
    //x=[-2; 4]
    double a = -2;
    double b = 4;
    std::vector<double> P;
    std::vector<double> q;
    int N;
    int max_N_length = 3;
    int max_qP_length = 5;
    int max_f_length = 8;
    int max_g_length = 10;
    for (auto i = 0; i < 10; ++i) {
        P.push_back(0.9 + i / 100.);
        q.push_back(0.005 + i / 100.);
        q.push_back(0.01 + i / 100.);
    }

    std::vector<double> ::iterator it_P = P.begin();
    std::vector<double> ::iterator it_q = q.begin();
    std::map<double, double> values;
    double Xi, Pn, P1;
   for (auto i = 0; i < 20; ++i) {
        for (auto j = 0; j < 10; ++j) {
            N = search_N(*it_q, *it_P);
            for (auto k = 0; k < N; ++k) {
                Xi = fRand(a, b);
                values.insert(std::make_pair(used_f(Xi), Xi));
            }
            P1 = 1 - *it_q;
            Pn = pow(P1, N);
            std::map<double, double> ::iterator it = values.begin();
            std::cout << "\nP = " << *it_P << " q = " << *it_q
                << " N = " << N << " min: " << it->first
                << " P1 = " << P1 << " Pn = " << Pn;
            values.clear();
            ++it_P;
        }
        ++it_q;
        it_P = P.begin();
    }
   std::cout << "\n";
   it_q = q.begin();
    for (auto i = 0; i < 20; ++i) {
        for (auto j = 0; j < 10; ++j) {
            N = search_N(*it_q, *it_P);
            for (auto i = 0; i < N; ++i) {
                Xi = fRand(a, b);
                values.insert(std::make_pair(used_g(Xi), Xi));
            }
            P1 = 1 - *it_q;
            Pn = pow(P1, N);
            std::map<double, double> ::iterator it = values.begin();
            std::cout << "\nP = " << *it_P << " q = " << *it_q
                << " N = " << N << " min: " << it->first
                << " P1 = " << P1 << " Pn = " << Pn;
            values.clear();
            ++it_P;
        }
        ++it_q;
        it_P = P.begin();
    }
    std::cout << "\n";
    system("pause");
    return 0;
}
