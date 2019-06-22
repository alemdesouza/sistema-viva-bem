# Listar médicos por especialidade:
Este arquivo contém a documentação, assinatura, parâmentros de entrada e registro de execução de testes da funcionalidade listar médicos por especialidade.

## Assinatura

1. A função listar médicos será INT.
2. A função recebera o arquivo como parâmentro.
3. A função retornará 0 se forem localizados médicos com a especialidade desejada, ou retornará -1 se não for localizado nenhum médico com esta especialidade.
4. O propósito da função é ler a especialidade e iterar sobre a lista de medicos para apresentar os que são da especialidade lida.
5. Os dados necessários para listar os médicos por especialidade são

- especialidade
- lista de medicos

## Assinatura da Função

int localiza_medico_especialidade(FILE *f);

## Entrada da função
- especialidade
- lista de medicos

## Saída da função
-  imprime todos os dados dos médicos de determinada especialidade 

