#ifndef function_example
#define function_example
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <SDL2/SDL.h>
static SDL_Renderer *renderer;
static SDL_Texture *digit_0_texture;
static SDL_Texture *digit_1_texture;
static SDL_Texture *digit_2_texture;
static SDL_Texture *digit_3_texture;
static SDL_Texture *digit_4_texture;
static SDL_Texture *digit_5_texture;
static SDL_Texture *digit_6_texture;
static SDL_Texture *digit_7_texture;
static SDL_Texture *digit_8_texture;
static SDL_Texture *digit_C_texture;
static SDL_Texture *digit_F_texture;
struct Constants field_info;
struct Cell
{
	char vissible_value [2];
	char actual_value [2];
};

struct Constants 
{   
   int  no_horizontal_cels;
   int  no_vertical_cels;
   int  no_Bombs;
   int  bombs_set;
};
void check_suroundings(struct Cell *ptr_field ,int x0,int y0 , int bombs_or_zeroes , struct Constants info);
void print_grid_frontend(struct Cell *ptr_field , struct Constants *info , char action);
void mine_checker(struct Cell *ptr_field , int move_x, int move_y , struct Constants info);
int find(int move_x ,int move_y , int vertical_cels);
int el_ctr(char el , struct Cell *ptr_field ,int vis_or_act);
void make_move(struct Cell *ptr_field);
void print_grid(struct Cell *ptr_field , int actual) ;
void place_mines(int first_move_x, int first_move_y, struct Cell *ptr_field , struct Constants info);
void update_field(struct Cell *ptr_field, int move_x, int move_y , struct Constants *info);
//HULPFUNCTIES 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////										FRONTEND FUNCTIONS																	///////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
