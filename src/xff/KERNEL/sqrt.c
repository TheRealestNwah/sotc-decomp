extern double __ieee754_sqrt(double x);

double sqrt(double x)
{
    return __ieee754_sqrt(x);
}
