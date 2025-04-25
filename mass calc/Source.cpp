#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

void in(float a[], float b[], float n)
{
    std::ifstream in("Input.csv");
    for (int i = 0; i < n; i++)
    {
        in >> a[i] >> b[i];
    }
}

void mass_calc(float a[], float b[], float n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = a[i] * 3.14 * pow((b[i] / 2), 3) * 4 / 3;
    }
}

void out(float a[], float b[], float n)
{
    mass_calc(a, b, n);
    std::ofstream out("Output.csv");

    for (int i = 0; i < n; ++i)
    {
        out << std::setprecision(1) << a[i] << std::endl;
    }
}

int main()
{
    float n = 6;
    float a[6];
    float b[6];

    in(a, b, n);
    out(a, b, n);

    return EXIT_SUCCESS;
}