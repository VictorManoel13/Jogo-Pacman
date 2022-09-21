#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#define L 20
#define C 29

struct coord
{
    int x;
    int y;
};

// vari�veis do pacman
struct PacMan
{
    struct coord posicao; // posição do cursor
    int vx; // posição x do movimento
    int vy; // posição y do movimento
    int comida; // comida do comecome
    int i;   // pausar
    int sec; // segundos
    int min; // minutos
    int hr; // hora
    int j;// variável para continuar rodando o jogo
    char nome[30];
    char lista[3][20];
};

struct PacMan ComeCome = {
    {
        .x = 14, // posição x que o comecome começa
        .y = 15, // posição y que o comecome começa
    },
    .vx = 0, // posição de movimento x do comecome
    .vy = 0, // posição de movimento y do comecome
    .comida = 0, // comida inicial do comecome
    .i = 0, // critério para pausar o jogo
    .sec = 0, // segundos iniciais
    .min = 0, // minutos iniciais
    .hr = 0, // horas iniciais
    .j = 0}; // critério para continuar rodando o jogo

// vari�veis dos fantasmas
struct Fantasma
{
    int gx[4]; // variável da posição x do fantasma 
    int gy[4]; // variável da posição y do fantasma 
    int vgx[4]; // variável movimento x do fantasma
    int vgy[4]; // variável movimento y do fantasma
    int ig[4]; // variável para permitir movimento do fantasma
};

struct Fantasma ghost =
    { // FANTASMA 1
        .gx[0] = 1,
        .gy[0] = 1,
        .vgx[0] = 0,
        .vgy[0] = 0,
        .ig[0] = 0,
        // FANTASMA 2
        .gx[1] = 9,
        .gy[1] = 14,
        .vgx[1] = 0,
        .vgy[1] = 0,
        .ig[1] = 0,
        // FANTASMA 3
        .gx[2] = 9,
        .gy[2] = 12,
        .vgx[2] = 0,
        .vgy[2] = 0,
        .ig[2] = 0,
        // FANTASMA 4
        .gx[3] = 1,
        .gy[3] = 27,
        .vgx[3] = 0,
        .vgy[3] = 0,
        .ig[3] = 0};

int mapa[L][C] = {

    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void inicializar()
{

    int i, j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 29; j++)
        {
            // onde tiver 0 no mapa vai ser substituído por '.'
            if (mapa[i][j] == 0)
                mapa[i][j] = '.';
        }
    }
}
void reiniciar()
{
    int i, j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 29; j++)
        {
            // reinicia o jogo realocando os pontos no lugar do espaço, do comecome e dos fantasmas
            if (mapa[i][j] == ' ' || mapa[i][j] == 3 || mapa[i][j] == 2)
                mapa[i][j] = '.';
        }
    }
}

void linhaCol(int lin, int col);
void box(int lin1, int col1, int lin2, int col2);
int menu(int lin1, int col1, int qtd, char lista[2][20]);
void textColor(int letras, int fundo);
// COR DA LETRA
enum
{
    BLACK,        // 0
    BLUE,         // 1
    GREEN,        // 2
    CYAN,         // 3
    RED,          // 4
    MAGENTA,      // 5
    BROWN,        // 6
    LIGHTGRAY,    // 7
    DARKGRAY,     // 8
    LIGHTBLUE,    // 9
    LIGHTGREEN,   // 10
    LIGHTCYAN,    // 11
    LIGHTRED,     // 12
    LIGHTMAGENTA, // 13
    YELLOW,       // 14
    WHITE         // 15

};
// COR DO FUNDO
enum
{
    _BLACK = 0,          // 0
    _BLUE = 16,          // 1
    _GREEN = 32,         // 2
    _CYAN = 48,          // 3
    _RED = 64,           // 4
    _MAGENTA = 80,       // 5
    _BROWN = 96,         // 6
    _LIGHTGRAY = 112,    // 7
    _DARKGRAY = 128,     // 8
    _LIGHTBLUE = 144,    // 9
    _LIGHTGREEN = 160,   // 10
    _LIGHTCYAN = 176,    // 11
    _LIGHTRED = 192,     // 12
    _LIGHTMAGENTA = 208, // 13
    _YELLOW = 224,       // 14
    _WHITE = 240         // 15
};

void textColor(int letra, int fundo)
{ // altera a cor da letra e do fundo
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);
}

void linhaCol(int lin, int col)
{ // coordenada na tela
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){col - 1, lin - 1});

    // funcao para deixar o cursor invisivel
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void box(int lin1, int col1, int lin2, int col2)
{ // criar o box
    int i, j, tamlin, tamcol;

    // achar o tamanho do box
    tamlin = lin2 - lin1;
    tamcol = col2 - col1;

    // Monta o Box

    for (i = col1; i <= col2; i++)
    { // linhas
        linhaCol(lin1, i);
        printf("%c", 196);
        linhaCol(lin2, i);
        printf("%c", 196);
    }

    for (i = lin1; i <= lin2; i++)
    { // colunas
        linhaCol(i, col1);
        printf("%c", 179);
        linhaCol(i, col2);
        printf("%c", 179);
    }
    for (i = lin1 + 1; i < lin2; i++)
    {
        for (j = col1 + 1; j < col2; j++)
        {
            linhaCol(i, j);
            printf(" ");
        }
    }
    // Posi��o dos cantos
    linhaCol(lin1, col1);
    printf("%c", 218);
    linhaCol(lin1, col2);
    printf("%c", 191);
    linhaCol(lin2, col1);
    printf("%c", 192);
    linhaCol(lin2, col2);
    printf("%c", 217);
}
int menu(int lin1, int col1, int qtd, char lista[2][20])
{
    int opc = 1, lin2, col2, linha, i, tamMaxItem, tecla;

    // calcula as coordenadas
    tamMaxItem = strlen(lista[0]);
    // tamanho maximo do item
    for (i = 1; i < qtd; i++)
    {
        if (strlen(lista[i]) > tamMaxItem)
        {
            tamMaxItem = strlen(lista[i]);
        }
    }
    lin2 = lin1 + (qtd * 2 + 2);
    col2 = col1 + tamMaxItem + 20;

    // Monta Tela
    textColor(WHITE, _BLUE);
    setlocale(LC_ALL, "C");
    box(lin1, col1, lin2, col2);
    setlocale(LC_ALL, "");
    // la�o das opc�es
    while (1)
    {

        linha = lin1 + 2;
        for (i = 0; i < qtd; i++)
        {
            if (i + 1 == opc)
            {
                textColor(BLACK, _RED);
            }
            else
            {
                textColor(WHITE, _BLUE);
            }
            linhaCol(linha, col1 + 10);
            printf("%s", lista[i]);
            linha += 2;
        }

        // Aguarda tecla
        linhaCol(1, 1);
        tecla = getch();
        linhaCol(22, 1);
       
        // Op��o
        if (tecla == 13)
        { // ENTER
            break;
        }
        // Seta para cima
        else if (tecla == 72)
        { // se possivel seleciona o item anterior - seta para cima
            if (opc > 1)
            {
                opc--; // se opcao for maior que 1, pode voltar
            }
        }
        else if (tecla == 80)
        { // seta para baixo
            if (opc < qtd)
            {
                opc++; // Se opcao for menor que quantidade de itens, posso avan�ar
            }
        }
    }
    return opc;
}

void teclado()
{

    if (_kbhit()) // verifica se � tecla
    {
        char c1 = _getch();         // c1 pega a tecla
        if (c1 == -32 || c1 == 115) // todas as setas s�o -32 e a tecla s � 115
        {
            char c1 = _getch(); // ler de novo, as setas ficam com vari�veis diferentes

            ComeCome.vx = 0;
            ComeCome.vy = 0;

            switch (c1)
            {
            case 72:
                ComeCome.vy = -1; // cima
                break;
            case 80:
                ComeCome.vy = +1; // baixo
                break;
            case 75:
                ComeCome.vx = -1; // esquerda
                break;
            case 77:
                ComeCome.vx = +1; // direita
                break;
            case 115:
                ComeCome.i = 2; // pause
                break;
            }
        }
    }
}

void teclado_fantasma()
{
    int i;
    for (i = 0; i < 4; i++)
    {
        ghost.vgx[i] = 0;
        ghost.vgy[i] = 0;
        // escolhendo o próximo movimento do fantasma
        switch (ghost.ig[i])
        {
        case 0:
            ghost.vgx[i] = -1; // direita
            break;
        case 1:
            ghost.vgx[i] = +1; // esquerda
            break;
        case 2:
            ghost.vgy[i] = -1; //  cima
            break;
        case 3:
            ghost.vgy[i] = +1; // baixo
            break;
        }
    }
}

void movimento_fantasma()
{
    int i;
    int n = 0;
    for (i = 0; i < 4; i++)
    {
        // nova posi��o de fantasma

        int ngx[i];
        int ngy[i];
        ngx[i] = ghost.vgx[i] + ghost.gx[i];
        ngy[i] = ghost.vgy[i] + ghost.gy[i];
        // verifica se � parede, se for parede, ent�o o pr�ximo movimento � aleat�rio
        parede_fantasma();
        // caso a nova posi��o seja a comdia, a antiga recebe comida tamb�m
        if (mapa[ngx[i]][ngy[i]] == '.')
        {
            mapa[ghost.gx[i]][ghost.gy[i]] = '.';
        }
        // caso a nova posi��o seja espa�o vazio, a antiga recebe espa�o vazio tamb�m
        if (mapa[ngx[i]][ngy[i]] == ' ')
        {
            mapa[ghost.gx[i]][ghost.gy[i]] = ' ';
        }
        // fantasma verifica se a nova posi��o � o pacman, se for o pacman, ent�o o programa encerra
        if (mapa[ngx[i]][ngy[i]] == 3)
        {
            ComeCome.i = 3;
        }
        // movimento do fantasma
        ghost.gx[i] += ghost.vgx[i];
        ghost.gy[i] += ghost.vgy[i];
        // nova posi��o do fantasma
        mapa[ghost.gx[0]][ghost.gy[0]] = 2;
        mapa[ghost.gx[1]][ghost.gy[1]] = 2;
        mapa[ghost.gx[2]][ghost.gy[2]] = 2;
        mapa[ghost.gx[3]][ghost.gy[3]] = 2;
    }
}

void parede_fantasma()
{
    int n = 0;
    int i;
    int ngx[4];
    int ngy[4];
    // nova posição fantasma 1
    ngx[0] = ghost.vgx[0] + ghost.gx[0];
    ngy[0] = ghost.vgy[0] + ghost.gy[0];
    // nova posição fantasma 2
    ngx[1] = ghost.vgx[1] + ghost.gx[1];
    ngy[1] = ghost.vgy[1] + ghost.gy[1];
    // nova posição fantasma 3
    ngx[2] = ghost.vgx[2] + ghost.gx[2];
    ngy[2] = ghost.vgy[2] + ghost.gy[2];
    // nova posição fantasma 4
    ngx[3] = ghost.vgx[3] + ghost.gx[3];
    ngy[3] = ghost.vgy[3] + ghost.gy[3];

    // fantasma 1
    if (mapa[ngx[0]][ngy[0]] == 1 || mapa[ngx[0]][ngy[0]] == 2)
    {
        ghost.vgx[0] = 0;
        ghost.vgy[0] = 0;

        if (n == 0)
        {
            // escolhendo próximo movimento do fantasma 1
            srand(time(NULL));
            ghost.ig[0] = rand() % 4;
            n = 1;
        }
        else if (n == 1)
        {
            ghost.ig[0] = rand() % 4;
        }
    }
    // fantasma 2
    if (mapa[ngx[1]][ngy[1]] == 1 || mapa[ngx[1]][ngy[1]] == 2)
    {
        ghost.vgx[1] = 0;
        ghost.vgy[1] = 0;
        // escolhendo próximo movimento do fantasma 2
        if (n == 0)
        {
            srand(time(NULL));
            ghost.ig[1] = rand() % 4;
            n = 1;
        }
        else if (n == 1)
        {
            ghost.ig[1] = rand() % 4;
        }
    }
    // fantasma 3
    if (mapa[ngx[2]][ngy[2]] == 1 || mapa[ngx[2]][ngy[2]] == 2)
    {
        ghost.vgx[2] = 0;
        ghost.vgy[2] = 0;
        // escolhendo próximo movimento do fantasma 3
        if (n == 0)
        {
            srand(time(NULL));
            ghost.ig[2] = rand() % 4;
            n = 1;
        }
        else if (n == 1)
        {
            ghost.ig[2] = rand() % 4;
        }
    }
    // fantasma 4
    if (mapa[ngx[3]][ngy[3]] == 1 || mapa[ngx[3]][ngy[3]] == 2)
    {
        ghost.vgx[3] = 0;
        ghost.vgy[3] = 0;
        // escolhendo próximo movimento do fantasma 4
        if (n == 0)
        {
            srand(time(NULL));
            ghost.ig[3] = rand() % 4;
            n = 1;
        }
        else if (n == 1)
        {
            ghost.ig[3] = rand() % 4;
        }
    }
}

void movimento()
{
    float j = 0;
    // antiga posi��o
    mapa[ComeCome.posicao.y][ComeCome.posicao.x] = ' ';
    // nova posi��o
    int nx = ComeCome.vx + ComeCome.posicao.x;
    int ny = ComeCome.vy + ComeCome.posicao.y;
    // verifca se � parede
    if (mapa[ny][nx] == 1)
    {

        ComeCome.vx = 0;
        ComeCome.vy = 0;
    }
    // verifica se � fantasma
    if (mapa[ny][nx] == 2)
    {
        ComeCome.i = 3;
    }
    // movimento

    ComeCome.posicao.x += ComeCome.vx;
    ComeCome.posicao.y += ComeCome.vy;

    // verifica se � comida
    if (mapa[ny][nx] == '.')
    {
        ComeCome.comida++;
    }
    // nova posi��o do pacman
    mapa[ComeCome.posicao.y][ComeCome.posicao.x] = 3;
}

void cronometro()
{
    // conta os segundos, adaptado por conta do sleep geral que não é Sleep(1000) = 1 segundo
    if (ComeCome.sec == 590)
    {
        ComeCome.sec = 0;
        ComeCome.min++;
    }

    if (ComeCome.min == 600)
    {
        ComeCome.min = 0;
        ComeCome.hr++;
    }

    if (ComeCome.hr == 240)
    {
        ComeCome.hr = 0;
    }

    Sleep(100); // tem a fun��o de pausar a execu��o por um determinado tempo
    ComeCome.sec += 2.8;
}

void mostrar_mapa()
{
    int i, j;
    // mostra pontos e cronomentro
    printf("\t\t\t\t\t\tPontos: %d\t%dh:%dm:%ds\n", ComeCome.comida, ComeCome.hr / 10, ComeCome.min, ComeCome.sec / 10);

    for (i = 0; i < L; i++)
    {
        printf("\t\t\t\t\t\t");
        for (j = 0; j < C; j++)
        {
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
    // auxilia em que botão apertar para pausar o jogo
    printf("\t\t\t\t\t\tAperte S duas vezes para pausar\n");
}

// defini posição do cursor
void set_cursor_position(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void pause()
{
    // j é uma forma de limpar a tela uma vez e depois mostrar a tela pause.
    int j = 0;
    // critério para entrar no pause
    while (ComeCome.i == 2)
    {

        if (j == 0)
        {
            system("cls");
            j = 1;
        }

        int opc;
        char lista[3][20] = {"CONTINUAR","REINICIAR", "SAIR"};
        setlocale(LC_ALL, "");
        linhaCol(2, 5);
        textColor(RED, _BLACK);
        // pode ter e pode nao ter
        printf("\t\t\t\t\t| #####     ##    ##  ##   ####    ##   |\n");
        printf("\t\t\t\t\t| ##   #   #  #   ##  ##  #       #  #  |\n");
        printf("\t\t\t\t\t| #####   ######  ##  ##  ####   ###### |\n");
        printf("\t\t\t\t\t| ##      ##  ##  ##  ##      #  ##  ## |\n");
        printf("\t\t\t\t\t| ##      ##  ##   ####   ####   ##  ## |\n\n");
        printf("\t\t\t\t\tO(a) jogador(a) %s esta com %d ponto(s)\n\n", ComeCome.nome, ComeCome.comida);
        while (true)
        {
            opc = menu(10, 47, 3, lista);
            if (opc == 1)
            { // continuar o jogo
                linhaCol(1, 1);
                textColor(WHITE, _BLACK);
                printf("\ncontinua o jogo");
                system("cls");
                ComeCome.i = 1;
                break;
            }
            if (opc == 2)
            { // reinicia o jogo declarando tudo novamente como estava no ínicio do código

				linhaCol(1, 1);
                textColor(WHITE, _BLACK);
                system("cls");
                ComeCome.posicao.x = 14;
                ComeCome.posicao.y = 15;
                ComeCome.vx = 0;
                ComeCome.vy = 0;
                ComeCome.comida = 0;
                ComeCome.i = 0;
                ComeCome.sec = 0;
                ComeCome.min = 0;
                ComeCome.hr = 0;
                ComeCome.j = 0;

                ghost.gx[0] = 1;
                ghost.gy[0] = 1;
                ghost.vgx[0] = 0;
                ghost.vgy[0] = 0;
                ghost.ig[0] = 0;

                ghost.gx[1] = 9;
                ghost.gy[1] = 14;
                ghost.vgx[1] = 0;
                ghost.vgy[1] = 0;
                ghost.ig[1] = 0;

                ghost.gx[2] = 9;
                ghost.gy[2] = 12;
                ghost.vgx[2] = 0;
                ghost.vgy[2] = 0;
                ghost.ig[2] = 0;

                ghost.gx[3] = 1;
                ghost.gy[3] = 27;
                ghost.vgx[3] = 0;
                ghost.vgy[3] = 0;
                ghost.ig[3] = 0;
                reiniciar();
                break;
            	  
            }
            if (opc == 3)
            { // encerra o jogo 
                textColor(WHITE, _BLACK);
                system("cls");
                ComeCome.i = 1;
                ComeCome.j = 1;
                break;
            }
        }
        textColor(WHITE, _BLACK);
        linhaCol(24, 1);
        printf("");
    }
    
}

void menu_inicial()
{
    int opc;
    char lista[2][20] = {"JOGAR", "SAIR"};
    setlocale(LC_ALL, "");
    linhaCol(2, 5);
    textColor(RED, _BLACK);
    // ideia de nome
    printf("\t\t\t\t\t|   ###    ###    ##      ##  ##### |\n");
    printf("\t\t\t\t\t| ##     ##   ##  ## #  # ##  ##    |\n");
    printf("\t\t\t\t\t| ##     ##   ##  ##  ##  ##  ####  |\n");
    printf("\t\t\t\t\t| ##     ##   ##  ##      ##  ##    |\n");
    printf("\t\t\t\t\t|   ###    ###    ##      ##  ##### |\n\n");
    printf("\t\t\t\t\t|   ###    ###    ##      ##  ##### |\n");
    printf("\t\t\t\t\t| ##     ##   ##  ## #  # ##  ##    |\n");
    printf("\t\t\t\t\t| ##     ##   ##  ##  ##  ##  ####  |\n");
    printf("\t\t\t\t\t| ##     ##   ##  ##      ##  ##    |\n");
    printf("\t\t\t\t\t|   ###    ###    ##      ##  ##### |\n");

    while (true)
    {
        opc = menu(15, 47, 2, lista);
        if (opc == 1)
        { // redirecionar para o jogo
            linhaCol(1, 1);
            textColor(WHITE, _BLACK);
            printf("\nINICIA O JOGO");
            system("cls");
            break;
        }
        if (opc == 2)
        { // encerra o jogo
            textColor(WHITE, _BLACK);
            system("cls");
            ComeCome.j = 1;
            break;
        }
    }

    textColor(WHITE, _BLACK);
    linhaCol(24, 1);
    printf("");
    system("cls");
}

void morte()
{
    // critério para entrar no if da morte
    if (ComeCome.i == 3)
    {

    system("cls");
    int opc;
    char lista[2][20] = {"JOGAR NOVAMENTE", "SAIR"};
    setlocale(LC_ALL, "");
    linhaCol(2, 5);
    textColor(RED, _BLACK);
    printf("\t\t\t\t\t| ##        ##    ###      #####  ###### |\n");
    printf("\t\t\t\t\t|  ##      ##   ##   ##  ##       ##     |\n");
    printf("\t\t\t\t\t|   ##    ##    ##   ##  ##       #####  |\n");
    printf("\t\t\t\t\t|    ##  ##     ##   ##  ##       ##     |\n");
    printf("\t\t\t\t\t|      ##         ###      #####  ###### |\n\n");
    printf("\t\t\t\t| ######   ######  ######    #######    ######  ##   ## |\n");
    printf("\t\t\t\t| ##   ##  ##      ##   ##   ##     ##  ##      ##   ## |\n");
    printf("\t\t\t\t| ######   #####   ######    ##     ##  #####   ##   ## |\n");
    printf("\t\t\t\t| ##       ##      ##   ##   ##     ##  ##      ##   ## |\n");
    printf("\t\t\t\t| ##       ######  ##    ##  #######    ######    ###   |\n");
    printf("\t\t\t\t\t\tO(a) jogador(a) %s fez %d ponto(s)\n\n", ComeCome.nome, ComeCome.comida);
        while (true)
        {
            opc = menu(15, 47, 2, lista);
            if (opc == 1)
            { // reinicia o jogo
                linhaCol(1, 1);
                textColor(WHITE, _BLACK);
                system("cls");
                ComeCome.posicao.x = 14;
                ComeCome.posicao.y = 15;
                ComeCome.vx = 0;
                ComeCome.vy = 0;
                ComeCome.comida = 0;
                ComeCome.i = 0;
                ComeCome.sec = 0;
                ComeCome.min = 0;
                ComeCome.hr = 0;
                ComeCome.j = 0;

                ghost.gx[0] = 1;
                ghost.gy[0] = 1;
                ghost.vgx[0] = 0;
                ghost.vgy[0] = 0;
                ghost.ig[0] = 0;

                ghost.gx[1] = 9;
                ghost.gy[1] = 14;
                ghost.vgx[1] = 0;
                ghost.vgy[1] = 0;
                ghost.ig[1] = 0;

                ghost.gx[2] = 9;
                ghost.gy[2] = 12;
                ghost.vgx[2] = 0;
                ghost.vgy[2] = 0;
                ghost.ig[2] = 0;

                ghost.gx[3] = 1;
                ghost.gy[3] = 27;
                ghost.vgx[3] = 0;
                ghost.vgy[3] = 0;
                ghost.ig[3] = 0;
                reiniciar();
                break;
            }
            if (opc == 2)
            { // encerra o jogo
                textColor(WHITE, _BLACK);
                system("cls");
                ComeCome.j = 1;
                break;
            }
        }

        textColor(WHITE, _BLACK);
        linhaCol(24, 1);
        printf("");
        system("cls");
    }
}

void ganhou(){
    // critério para ganhar o jogo
	if(ComeCome.comida == 174){
	system("cls");
	int opc;
    char lista[2][20] = {"JOGAR NOVAMENTE", "SAIR"};
    setlocale(LC_ALL, "");
	linhaCol(2, 5);
    textColor(RED, _BLACK);
	printf("\t\t\t\t\t| ##        ##    ###      #####  ###### |\n");
    printf("\t\t\t\t\t|  ##      ##   ##   ##  ##       ##     |\n");
    printf("\t\t\t\t\t|   ##    ##    ##   ##  ##       #####  |\n");
    printf("\t\t\t\t\t|    ##  ##     ##   ##  ##       ##     |\n");
    printf("\t\t\t\t\t|      ##         ###      #####  ###### |\n\n");
    printf("\t\t\t\t| ######      ##     ###    ##  ##  ##    ###    ##   ## |\n");
    printf("\t\t\t\t| ##         #  #    ## #   ##  ##  ##  ##   ##  ##   ## |\n");
    printf("\t\t\t\t| ##  ###   ######   ##  #  ##  ######  ##   ##  ##   ## |\n");
    printf("\t\t\t\t| ##    #  ##    ##  ##   # ##  ##  ##  ##   ##  ##   ## |\n");
    printf("\t\t\t\t| ######   ##    ##  ##    ###  ##  ##    ###      ###   |\n\n");
    printf("\t\t\t\t\t\tO(a) jogador(a) %s fez %d ponto(s)\n\n", ComeCome.nome, ComeCome.comida);
	 while (true)
        {
            opc = menu(15, 47, 2, lista);
            if (opc == 1)
            { // reinicia o jogo
                linhaCol(1, 1);
                textColor(WHITE, _BLACK);
                system("cls");
                ComeCome.posicao.x = 14;
                ComeCome.posicao.y = 15;
                ComeCome.vx = 0;
                ComeCome.vy = 0;
                ComeCome.comida = 0;
                ComeCome.i = 0;
                ComeCome.sec = 0;
                ComeCome.min = 0;
                ComeCome.hr = 0;
                ComeCome.j = 0;

                ghost.gx[0] = 1;
                ghost.gy[0] = 1;
                ghost.vgx[0] = 0;
                ghost.vgy[0] = 0;
                ghost.ig[0] = 0;

                ghost.gx[1] = 9;
                ghost.gy[1] = 14;
                ghost.vgx[1] = 0;
                ghost.vgy[1] = 0;
                ghost.ig[1] = 0;

                ghost.gx[2] = 9;
                ghost.gy[2] = 12;
                ghost.vgx[2] = 0;
                ghost.vgy[2] = 0;
                ghost.ig[2] = 0;

                ghost.gx[3] = 1;
                ghost.gy[3] = 27;
                ghost.vgx[3] = 0;
                ghost.vgy[3] = 0;
                ghost.ig[3] = 0;
                reiniciar();
                break;
            }
            if (opc == 2)
            { // encerra o jogo
                textColor(WHITE, _BLACK);
                system("cls");
                ComeCome.j = 1;
                break;
            }
        }

        textColor(WHITE, _BLACK);
        linhaCol(24, 1);
        printf("");
        system("cls");
    }
}

void nome(){
    
    printf("\t\t\t\t\t#########################################\n");
    printf("\t\t\t\t\t#   #    #  # # #   #       #   # # #   #\n");
    printf("\t\t\t\t\t#   # # #   #   #   # #   # #   #       #\n");
    printf("\t\t\t\t\t#   #  #    #   #   #  # #  #   # # #   #\n");
    printf("\t\t\t\t\t#   #       #   #   #       #   #       #\n");
    printf("\t\t\t\t\t#   #       # # #   #       #   # # #   #\n");
    printf("\t\t\t\t\t#                                       #\n");
    printf("\t\t\t\t\t#########################################\n");
    printf("\t\t\t\t\t          Digite o seu nome: ");
    gets(ComeCome.nome);
    system("cls");
}

int main()
{
    SetConsoleTitle("Jogo que Ceres gostou");
    menu_inicial();
    inicializar();
    nome();
    while (ComeCome.j == 0)
    {
        teclado();
        teclado_fantasma();
        movimento();
        movimento_fantasma();
        mostrar_mapa();
        cronometro();
        pause();
        morte();
		ganhou();
        Sleep(100);
        set_cursor_position(0, 0);
    }
    system("cls");
    linhaCol(2, 5);
    textColor(RED, _BLACK);
    printf("\t\t\t\t|  ###   #####   #####    ##  ######     ##    #######      ###  |\n");
    printf("\t\t\t\t|##   ## ##   #  ##   #   ##  ##        #  #   ##     #   ##   ##|\n");
    printf("\t\t\t\t|##   ## ######  #####    ##  ##  ###  ######  ##      #  ##   ##|\n");
    printf("\t\t\t\t|##   ## ##    # ##  ##   ##  ##    # ##    ## ##     #   ##   ##|\n");
    printf("\t\t\t\t|  ###   ######  ##   ##  ##  ######  ##    ## #######      ###  |\n\n");
    printf("\t\t\t\t\t\t|#####     ###    #####  |\n");
    printf("\t\t\t\t\t\t|##   #  ##   ##  ##   # |\n");
    printf("\t\t\t\t\t\t|#####   ##   ##  #####  |\n");
    printf("\t\t\t\t\t\t|##      ##   ##  ##  ## |\n");
    printf("\t\t\t\t\t\t|##        ###    ##   ##|\n\n");
    printf("\t\t\t\t\t|########   ###    ######      ##     #####  |\n");
    printf("\t\t\t\t\t|    ##   ##   ##  ##         #  #    ##   # |\n");
    printf("\t\t\t\t\t|    ##   ##   ##  ##  ###   ######   #####  |\n");
    printf("\t\t\t\t\t|##  ##   ##   ##  ##    #  ##    ##  ##  ## |\n");
    printf("\t\t\t\t\t|  ###      ###    ######   ##    ##  ##   ##|\n\n");
	
}
