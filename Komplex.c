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

struct speicher
{
    char name[25];
    struct complex cpm;
};

int arg_cnt(char *input);
char **arg_arr(char *input);
double str_to_nbr(char *input);
_Bool begin_with_letter(char *input);
_Bool begin_with_nbr(char *input);
_Bool begin_with_signe(char *input);
_Bool begin_with_equals(char *input);
int speicher_exist (struct speicher *spr, char *ziel, int index);
struct complex lesen (char *input1, char *signe, char *input2);
struct complex rechnen (struct speicher *spr1, char *signe, struct speicher *spr2);
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

int main()
{
    int i = 0;
    char *input;
    input = (char *)malloc(100);
    _Bool done = 0;
    char **arg;
    int arg_size = 0;
    struct complex cpx1;
    fill_cpxp(&cpx1, 0.0, 0.0);
    int index = 1;
    struct speicher *spr;
    spr = (struct speicher*)malloc(sizeof(struct speicher));
    strcpy(spr[0].name, "ans");
    spr[0].cpm = cpx1;
    int exist = -1;
    int exist1 = -1;
    int exist2 = -1;
    struct speicher puffer1;
    struct speicher puffer2;
    printf("Ready...\n");

    while (!done)
    {
        fgets(input, 100, stdin);
        arg_size = arg_cnt(input);
        arg = arg_arr(input);

        if ((arg_size>0) && begin_with_letter(arg[0]))
        {
            exist = speicher_exist(spr, arg[0], index);
            if (!strcmp(arg[0],"quit"))
            {
                done = 1;
                continue;
            }
            else if (!strcmp(arg[0],"help"))
            {
                printf("under construction!!!\n");
            }
            else if (!strcmp(arg[0],"clear"))
            {
                system("clear");
            }
            else if (!strcmp(arg[0],"memory"))
            {
                for (i=0; i<index; i++)
                {
                    printf("%d.%s  ", i, spr[i].name);
                }
                printf("\n");
            }
            else if (!strcmp(arg[0],"rad"))
            {
                rad = 1;
            }
            else if (!strcmp(arg[0],"deg"))
            {
                rad = 0;
            }
            else if ((!strcmp(arg[0],"cc")) && (arg_size == 2) && begin_with_letter(arg[1]))
            {
                if ((exist1 = speicher_exist(spr, arg[1], index)) >= 0)
                {
                    fill_cpxr(&spr[exist1].cpm, spr[exist1].cpm.real, -(spr[exist1].cpm.image));
                }
                else
                {
                    error();
                }
            }
            else if ((exist) >= 0 && (arg_size == 1))
            {
                display_cpx(&spr[exist].cpm);
            }
            else if (begin_with_equals(arg[1]))
            {
                if (exist<0)
                {
                    index ++;
                    spr = (struct speicher*)realloc(spr, index * sizeof(struct speicher));
                    strcpy(spr[index-1].name, arg[0]);
                    exist = index - 1;
                }
                if ((arg_size == 5))
                {
                    if (begin_with_nbr(arg[2]) && begin_with_nbr(arg[4]))
                    {
                        spr[0].cpm = lesen(arg[2], arg[3], arg[4]);
                    }
                    else if (begin_with_letter(arg[2]) && begin_with_letter(arg[4]) && begin_with_signe(arg[3]))
                    {
                        if ((exist1 = speicher_exist(spr, arg[2], index)) >=0 && (exist2 = speicher_exist(spr, arg[4], index)) >=0)
                             {
                                spr[0].cpm = rechnen(&spr[exist1], arg[3], &spr[exist2]);
                             }
                    }
                    spr[exist].cpm=spr[0].cpm;
                }
                else if (arg_size == 3)
                {
                    if ((exist1 = speicher_exist(spr, arg[2], index)) >= 0)
                    {
                        spr[exist].cpm = spr[exist1].cpm;
                    }
                    else
                    {
                        error();
                    }
                }
                else
                {
                    error();
                }
            }
            else if (begin_with_signe(arg[1]))
            {
                if ((arg_size == 3))
                {
                    if ((exist1 = speicher_exist(spr, arg[0], index)) >=0 && (exist2 = speicher_exist(spr, arg[2], index)) >=0)
                    {
                        spr[0].cpm = rechnen(&spr[exist1], arg[1], &spr[exist2]);
                        display_cpx(&spr[0].cpm);
                    }
                    else
                    {
                        error();
                    }
                }
                else if ((arg_size == 5))
                {

                }
            }
            else
            {
                error();
            }
        }
        else if ((arg_size>0) && begin_with_nbr(arg[0]))
        {
            if (arg_size == 3)
            {
                if (begin_with_nbr(arg[2]) && begin_with_letter(arg[1]))
                {
                    spr[0].cpm = lesen(arg[0], arg[1], arg [2]);
                    display_cpx(&spr[0].cpm);
                }
                else
                {
                    error();
                }
            }
            else if (arg_size == 5)
            {
                if (begin_with_nbr(arg[2]) && begin_with_signe(arg[3]) && begin_with_letter(arg[4]) && ((exist1 = speicher_exist(spr, arg[4], index))>=0))
                {
                    puffer1.cpm = lesen(arg[0], arg[1], arg[2]);
                    spr[0].cpm = rechnen(&puffer1 ,arg[3], &spr[exist1]);
                    display_cpx(&spr[0].cpm);
                }
                else
                {
                    error();
                }
            }
            else if (arg_size == 7)
            {
                if (begin_with_nbr(arg[2]) && begin_with_nbr(arg[4]) && begin_with_nbr(arg[6]) && begin_with_signe(arg[3]))
                {
                    puffer1.cpm = lesen(arg[0], arg[1], arg[2]);
                    puffer2.cpm = lesen(arg[4], arg[5], arg[6]);
                    spr[0].cpm = rechnen(&puffer1 ,arg[3], &puffer2);
                    display_cpx(&spr[0].cpm);
                }
                else
                {
                    error();
                }
            }
            else
            {
                error();
            }
        }
        else if ((arg_size>0) && begin_with_signe(arg[0]))
        {
            if ((arg_size == 2) && begin_with_letter(arg[1]))
            {
                if ((exist1 = speicher_exist(spr, arg[1], index)) >= 0)
                {
                    spr[0].cpm = rechnen(&spr[0], arg[0], &spr[exist1]);
                    display_cpx(&spr[0].cpm);
                }
                else
                {
                    error();
                }
            }
            else if ((arg_size == 4) && begin_with_nbr(arg[1]) && begin_with_nbr(arg[3]) && begin_with_letter(arg[2]))
            {
                puffer1.cpm = lesen(arg[1], arg[2], arg[3]);
                spr[0].cpm = rechnen(&spr[0], arg[0], &puffer1);
                display_cpx(&spr[0].cpm);
            }
            else
            {
                error();
            }
        }
        else
        {
            error();
        }
        free(arg);
    }
    // free(input);
    // free(spr);
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

struct complex rechnen (struct speicher *spr1, char *signe, struct speicher *spr2)
{
    struct complex out;
    if (signe[0]=='+')
    {
        out = add_cpx(&spr1->cpm, &spr2->cpm);
    }
    else if (signe[0]=='-')
    {
        out = sub_cpx(&(spr1->cpm), &(spr2->cpm));
    }
    else if (signe[0]=='*')
    {
        out = mult_cpx(&(spr1->cpm), &(spr2->cpm));
    }
    else if (signe[0]=='/')
    {
        out = div_cpx(&(spr1->cpm), &(spr2->cpm));
    }
    else if (signe[0]=='|')
    {
        out = C_par(&(spr1->cpm), &(spr2->cpm));
    }
    return (out);
}
int speicher_exist (struct speicher *spr, char *ziel, int index)
{
    int i = 0;
    int out = -1;
    for (i=0; i < index; i++)
    {
        if (!strcmp(spr[i].name, ziel))
        {
            out = i;
        }
    }
    return (out);
}
char **arg_arr(char *input)
{
    int i, j = 0;
    char **arg;
    int cnt = arg_cnt(input);

    arg = malloc(cnt*sizeof(char*));

    for (i=0; i<cnt; i++)
    {
        arg[i] = malloc(25*sizeof(char));
    }

    int cursor = 0;
    for (i=0; i<cnt; i++)
    {
        for (j=0; (input[cursor] != ' ') && (input[cursor] != '\n');j++)
        {
            arg[i][j] = input[cursor];
            cursor++;
        }
        cursor++;
        arg[i][j] = '\0';
    }
    return(arg);
}
int arg_cnt(char *input)
{
    int cnt = 1;
    int i = 0;
    for (i = 0; input[i] != '\n'; i++)
    {
        if (input[i] == ' ')
        {
            cnt++;
        }
    }
return (cnt);
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
