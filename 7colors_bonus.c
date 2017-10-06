/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* We want a 30x30 board game by default */

#define BOARD_SIZE 10
#define NUM_COLOR 7
#define COLOR_PLAYER1 '^'
#define COLOR_PLAYER2 'v'

/** Represent the actual current board game
 *
 * NOTE: global variables are usually discouraged (plus encapsulation in
 *     an appropriate data structure would also be preferred), but don't worry.
 *     For this first assignment, no dinosaure will get you if you do that.
 */
 
char board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros

/** Retrieves the color of a given board cell */

char get_cell(int x, int y)
{
    return board[y * BOARD_SIZE + x];
}

/** Changes the color of a given board cell */

void set_cell(int x, int y, char color)
{
    board[y * BOARD_SIZE + x] = color;
}

/** Prints the current state of the board on screen
 *
 * Implementation note: It would be nicer to do this with ncurse or even
 * SDL/allegro, but this is not really the purpose of this assignment.
 */
 
void print_board(void){
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c", get_cell(i, j));
        }
        printf("\n");
    }
}
/** LIFO Structure */

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct Pile Pile;
struct Pile
{
    Element *premier;
};

void empiler(Pile *pile, int nvNombre){
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL){
        exit(EXIT_FAILURE);
    }
    nouveau->nombre = nvNombre;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

int depiler(Pile *pile){
    if (pile == NULL){
        exit(EXIT_FAILURE);
    }
    int nombreDepile = 0;
    Element *elementDepile = pile->premier;
    if (pile != NULL && pile->premier != NULL){
        nombreDepile = elementDepile->nombre;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }
    return nombreDepile;
}

void afficherPile(Pile *pile){
    if (pile == NULL){
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;

    while (actuel != NULL){
        printf("%d\n", actuel->nombre);
        actuel = actuel->suivant;
    }

    printf("\n");   
}

int is_empty(Pile *pile){
	if (pile == NULL){
		exit(EXIT_FAILURE);
	}
	else if (pile->premier == NULL){
		return 1;
	}
	else{
		return 0;
	}
}

/** Headers */

void gene_board();
void update_board(char color_player, char color_played, Pile *p_x, Pile *p_y);
int finish();
void prop();

/** Program entry point */

int main(void){
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
	   "*****************************************************\n\n"
	   "Current board state:\n");
	   
	gene_board();
    print_board();
	int num_turn = 0;
	int player_playing = 0;
	char color_played;
	char c;
	Pile p1_x, p1_y, p2_x, p2_y;
	do{
		
		player_playing = num_turn % 2 + 1;
		printf("Player %d playing... color \n", player_playing);
		scanf("%c", &color_played);
		while ( (c = getchar()) != '\n' && c != EOF) { }
		if (player_playing == 1){
			update_board(COLOR_PLAYER1, color_played, &p1_x, &p1_y);
		}
		else{
			update_board(COLOR_PLAYER2, color_played, &p2_x, &p2_y);
		}
		num_turn ++;
		print_board();
		printf("\n");
		
	}while (finish() != 1);
	
    return 0; // Everything went well
}

// Generate randomly the color on the field

void gene_board(){
	char list_color[NUM_COLOR];
	for (int i = 0; i < NUM_COLOR; i++){
		list_color[i] = 'A' + i;
	}
	
	srand(time(NULL));
	int ran_color_xy = -1;
	for (int x = 0; x < BOARD_SIZE; x++){
		for (int y = 0; y < BOARD_SIZE; y++){
			ran_color_xy = (rand() % NUM_COLOR);
			set_cell(x, y, list_color[ran_color_xy]);
		}
	}
	set_cell(0, BOARD_SIZE - 1, COLOR_PLAYER1);
	set_cell(BOARD_SIZE - 1, 0, COLOR_PLAYER2);
}

// Test if the cell selected is on the board and the right color

int test(int x, int y,  char color_played){
	if ( x != -1 && y != -1 && x != BOARD_SIZE && y != BOARD_SIZE){
		if (get_cell(x, y) == color_played){
			return 1;
		}
	else{
		return 0;
		}
	}
	return 0;
}

// Update the board every turn

void update_board(char color_player, char color_played, Pile *p_x, Pile *p_y){
	int current_x, current_y;
	
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (get_cell(i,j) == color_player) {
				empiler(p_x, i);
				empiler(p_y, j);
			}
		}
	}
	
	do{
		current_x = depiler(p_x);
		current_y = depiler(p_y);
		if (test(current_x - 1, current_y, color_played)) {
			empiler(p_x, current_x - 1);
			empiler(p_y, current_y);
		}
		if (test(current_x + 1, current_y, color_played)) {
			empiler(p_x, current_x + 1);
			empiler(p_y, current_y);
		}
		if (test(current_x, current_y - 1, color_played)) {
			empiler(p_x, current_x);
			empiler(p_y, current_y - 1);
		}
		if (test(current_x, current_y + 1, color_played)) {
			empiler(p_x, current_x);
			empiler(p_y, current_y + 1);
		}
		if (get_cell(current_x, current_y) != color_player) {
			set_cell(current_x, current_y, color_player);
		}
	}while ((is_empty(p_x)) != 1);
	
	prop();
}

// Test if the board if there is any cell left on the board to play with

int finish(){
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (get_cell(i,j) >= 'A' && get_cell(i,j) <= 'A' + NUM_COLOR) {
				return 0;
			}
		}
	}
	printf("The end!\n");
	prop();
	return 1;
}

void prop(){
	float counter_p1 = 0;
	float counter_p2 = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (get_cell(i,j) == COLOR_PLAYER1) {
				counter_p1 ++;
			}
			else {
				counter_p2 ++;
			}
		}
	}
	float prop_p1 = (counter_p1 * 100.) / (BOARD_SIZE * BOARD_SIZE *1.);
	float prop_p2 = 100 - prop_p1;
	printf("Player one proportion : %f.\nPlayer two proportion : %f.\n", prop_p1, prop_p2);
}

// Une ligne sur deux en couleurs ou serpent (il progresse d'un en un suivant un serpent)
//Plus d'une certaine proportion (préprocesseur)
//Plus grand nombre de cases au bout d'un nombre de tour fixé (préproc)
//Plus on prend de cases plus on marque de points (non linéaire)

