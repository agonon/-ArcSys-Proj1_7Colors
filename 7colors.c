/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>
/* We want a 30x30 board game by default */
#define BOARD_SIZE 30
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
void print_board(void)
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c", get_cell(i, j));
        }
        printf("\n");
    }
}

void gene_board();
int win();
void update_board(char color_player, char color_played);

/** Program entry point */
int main(void)
{
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
	   "*****************************************************\n\n"
	   "Current board state:\n");
gene_board();
    print_board();
int num_turn = 0;
int player_playing = 0;
char color_played;
char c;
do{
player_playing = num_turn % 2 + 1;
printf("Player %d playing... color \n", player_playing);
scanf("%c", &color_played);
while ( (c = getchar()) != '\n' && c != EOF) { }
if (player_playing == 1){
update_board(COLOR_PLAYER1, color_played);
}
else{
update_board(COLOR_PLAYER2, color_played);
}
num_turn ++;
print_board();
}while (win() != 1);

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

void update_board(char color_player, char color_played){
int updated_cell = 0;
do{
updated_cell = 0;
for (int x = 0; x < BOARD_SIZE; x++){
for (int y = 0; y < BOARD_SIZE; y++){
int friendly_neighbour = 0;
if (test(x - 1, y, color_player) || test(x, y-1, color_player) || test(x + 1, y, color_player) || test(x, y + 1, color_player)){
friendly_neighbour = 1;
}
if (test(x, y, color_played) == 1 && friendly_neighbour == 1){
set_cell(x, y, color_player);
updated_cell ++;
}
}
}
}while (updated_cell != 0);
}

int win(){

}
int propor_player(char color_player){
int num_owned = 0;
double propor;
for (int i = 0; i < BOARD_SIZE; i++){
for (int j = 0; j < BOARD_SIZE; j++){

// Une ligne sur deux en couleurs ou serpent (il progresse d'un en un suivant un serpent)
//Plus d'une certaine proportion (préprocesseur)
//Plus grand nombre de cases au bout d'un nombre de tour fixé (préproc)
//Plus on prend de cases plus on marque de points (non linéaire)


