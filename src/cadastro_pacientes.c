#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <conio.h>
#include <locale.h>

struct Tpaciente //estrutura dos pacientes
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

void cadastro_pacientes (FILE *f)
{
    paciente p;
    int posicao, codigo;
//lendo os dados do teclado
    printf("Digite um código: ");
    fflush(stdin);
    scanf("%d",&p.codigo);
    posicao=localiza_codigo(f,p.codigo);
    if (posicao==-1) //não tinha codigo no arquivo
    {
        printf("Digite o nome completo do paciente: ");
        fflush(stdin);
        gets(p.nome);

        printf("Ex.: R./Av. das Flores 105 APTO 402 Bloco 3");
        printf("Digite um endereço: ");
        fflush(stdin);
        gets(p.endereco);

        printf("\nPara o telefone, digite 9 números, sem espaço entre eles");
        printf("Digite um telefone: ");
        fflush(stdin);
        gets(p.telefone);

        printf("\nPara o dia, digite 2 números, sem espaço entre eles (Ex.: 06)");
        printf("Digite o dia do nascimento: ");
        fflush(stdin);
        gets(p.dia_nasc);

        printf("\nPara o mês, digite 2 números, sem espaço entre eles (Ex.: 01)");
        printf("Digite o mês do nascimento: ");
        fflush(stdin);
        gets(p.mes_nasc);

        printf("\nPara o ano, digite 4 números, sem espaço entre eles (Ex.: 1999)");
        printf("Digite o ano do nascimento: ");
        fflush(stdin);
        gets(p.ano_nasc);

        fseek(f,0,SEEK_END); // posicionado o arquivo no final
        fwrite(&p, sizeof(p),1,f); //gravando os dados na pasta
        fflush(f);

    }
    else
    {
        printf("Paciente %s já existe no arquivo. Inclusão não realiiada!\n",p.nome); // caso o paciente já exista no sistema - localiza por código e informa o nome
    }
}

int localiza_codigo(FILE *f,int cod) // procura no arquivo se já existe o paciente, pelo código informado 
{
    int posicao=-1,achou=0;
    paciente p;
    fseek(f,0,SEEK_SET);
    fread(&p, sizeof(p),1, f);
    while (!feof(f) && !achou)
    {
        posicao++; 
        if (p.codigo==cod)
        {
            achou=1;
        }
        fread(&p, sizeof(p),1, f);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

