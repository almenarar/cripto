#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int ehprimo(int num);
int menorPrimoDe(int num);
int proximoPrimo(int num);
int decode(int P, int Y);
void writeFile(FILE *file, int first, int second);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Insira somente 2 números primos.\n");
    }
    else if (ehprimo(atoi(argv[1])) == TRUE && ehprimo(atoi(argv[2])) == TRUE)
    {
        int produto = atoi(argv[1]) * atoi(argv[2]);
        int Y = (atoi(argv[1]) - 1) * (atoi(argv[2]) - 1);
        int P = menorPrimoDe(Y);
        int X = decode(P, Y);

        FILE *public = fopen("numcripto.txt", "w");
        FILE *private = fopen("numdescripto.txt", "w");

        writeFile(public, produto, P);
        writeFile(private, produto, X);
        printf("%d-%d-%d-%d\n", produto, Y, P, X);
    }
    else
    {
        printf("Os números informados não são primos.\n");
    }

    return 0;
}

int ehprimo(int num)
{
    int ehprimo = TRUE;
    int lim = num / 2;
    for (int i = 2; i <= lim; i++)
    {
        if (num % i == 0)
        {
            ehprimo = FALSE;
            return ehprimo;
        }
    }
    return ehprimo;
}

int menorPrimoDe(int num)
{
    int i = 2;
    while (num > 1)
    {
        if (num % i == 0)
        {
            num = num / i;
        }
        else
        {
            i = proximoPrimo(i);
        }
    }
    return proximoPrimo(i);
}

int proximoPrimo(int num)
{
    num++;
    while (ehprimo(num) != TRUE)
    {
        num++;
    }
    return num;
}

//solução da equação Px = hY + 1
int decode(int P, int Y)
{
    int h = 1;
    while (((h * Y) + 1) % P != 0)
    {
        h++;
    }
    return ((h * Y) + 1) / P;
}

void writeFile(FILE *file, int first, int second)
{
    char buffer[100];

    sprintf(buffer, "%d", first);
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        putc(buffer[i], file);
    }
    putc('\n', file);
    sprintf(buffer, "%d", second);
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        putc(buffer[i], file);
    }
}
