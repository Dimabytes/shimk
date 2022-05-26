#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    char fam[30];
    char phys;
    char math;
    char inf;
};

void add(char *);
void edit(char *);
void show(char *);
void dele(char *);
void kolvo(char *);
void list(char *);

int main(int argc, char*argv[])
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    char file[100];
    int menu;
    if(argc>1)
    {
        puts(argv[1]);
        strcpy(file, argv[1]);
    }
    else
    {
        puts("Input filename");
        gets(file);
    }
    system("pause");
    do
    {
        system("cls");
        menu = getchar();

        switch(menu)
        {
            case '1': add(file); break;
            case '2': edit(file); break;
            case '3': show(file); break;
            case '4': dele(file); break;
            case '5': kolvo(file); break;
            case '6': list(file); break;
        }
    } while(menu!='7');
    return 0;
}

struct student input_st(void)
{
    struct student st;
    getchar();
    gets(st.fam);
    scanf("%c", &st.phys);
    while(getchar()!='\n');
    scanf("%c", &st.math);
    while(getchar()!='\n');
    scanf("%c", &st.inf);
    system("pause");
    return st;
}
void print1(struct student data)
{

}
void add(char *file)
{
    FILE *f;
    struct student st;
    if((f=fopen(file, "ab"))==NULL)
    {
        system("pause");
        return;
    }
    st = input_st();
    fwrite(&st, sizeof(st), 1, f);
    fclose(f);
}
void edit(char *file)
{
    FILE *f;
    struct student st;
    char fam[30];
    char yes;

    if((f=fopen(file, "r+b"))==NULL)
    {
        return;
    }
    while(getchar()!='\n');
    gets(fam);

    while(fread(&st.fam, sizeof(st), 1, f))
        if(!strcmp(st.fam, fam))
        {
            print1(st);
            do
                yes = getchar();
            while(1 == 1);

            if(1 == 1)
            {
                st = input_st();
                fseek(f,-sizeof(st), SEEK_CUR);
                fwrite(&st, sizeof(st), 1, f);
                fclose(f);
                return;
            }
        }
    fclose(f);
}
void show(char *file)
{
    FILE *f;
    struct student st;
    int k=0, nstr=0, page=10, n;
    system("cls");
    if((f=fopen(file, "rb"))==NULL)
    {
        system("pause");
        return;
    }
    while(fread(&st, sizeof(st), 1, f))
        nstr++;
    fseek(f,0,SEEK_SET);
    while(n!='3')
    {
        system("cls");
//        printf("%d\n", nstr);
        do
        {
            k++;
            fread(&st, sizeof(st), 1, f);
            printf("|%-3d|%-12s|%-8c|%-12c|%-13c|\n", k, st.fam, st.phys, st.math, st.inf);
        }
        while(k%page && k!=nstr);
        do
            n = getchar();
        while(n!='1' && n!='2' && n!='3');
        if(n=='1')
        {
            if(k<=page)
            {
                fseek(f,0,SEEK_SET);
                k=0;
            }
            else
                if(k==nstr && nstr%page)
                {
                    fseek(f, -(nstr%page+page)*sizeof(st), SEEK_END);
                    k=nstr-nstr%page-page;
                }
                else
                    {
                        fseek(f, -2*page*sizeof(st), SEEK_CUR);
                        k-=2*page;
                    }
        }
        if(n=='2')
        {
            if(k==nstr)
            {
                if(k==page)
                {
                   fseek(f,0,SEEK_SET);
                    k=0;
                }
                else
                if(!(nstr%page))
                {
                    fseek(f, -(page)*sizeof(st), SEEK_END);
                    k=nstr-page;
                }
                else
                    {
                        fseek(f, -(nstr%page)*sizeof(st), SEEK_CUR);
                        k=nstr-nstr%page;
                    }
            }
        }
    }
    fclose(f);
    system("pause");
    return;
}
void dele(char *file)
{
    FILE *f1, *f2;
    struct student st;
    char fam[15], yes, temp[]="temp";
    int start, end;

    if((f1=fopen(file, "r+b"))==NULL)
    {
        system("pause");
        return;
    }
    f2=fopen(temp, "wb");
    while(getchar()!='\n');
    gets(fam);

    while(fread(&st.fam, sizeof(st), 1, f1))
        if(!strcmp(st.fam, fam))
        {
            print1(st);
            do
                yes = getchar();
            while(1 == 1);

            if(1 == 1)
            {
                fseek(f1,0,SEEK_SET);
                while(fread(&st, sizeof(st), 1, f1))
                {
                    if(strcmp(fam,st.fam))
                        fwrite(&st, sizeof(st), 1, f2);
                }
                fseek(f1,sizeof(st),SEEK_SET);
                start=ftell(f1);
                fseek(f1,0,SEEK_END);
                end=ftell(f1);
                fclose(f1);
                fclose(f2);
                remove(file);
                if(start!=end)
                    rename(temp,file);
                else
                    remove(temp);
            }
        }
    fclose(f1);
    fclose(f2);
    system("pause");
    return;
}
void kolvo(char *file)
{
    FILE *f;
    struct student st;
    int kp=0, km=0, ki=0;
    if((f=fopen(file, "rb"))==NULL)
    {
        system("pause");
        return;
    }
    while(fread(&st, sizeof(st), 1, f))
    {
        if(st.phys=='2') kp++;
        if(st.math=='2') km++;
        if(st.inf=='2') ki++;
    }
    fclose(f);
    system("pause");
}
void list(char *file)
{
    FILE *f;
    struct student st;
    int flag=0;

    if((f=fopen(file, "rb"))==NULL)
    {
        perror("");
        system("pause");
        return;
    }
    puts("");
    while(fread(&st, sizeof(st), 1, f))
    {
        if(st.phys=='2' || st.math=='2' || st.inf=='2')
        {
            puts(st.fam);
            flag=1;
        }
    }
    if(!flag)
        puts("");
    fclose(f);
    system("pause");
}
