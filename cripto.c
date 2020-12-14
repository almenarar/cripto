/*
cripto:
- função de criptografia
- função de descriptografia
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void criptografa();
void decriptografa();
void lerCriptoFile(FILE *file, int *P, int *X);
int calculo(int base, int pot, int resto);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Insira somente -d para decodificar ou -c para codificar.\n");
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        decriptografa();
    }
    else if (strcmp(argv[1], "-c") == 0)
    {
        criptografa();
    }
    else
    {
        printf("Insira -d para decodificar ou -c para codificar.\n");
    }
}

void criptografa()
{
    int P = 0, X = 0;
    FILE *public = fopen("numcripto.txt", "r");
    lerCriptoFile(public, &P, &X);

    int c;
    while ((c = getchar()) != EOF)
    {
        printf("%d ", calculo(c, X, P));
    }
}

void decriptografa()
{
    int P = 0, X = 0;
    FILE *private = fopen("numdescripto.txt", "r");
    lerCriptoFile(private, &P, &X);

    int c, num, i = 0;
    char buffer[100];
    while ((c = getchar()) != EOF)
    {
        if (c != ' ')
        {
            buffer[i] = c;
            i++;
        }
        else
        {
            buffer[i] = '\0';
            num = atoi(buffer);
            printf("%c ", calculo(num, X, P));
            i = 0;
        }
    }
}

int calculo(int base, int pot, int resto)
{
    int i = 0;
    int final = 1;
    int result[100];
    int arr[100];
    while (pot > 0)
    {
        arr[i] = pot % 2;
        pot /= 2;
        i++;
    }

    result[0] = base % resto;
    for (int j = 1; j < i; j++)
    {
        result[j] = (result[j - 1] * result[j - 1]) % resto;
    }

    for (int j = 0; j < i; j++)
    {
        if (arr[j] != 0)
        {
            final *= result[j];
        }
    }

    return final % resto;
}

void lerCriptoFile(FILE *file, int *P, int *X)
{
    int c, i = 0;
    int primeiraPalavra = TRUE;
    char produto[100], pot[100];
    while ((c = getc(file)) != EOF)
    {
        if (c == '\n')
        {
            produto[i] = '\0';
            primeiraPalavra = FALSE;
            i = 0;
        }
        if (primeiraPalavra == TRUE)
        {
            produto[i] = c;
            i++;
        }
        else
        {
            pot[i] = c;
            i++;
        }
    }
    pot[i] = '\0';
    *P = atoi(produto);
    *X = atoi(pot);
}