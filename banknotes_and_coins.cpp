#include <iostream>

int main() {

    float monetary_value;

    std::cin >> monetary_value;

    int total_cents = static_cast<int>(monetary_value * 100 + 0.5);

    std::cout << "NOTAS:" << std::endl;
    int bill_100 = total_cents / 10000;
    total_cents -= bill_100 * 10000;

    int bill_50 = total_cents / 5000;
    total_cents -= bill_50 * 5000;

    int bill_20 = total_cents / 2000;
    total_cents -= bill_20 * 2000;

    int bill_10 = total_cents / 1000;
    total_cents -= bill_10 * 1000;

    int bill_5 = total_cents / 500;
    total_cents -= bill_5 * 500;

    int bill_2 = total_cents / 200;
    total_cents -= bill_2 * 200;

    std::cout << bill_100 << " nota(s) de R$ 100.00\n";
    std::cout << bill_50 << " nota(s) de R$ 50.00\n";
    std::cout << bill_20 << " nota(s) de R$ 20.00\n";
    std::cout << bill_10 << " nota(s) de R$ 10.00\n";
    std::cout << bill_5 << " nota(s) de R$ 5.00\n";
    std::cout << bill_2 << " nota(s) de R$ 2.00\n";

    std::cout << "MOEDAS:" << std::endl;
    int coin_1 = total_cents / 100;
    total_cents -= coin_1 * 100;
    int coin_050 = total_cents / 50;
    total_cents -= coin_050 * 50;
    int coin_025 = total_cents / 25;
    total_cents -= coin_025 * 25;
    int coin_010 = total_cents / 10;
    total_cents -= coin_010 * 10;
    int coin_005 = total_cents / 5;
    total_cents -= coin_005 * 5;
    int coin_001 = total_cents / 1;

    std::cout << coin_1 << " moeda(s) de R$ 1.00\n";
    std::cout << coin_050 << " moeda(s) de R$ 0.50\n";
    std::cout << coin_025 << " moeda(s) de R$ 0.25\n";
    std::cout << coin_010 << " moeda(s) de R$ 0.10\n";
    std::cout << coin_005 << " moeda(s) de R$ 0.05\n";
    std::cout << coin_001 << " moeda(s) de R$ 0.01\n";

    return 0;
}