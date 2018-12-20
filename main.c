#include <stdio.h>
#include <stdlib.h>

void ouvrirfichier()
{
    int c;
    FILE*fi;

    //pointeur sur fichier
    FILE* f = fopen("test.txt", "r");

    //affichage du fichier
    if(f != NULL)
    {
        fi=fopen("test.txt", "r+"); //chemin où le fichier est situé


        while((c = fgetc(fi)) !=EOF)
        {
        printf("%c", c);
        }
    }
    //si le fichier est introuvlable
    else
        {
        printf("Le fichier est inexistant ou introuvable");
        }

    fclose(f);
    system("pause");
}

int main()
{
    ouvrirfichier();
    return 0;
}

