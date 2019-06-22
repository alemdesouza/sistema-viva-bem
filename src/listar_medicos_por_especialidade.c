#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <locale.h>


int localiza_medico_especialidade(FILE *f)
{
    char especialidade[40];
    printf("Digite uma especialidade para busca: ");
    fflush(stdin);
    gets(especialidade);
    int posicao=-1,achou=0;
    medico m;
    fseek(f,0,SEEK_SET);
    fread(&m, sizeof(m),1, f);
    printf("\nMédicos especializados em %s:\n", especialidade);
    while (!feof(f))
    {
        posicao++; // semelhante a posicao = posicao +1;
        if (strcmp(m.especialidade,especialidade)==0)
        {
            printf("Código....:%d \n",m.codigo);
            printf("Nome.:%s \n",m.nome);
            printf("Telefone.....:%s\n",m.telefone);
            printf("Especialidade.....:%s\n",m.especialidade);
            achou=1;
        }
        fread(&m, sizeof(m),1, f);
    }
    if (achou)
    {
        return 0;
    }
    else
    {
        printf("\nEspecialidade não encontrada");
        return -1;
    }
}
