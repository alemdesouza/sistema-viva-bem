//
#include <stdio.h>

struct Medico {
  
    int codigo;
    char nome [50];
    char telefone [11];
    char especialidade [40];
};
typedef struct Medico medico;



int localiza_codigo_medico (FILE *f,int cod)
{
    int posicao=-1,achou=0;
    medico m;
    fseek(f,0,SEEK_SET);
    fread(&m, sizeof(m),1, f);
    while (!feof(f) && !achou)
    {
        posicao++; // semelhante a posicao = posicao +1;
        if (m.codigo == cod)
        {
            achou=1;
        }
        fread(&m, sizeof(m),1, f);
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

void cadastro_medico (FILE *f){
    medico m;
    
    int posicao;
    
    //lendo os dados do teclado
    
    printf("Digite um código: ");
    fflush(stdin);
    
    scanf("%d",&m.codigo);
    
    posicao=localiza_codigo_medico(f,m.codigo);
    if (posicao==-1) //não tinha codigo no arquivo
    {
        printf("Digite um nome: ");
        fflush(stdin);
        gets(m.nome);
        
        printf("\nDigite a especialidade médica em letras maiúsculas e sem acentos: ");
        fflush(stdin);
        gets(m.especialidade);
        
        printf("\nPara o telefone, digite 9 números, sem espaço entre eles");
        printf("Digite um telefone: ");
        fflush(stdin);
        gets(m.telefone);
        

        fseek(f,0,SEEK_END); // posicionado o arquivo no fnal
        fwrite(&m, sizeof(m),1,f); //gravando os dados
        fflush(f);
    }
    
}


int main() {

    

    
    printf("Hello, World!\n");
    return 0;
}
