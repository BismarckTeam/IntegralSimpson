#include <iostream>
#include <cmath>

// Подынтегральная функция
double f(double x)
{
    return 1/x;
}

// Принимает на вход коэффициенты параболы и пределы интегрирования
// Считает определенный интеграл от квадратичной функции
double integrate_parabola(double a, double b, double c, double low, double high)
{
    return (a/3 * pow(high,3) + b/2 * pow(high, 2) + c*high) - (a/3 * pow(low,3) + b/2 * pow(low,2) + c*low);
}

double integrate(double low, double high)
{
    // шаг интегрирования
    double h=1e-6;
    // Здесь считаем результат
    double sum=0;
    // Проходим с шагом h
    // Важно, что мы выбираем три точки. Между тремя точками оказываются зажат кусок функции шириной в 2h
    // Почти все отрезки интегрирования будут посчитаны дважды
    // При этом крайние отрезки интегрирования, [low; low+h] и [high-h; high] будут посчитаны по одному разу.
    for (double x=low; x+2*h<=high; x=x+h)
    {
        // Рассчитывваем координаты трех точек, лежащих на параболе.
        double x1=x;
        double x2=x+h;
        double x3=x+2*h;
        double y1=f(x1);
        double y2=f(x2);
        double y3=f(x3);

        // Считаем коэффициенты параболы
        double a=(y3-(x3*(y2-y1)+x2*y1-x1*y2)/(x2-x1))/(x3*(x3-x1-x2)+x1*x2);
        double b=(y2-y1)/(x2-x1)-a*(x1+x2);
        double c=(x2*y1-x1*y2)/(x2-x1)+a*x1*x2;

        // Прибавляем к общему результату.
        sum=sum+integrate_parabola(a,b,c,x1,x3);
    }
    // Посчитали еще и крайние маленькие отрезки по методу трапеций
    sum=sum+h*(f(low)+f(low+h))/2;
    sum=sum+h*(f(high-h)+f(high))/2;
    // Т.к площадь под графиком оказалась посчитана дважды, просто делим на два.
    sum=sum/2;
    return sum;
}
using namespace std;

int main()
{
    // Интеграл от 1/x на промежутке от 1 до почти е, 2.718
    // Должен быть равен единице.
    cout << integrate(1,2.718) << endl;
    return 0;
}
