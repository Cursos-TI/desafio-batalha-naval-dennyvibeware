#include <stdio.h>
#include <stdlib.h>


void exibir_tabuleiro(int tabuleiro[10][10]){

    printf("\n## TABULEIRO DE BATALHA NAVAL ##\n");
    printf("=============================== \n");
    printf("  ");
    for (int linha = 0; linha < 10; linha++)
    {
        //imprime letra da coluna
        if (linha==0)
        {
            for(char letra_coluna = 'A'; letra_coluna <= 'J'; letra_coluna++) 
            {
                 printf(" %c ", letra_coluna);
            }
            printf("\n");
        }
        
        printf("%d ", linha+1); // imprime numero da linha
        for(int coluna = 0; coluna < 10; coluna++)
        {               
            if ( (linha==9) && (coluna==0) )
            {
                printf("%d ", tabuleiro[linha][coluna]);
            }
            else
            {
                printf(" %d ", tabuleiro[linha][coluna]);
            }
            
        }
        printf("\n");
    }
}

// valida se o valor digitado da linha ou coluna esta entre 1 e 10
int validar_coordernada(int x)
{
    if(x > 10 || x < 1)
    {
        printf("O valor deve ser entre 1 e 10 \n");
        return 0; // falso
    }
    else
    {
        return 1; // verdadeiro ou ok
    }    
}

// valida se o navio esta dentro do tabuleiro
int validar_navio_tabuleiro(int x)
{
    if( (x+2) > 10){

        printf("Parte do navio esta fora do tabuleiro \n");
        return 0; // falso , nao é valido
    }
    else    
        return 1; // verdadeiro, valido
}


int colisao_navios_tabuleiro(int linha_navio_2, int coluna_navio_2, int tabuleiro[10][10])
{
    int colisao = 0;
    int i = 0; //para percorrer as linhas da matriz
    int j = 0; //para percorrer as colunas da matriz

    for (i = 0; (i < 10) && (colisao == 0 ); i++)
    {
        for(j = 0; (j < 10) && (colisao == 0 ); j++)
        {
            if(tabuleiro[i][j] == 3) // encontrou um navio no tabuleiro
            {  
                if( (i == linha_navio_2) && (j == coluna_navio_2) ) // checa se a coordenada do navio 2 esta na mesma coordenada do navio 1
                {
                    printf("Navio 2 e Navio 1 estao se colidindo: linha %d coluna %d \n", i+1, j+1);
                    colisao = 1;
                    break;
                }
                if(j == coluna_navio_2) // tem um x e esta na mesma coluna do navio 2
                {
                    if (i>linha_navio_2) //navio 2 esta acima do navio 1;
                    { 
                        if(abs(i-linha_navio_2) < 3 ) //checa se existe uma diferença de no minimo 2 linhas entre o navio 2 e o navio 1
                        {
                            printf("Navio 2 e Navio 1, estão se colidindo na coordenada: linha %d coluna %d \n", i+1, j+1);
                            colisao = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    if(colisao){
        return 0;
    }
    else{
        return 1;
    }

}


int main(){

    // -----------------------------------------------------------------------------------------------------------------------------
    
    int linha = 0, coluna = 0; // variaveis usadas para auxiliar a inserir os navios no tabuleiro
    int tabuleiro[10][10] = {0};
    int navio_1[3] = {3}; //navio horizontal
    int navio_2[3] = {3}; //navio vertical
    int posicao_inicial_navio_1[2] = {0,0}; // guarda a coordenada, onde o primeiro elemento do vetor é a linha e o segundo elemento é a coluna
    int posicao_inicial_navio_2[2] = {0,0};

    // valida se a coordenada inserida esta dentro do tabuleiro , 0 = falso, 1 = verdadeiro ou ok
    int validacao_1 = 0;  
    // valida se o navio esta dentro do tabuleiro, 0 = falso, 1 = verdadeiro ou ok
    int validacao_2 = 0; 
    // valida se já existe um navio ocupando aquela posicao
    int validacao_3 = 0; 

    // -----------------------------------------------------------------------------------------------------------------------------

    //ler coordenadas dos navio 1
    printf("NAVIO 1 | POSIÇÃO HORIZONTAL | TAMANHO 3\n");
    do{
        printf("linha inicial do navio 1 (1-10): ");
        scanf("%d", &posicao_inicial_navio_1[0]);
        validacao_1 = validar_coordernada(posicao_inicial_navio_1[0]); // checa se o valor esta entre 1 e 10
    }while(validacao_1 == 0);

    do{
        printf("coluna inicial do navio 1 (1-10): ");
        scanf("%d", &posicao_inicial_navio_1[1]);
        validacao_1 = validar_coordernada(posicao_inicial_navio_1[1]); 
        if(validacao_1)
        {
            validacao_2 = validar_navio_tabuleiro(posicao_inicial_navio_1[1]); // checa se a coluna do navio nao vai deixar ele de fora do tabuleiro
        }
            
    }while( (validacao_1 == 0) || (validacao_2 == 0) ); // enquanto alguma das condicoes forem falsa, continua no loop)
    /* 
    tabela verdade operador ou (||)
    A	B	=  A || B (resultado)
    0	0	=  0 (falso)
    0	1	=  1 (verdadeiro)
    1	0	=  1 (verdadeiro)
    1	1	=  1 (verdadeiro)
    */
    
    //insere o navio 1 no tabuleiro
    linha = posicao_inicial_navio_1[0]; // retorna linha 
    linha--; //diminui 1 por que a linha começa do zero
    coluna = posicao_inicial_navio_1[1]; // retorna coluna 
    coluna--;
    for(int i = 0; i < 3; i++)
    {
        tabuleiro[linha][coluna+i] = 3;
    }
    
    // -----------------------------------------------------------------------------------------------------------------------------
    
    //ler coordenadas dos navio 2
    //para a leitura da coordenada (linha e coluna) checar se ñ tem um navio naquela posição no tabuleiro
    printf("NAVIO 2 | POSIÇÃO VERTICAL | TAMANHO 3\n");
    do{
        printf("linha inicial do navio 2 (1-10): ");
        scanf("%d", &posicao_inicial_navio_2[0]);
        validacao_1 = validar_coordernada(posicao_inicial_navio_2[0]); // checa se o valor esta entre 1 e 10 
        if(validacao_1)
        {
            // checa se a linha do navio nao vai deixar ele de fora do tabuleiro
            // considerando que a direção do navio, a extensão dele esta indo para baixo
            validacao_2 = validar_navio_tabuleiro(posicao_inicial_navio_2[0]); 
        }
        if(validacao_1 && validacao_2){
            printf("coluna inicial do navio 2 (1-10): ");
            scanf("%d", &posicao_inicial_navio_2[1]);
            validacao_1 = validar_coordernada(posicao_inicial_navio_2[1]); 
            int linha = posicao_inicial_navio_2[0];
            int coluna = posicao_inicial_navio_2[1];
            validacao_3 = colisao_navios_tabuleiro(linha-1, coluna-1, tabuleiro);
        }
    }while( (validacao_1 == 0) || (validacao_2 == 0) || (validacao_3 == 0));
    //para sair precisa
    //a) ser um numero entre 1 e 10
    //b) precisa saber se o navio ñ esta fora do tabuleiro
    //c) precisa checar se o navio 2 ñ esta colidindo com o navio 1


    
    // inseri navio 2 no tabuleiro
    linha = posicao_inicial_navio_2[0]; // retorna linha 
    linha--; //diminui 1 por que a linha começa do zero
    coluna = posicao_inicial_navio_2[1]; // retorna coluna 
    coluna--;
    for(int i = 0; i < 3; i++)
    {
        tabuleiro[linha+i][coluna] = 3;
    }

    // desenha tabuleiro
    exibir_tabuleiro(tabuleiro);

    return 0;
}