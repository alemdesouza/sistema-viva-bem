#include <stdlib.h>

struct Date {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
};
typedef struct Date date;

struct Consulta {
    int codigo;
    medico m;
    paciente p;
    date data;
};
typedef struct Consulta consulta;

void consultas(FILE * f) {

    consulta nova_consulta;
    consulta verificacao;
    int verifica_horario = 0;

    do
    {
        printf("Insira o horário da consulta:\n");
        printf("Dia: ");
        scanf("%d", &nova_consulta.data.dia);
        printf("Mes: ");
        scanf("%d", &nova_consulta.data.mes);
        printf("Ano: ");
        scanf("%d", &nova_consulta.data.ano);
        printf("Hora: ");
        scanf("%d", &nova_consulta.data.hora);
        printf("Minutos: ");
        scanf("%d", &nova_consulta.data.minuto);

        fseek(f, 0, SEEK_SET);
        fread(&verificacao, sizeof(verificacao), 1, f);

        while (!feof(f))
        {
            if (nova_consulta.data.dia == verificacao.data.dia && nova_consulta.data.mes == verificacao.data.mes && nova_consulta.data.ano == verificacao.data.ano)
            {

                if(nova_consulta.data.hora == verificacao.data.hora)
                {
                    if(abs(nova_consulta.data.minuto) - verificacao.data.minuto <= 30 || nova_consulta.data.minuto - verificacao.data.minuto == 0)
                    {
                        printf("\nHorário ocupado, tente outro.\n\n");
                    }
                    else
                    {
                        verifica_horario = 1;
                    }
                }
                else
                {
                    if (nova_consulta.data.hora > verificacao.data.hora)
                    {
                        if(nova_consulta.data.minuto + (60 - verificacao.data.minuto) <= 30)
                        {
                            printf("\nHorário ocupado, tente outro.\n\n");
                        }
                        else
                        {
                            verifica_horario = 1;
                        }
                    }
                    else
                    {
                        if(verificacao.data.minuto + (60 - nova_consulta.data.minuto) < 20)
                        {
                            printf("\nHorário ocupado, tente outro.\n\n");
                        }
                        else
                        {
                            verifica_horario = 1;
                        }
                    }
                }
            }

            fread(&verificacao, sizeof(verificacao), 1, f);
        }
    }
    while (verifica_horario != 1);
}