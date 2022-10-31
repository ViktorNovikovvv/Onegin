#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

int main()
{
//функция создания буфера
struct stat SizeOfFile;
 stat("Hamlet.TXT", &SizeOfFile);
 char * Buf = (char *)calloc(SizeOfFile.st_size + 1, sizeof(char));
//конец функции создания буферв
FILE *fp = fopen("Hamlet.TXT", "r");
//функция считывает все символы в буфер
fread(Buf, sizeof(char),SizeOfFile.st_size, fp);
//конец функции

//создание массива указателей
int NumbOfStr = 1;
for(int i = 0; i < SizeOfFile.st_size; i++)
{
    if( *(Buf + i) == '\n')     //TODO '\n' = '\0'
    NumbOfStr++;
}

char *PtrToStr[NumbOfStr];      //TODO calloc
PtrToStr[0] = Buf;

for(int i = 0; i < SizeOfFile.st_size; i++)
{
    int Str = 1;
    if( *(Buf + i) == '\n') //'\n' = '\0' change pointers
        {
        PtrToStr[Str] = Buf + i;
        Str++;
        }
}
//конец создания массива указателей

//сортировка указателей
for(int Str = 0; Str < NumbOfStr - 1; Str++) //TODO change sort
{   
    int NumbOfSymb = 0;
    while(PtrToStr[Str][NumbOfSymb] != '\n' && (PtrToStr[Str+1][NumbOfSymb] != '\n' && PtrToStr[Str+1][NumbOfSymb] != EOF))
    {
        if(isalpha(PtrToStr[Str][NumbOfSymb]) && isalpha(PtrToStr[Str+1][NumbOfSymb]))
        {
            if(strcmp(PtrToStr[Str] + NumbOfSymb, PtrToStr[Str+1] + NumbOfSymb) < 0)
            {
                char *Change = PtrToStr[Str];
                PtrToStr[Str] =  PtrToStr[Str + 1];
                PtrToStr[Str + 1] = PtrToStr[Str];
                break;
            }
        }
        else
        {
            NumbOfSymb++;
        }

    }

}
//конец сортировки указателей


//вывод строк через массив указателей
FILE *ffp = fopen("SortHamlet.TXT", "w");
for(int i = 0; i < NumbOfStr; i++)
{
    int NumbOfSymb = 0;
    while(PtrToStr[i][NumbOfSymb] != '\n')
    {
        fprintf(ffp,"%c", PtrToStr[i][NumbOfSymb]);
    }
    fprintf(fp, "\n");
}
//конец функции
    return 0;
}