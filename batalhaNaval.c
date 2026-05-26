#include <stdio.h>
#include <stdlib.h>

#define linha_tab 10 
#define coluna_tab 10
#define tamanho_navio 5

#define linha_matriz 5
#define coluna_matriz 5

//variavel global
int matriz_cone[linha_matriz][coluna_matriz];
int matriz_cruz[linha_matriz][coluna_matriz];
int matriz_octaedro[linha_matriz][coluna_matriz];

//variavel global
int tabuleiro [linha_tab][coluna_tab]; 

void exibir_tabuleiro()
{

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

// checa se a coordenada deixa a bomba fora do tabuleiro
int bomba_fora_tabuleiro(int x)
{
    int fora =0;
    int linha_minima = 0;
    int linha_maxima = 0;

    linha_minima = linha_tab - linha_matriz - (linha_matriz/2); // 10 - 5 - 2 = 3
    linha_maxima = linha_tab - (linha_matriz/2); //10 - 2 = 8

    /*
    10 linha tabuleiro
    5 linha matriz
    3 linha min
    8 linha max
    */

    if( (x >= linha_minima) &&  (x <=linha_maxima)  ) // se esta dentro do tabuleiro
    {
        return 1;
    }
    else{
        return 0;
    }
}

// inserir bomba no tabuleiro
void inserir_bomba_tabuleiro(int matriz[linha_matriz][coluna_matriz], int x, int y)
{
    int linha = x-2;
    int coluna = y-2;
    int i=0; //
    int j=0; // 

    //percorre tabuleiro
    for(linha; i < linha_matriz ; linha++)
    {
        for(coluna; j < linha_matriz; coluna++)
        {
            if(matriz[i][j] == 1){ //
                tabuleiro[linha][coluna] = 5;
            }  
            j++;
        }
        i++;
        j = 0;
        coluna = y-2;

    }
}

// cria a matriz octaedro onde é fornecido a coordenada x,y que é o ponto de origem
void criar_matriz_octaedro(int linha_octaedro, int coluna_octaedro)
{
    int linha = linha_octaedro;
    int coluna = coluna_octaedro;
    int d,e,b,c; //d = direita, e=esquerda , b= baixo, c=cima
    int atingiu_borda = 0;

    for(int i = 0; i < linha_matriz; i++){
        for(int j = 0; j < coluna_matriz; j++){
            matriz_cruz[i][j] = 0;
        }
    }

    d = coluna_octaedro;
    e = coluna_octaedro;
    b = linha_octaedro;
    c = linha_octaedro;
    
    matriz_octaedro[linha_octaedro][coluna_octaedro] = 1;
    do{
        
        d++; //anda em relação a coluna para direita
        e--; //anda em relaçao a coluna para esquerda
        c--; //anda em relação a linha para cima
        b++; //anda em relação a linha para baixo
        // se ainda estiver dentro do tabuleiro continua a crescer o desenho da cruz em todas as direções
        if( (d < coluna_matriz) && (e >= 0) && (b < linha_matriz) && (c >= 0)){
            matriz_octaedro[b][coluna_octaedro] = 1; //linha de baixo
            matriz_octaedro[c][coluna_octaedro] = 1; //linha de cima
            matriz_octaedro[linha_octaedro][d] = 1;  //coluna direita
            matriz_octaedro[linha_octaedro][e] = 1;  //coluna esquerda

            if( (d+1 < coluna_matriz) && (e+1 > 1) && (b+1 < linha_matriz) && (c+1 > 1)  ) { // se ainda vao crescer 1 unidade para os lados, faz o quadrado
                matriz_octaedro[b][coluna_octaedro+1] = 1; //linha de baixo
                matriz_octaedro[b][coluna_octaedro-1] = 1; //linha de baixo
                matriz_octaedro[c][coluna_octaedro+1] = 1; //linha de cima
                matriz_octaedro[c][coluna_octaedro-1] = 1; //linha de cima
            }

        }else
        {
            atingiu_borda = 1;
        }
    }while(atingiu_borda==0);
}

// cria a matriz cruz onde é fornecido a coordenada x,y que é o ponto de origem
void criar_matriz_cruz(int linha_cruz, int coluna_cruz)
{
    int linha = linha_cruz;
    int coluna = coluna_cruz;
    int d,e,b,c; //d = direita, e=esquerda , b= baixo, c=cima
    int atingiu_borda = 0;


    for(int i = 0; i < linha_matriz; i++){
        for(int j = 0; j < coluna_matriz; j++){
            matriz_cruz[i][j] = 0;
        }
    }

    d = coluna_cruz;
    e = coluna_cruz;
    b = linha_cruz;
    c = linha_cruz;

    matriz_cruz[linha_cruz][coluna_cruz] = 1;
    do{
        
        d++; //anda em relação a coluna para direita
        e--; //anda em relaçao a coluna para esquerda
        c--; //anda em relação a linha para cima
        b++; //anda em relação a linha para baixo
        // se ainda estiver dentro do tabuleiro continua a crescer o desenho da cruz em todas as direções
        if( (d < coluna_matriz) && (e >= 0) && (b < linha_matriz) && (c >= 0)){
            matriz_cruz[b][coluna_cruz] = 1;
            matriz_cruz[c][coluna_cruz] = 1;
            matriz_cruz[linha_cruz][d] = 1;
            matriz_cruz[linha_cruz][e] = 1;
        }else
        {
            atingiu_borda = 1;
        }
    }while(atingiu_borda==0);

}

// cria a matriz cone, onde é fornecido o ponto de origem
void criar_matriz_cone(int linha_cone, int coluna_cone)
{
    int linha = linha_cone;
    int coluna = coluna_cone;
    int y1 = coluna;
    int y2 = coluna;
    int atingiu_borda = 0;


    for(int i = 0; i < linha_matriz; i++){
        for(int j = 0; j < coluna_matriz; j++){
            matriz_cone[i][j] = 0;
        }
    }

    for(int i = linha; atingiu_borda == 0 ; i++){
        for(int j = y1; j <= y2; j++){
            matriz_cone[linha-1][j-1] = 1;
        }
        if(y1 == 1){ //atingiu borda esq
            atingiu_borda = 1;
            break;
        }
        else{
            y1--;
        }
        if(y2 == coluna_matriz){ // atingiu borda direita
            atingiu_borda = 1;
            break;
        }
        else{
            y2++;
        }
        if(linha == linha_matriz){ // atingiu borda inferior
            atingiu_borda = 1; 
            break;
        }
        else{
            linha++;
        }
        printf("\n");
    }
}

//recebe qualquer tipo de matriz (cone ,cruz e octaedro) e exibe
void exibir_matriz(int matriz[linha_matriz][coluna_matriz]){

//    printf("\n## MATRIZ DE HABILIDADE ##\n");
//    printf("========================== \n");
    printf("  ");
    for (int linha = 0; linha < linha_matriz; linha++)
    {
        //imprime letra da coluna
        if (linha==0)
        {
            for(int indice_coluna = 1; indice_coluna <= coluna_matriz ; indice_coluna++) 
            {
                 printf(" %d ", indice_coluna);
            }
            printf("\n");
        }
        
        printf("%d ", linha+1); // imprime numero da linha
        for(int coluna = 0; coluna < coluna_matriz; coluna++)
        {               
            if ( (linha==9) && (coluna==0) )
            {
                printf("%d ", matriz[linha][coluna]);
            }
            else
            {
                printf(" %d ", matriz[linha][coluna]);
            }
            
        }
        printf("\n");
    }

}

int main(){

    // -----------------------------------------------------------------------------------------------------------------------------
    
    // variaveis usadas para auxiliar a inserir os navios no tabuleiro
    int linha = 0, coluna = 0; 

    // guarda a coordenadas x e y do navio, onde o primeiro elemento do vetor é a linha e o segundo elemento é a coluna
    int navio_1_x_y[2] = {0,0};
    int navio_2_x_y[2] = {0,0};
    int navio_3_x_y[2] = {0,0};
    int navio_4_x_y[2] = {0,0};

    // valida se a coordenada inserida esta dentro do tabuleiro , 0 = falso, 1 = verdadeiro 
    int validacao_1 = 0;  
    // valida se o navio esta dentro do tabuleiro, 0 = falso, 1 = verdadeiro
    int validacao_2 = 0; 
    // valida se já existe um navio ocupando aquela posicao, 0 = falso, 1 = verdadeiro
    int validacao_3 = 0; 

    // checa se da para inserir navio
    int opcao_inserir_navio = 0;

    //opcoes para controle do menu
    int opcao_menu_principal = 0;
    int opcao_matriz_habilidade = 0;
    int opcao_lancar_bomba = 0;


    // guarda as coordenadas para gerar as matrizes
    int cone_x_y[2];
    int cruz_x_y[2];
    int octaedro_x_y[2];

    // ponto de origem para cada habilidade (bomba)
    int bomba_cone_x_y[2];
    int bomba_cruz_x_y[2];
    int bomba_octaedro_x_y[2];


    // -----------------------------------------------------------------------------------------------------------------------------

    do{
        printf("\n");
        printf("#################### JOGO DE BATALHA NAVAL ####################\n\n");
        printf("                                  )___(\n");
        printf("                           _______/__/_\n");
        printf("                  ___     /===========|   ___\n");
        printf(" ____       __   [\\\\\\]___/____________|__[///]   __\n");
        printf(" \\\\   \\\\_____[\\\\\\\\]__/___________________________\\\\__[//]___\n");
        printf("  \\\\                                                    |\n");
        printf("   \\\\              [VIBEWARE - ESTACIO]                /\n");
        printf("    \\\\                                                /\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("[1] - Inserir navios\n");
        printf("[2] - Criar Matriz de habilidade \n");
        printf("[3] - Integrar Matriz de habilidade (LANÇAR BOMBAS) \n");
        printf("[0] - Sair \n");
        printf("OPÇÃO: ");
        scanf("%d",&opcao_menu_principal);

        switch (opcao_menu_principal)
        {
            case 1:
                do
                {
                    exibir_tabuleiro();
                    printf("\nESCOLHA O TIPO DE NAVIO (0 - PARA SAIR):  \n");
                    printf("\n[1] NAVIO HORIZONTAL | [2] NAVIO VERTICAL  | [3] NAVIO DIAGONAL DIREITA | [4] NAVIO DIAGONAL ESQUERDA \n");
                    printf("===================================================================================================== \n");
                    printf("      0 0 0 0 0      |      0 0 0 0 0      |         0 0 0 0 0          |         0 0 0 0 0          \n");
                    printf("      0 0 0 0 0      |      0 0 1 0 0      |         0 1 0 0 0          |         0 0 0 1 0          \n");
                    printf("      0 1 2 3 0      |      0 0 2 0 0      |         0 0 2 0 0          |         0 0 2 0 0          \n");
                    printf("      0 0 0 0 0      |      0 0 3 0 0      |         0 0 0 3 0          |         0 3 0 0 0          \n");
                    printf("      0 0 0 0 0      |      0 0 0 0 0      |         0 0 0 0 0          |         0 0 0 0 0          \n");
                    printf("\nO navio é 1 2 3, onde o 1 é a posição inicial do navio");
                    printf("\nOPÇÃO: ");
                    scanf("%d",&opcao_inserir_navio);

                    switch(opcao_inserir_navio)
                    {
                        case 1:
                            //ler coordenadas dos navio 1
                            printf("NAVIO 1 | POSIÇÃO HORIZONTAL | TAMANHO %d\n", tamanho_navio);
                            do
                            {
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
                                        validacao_2 = validar_navio_tabuleiro(navio_1_x_y[1], opcao_inserir_navio); // checa se o navio vai ficar fora do tabuleiro
                                        if(validacao_2)
                                        {
                                            int linha = navio_1_x_y[0]; // pega a linha
                                            int coluna = navio_1_x_y[1]; // pega a coluna
                                            linha--;
                                            coluna--;
                                            validacao_3 = colisao_navio(linha, coluna, opcao_inserir_navio);
                                        }
                                    }
                                }
                            }while( (validacao_1 == 0) || (validacao_2 == 0) || (validacao_3==0) ); // enquanto alguma das condicoes forem falsa, continua no loop)

                            //insere o navio 1 no tabuleiro
                            inserir_navio(navio_1_x_y[0]-1, navio_1_x_y[1]-1, opcao_inserir_navio);
                            //exibe tabuleiro
                            exibir_tabuleiro();
                            break;

                        case 2:
                            //ler coordenadas dos navio 2
                            printf("NAVIO 2 | VERTICAL | TAMANHO %d\n", tamanho_navio);
                            do
                            {
                                printf("linha inicial do navio 2 (1-10): ");
                                scanf("%d", &navio_2_x_y[0]);
                                validacao_1 = validar_coordernada(navio_2_x_y[0]);
                                if (validacao_1) // se a linha esta entre um valor entre 1 e 10 passa
                                {
                                    validacao_2 = validar_navio_tabuleiro(navio_2_x_y[0], opcao_inserir_navio); // checa se o navio esta fora do tabuleiro
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
                                            validacao_3 = colisao_navio(linha, coluna, opcao_inserir_navio);
                                        }
                                    }
                                }
                            }while( (validacao_1 == 0) || (validacao_2 == 0) || (validacao_3==0) ); // enquanto alguma das condicoes forem falsa, continua no loop)

                            //insere o navio 2 no tabuleiro
                            inserir_navio(navio_2_x_y[0]-1, navio_2_x_y[1]-1, opcao_inserir_navio);
                            //exibe tabuleiro
                            exibir_tabuleiro();
                            break;
                        case 3:
                            //ler coordenadas dos navio 3
                            printf("NAVIO 3 | DIAGONAL DIREITA | TAMANHO %d\n", tamanho_navio);
                            do
                            {
                                printf("linha inicial do navio 3 (1-10): ");
                                scanf("%d", &navio_3_x_y[0]);
                                validacao_1 = validar_coordernada(navio_3_x_y[0]);
                                if (validacao_1) // se a linha esta entre um valor entre 1 e 10 passa
                                {
                                    validacao_2 = validar_navio_tabuleiro(navio_3_x_y[0], opcao_inserir_navio); // checa se o navio esta fora do tabuleiro em relacao a linha
                                    if(validacao_2) // se o navio esta dentro do tabuleiro em relacao a linha passa
                                    {
                                        printf("coluna inicial do navio 3 (1-10): ");
                                        scanf("%d", &navio_3_x_y[1]);
                                        validacao_1 = validar_coordernada(navio_3_x_y[1]);     
                                        if(validacao_1) // se a coluna esta entre 1 e 10 passa
                                        {
                                            validacao_2 = validar_navio_tabuleiro(navio_3_x_y[1], opcao_inserir_navio); //checa se o navio esta fora do tabuleiro em relação a coluna
                                            if(validacao_2)
                                            {
                                                int linha = navio_3_x_y[0]; // pega a linha
                                                int coluna = navio_3_x_y[1]; // pega a coluna
                                                linha--;
                                                coluna--;
                                                validacao_3 = colisao_navio(linha, coluna, opcao_inserir_navio);
                                            }
                                        }
                                    }
                                }
                            }while( (validacao_1 == 0) || (validacao_2 == 0) || (validacao_3==0) ); // enquanto alguma das condicoes forem falsa, continua no loop)

                            //insere o navio 2 no tabuleiro
                            inserir_navio(navio_3_x_y[0]-1, navio_3_x_y[1]-1, opcao_inserir_navio);
                            //exibe tabuleiro
                            exibir_tabuleiro();
                            break;
                        case 4:
                            //ler coordenadas dos navio 4
                            printf("NAVIO 4 | DIAGONAL ESQUERDA| TAMANHO %d\n", tamanho_navio);
                            do
                            {
                                printf("linha inicial do navio 4 (1-10): ");
                                scanf("%d", &navio_4_x_y[0]);
                                validacao_1 = validar_coordernada(navio_4_x_y[0]);
                                if (validacao_1) // se a linha esta entre um valor entre 1 e 10 passa
                                {
                                    validacao_2 = validar_navio_tabuleiro(navio_4_x_y[0], opcao_inserir_navio); // checa se o navio esta fora do tabuleiro em relacao a linha
                                    if(validacao_2) // se o navio esta dentro do tabuleiro em relacao a linha passa
                                    {
                                        printf("coluna inicial do navio 4 (1-10): ");
                                        scanf("%d", &navio_4_x_y[1]);
                                        validacao_1 = validar_coordernada(navio_4_x_y[1]);     
                                        if(validacao_1) // se a coluna esta entre 1 e 10 passa
                                        {
                                            validacao_2 = validar_navio_tabuleiro(navio_4_x_y[1], opcao_inserir_navio); //checa se o navio esta fora do tabuleiro em relação a coluna
                                            if(validacao_2)
                                            {
                                                int linha = navio_4_x_y[0]; // pega a linha
                                                int coluna = navio_4_x_y[1]; // pega a coluna
                                                linha--;
                                                coluna--;
                                                validacao_3 = colisao_navio(linha, coluna, opcao_inserir_navio);
                                            }
                                        }
                                    }
                                }
                            }while( (validacao_1 == 0) || (validacao_2 == 0) || (validacao_3==0) ); // enquanto alguma das condicoes forem falsa, continua no loop)

                            //insere o navio 2 no tabuleiro
                            inserir_navio(navio_4_x_y[0]-1, navio_4_x_y[1]-1, opcao_inserir_navio);
                            //exibe tabuleiro
                            exibir_tabuleiro();
                            break;
                        default:
                            break;
                    }
                } while (opcao_inserir_navio);
                break;
            case 2:
                do
                {
                    printf("\nGERAR MATRIZ DE HABILIDADE DE TAMANHO %dX%d (0 - PARA SAIR): \n", linha_matriz, coluna_matriz);
                    printf("\n");
                    printf("[1] MATRIZ CONE  | [2] MATRIZ CRUZ | [3] MATRIZ OCTAEDRO\n");
                    printf("===================================================================================================== \n");
                    printf("    0 0 0 0 0    |    0 0 1 0 0    |     0 0 1 0 0   \n");
                    printf("    0 0 1 0 0    |    0 0 1 0 0    |     0 1 1 1 0   \n");
                    printf("    0 1 1 1 0    |    1 1 1 1 1    |     1 1 1 1 1   \n");
                    printf("    1 1 1 1 1    |    0 0 1 0 0    |     0 1 1 1 0   \n");
                    printf("    0 0 0 0 0    |    0 0 1 0 0    |     0 0 1 0 0   \n");
                    printf("\nOPÇÃO: ");
                    scanf("%d",&opcao_matriz_habilidade);
                    
                    switch (opcao_matriz_habilidade)
                    {
                        case 1:
                            printf("\n#  MATRIZ CONE #\n");
                            exibir_matriz(matriz_cone);
                            printf("\nMATRIZ CONE - DEFINA A COORDENADA (X,Y) \n");
                            do
                            {
                                printf("linha inicial da matriz cone (1-%d): ", linha_matriz-1);
                                scanf("%d", &cone_x_y[0]);
                                if( (cone_x_y[0] > 0) && (cone_x_y[0] < linha_matriz)) { //linha entre 1 e 4 passa
                                    validacao_1 = 1;
                                    if(validacao_1){
                                        printf("coluna inicial da matriz cone (2-%d): ", linha_matriz -1);
                                        scanf("%d", &cone_x_y[1]);
                                        if( (cone_x_y[1] > 1)  && (cone_x_y[1] < coluna_matriz)){
                                            validacao_1 = 1;     
                                        }
                                        else{
                                            validacao_1 = 0;
                                            printf("Nessa coluna o cone esta fora do tabuleiro \n");
                                        }
                                    }
                                }
                                else{
                                    validacao_1 = 0;
                                    printf("Nessa linha o cone esta fora do tabuleiro \n");
                                }
                            }while(validacao_1 == 0);

                            //cria a matriz cone
                            criar_matriz_cone(cone_x_y[0], cone_x_y[1]);
                            //exibe tabuleiro
                            printf("#  MATRIZ CONE #\n");
                            exibir_matriz(matriz_cone);
                            break;

                        case 2:
                            printf("\n#  MATRIZ CRUZ #\n");
                            exibir_matriz(matriz_cruz);
                            printf("\nMATRIZ CRUZ - DEFINA A COORDENADA (X,Y) \n");
                            do
                            {
                                printf("linha inicial da matriz cruz (2-%d): ", linha_matriz-1);
                                scanf("%d", &cruz_x_y[0]);
                                if( (cruz_x_y[0] > 1) && (cruz_x_y[0] < linha_matriz)) { //linha entre 2 e 4 passa
                                    validacao_1 = 1;
                                    if(validacao_1){
                                        printf("coluna inicial da matriz cruz (2-%d): ", linha_matriz-1);
                                        scanf("%d", &cruz_x_y[1]);
                                        if( (cruz_x_y[1] > 1)  && (cruz_x_y[1] < coluna_matriz)){ //coluna entre 2 e 4
                                            validacao_1 = 1;     
                                        }
                                        else{
                                            validacao_1 = 0;
                                            printf("Nessa coluna a cruz esta fora do tabuleiro \n");
                                        }
                                    }
                                }
                                else{
                                    validacao_1 = 0;
                                    printf("Nessa linha a cruz esta fora do tabuleiro \n");
                                }
                            }while(validacao_1 == 0);

                            //cria a matriz cruz
                            criar_matriz_cruz(cruz_x_y[0]-1, cruz_x_y[1]-1);
                            //exibe tabuleiro                        
                            printf("\n#  MATRIZ CRUZ #\n");
                            exibir_matriz(matriz_cruz);
                            break;
                        case 3:
                            printf("\n MATRIZ OCTAEDRO \n");
                            exibir_matriz(matriz_octaedro);
                            printf("\nMATRIZ OCTAEDRO - DEFINA A COORDENADA (X,Y) \n");
                            do
                            {
                                printf("linha inicial da matriz octaedro (2-%d): ", linha_matriz-1);
                                scanf("%d", &octaedro_x_y[0]);
                                if( (octaedro_x_y[0] > 1) && (octaedro_x_y[0] < linha_matriz)) { //linha entre 2 e 4 passa
                                    validacao_1 = 1;
                                    if(validacao_1){
                                        printf("coluna inicial da matriz octaedro (2-%d): ", linha_matriz-1);
                                        scanf("%d", &octaedro_x_y[1]);
                                        if( (octaedro_x_y[1] > 1)  && (octaedro_x_y[1] < coluna_matriz)){ //coluna entre 2 e 4
                                            validacao_1 = 1;     
                                        }
                                        else{
                                            validacao_1 = 0;
                                            printf("Nessa coluna o octaedro esta fora do tabuleiro \n");
                                        }
                                    }
                                }
                                else{
                                    validacao_1 = 0;
                                    printf("Nessa linha o octaedro esta fora do tabuleiro \n");
                                }
                            }while(validacao_1 == 0);

                            //cria a matriz octaedro
                            criar_matriz_octaedro(octaedro_x_y[0]-1, octaedro_x_y[1]-1);
                            //exibe tabuleiro                        
                            printf("\n MATRIZ OCTAEDRO \n");
                            exibir_matriz(matriz_octaedro);
                            break;

                        default:
                            // código executado se nenhum caso for verdadeiro
                    }
                } while (opcao_matriz_habilidade);
                break;
            case 3:
                do
                {
                    printf("\nLANÇAR BOMBA, ESCOLHA O EFEITO (0 - PARA SAIR): \n");
                    printf("\n");
                    printf("[1] MATRIZ CONE\n");
                    exibir_matriz(matriz_cone);
                    printf("\n");
                    printf("[2] MATRIZ CRUZ\n");
                    exibir_matriz(matriz_cruz);
                    printf("\n");
                    printf("[3] MATRIZ OCTAEDRO\n");
                    exibir_matriz(matriz_octaedro);

                    /*
                    printf("[1] MATRIZ CONE  | [2] MATRIZ CRUZ | [3] MATRIZ OCTAEDRO\n");
                    printf("===================================================================================================== \n");
                    printf("    0 0 0 0 0    |    0 0 1 0 0    |     0 0 1 0 0   \n");
                    printf("    0 0 1 0 0    |    0 0 1 0 0    |     0 1 1 1 0   \n");
                    printf("    0 1 1 1 0    |    1 1 1 1 1    |     1 1 1 1 1   \n");
                    printf("    1 1 1 1 1    |    0 0 1 0 0    |     0 1 1 1 0   \n");
                    printf("    0 0 0 0 0    |    0 0 1 0 0    |     0 0 1 0 0   \n");
                    */
                    printf("\nOPÇÃO: ");
                    scanf("%d",&opcao_lancar_bomba);               

                    switch (opcao_lancar_bomba) 
                    {
                        case 1:
                            exibir_tabuleiro();
                            printf("\nSelecione a coordenada (X,Y) para lançar a bomba\n");
                            do{
                                printf("linha (x): ");
                                scanf("%d",&bomba_cone_x_y[0]);
                                validacao_1 = bomba_fora_tabuleiro(bomba_cone_x_y[0]);
                                if(validacao_1){ // escolheu uma linha valida
                                    printf("coluna (y): ");
                                    scanf("%d",&bomba_cone_x_y[1]);
                                    validacao_1 = bomba_fora_tabuleiro(bomba_cone_x_y[1]);
                                    if(validacao_1){ // escolheu uma coluna valida
                                        validacao_1 = 1;
                                        break;
                                    }
                                    else{
                                        validacao_1 = 0;
                                        printf("A bomba esta fora do tabuleiro\n");    
                                    }
                                }else{
                                    validacao_1 = 0;
                                    printf("A bomba esta fora do tabuleiro\n");
                                }
                            }while(validacao_1 ==0);
                            //cria a matriz octaedro
                            inserir_bomba_tabuleiro(matriz_cone, bomba_cone_x_y[0]-1, bomba_cone_x_y[1]-1);
                            //exibe tabuleiro                        
                            exibir_tabuleiro();
                            break;
                            
                        case 2:
                            exibir_tabuleiro();
                            printf("\nSelecione a coordenada (X,Y) para lançar a bomba\n");
                            do{
                                printf("linha (x): ");
                                scanf("%d",&bomba_cruz_x_y[0]);
                                validacao_1 = bomba_fora_tabuleiro(bomba_cruz_x_y[0]);
                                if(validacao_1){ // escolheu uma linha valida
                                    printf("coluna (y): ");
                                    scanf("%d",&bomba_cruz_x_y[1]);
                                    validacao_1 = bomba_fora_tabuleiro(bomba_cruz_x_y[1]);
                                    if(validacao_1){ // escolheu uma coluna valida
                                        validacao_1 = 1;
                                        break;
                                    }
                                    else{
                                        validacao_1 = 0;
                                        printf("A bomba esta fora do tabuleiro\n");    
                                    }
                                }else{
                                    validacao_1 = 0;
                                    printf("A bomba esta fora do tabuleiro\n");
                                }
                            }while(validacao_1 ==0);
                            //cria a matriz octaedro
                            inserir_bomba_tabuleiro(matriz_cruz, bomba_cruz_x_y[0]-1, bomba_cruz_x_y[1]-1);
                            //exibe tabuleiro                        
                            exibir_tabuleiro();
                            break;

                        case 3:
                            exibir_tabuleiro();
                            printf("\nSelecione a coordenada (X,Y) para lançar a bomba\n");
                            do{
                                printf("linha (x): ");
                                scanf("%d",&bomba_octaedro_x_y[0]);
                                validacao_1 = bomba_fora_tabuleiro(bomba_octaedro_x_y[0]);
                                if(validacao_1){ // escolheu uma linha valida
                                    printf("coluna (y): ");
                                    scanf("%d",&bomba_octaedro_x_y[1]);
                                    validacao_1 = bomba_fora_tabuleiro(bomba_octaedro_x_y[1]);
                                    if(validacao_1){ // escolheu uma coluna valida
                                        validacao_1 = 1;
                                        break;
                                    }
                                    else{
                                        validacao_1 = 0;
                                    printf("A bomba esta fora do tabuleiro\n");    
                                    }
                                }else{
                                    validacao_1 = 0;
                                    printf("A bomba esta fora do tabuleiro\n");
                                }
                            }while(validacao_1 ==0);
                            //cria a matriz octaedro
                            inserir_bomba_tabuleiro(matriz_octaedro, bomba_octaedro_x_y[0]-1, bomba_octaedro_x_y[1]-1);
                            //exibe tabuleiro                        
                            exibir_tabuleiro();
                            break;
                        default:
                            break;
                    }
                }while (opcao_lancar_bomba != 0);
                break;
            default:
                break;
        }
    }while(opcao_menu_principal);

    return 0;
}