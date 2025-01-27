#include "tests.h"

bool compareDouble(double a, double b)
{
    double diff = a - b;
    if (diff < 0) diff = -diff;

    double error = std::max(1e-4, std::max(a, b) * 1e-4);

    return diff < error;
}

void tests_calculator() {
    Calculator calc;

    assert(compareDouble(calc.calc(".10"), 0.1));
    assert(compareDouble(calc.calc("(1.)"), 1.0));
    assert(compareDouble(calc.calc("2.0 ^ 2. ^ 3.0"), 256.0));
    assert(compareDouble(calc.calc("13. / 2.0"), 6.5));
    assert(compareDouble(calc.calc("((4. - 1.0) / ((2.) - 1.0))"), 3.0));

    assert(compareDouble(calc.calc("500"), 500.0));
    assert(compareDouble(calc.calc("1 + 0"), 1.0));
    assert(compareDouble(calc.calc("2 + 3"), 5.0));
    assert(compareDouble(calc.calc("7 - 4"), 3.0));
    assert(compareDouble(calc.calc("7 * 4"), 28.0));
    assert(compareDouble(calc.calc("798 * 0"), 0.0));
    assert(compareDouble(calc.calc("10 / 2"), 5.0));
    assert(compareDouble(calc.calc("7 / 2"), 3.5));
    assert(compareDouble(calc.calc("8 / 2 * 3 - 4 * 5 + 6"), -2.0));

    assert(compareDouble(calc.calc("-5"), -5.0));
    assert(compareDouble(calc.calc("-(8 + 9)"), -17.0));
    assert(compareDouble(calc.calc("-(2)"), -2.0));
    assert(compareDouble(calc.calc("-(-11)"), 11.0));

    assert(compareDouble(calc.calc("(65 + 3) * 4"), 272.0));
    assert(compareDouble(calc.calc("(14 - 4) * (9 + 159)"), 1680.0));

    assert(compareDouble(calc.calc("8 ^ 2"), 64.0));
    assert(compareDouble(calc.calc("4 ^ 0.5"), 2.0));
    assert(compareDouble(calc.calc("-2 ^ 2"), -4.0));
    assert(compareDouble(calc.calc("-(2 ^ 2)"), -4.0));
    assert(compareDouble(calc.calc("(-2) ^ 2"), 4.0));

    assert(compareDouble(calc.calc("65 + 3 * 6 - 5"), 78.0));
    assert(compareDouble(calc.calc("(1 + 98) ^ 2 - 4 / 2"), 9799.0));
    assert(compareDouble(calc.calc("23 + 4 * (76 - 37) ^ 3 / 90"), 2659.4));

    assert(compareDouble(calc.calc("0.5 + 0.5"), 1.0));
    assert(compareDouble(calc.calc("1.7 * 3.4"), 5.78));

    assert(compareDouble(calc.calc("(((10. * 2.) + (3.5 - 1.5)) / (4. + 2.0)) ^ 2.0"), 13.4444444444));
    assert(compareDouble(calc.calc("(((5.5 * (3.5 + 1.5)) - 7.) / (2. + 3.0)) * (4.0 + 2.)"), 24.6));
    assert(compareDouble(calc.calc("((3.0 ^ 3.0) + (2. ^ 4.)) ^ (1.0 / 2.)"), 6.5574385243));
    assert(compareDouble(calc.calc("(((8.8 ^ 2.0) ^ 2.0) + (2.9 ^ 3.0)) ^ 2.0"), 3.62566e+07));
    assert(compareDouble(calc.calc("-(11.0 ^ 2.0) + ((-67.0) * (34.0 ^ 3.0)) - ((-5.0) / (6.7 ^ 2.)) + ((-6.) * (2. ^ 4.0))"), -2633584.88862));

    assert(compareDouble(calc.calc("((23 * 15) + 129) / (56 ^ 2) - 75"), -74.8489));
    assert(compareDouble(calc.calc("959 * (33 + 58) - (137 ^ 3) + 9999"), -2474085));
    assert(compareDouble(calc.calc("- (859 * 36) + 10 ^ 5 / 3729 - (2749 - 6789)"), -26857.183159));
    assert(compareDouble(calc.calc("(54 + 32) * 111 + (8472 / 296) - 6392 ^ 2"), -40848089.3784));
    assert(compareDouble(calc.calc("(99 ^ 4) / (10 ^ 2) + (5834 - 4021)"), 962409.01));
    assert(compareDouble(calc.calc("-1500 + (200 * 25) ^ 2 / 4862"), 3641.91690662));
    assert(compareDouble(calc.calc("1749 * (2 ^ 5) - 6529 + (7307 / 12)"), 50047.9166667));

    assert(compareDouble(calc.calc("123456789 * 987654321"), 1.21933e+17));
    assert(compareDouble(calc.calc("1000000000000 / 250000000"), 4000));
    assert(compareDouble(calc.calc("987654321 + 123456789"), 1.11111e+09));
    assert(compareDouble(calc.calc("1000000000000 + 999999999999"), 2e+12));
    assert(compareDouble(calc.calc("1000000000000 - 500000000000"), 5e+11));
    assert(compareDouble(calc.calc("1000000000000000 / 200000000"), 5e+6));
    assert(compareDouble(calc.calc("1234567890 * 987654321"), 1.2193263e+18));
    assert(compareDouble(calc.calc("500000000000000000000 / 5"), 1e+20));
    assert(compareDouble(calc.calc("5432109876543210 + 987654321987654"), 6.4197642e+15));
    assert(compareDouble(calc.calc("1000000000000000000000 / 9999999999"), 1e+11));

    std::cout << "All tests passed successfully!" << std::endl;
}