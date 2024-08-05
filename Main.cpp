#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

// Structure to hold option data
struct Option {
    double strike;
    double price;
};

// Function to compute the second derivative numerically for irregular intervals
double secondDerivative(const std::vector<Option>& options, int index) {
    if (index <= 0 || index >= options.size() - 1) {
        throw std::out_of_range("Index out of range for second derivative computation");
    }

    double K1 = options[index - 1].strike;
    double K2 = options[index].strike;
    double K3 = options[index + 1].strike;

    double C1 = options[index - 1].price;
    double C2 = options[index].price;
    double C3 = options[index + 1].price;

    double h1 = K2 - K1;
    double h2 = K3 - K2;

    // Formula for the second derivative with irregular intervals
    return (2.0 / (h1 + h2)) * ((C3 - C2) / h2 - (C2 - C1) / h1);
}

int main() {
    // Risk-free interest rate
    double r = 0.05;
    // Time to maturity in years
    double T = 1.0;

    // Example option data (strike price and corresponding call option price)
    std::vector<Option> options = {
        {90, 10.0},
        {92.5, 9.0},
        {95, 8.0},
        {97.5, 7.0},
        {100, 6.0},
        {102.5, 5.0},
        {105, 4.0},
        {107.5, 3.0},
        {110, 2.0}
    };

    // Calculate the risk-neutral probability density function
    std::vector<double> pdf(options.size(), 0.0);
    for (int i = 1; i < options.size() - 1; ++i) {
        double secondDeriv = secondDerivative(options, i);
        pdf[i] = exp(r * T) * secondDeriv;
    }

    // Print the results
    std::cout << "Strike Price\tPDF\n";
    for (int i = 0; i < options.size(); ++i) {
        std::cout << options[i].strike << "\t\t" << pdf[i] << "\n";
    }

    return 0;
}
