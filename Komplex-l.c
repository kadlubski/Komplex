#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct complex
{
    float real;
    float image;
    float betrag;
    float versor;
};

double str_to_nbr(char *input);
_Bool begin_with_letter(char *input);
_Bool begin_with_nbr(char *input);
_Bool begin_with_signe(char *input);
_Bool begin_with_equals(char *input);

struct complex lesen (char *input1, char *signe, char *input2);
struct complex rechnen (struct complex *spr1, char *signe, struct complex *spr2);
void error ();

void display_cpx(struct complex *cpx);
float get_real(struct complex *cpx);
float get_image(struct complex *cpx);
float get_betrag(struct complex *cpx);
float get_versor(struct complex *cpx);
void fill_cpxr (struct complex *cpx, float re, float im);
void fill_cpxp (struct complex *cpx, float be, float ve);
float deg_rad (float deg);
struct complex add_cpx(struct complex *cpx1, struct complex *cpx2);
struct complex sub_cpx(struct complex *cpx1, struct complex *cpx2);
struct complex mult_cpx(struct complex *cpx1, struct complex *cpx2);
struct complex div_cpx(struct complex *cpx1, struct complex *cpx2);
struct complex C_par(struct complex *cpx1, struct complex *cpx2);
_Bool rad = 1;

int main(int argv, char *argc[])
{
  struct complex cpx1 = lesen(argc[1], argc[2], argc[3]);
  struct complex cpx2 = lesen(argc[5], argc[6], argc[7]);
  struct complex cpxout = rechnen(&cpx1, argc[4], &cpx2);
  display_cpx(&cpxout);
    return 0;
}

void error ()
{
    printf("Syntax Error\n");
}

void display_cpx(struct complex *cpx)
{
    float ve = cpx->versor;
    if (!rad)
    {
        ve = (ve/M_PI)*180;
    }
    printf("Re= %.3lf\n", cpx->real);
    printf("Im= %.3lf\n", cpx->image);
    printf("Be= %.3lf\n", cpx->betrag);
    printf("Ve= %.3lf\n", ve);
}

struct complex lesen (char *input1, char *signe, char *input2)
{
    struct complex out;
    if (signe[0]=='v')
    {
        fill_cpxp(&out, str_to_nbr(input1),str_to_nbr(input2));
    }
    else if (signe[0]=='i' || signe[0]=='j')
    {
        fill_cpxr(&out, str_to_nbr(input1),str_to_nbr(input2));
    }
    return (out);
}

struct complex rechnen (struct complex *spr1, char *signe, struct complex *spr2)
{
    struct complex out;
    if (signe[0]=='+')
    {
        out = add_cpx(spr1, spr2);
    }
    else if (signe[0]=='-')
    {
        out = sub_cpx(spr1, spr2);
    }
    else if (signe[0]=='*')
    {
        out = mult_cpx(spr1, spr2);
    }
    else if (signe[0]=='/')
    {
        out = div_cpx(spr1, spr2);
    }
    else if (signe[0]=='p')
    {
        out = C_par(spr1, spr2);
    }
    return (out);
}


double str_to_nbr(char *input)
{
    int i = 0;
    _Bool com = 0;
    double minus = 1.0;
    long long nbr = 0;
    int mult = 0;
    for (i=0;input[i] != '\0'; i++)
    {
        if (input[i] == '.')
        {
            com = 1;
            continue;
        }
        else if (input[i] == '-')
        {
            minus = -1.0;
            continue;
        }
        if (com)
        {
            mult++;
        }
        nbr *= 10;
        nbr += input[i]-48;
    }
    return ((((double)nbr)/(pow(10.0, (double)mult)))* minus);
}
_Bool begin_with_letter(char *input)
{
    return(((input[0] >= 65) && (input[0] <= 90)) || ((input[0] >= 97) && (input[0] <= 121)));
}
_Bool begin_with_nbr(char *input)
{
    _Bool out = (input[0] == '-') && ((input[1] >= 48) && (input[1] <= 57));
    return(((input[0] >= 48) && (input[0] <= 57)) || out);
}
_Bool begin_with_signe(char *input)
{
    return(((input[0] == 42) || (input[0] == 43) || (input[0] == 45) || (input[0] == 47) || (input[0] == '|')) && (input[1] == '\0'));
}
_Bool begin_with_equals(char *input)
{
    return(input[0] == 61);
}
void fill_cpxr (struct complex *cpx, float re, float im)
{
    _Bool done = 0;
    float ve = 0;
    cpx->real = re;
    cpx->image = im;
    cpx->betrag = sqrt(pow(re,2.0)+pow(im, 2.0));
    if (re >= 0.0)
    {
        ve = atan(im/re);
    }
    else
    {
        ve = atan(im/re)+M_PI;
    }
    while (!done)
    {
        if (ve > (2 * M_PI))
        {
            ve -= 2*M_PI;
        }
        else if (ve < (-2 * M_PI))
        {
            ve += 2*M_PI;
        }
        else
        {
            done = 1;
        }
    }
    cpx->versor = ve;
}
void fill_cpxp (struct complex *cpx, float be, float ve)
{
    _Bool done = 0;
    if (!rad)
    {
        ve = deg_rad(ve);
    }
    while (!done)
    {
        if (ve > (2*M_PI))
        {
            ve -= 2*M_PI;
        }
        else if (ve < (-2*M_PI))
        {
            ve += 2*M_PI;
        }
        else
        {
            done = 1;
        }
    }
    cpx->real = be * cos(ve);
    cpx->image = be * sin(ve);
    cpx->betrag = be;
    cpx->versor = ve;
}
float deg_rad (float deg)
{
    return (deg/180*M_PI);
}
struct complex add_cpx(struct complex *cpx1, struct complex *cpx2)
{
    struct complex out;
    fill_cpxr(&out, cpx1->real + cpx2->real, cpx1->image + cpx2->image);
    return (out);
}
struct complex sub_cpx(struct complex *cpx1, struct complex *cpx2)
{
    struct complex out;
    fill_cpxr(&out, cpx1->real - cpx2->real, cpx1->image - cpx2->image);
    return (out);
}
struct complex mult_cpx(struct complex *cpx1, struct complex *cpx2)
{
    struct complex out;
    fill_cpxp(&out, cpx1->betrag * cpx2->betrag, cpx1->versor + cpx2->versor);
    return (out);
}
struct complex div_cpx(struct complex *cpx1, struct complex *cpx2)
{
    struct complex out;
    fill_cpxp(&out, cpx1->betrag / cpx2->betrag, cpx1->versor - cpx2->versor);
    return (out);
}
struct complex C_par(struct complex *cpx1, struct complex *cpx2)
{
    struct complex cpx;
    struct complex c1;
    fill_cpxr(&c1, 1.0, 0.0);
    struct complex c2;
    c2 = div_cpx(&c1, cpx1);
    struct complex c3;
    c3 = div_cpx(&c1, cpx2);
    c2 = add_cpx(&c2, &c3);
    cpx = div_cpx(&c1, &c2);
    return (cpx);
}
