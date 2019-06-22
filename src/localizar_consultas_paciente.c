#include <stdio.h>


struct Consulta {
    int codigo;
    medico m;
    paciente p;
};
typedef struct Consulta consulta;

// Função recebe o nome do paciente e retorna
// todas as consultas
consulta * localiza_consultas(FILE * f, char nome[50])
{
    int posicao = -1, achou = 0, indice = -1;

    consulta consultas[1000];

    consulta con;
    fseek(f,0, SEEK_SET);
    fread(&con, sizeof(con), 1, f);

    while(!feof(f) && !achou)
    {
        posicao++;
        // compara com o nome do paciente
        if (con.p.nome == nome)
        {
            consultas[++indice] = con;
        }
        fread(&con, sizeof(con), 1, f);
    }

    return consultas;

}

int main(int argc, const char * argv[]) {

    return 0;
}