#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>


int pegar_codigo_medico(char nome[50]);
int achar_novo_codigo(FILE *fc);
int pegar_codigo_paciente(char nome[50]);
void menu_medicos();
int localiza_codigo(FILE *f,int cod);
void cadastro_pacientes (FILE *f);
void cadastro_medico ();
int localiza_codigo_medico (FILE *f,int cod);

struct Medico
{
    int codigo;
    char nome [50];
    char telefone [11];
    char especialidade [40];
};
typedef struct Medico medico;

struct Tpaciente
{
    int codigo;
    char nome[70];
    char endereco[100];
    char telefone[9];
    char dia_nasc[2];
    char mes_nasc[2];
    char ano_nasc[4];
};
typedef struct Tpaciente paciente;

struct SConsulta
{
    int codigo_consulta;
    int codigo_medico;
    char nome_medico[50];
    int codigo_paciente;
    char nome_paciente[70];
    int dia;
    int mes;
    int ano;
    int hora;
    int minutos;
};
typedef struct SConsulta consulta;

void cadastrar_consulta()
{
    int verifica_horario, opc;
    FILE *fc;
    fc = fopen("lista_consultas.dat", "a+b");
    consulta nova_consulta, verificacao;
    char nome_paciente[70], nome_medico[50];

    do
    {
        printf("\nDigite o nome completo do paciente: ");
        fflush(stdin);
        gets(nome_paciente);
        nova_consulta.codigo_paciente = pegar_codigo_paciente(nome_paciente);
        if (nova_consulta.codigo_paciente == -1)
        {
            printf("\nPaciente n„o encontrado, tente de novo.\n\n");
            printf("1 - Tentar de novo\n2 - Cancelar consulta\n-->");
            scanf("%d",&opc);
            if (opc == 2)
            {
                return;
            }
        }
    }
    while(nova_consulta.codigo_paciente == -1);
    strcpy(nova_consulta.nome_paciente, nome_paciente);

    do
    {
        printf("\nDigite o nome completo de MÈdico: ");
        fflush(stdin);
        gets(nome_medico);
        nova_consulta.codigo_medico = pegar_codigo_medico(nome_medico);
        if (nova_consulta.codigo_medico == -1)
        {
            printf("\nMÈdico n„o encontrado, tente de novo.\n\n");
            printf("1 - Tentar de novo\n2 - Cancelar consulta\n-->");
            scanf("%d",&opc);
            if (opc == 2)
            {
                return;
            }
        }
    }
    while(nova_consulta.codigo_medico == -1);
    strcpy(nova_consulta.nome_medico, nome_medico);

    int verificar_medico = 0;

    do
    {
        printf("Insira a data da consulta:\n");
        do
        {
            printf("Dia: ");
            scanf("%d",&nova_consulta.dia);
            if (nova_consulta.dia>31||nova_consulta.dia<1)
            {
                printf("Dia inv·lido, tente de novo:\n");
            }
        }
        while (nova_consulta.dia>31||nova_consulta.dia<1);

        do
        {
            printf("MÍs: ");
            scanf("%d",&nova_consulta.mes);
            if (nova_consulta.mes>12||nova_consulta.dia<1)
            {
                printf("MÍs inv·lido, tente de novo:\n");
            }
        }
        while (nova_consulta.mes>12||nova_consulta.dia<1);

        do
        {
            printf("Ano: ");
            scanf("%d",&nova_consulta.ano);
            if (nova_consulta.ano<2019)
            {
                printf("Ano inv·lido, tente de novo:\n");
            }
        }
        while (nova_consulta.ano<2019);


        fseek(fc,0,SEEK_SET);
        fread(&verificacao, sizeof(verificacao),1, fc);
        verificar_medico = 0;
        if (!feof(fc))
        {
            while (!feof(fc))
            {
                if (nova_consulta.dia == verificacao.dia&&nova_consulta.mes == verificacao.mes&&nova_consulta.ano == verificacao.ano&&nova_consulta.codigo_medico == verificacao.codigo_medico)
                {
                    verificar_medico++;
                }
                fread(&verificacao,sizeof(verificacao),1,fc);
            }
        }
        else
        {
            verificar_medico = 0;
        }

        if(verificar_medico<2)
        {
            do
            {
                printf("Insira o hor·rio da consulta:\n");
                do
                {
                    printf("Hora: ");
                    scanf("%d",&nova_consulta.hora);
                    if (nova_consulta.hora>=24||nova_consulta.hora<0)
                    {
                        printf("Hora inv·lido, tente de novo:\n");
                    }
                }
                while (nova_consulta.hora>=24||nova_consulta.hora<0);

                do
                {
                    printf("Minutos: ");
                    scanf("%d",&nova_consulta.minutos);
                    if (nova_consulta.minutos>=60||nova_consulta.minutos<0)
                    {
                        printf("Minutos inv·lidos, tente de novo:\n");
                    }
                }
                while (nova_consulta.minutos>=60||nova_consulta.minutos<0);

                fseek(fc,0,SEEK_SET);
                fread(&verificacao, sizeof(verificacao),1, fc);
                verifica_horario = 0;
                if (!feof(fc))
                {
                    while (!feof(fc))
                    {
                        if (nova_consulta.dia == verificacao.dia&&nova_consulta.mes==verificacao.mes&&nova_consulta.ano==verificacao.ano)
                        {

                            if(nova_consulta.hora==verificacao.hora)
                            {
                                if(abs(nova_consulta.minutos-verificacao.minutos)<30)
                                {
                                    printf("\nHor·rio ocupado, tente outro.\n\n");
                                    printf("1 - Tentar outro\n2 - Cancelar consulta\n-->");
                                    scanf("%d",&opc);
                                    if (opc == 2)
                                    {
                                        return;
                                    }
                                    break;
                                }
                                else
                                {
                                    verifica_horario = 1;
                                    break;
                                }
                            }
                            else
                            {
                                if(nova_consulta.hora>verificacao.hora)
                                {
                                    if(nova_consulta.minutos+(60-verificacao.minutos)<30)
                                    {
                                        printf("\nHor·rio ocupado, tente outro.\n\n");
                                        printf("1 - Tentar outro\n2 - Cancelar consulta\n-->");
                                        scanf("%d",&opc);
                                        if (opc == 2)
                                        {
                                            return;
                                        }
                                        break;
                                    }
                                    else
                                    {
                                        verifica_horario = 1;
                                        break;
                                    }
                                }
                                else
                                {
                                    if(verificacao.minutos+(60-nova_consulta.minutos)<30)
                                    {
                                        printf("\nHor·rio ocupado, tente outro.\n\n");
                                        printf("1 - Tentar outro\n2 - Cancelar consulta\n-->");
                                        scanf("%d",&opc);
                                        if (opc == 2)
                                        {
                                            return;
                                        }
                                        break;
                                    }
                                    else
                                    {
                                        verifica_horario = 1;
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            verifica_horario = 1;
                        }
                        fread(&verificacao,sizeof(verificacao),1,fc);
                    }
                }
                else
                {
                    verifica_horario = 1;
                    break;
                }
            }
            while (verifica_horario != 1);

            nova_consulta.codigo_consulta = achar_novo_codigo(fc);

            system("cls");
            printf("Consulta cadastrada com susseso:\n");
            printf("| CÛdigo: %d | MÈdico: %s | Paciente: %s | Data: %d/%d/%d | Hor·rio: %d:%d |\n", nova_consulta.codigo_consulta, nome_medico, nome_paciente,nova_consulta.dia,nova_consulta.mes,nova_consulta.ano,nova_consulta.hora,nova_consulta.minutos);


            fseek(fc,0,SEEK_END);
            fwrite(&nova_consulta, sizeof(nova_consulta),1,fc);
        }
        else
        {
            printf("Esse mÈdico j· tem duas consultas marcadas nesse dia. Tente outro dia.\n");
        }
    }
    while (verificar_medico >2);
    fclose(fc);
}

int achar_novo_codigo(FILE *fc)
{
    int novo_codigo;
    consulta ultima_consulta;
    fseek(fc,0,SEEK_SET);
    fread(&ultima_consulta, sizeof(ultima_consulta),1, fc);
    if(!feof(fc))
    {
        while (!feof(fc))
        {
            fread(&ultima_consulta, sizeof(ultima_consulta),1, fc);
        }
    }
    else
    {
        novo_codigo = 15000;
        return novo_codigo;
    }
    novo_codigo = ultima_consulta.codigo_consulta + 1;
    return novo_codigo;
}

int pegar_codigo_paciente(char nome[50])
{
    FILE *fp;
    int achou = 0;
    strlwr(nome);
    paciente p;
    fp = fopen("lista_pacientes.dat", "r+b");
    fseek(fp,0,SEEK_SET);
    fread(&p,sizeof(p),1,fp);
    while (!feof(fp)&&!achou)
    {
        strlwr(p.nome);
        if (!strcmp(p.nome, nome))
        {
            achou = 1;
            return p.codigo;
        }
        fread(&p,sizeof(p),1,fp);
    }
    return -1;
}

int pegar_codigo_medico(char nome[50])
{
    FILE *fm;
    int achou = 0;
    strlwr(nome);
    medico m;
    fm = fopen("lista_medicos.dat", "r+b");
    fseek(fm,0,SEEK_SET);
    fread(&m,sizeof(m),1,fm);
    while (!feof(fm)&&!achou)
    {
        strlwr(m.nome);
        if (!strcmp(m.nome, nome))
        {
            achou = 1;
            return m.codigo;
        }
        fread(&m,sizeof(m),1,fm);
    }
    return -1;
}

void listar_consultas()
{
    consulta consulta_lista;
    FILE *fc;
    fc = fopen("lista_consultas.dat", "a+b");
    fseek(fc,0,SEEK_SET);
    fread(&consulta_lista,sizeof(consulta_lista),1,fc);
    if (feof(fc))
    {
        printf("Lista vazia.\n");
    }
    while(!feof(fc))
    {
        printf("| CÛdigo: %d | MÈdico: %s | Paciente: %s     | Data: %d/%d/%d | Hor·rio: %d:%d |\n", consulta_lista.codigo_consulta, consulta_lista.nome_medico, consulta_lista.nome_paciente,consulta_lista.dia,consulta_lista.mes,consulta_lista.ano,consulta_lista.hora,consulta_lista.minutos);
        fread(&consulta_lista,sizeof(consulta_lista),1,fc);
    }
}

void menu_consultas()
{
    setlocale(LC_ALL, "portuguese");
    int opc;
    do
    {
        system("cls");
        printf("--------------------------\n");
        printf("|        Escolha:        |\n");
        printf("--------------------------\n");
        printf("| 1 - Cadastrar consulta |\n");
        printf("| 2 - Editar consulta    |\n");
        printf("| 3 - Listar consultas   |\n");
        printf("| 4 - Voltar             |\n");
        printf("--------------------------\n\n--> ");
        scanf("%d",&opc);
        switch (opc)
        {
        case 1:
            system("cls");
            cadastrar_consulta();
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            listar_consultas();
            system("pause");
            system("cls");
            break;
        case 4:
            break;
        default:
            printf("N˙mero inv·lido, tente de novo.\n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(opc!=4);
    return;
}

void menu_pacientes()
{
    FILE *fp;
    fp = fopen("lista_pacientes.dat", "a+b");
    int opc;
    do
    {
        system("cls");
        printf("--------------------------\n");
        printf("|        Escolha:        |\n");
        printf("--------------------------\n");
        printf("| 1 - Cadastrar paciente |\n");
        printf("| 2 - Voltar             |\n");
        printf("--------------------------\n\n--> ");
        scanf("%d",&opc);
        switch (opc)
        {
        case 1:
            cadastro_pacientes(fp);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            break;
        default:
            printf("N˙mero inv·lido, tente de novo.\n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(opc!=2);
    return;
    fclose(fp);
}

int main()
{
    setlocale(LC_ALL, "portuguese");
    int opc;
    do
    {
        system("cls");
        printf("--------------------------\n");
        printf("|        Escolha:        |\n");
        printf("--------------------------\n");
        printf("| 1 - Consultas          |\n");
        printf("| 2 - MÈdicos            |\n");
        printf("| 3 - Pacientes          |\n");
        printf("| 4 - Sair               |\n");
        printf("--------------------------\n\n--> ");
        scanf("%d",&opc);
        switch (opc)
        {
        case 1:
            menu_consultas();
            break;
        case 2:
            menu_medicos();
            break;
        case 3:
            menu_pacientes();
            break;
        case 4:
            break;
        default:
            printf("N˙mero inv·lido, tente de novo.\n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(opc!=4);
    return 0;
}
