# Listar médicos por especialidade:
Este arquivo contém a documentação, assinatura, parâmentros de entrada e registro de execução de testes da funcionalidade listar médicos por especialidade.

## Assinatura

1. A função listar médicos será VOID.
2. A funcção recebera o arquivo como parâmentro.
3. Tendo em vista ser uma função VOID, não tem retorno.
4. O propósito da função é ler a especialidade e iterar sobre a lista de medicos para apresentar os que são da especialidade lida.
5. Os dados necessários para listar os médicos por especialidade são

- especialidade
- lista de medicos

## Código

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
