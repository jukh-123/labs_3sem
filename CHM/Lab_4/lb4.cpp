



#include </home/jukh/PycharmProjects/atasd/Lab_4/Nonlinear_equation.h>

int main(int argc, char const *argv[])
{
    float interval1[2] = {-3, -2.5};
    float interval2[2] = {1.5, 2};
    Nonlinear_equation s;
    s.half_cut(interval1);
    s.half_cut(interval2);

    s.hord_method(interval1);
    s.hord_method(interval2);

    s.newton_method(interval1);
    s.newton_method(interval2);
    return 0;
}
