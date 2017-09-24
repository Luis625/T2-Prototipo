#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'

#define ABERTO '-'
#define FECHADO '+'


typedef struct{
	int i, j, pedacos;
	char estado;
}porta_t;

typedef struct{
	int i, j;
}player_t;

void imprime_mapa(char mapa[][77]){
	int i;
	printf("\n\n\n");
	for(i=0;i<36;i++)
		printf("%s", mapa[i]);
}

void move_jogador(player_t* p, char comando, char mapa[][77]){
	if(comando == CIMA && (mapa[p->i - 1][p->j] == ' ' || mapa[p->i - 1][p->j] == '-'))
		p->i--;
	if(comando == BAIXO && (mapa[p->i + 1][p->j] == ' ' || mapa[p->i + 1][p->j] == '-'))
		p->i++;
	if(comando == ESQUERDA && (mapa[p->i][p->j - 1] == ' ' || mapa[p->i][p->j - 1] == '-'))
		p->j--;
	if(comando == DIREITA && (mapa[p->i][p->j + 1] == ' ' || mapa[p->i][p->j + 1] == '-'))
		p->j++;
	mapa[p->i][p->j] = '@';
}

int mata_vampiro(player_t* player, char mapa[][77]){
	int i, j;
	for (i = player->i - 1; i <= player->i + 1; ++i)
		for (j = player->j - 1; j <= player->j + 1; ++j)
			if (mapa[i][j] == 'v'){
				mapa[i][j] = 'M';
				return 1;
			}
	return 0;
}

void respawn(char mapa[][77], player_t* player){
	int i, j;
	if (player->i < 16){
	for (i = 15; i < 25; ++i)
		for (j = 0; j < 76; ++j)
			if (mapa[i][j] == 'M')
				mapa[i][j] = 'v';
	}else{
	for (i = 0; i < 15; ++i)
		for (j = 0; j < 76; ++j)
			if (mapa[i][j] == 'M')
				mapa[i][j] = 'v';
	}
}

int main(){
	porta_t porta[2];
	player_t jogador;
	jogador.i = 23;
	jogador.j = 2;

	porta[0].i = 16;
	porta[0].j = 35;
	porta[0].pedacos = 3;
	porta[0].estado = FECHADO;

	porta[1].i = 7;
	porta[1].j = 36;
	porta[1].pedacos = 4;
	porta[1].estado = FECHADO;	

	char comando;

	char mapa[][77] = {
		{"###########################################################################\n"},
		{"#          #                 #   #    #   #                               #\n"},
		{"#          #                 #   # v  #   #                               #\n"},
		{"#    v     #                 #            #                               #\n"},
		{"#          #                 ###        ###                               #\n"},
		{"#          #                   #        #                                 #\n"},
		{"#          #                   #        #                                 #\n"},
		{"#      #####                   #####+####                                 #\n"},
		{"#      #                                                       v          #\n"},
		{"#      #                                                                  #\n"},
		{"#    ###                               v                                  #\n"},
		{"#                                                                         #\n"},
		{"#                 v                                                       #\n"},
		{"#                                                                         #\n"},
		{"#                                                                         #\n"},
		{"#                                                                         #\n"},
		{"###################################+#######################################\n"},
		{"#                                                                         #\n"},
		{"#                          v               v                              #\n"},
		{"#                                                                         #\n"},
		{"#                                                                         #\n"},
		{"#                                                                         #\n"},
		{"#                                  v                                      #\n"},
		{"#                                                                         #\n"},
		{"###########################################################################\n"},
		{"             cima             \n"},
		{"               |              \n"},
		{"               w              \n"},
		{"  esquerda - a   d - direita  \n"},
		{"               s              \n"},
		{"               |              \n"},
		{"             baixo            \n"},
		{"                              \n"},
		{"          t -> mata vampiro   \n"},
		{"               ao redor       \n"},
		{"          m -> sai do programa\n\n\n\n\n"},
	};

	mapa[jogador.i][jogador.j] = '@';
	system("clear || cls");
	imprime_mapa(mapa);
	do{
		comando = getchar();

		if(comando == CIMA || comando == BAIXO || comando == ESQUERDA || comando == DIREITA){
			mapa[jogador.i][jogador.j] = ' ';
			move_jogador(&jogador, comando, mapa);

		}else if(comando == 't'){

			if(mata_vampiro(&jogador, mapa)){
				if(jogador.i > 16 && porta[0].pedacos)
					porta[0].pedacos--;
				else if(jogador.i < 16 && porta[1].pedacos)
					porta[1].pedacos--;

				if(!porta[0].pedacos)
					mapa[porta[0].i][porta[0].j] = ' ';
				if(!porta[1].pedacos)
					mapa[porta[1].i][porta[1].j] = ' ';
			}
		}

		if(jogador.i == 15 || jogador.i == 17)
			respawn(mapa, &jogador);

		system("clear || cls");
		imprime_mapa(mapa);

	}while(comando != 'm');

	return 0;
}