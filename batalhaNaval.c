#include <stdio.h>
#include <stdlib.h>

#define linha_tab 10 
#define coluna_tab 10
#define tamanho_navio 3

int tabuleiro [linha_tab][coluna_tab]; 

void exibir_tabuleiro(){

    printf("\n## TABULEIRO DE BATALHA NAVAL ##\n");
    printf("=============================== \n");
    printf("  ");
    for (int linha = 0; linha < 10; linha++)
    {
        //imprime letra da coluna
        if (linha==0)
        {
            for(int indice_coluna = 1; indice_coluna < 11 ; indice_coluna++) 
            {
                 printf(" %d ", indice_coluna);
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

void inserir_navio(int linha, int coluna, int opcao)
{
    switch(opcao)
    {
        case 1: // inseri navio horizontal
            for(int i = 0; i < tamanho_navio; i++)
            {
                tabuleiro[linha][coluna+i] = 3;
            }
            break;
        case 2: // inseri navio vertical
            for(int i = 0; i < tamanho_navio; i++)
            {
                tabuleiro[linha+i][coluna] = 3;
            }
            break;
        case 3: // inserir navio diagonal direita
            for(int i = 0; i < tamanho_navio; i++)
            {
                tabuleiro[linha+i][coluna+i] = 3;
            }
            break;
        case 4: // inseri navio diagonal esquerda
            for(int i = 0; i < tamanho_navio; i++)
            {
                tabuleiro[linha+i][coluna-i] = 3;
            }
            break;
        default:
            printf("Opcao invalida\n");
            break;
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
int validar_navio_tabuleiro_diagonal_esquerda(int x){

    if (x > 2)
    {   
        printf("Parte do navio esta fora do tabuleiro \n");
        return 0; // falso , nao é valido
    }
    else    
        return 1; // verdadeiro, valido

}

int validar_navio_tabuleiro(int x, int opcao)
{

    switch (opcao) 
    {
        case 1:
        case 2:
        case 3:
            if( (x-1+tamanho_navio) > 10)
            {
                printf("Parte do navio esta fora do tabuleiro \n");
                return 0; // falso , nao é valido
            }
            else    
            {
                return 1; // verdadeiro, valido
            }
            break;
        case 4:   
            if (x < 2)
            {
                printf("Parte do navio esta fora do tabuleiro \n");
                return 0; // falso , nao é valido
            }
            else
            {
                return 1; // verdadeiro, valido
            }
            break;  
        default:
            break;
    }
}

// checa colisão para navios do tipo horizontal
int colisao_navio(int linha, int coluna, int opcao)
{
    int colisao = 0;

    switch(opcao) 
    {
        case 1: //verifica colisao navio horizontal
            for(int i = 0; (i < tamanho_navio) && (colisao == 0) ; i++)
            {
                if(tabuleiro[linha][coluna+i] == 3) 
                {
                    colisao  = 1; // encontrou colisão
                    printf("Os navios estão se colidindo escolha outra coordenada \n");
                    break;
                }
            }
            break;
        case 2: // verifica colisao navio vertical
            for(int i = 0; (i < tamanho_navio) && (colisao == 0) ; i++)
            {
                if(tabuleiro[linha+i][coluna] == 3) 
                {
                    colisao  = 1; // encontrou colisão
                    printf("Os navios estão se colidindo escolha outra coordenada \n");
                    break;
                }
            }
            break;
        case 3: // verifica colisão navio diagonal direita
            for(int i = 0; (i < tamanho_navio) && (colisao == 0) ; i++)
            {
                if(tabuleiro[linha+i][coluna+i] == 3) 
                {
                    colisao  = 1; // encontrou colisão
                    printf("Os navios estão se colidindo escolha outra coordenada \n");
                    break;
                }

                /* 
                checa se um navio 3 3 3 diagonal direito esta se chocando com um navio 4 4 4 diagonal esquerda, pois eles ñ podem se cruzar

                caso 1: navio 3, uma coluna antes da coluna inicial do navio 4
                0 0 0 0 0 0 0 0 0 
                0 0 0 0 0 0 0 0 0 
                0 0 0 0 3 4 0 0 0 
                0 0 0 0 4 3 0 0 0 
                0 0 0 4 0 0 3 0 0 
                0 0 0 0 0 0 0 0 0 
                
                caso 2: navio 3, duas coluna antes da coluna inicial do navio 4
                0 0 0 0 0 0 0 0 0 
                0 0 0 3 0 0 0 0 0 
                0 0 0 0 3 4 0 0 0 
                0 0 0 0 4 3 0 0 0 
                0 0 0 4 0 0 0 0 0 
                0 0 0 0 0 0 0 0 0 

                0 0 0 0 0 0 0 0 0 
                0 0 0 0 0 0 0 0 0 
                0 0 0 0 0 4 0 0 0 
                0 0 0 3 4 0 0 0 0 
                0 0 0 4 3 0 0 0 0 
                0 0 0 0 0 3 0 0 0 
                0 0 0 0 0 0 0 0 0 

                caso 2: navio 3, 3 coluna antes da coluna inicial do navio 4

                0 0 0 0 0 0 0 0 0 
                0 0 0 0 0 0 0 0 0 
                0 0 3 0 0 4 0 0 0 
                0 0 0 3 4 0 0 0 0 
                0 0 0 4 3 0 0 0 0 
                0 0 0 0 0 0 0 0 0 
                0 0 0 0 0 0 0 0 0 

                if (tabuleiro[linha+i][coluna+i+1] == 3) // 
                {
                    //antes de inserir o navio 3 eu preciso saber se o navio 4 é um navio vertical ou horizontal
                    int aux = 0;
                    for (j=0; j < 3; j++){
                        if(tabuleiro[linha+i-1][coluna+i+1] == 3) 
                            aux = 1;
                        if(tabuleiro[linha+i+1][coluna+i+1] == 3)
                            aux = 1;
                        if(tabuleiro[linha+i][coluna+i+1] == 3)
                            aux = 1;
                        if(tabuleiro[linha+i][coluna+i+1] == 3)
                            aux = 1;
                        
                    }
                }
                */
            }
            break;
        case 4: // verifica colisão navio diagonal esquerda
            for(int i = 0; (i < tamanho_navio) && (colisao == 0) ; i++)
            {
                if(tabuleiro[linha+i][coluna-i] == 3) 
                {
                    colisao  = 1; // encontrou colisão
                    printf("Os navios estão se colidindo escolha outra coordenada \n");
                    break;
                }
            }
            break;
        default:
            printf("Opcao invalida\n");
            break;
    }

    if(colisao)
    {
        return 0; // se existe colisao, joga 0 para a variavel validacao_3, ou seja nao valida 
    }else
    {
        return 1;
    }
    
}

/*
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
                    printf("Navios estao se colidindo: linha %d coluna %d \n", i+1, j+1);
                    colisao = 1;
                    break;
                }
                if(j == coluna_navio_2) // tem um x e esta na mesma coluna do navio 2
                {
                    if (i>linha_navio_2) //navio 2 esta acima do navio 1;
                    { 
                        if(abs(i-linha_navio_2) < 3 ) //checa se existe uma diferença de no minimo 2 linhas entre o navio 2 e o navio 1
                        {
                            printf("Navios estão se colidindo na coordenada: linha %d coluna %d \n", i+1, j+1);
                            colisao = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    if(colisao){
        return 0; // se identificou uma colisão retorna o valor 0 (falso) para a variavel validacao_3
    }
    else{
        return 1;
    }

}

*/


int main(){

    // -----------------------------------------------------------------------------------------------------------------------------
    
    // variaveis usadas para auxiliar a inserir os navios no tabuleiro
    int linha = 0, coluna = 0; 

    // guarda a coordenadas x e y do navio, onde o primeiro elemento do vetor é a linha e o segundo elemento é a coluna
    int navio_1_x_y[2] = {0,0};
    int navio_2_x_y[2] = {0,0};
    int navio_3_x_y[2] = {0,0};
    int navio_4_x_y[2] = {0,0};

    // valida se a coordenada inserida esta dentro do tabuleiro , 0 = falso, 1 = verdadeiro ou ok
    int validacao_1 = 0;  
    // valida se o navio esta dentro do tabuleiro, 0 = falso, 1 = verdadeiro ou ok
    int validacao_2 = 0; 
    // valida se já existe um navio ocupando aquela posicao
    int validacao_3 = 0; 

    int opcao = 0;

    // -----------------------------------------------------------------------------------------------------------------------------

    do
    {
        exibir_tabuleiro();
        //printf("\n### JOGO DA BATALHA NAVAL ###\n");
        printf("\nESCOLHA O TIPO DE NAVIO (0 - PARA SAIR):  \n");
        
        printf("\n");
        printf("[1] NAVIO HORIZONTAL | [2] NAVIO VERTICAL  | [3] NAVIO DIAGONAL DIREITA | [4] NAVIO DIAGONAL ESQUERDA \n");
        printf("===================================================================================================== \n");
        printf("      0 0 0 0 0      |      0 0 0 0 0      |         0 0 0 0 0          |         0 0 0 0 0          \n");
        printf("      0 0 0 0 0      |      0 0 1 0 0      |         0 1 0 0 0          |         0 0 0 1 0          \n");
        printf("      0 1 2 3 0      |      0 0 2 0 0      |         0 0 2 0 0          |         0 0 2 0 0          \n");
        printf("      0 0 0 0 0      |      0 0 3 0 0      |         0 0 0 3 0          |         0 3 0 0 0          \n");
        printf("      0 0 0 0 0      |      0 0 0 0 0      |         0 0 0 0 0          |         0 0 0 0 0          \n");
        printf("\nO navio é 1 2 3, onde o 1 é a posição inicial do navio");
        printf("\nOPÇÃO: ");
        scanf("%d",&opcao);

        switch(opcao)
        {
            case 1:
                //ler coordenadas dos navio 1
                printf("NAVIO 1 | POSIÇÃO HORIZONTAL | TAMANHO %d\n", tamanho_navio);
                do{
                    printf("linha inicial do navio 1 (1-10): ");
                    scanf("%d", &navio_1_x_y[0]);
                    validacao_1 = validar_coordernada(navio_1_x_y[0]); // checa se o valor esta entre 1 e 10
                    if(validacao_1)
                    {
                        printf("coluna inicial do navio 1 (1-10): ");
                        scanf("%d", &navio_1_x_y[1]);
                        validacao_1 = validar_coordernada(navio_1_x_y[1]);     
                        if(validacao_1)
                        {
                            validacao_2 = validar_navio_tabuleiro(navio_1_x_y[1], opcao); // checa se o navio vai ficar fora do tabuleiro
                            if(validacao_2)
                            {
                                int linha = navio_1_x_y[0]; // pega a linha
                                int coluna = navio_1_x_y[1]; // pega a coluna
                                linha--;
                                coluna--;
                                validacao_3 = colisao_navio(linha, coluna, opcao);
                            }
                        }
                    }
                }while( (validacao_1 == 0) || (validacao_2 == 0) || (validacao_3==0) ); // enquanto alguma das condicoes forem falsa, continua no loop)

                //insere o navio 1 no tabuleiro
                inserir_navio(navio_1_x_y[0]-1, navio_1_x_y[1]-1, opcao);
                //exibe tabuleiro
                exibir_tabuleiro();
                break;

            case 2:
                //ler coordenadas dos navio 2
                printf("NAVIO 2 | VERTICAL | TAMANHO %d\n", tamanho_navio);
                do{
                    printf("linha inicial do navio 2 (1-10): ");
                    scanf("%d", &navio_2_x_y[0]);
                    validacao_1 = validar_coordernada(navio_2_x_y[0]);
                    if (validacao_1) // se a linha esta entre um valor entre 1 e 10 passa
                    {
                        validacao_2 = validar_navio_tabuleiro(navio_2_x_y[0], opcao); // checa se o navio esta fora do tabuleiro
                        if(validacao_2) // se o navio esta totalmente dentro do tabuleiro
                        {
                            printf("coluna inicial do navio 2 (1-10): ");
                            scanf("%d", &navio_2_x_y[1]);
                            validacao_1 = validar_coordernada(navio_2_x_y[1]);     
                            if(validacao_1) // se a coluna esta entre 1 e 10 passa
                            {
                                int linha = navio_2_x_y[0]; // pega a linha
                                int coluna = navio_2_x_y[1]; // pega a coluna
                                linha--;
                                coluna--;
                                validacao_3 = colisao_navio(linha, coluna, opcao);
                            }
                        }
                    }
                }while( (validacao_1 == 0) || (validacao_2 == 0) || (validacao_3==0) ); // enquanto alguma das condicoes forem falsa, continua no loop)

                //insere o navio 2 no tabuleiro
                inserir_navio(navio_2_x_y[0]-1, navio_2_x_y[1]-1, opcao);
                //exibe tabuleiro
                exibir_tabuleiro();
                break;
            case 3:
                //ler coordenadas dos navio 3
                printf("NAVIO 3 | DIAGONAL DIREITA | TAMANHO %d\n", tamanho_navio);
                do{
                    printf("linha inicial do navio 3 (1-10): ");
                    scanf("%d", &navio_3_x_y[0]);
                    validacao_1 = validar_coordernada(navio_3_x_y[0]);
                    if (validacao_1) // se a linha esta entre um valor entre 1 e 10 passa
                    {
                        validacao_2 = validar_navio_tabuleiro(navio_3_x_y[0], opcao); // checa se o navio esta fora do tabuleiro em relacao a linha
                        if(validacao_2) // se o navio esta dentro do tabuleiro em relacao a linha passa
                        {
                            printf("coluna inicial do navio 3 (1-10): ");
                            scanf("%d", &navio_3_x_y[1]);
                            validacao_1 = validar_coordernada(navio_3_x_y[1]);     
                            if(validacao_1) // se a coluna esta entre 1 e 10 passa
                            {
                                validacao_2 = validar_navio_tabuleiro(navio_3_x_y[1], opcao); //checa se o navio esta fora do tabuleiro em relação a coluna
                                if(validacao_2)
                                {
                                    int linha = navio_3_x_y[0]; // pega a linha
                                    int coluna = navio_3_x_y[1]; // pega a coluna
                                    linha--;
                                    coluna--;
                                    validacao_3 = colisao_navio(linha, coluna, opcao);
                                }
                            }
                        }
                    }
                }while( (validacao_1 == 0) || (validacao_2 == 0) || (validacao_3==0) ); // enquanto alguma das condicoes forem falsa, continua no loop)

                //insere o navio 2 no tabuleiro
                inserir_navio(navio_3_x_y[0]-1, navio_3_x_y[1]-1, opcao);
                //exibe tabuleiro
                exibir_tabuleiro();
                break;
            case 4:
                //ler coordenadas dos navio 4
                printf("NAVIO 4 | DIAGONAL ESQUERDA| TAMANHO %d\n", tamanho_navio);
                do{
                    printf("linha inicial do navio 4 (1-10): ");
                    scanf("%d", &navio_4_x_y[0]);
                    validacao_1 = validar_coordernada(navio_4_x_y[0]);
                    if (validacao_1) // se a linha esta entre um valor entre 1 e 10 passa
                    {
                        validacao_2 = validar_navio_tabuleiro(navio_4_x_y[0], opcao); // checa se o navio esta fora do tabuleiro em relacao a linha
                        if(validacao_2) // se o navio esta dentro do tabuleiro em relacao a linha passa
                        {
                            printf("coluna inicial do navio 4 (1-10): ");
                            scanf("%d", &navio_4_x_y[1]);
                            validacao_1 = validar_coordernada(navio_4_x_y[1]);     
                            if(validacao_1) // se a coluna esta entre 1 e 10 passa
                            {
                                validacao_2 = validar_navio_tabuleiro(navio_4_x_y[1], opcao); //checa se o navio esta fora do tabuleiro em relação a coluna
                                if(validacao_2)
                                {
                                    int linha = navio_4_x_y[0]; // pega a linha
                                    int coluna = navio_4_x_y[1]; // pega a coluna
                                    linha--;
                                    coluna--;
                                    validacao_3 = colisao_navio(linha, coluna, opcao);
                                }
                            }
                        }
                    }
                }while( (validacao_1 == 0) || (validacao_2 == 0) || (validacao_3==0) ); // enquanto alguma das condicoes forem falsa, continua no loop)

                //insere o navio 2 no tabuleiro
                inserir_navio(navio_4_x_y[0]-1, navio_4_x_y[1]-1, opcao);
                //exibe tabuleiro
                exibir_tabuleiro();
                break;
            default:
                break;
        }

    } while (opcao);
    
    /*
    
    // -----------------------------------------------------------------------------------------------------------------------------
    
    //ler coordenadas dos navio 2
    //para a leitura da coordenada (linha e coluna) checar se ñ tem um navio naquela posição no tabuleiro
    printf("\nNAVIO 2 | POSIÇÃO VERTICAL BAIXO | TAMANHO 3\n");
    do{
        printf("linha inicial do navio 2 (1-10): ");
        scanf("%d", &posicao_inicial_navio_2[0]);
        validacao_1 = validar_coordernada(posicao_inicial_navio_2[0]); // checa se o valor esta entre 1 e 10 
        if(validacao_1)
        {
            // checa se a linha do navio nao vai deixar ele de fora do tabuleiro
            validacao_2 = validar_navio_tabuleiro(posicao_inicial_navio_2[0]); 
        }
        if(validacao_1 && validacao_2){
            printf("coluna inicial do navio 2 (1-10): ");
            scanf("%d", &posicao_inicial_navio_2[1]);
            validacao_1 = validar_coordernada(posicao_inicial_navio_2[1]); 
            int linha = posicao_inicial_navio_2[0];
            int coluna = posicao_inicial_navio_2[1];
      //      validacao_3 = colisao_navios_tabuleiro(linha-1, coluna-1, tabuleiro);
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

    exibir_tabuleiro(tabuleiro);

    //-----------------------------------------------------------------------------------------------------------------------------

    //ler coordenadas dos navio 3
    //para a leitura da coordenada (linha e coluna) checar se ñ tem um navio naquela posição no tabuleiro
    printf("\nNAVIO 3 | POSIÇÃO DIAGONAL BAIXO DIREITA | TAMANHO 3\n");
    do{
        printf("linha inicial do navio 3 (1-10): ");
        scanf("%d", &posicao_inicial_navio_3[0]);
        validacao_1 = validar_coordernada(posicao_inicial_navio_3[0]); // checa se o valor esta entre 1 e 10 
        if(validacao_1)
        {
            // checa se a linha do navio nao vai deixar ele de fora do tabuleiro
            // considerando que a direção do navio, a extensão dele esta indo para baixo
            validacao_2 = validar_navio_tabuleiro(posicao_inicial_navio_3[0]); // valida em relação a linha            
        }
        if(validacao_1 && validacao_2){
            printf("coluna inicial do navio 3 (1-10): ");
            scanf("%d", &posicao_inicial_navio_3[1]);
            validacao_1 = validar_coordernada(posicao_inicial_navio_3[1]); 
            validacao_2 = validar_navio_tabuleiro(posicao_inicial_navio_3[1]); // como o navio esta crescendo na diagonal direita, checa tbm se a coluna nao vai passar de 10
            int linha = posicao_inicial_navio_3[0];
            int coluna = posicao_inicial_navio_3[1];
    //        validacao_3 = colisao_navios_tabuleiro(linha-1, coluna-1, tabuleiro);
        }
    }while( (validacao_1 == 0) || (validacao_2 == 0) || (validacao_3 == 0));
    //para sair precisa
    //a) ser um numero entre 1 e 10
    //b) precisa saber se o navio ñ esta fora do tabuleiro
    //c) precisa checar se o navio 2 ñ esta colidindo com o navio 1
    
    // inseri navio 2 no tabuleiro
    linha = posicao_inicial_navio_3[0]; // retorna linha 
    linha--; //diminui 1 por que a linha começa do zero
    coluna = posicao_inicial_navio_3[1]; // retorna coluna 
    coluna--;
    for(int i = 0; i < 3; i++)
    {
        tabuleiro[linha+i][coluna+i] = 3;
    }

    // desenha tabuleiro
    exibir_tabuleiro(tabuleiro);

    */

    return 0;
}