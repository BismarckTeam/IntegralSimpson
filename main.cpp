#include <iostream>
#include <cmath>

// ��������������� �������
double f(double x)
{
    return 1/x;
}

// ��������� �� ���� ������������ �������� � ������� ��������������
// ������� ������������ �������� �� ������������ �������
double integrate_parabola(double a, double b, double c, double low, double high)
{
    return (a/3 * pow(high,3) + b/2 * pow(high, 2) + c*high) - (a/3 * pow(low,3) + b/2 * pow(low,2) + c*low);
}

double integrate(double low, double high)
{
    // ��� ��������������
    double h=1e-6;
    // ����� ������� ���������
    double sum=0;
    // �������� � ����� h
    // �����, ��� �� �������� ��� �����. ����� ����� ������� ����������� ����� ����� ������� ������� � 2h
    // ����� ��� ������� �������������� ����� ��������� ������
    // ��� ���� ������� ������� ��������������, [low; low+h] � [high-h; high] ����� ��������� �� ������ ����.
    for (double x=low; x+2*h<=high; x=x+h)
    {
        // ������������� ���������� ���� �����, ������� �� ��������.
        double x1=x;
        double x2=x+h;
        double x3=x+2*h;
        double y1=f(x1);
        double y2=f(x2);
        double y3=f(x3);

        // ������� ������������ ��������
        double a=(y3-(x3*(y2-y1)+x2*y1-x1*y2)/(x2-x1))/(x3*(x3-x1-x2)+x1*x2);
        double b=(y2-y1)/(x2-x1)-a*(x1+x2);
        double c=(x2*y1-x1*y2)/(x2-x1)+a*x1*x2;

        // ���������� � ������ ����������.
        sum=sum+integrate_parabola(a,b,c,x1,x3);
    }
    // ��������� ��� � ������� ��������� ������� �� ������ ��������
    sum=sum+h*(f(low)+f(low+h))/2;
    sum=sum+h*(f(high-h)+f(high))/2;
    // �.� ������� ��� �������� ��������� ��������� ������, ������ ����� �� ���.
    sum=sum/2;
    return sum;
}
using namespace std;

int main()
{
    // �������� �� 1/x �� ���������� �� 1 �� ����� �, 2.718
    // ������ ���� ����� �������.
    cout << integrate(1,2.718) << endl;
    return 0;
}
