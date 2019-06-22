#include <stdio.h>
struct Date {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
};

typedef Date date;
struct Consulta {
    int codigo;
    date data;
    medico m;
    paciente p;
};
typedef struct Consulta consulta;

// Função recebe o nome do paciente e retorna
// todas as consultas
void localiza_consultas(FILE * f, char nome[50])
{
    int posicao = -1, achou = 0, indice = -1;

    consulta con;
    fseek(f,0, SEEK_SET);
    fread(&con, sizeof(con), 1, f);

    while(!feof(f) && !achou)
    {
        posicao++;
        // compara com o nome do paciente
        if (con.p.nome == nome)
        {
          printf ("nome do médico: %s", con.m.nome);
          printf ("especialidade: %s", con.m.especialidade);
          printf ("data: %s", con.data.dia + "/" + con.data.mes + "/" + con.data.ano);

        }
        fread(&con, sizeof(con), 1, f);
    }

}
