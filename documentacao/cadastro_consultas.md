# Cadastro de Consultas:
Este arquivo contém a documentação, assinatura, parâmentros de entrada e registro de execução de testes da funcionalidade cadastro de consultas para a Clínica Viva Bem.

## Assinatura

1. A função cadastro de consultas será VOID.
2. A função receberá um arquivo como parâmentro da função menu.
3. Tendo em vista ser uma função VOID, não tem retorno.
4. O propósito da função é ler os campos de cadastro dos dados da consulta e salvar no arquivo.
5. A variável lista-consultas será do tipo array.
6. Os dados necessários para o cadastro da consulta são:

- nome do paciente;
- nome do médico;
- data da cosulta;
- horário da consulta;


## Assinatura da Função
void cadastro_consulta();

## Restrições
- o médico e o paciente devem estar cadastrados;
- intervalos de 30 minutos entre cada consulta;
- duas consultas para cada médico por dia.

## Entrada da função

- nome do paciente;
- nome do médico;
- data da cosulta;
- horário da consulta;


## Saída da função
- Consulta cadastrada no sistema