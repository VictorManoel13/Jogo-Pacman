#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <stdlib.h>
#define L 20
#define C 29

struct coord
{
	int x;
	int y;
};

// variáveis do pacman
struct PacMan
{
	struct coord posicao;
	int vx;
	int vy;
	int comida;
	int i;	 // pausar
	int sec; // segundos
	int min; // minutos
	int hr;
	int j; // hora
	int oldx;
	int oldy;
};

struct PacMan AllanAllan = {
	{
		.x = 14,
		.y = 15,
	},
	.vx = 0,
	.vy = 0,
	.comida = 0,
	.i = 0,
	.sec = 0,
	.min = 0,
	.hr = 0,
	.j = 0};

// variáveis dos fantasmas
struct Fantasma
{
	int gx[4];
	int gy[4];
	int vgx[4];
	int vgy[4];
	int ig[4];
};

struct Fantasma ghost =
	{   // FANTASMA 1
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
			if (mapa[i][j] == 0)
				mapa[i][j] = '.';
		}
	}
}

void teclado()
{

	if (_kbhit()) // verifica se é tecla
	{
		char c1 = _getch();			// c1 pega a tecla
		if (c1 == -32 || c1 == 115) // todas as setas são -32 e a tecla s é 115
		{
			char c1 = _getch(); // ler de novo, as setas ficam com variáveis diferentes

			AllanAllan.vx = 0;
			AllanAllan.vy = 0;

			switch (c1)
			{
			case 72:
				AllanAllan.vy = -1; // cima
				break;
			case 80:
				AllanAllan.vy = +1; // baixo
				break;
			case 75:
				AllanAllan.vx = -1; // esquerda
				break;
			case 77:
				AllanAllan.vx = +1; // direita
				break;
			case 115:
				AllanAllan.i = 2; // pause
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

		
			switch (ghost.ig[i])
			{
			case 0:
				ghost.vgx[i] = -1;
				break;
			case 1:
				ghost.vgx[i] = +1;
				break;
			case 2:
				ghost.vgy[i] = -1;
				break;
			case 3:
				ghost.vgy[i] = +1;
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
		// nova posição de fantasma
		
		int ngx[i];
		int ngy[i];
		ngx[i] = ghost.vgx[i] + ghost.gx[i];
		ngy[i] = ghost.vgy[i] + ghost.gy[i];
		// verifica se é parede, se for parede, então o próximo movimento é aleatório
		if (mapa[ngx[i]][ngy[i]] == 1 || mapa[ngx[i]][ngy[i]] == 2)
		{
			ghost.vgx[i] = 0;
			ghost.vgy[i] = 0;
			
			if(n==0){
				srand(time(NULL));
				ghost.ig[i] = rand() % 4;
				n = 1;
			} else if(n==1){
				ghost.ig[i] = rand() % 4;
			}
		}
		// caso a nova posição seja a comdia, a antiga recebe comida também
		if (mapa[ngx[i]][ngy[i]] == '.')
		{
			mapa[ghost.gx[i]][ghost.gy[i]] = '.';
		}
		// caso a nova posição seja espaço vazio, a antiga recebe espaço vazio também
		if (mapa[ngx[i]][ngy[i]] == ' ')
		{
			mapa[ghost.gx[i]][ghost.gy[i]] = ' ';
		}
		// fantasma verifica se a nova posição é o pacman, se for o pacman, então o programa encerra
		if (mapa[ngx[i]][ngy[i]] == 3)
		{
			AllanAllan.i = 3;
		}
		// movimento do fantasma
		ghost.gx[i] += ghost.vgx[i];
		ghost.gy[i] += ghost.vgy[i];
		// nova posição do fantasma
		mapa[ghost.gx[0]][ghost.gy[0]] = 2;
		mapa[ghost.gx[1]][ghost.gy[1]] = 2;
		mapa[ghost.gx[2]][ghost.gy[2]] = 2;
		mapa[ghost.gx[3]][ghost.gy[3]] = 2;
	}
}

void movimento()
{
	float j=0;
	// antiga posição
	mapa[AllanAllan.posicao.y][AllanAllan.posicao.x] = ' ';
	// nova posição
	int nx = AllanAllan.vx + AllanAllan.posicao.x;
	int ny = AllanAllan.vy + AllanAllan.posicao.y;
	// verifca se é parede
	if (mapa[ny][nx] == 1)
	{

		AllanAllan.vx = 0;
		AllanAllan.vy = 0;
	}
	// verifica se é fantasma
	if (mapa[ny][nx] == 2)
	{
		AllanAllan.i = 3;
	}
	// movimento
	while(j!=10){
		j=j+0.5;
	}
	if(j==10){
	AllanAllan.posicao.x += AllanAllan.vx;
	AllanAllan.posicao.y += AllanAllan.vy;
	}
	// verifica se é comida
	if (mapa[ny][nx] == '.')
	{
		AllanAllan.comida++;
	}
	// nova posição do pacman
	mapa[AllanAllan.posicao.y][AllanAllan.posicao.x] = 3;
}

void cornometro()
{

	if (AllanAllan.sec == 590)
	{
		AllanAllan.sec = 0;
		AllanAllan.min++;
	}

	if (AllanAllan.min == 600)
	{
		AllanAllan.min = 0;
		AllanAllan.hr++;
	}

	if (AllanAllan.hr == 240)
	{
		AllanAllan.hr = 0;
	}

	Sleep(100); // tem a função de pausar a execução por um determinado tempo
	AllanAllan.sec += 2.8;
}

void mostrar_mapa()
{
	int i, j;

	printf("Pontos: %d\t%dh:%dm:%ds\n", AllanAllan.comida, AllanAllan.hr / 10, AllanAllan.min, AllanAllan.sec / 10);

	for (i = 0; i < L; i++)
	{
		for (j = 0; j < C; j++)
		{
			printf("%c", mapa[i][j]);
		}
		printf("\n");
	}
	printf("Aperte S duas vezes para pausar\n");
}

// fixar mapa
void set_cursor_position(int x, int y)
{
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void pause()
{
	int j = 0, k;
	while (AllanAllan.i == 2)
	{

		if (j == 0)
		{
			system("cls");
			j = 1;
		}
		printf("Jogo pausado\n");
		printf("Para retornar ao jogo digite 1: ");
		scanf("%d", &k);
		if (k == 1)
		{
			system("cls");
			AllanAllan.i = 1;
			j = 0;
		}
		Sleep(100);
		set_cursor_position(0, 0);
	}
}

void morte()
{
	if (AllanAllan.i == 3)
	{
		AllanAllan.j = 1;
		AllanAllan.i = 3;
	}
}

int main()
{

	SetConsoleTitle("Jogo que Ceres gostou");
	inicializar();
	while (AllanAllan.j == 0)
	{
		teclado();
		teclado_fantasma();
		movimento();
		movimento_fantasma();
		mostrar_mapa();
		cornometro();
		pause();
		morte();
		
		set_cursor_position(0, 0);
	}
	system("cls");
	if (AllanAllan.i == 3)
	{
		printf("Voce perdeu\n");
	}
	printf("Obrigado por jogar");
	printf("Oi");
	int h;
}
