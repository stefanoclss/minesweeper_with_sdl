#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include "help_functions.h"
#include "GUI.h"
#define TOTAL_BOMBS 20
#define HORIZONTAL_CELS 10
#define VERTICAL_CELS 10
/* ,  *pre_for_loop pointer to function to use inside function
 void for_loop_proto(void (*pre_for_loop_func) () , int infinum_i , int supremum_i , int infinum_j , int supremum_j , *in_for_loop_func) () ,*post_for_loop_func) () ,ptr_field)
 {
 pre_for_loop_func
 	 *double for loop with boundaries
 post_for_loop_func
 }
 */



//HULPFUNCTIES 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////										BACKEND FUNCTIONS																	///////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int find(int move_x ,int move_y , int horizontal_cels)
{

	int offset_bytes = (move_x + (move_y * horizontal_cels )) * sizeof(struct Cell);    //hulpfunctie voor het zoeken van een elemnt op de grid
	return offset_bytes;
}


/*
        Count all the mines in the 8 adjacent
        cells

            N.W   N   N.E
              \   |   /
               \  |  /
            W----Cell----E
                 / | \
               /   |  \
            S.W    S   S.E

        Cell-->Current Cell (row, col)
        N -->  North        (row-1, col)
        S -->  South        (row+1, col)
        E -->  East         (row, col+1)
        W -->  West            (row, col-1)
        N.E--> North-East   (row-1, col+1)
        N.W--> North-West   (row-1, col-1)
        S.E--> South-East   (row+1, col+1)
        S.W--> South-West   (row+1, col-1)
*/      // mentioned in references!

void check_suroundings(struct Cell *ptr_field ,int x0,int y0 , int bombs_or_zeroes , int width_field , int height_field)
{
	//printf("\n do i check the suroundings???????");
	if (bombs_or_zeroes == 1)    //check for bombs
	{
		int ctr = 0;
		for (int i = x0 - 1 ; i < x0 + 2 ; i++)
		{
			for (int j = y0 - 1 ; j < y0 + 2 ; j++)
			{
				printf("\nthis is the value we are checking for bomb %c cur_x : %d cur_y : %d",*(ptr_field + find(i , j , width_field))->actual_value , i , j );
				if (i < 0 || j < 0 || i > (width_field - 1) || j > (height_field - 1))
				{
					continue;
				}
				else if (*(ptr_field + find(i , j , width_field))->actual_value == 'B')         //look for all mines and increment ctr
				{
					ctr++;
				}

			}
		}
		if (ctr == 0)
		{
			if (*(ptr_field + find(x0 , y0 , width_field))->vissible_value == 'F')     // if vissible value is F don't hint the player
			{
				mine_checker(ptr_field , x0 , y0, width_field , height_field);
			}
			else
			{
			*(ptr_field + find(x0 , y0 , width_field))->vissible_value = '0';         //if there are no adjecent mines change the values
			*(ptr_field + find(x0 , y0 , width_field))->actual_value = ' ';
			mine_checker(ptr_field , x0 , y0 , width_field , height_field);                          //call mine checker which wil recursivly call al adjecent spots
			}

		}
		else
		{
			char return_value = ctr + '0';                            //zet de value om naar een character
			*(ptr_field + find(x0 , y0 , width_field))->vissible_value = return_value;
			*(ptr_field + find(x0 , y0 , width_field))->actual_value = return_value;
			 mine_checker(ptr_field , x0 , y0 , width_field , height_field);                        // roep minechecker op (zal niet loopen)
		}

	}
	else
	{
		for (int i = x0 - 1 ; i < x0 + 2 ; i++)
		{
			for (int j = y0 - 1 ; j < y0 + 2 ; j++)
			{

				if (i == x0 && j == y0)                          //functie wordt opgeroepen indien een spot 0 heeft,
					                                             //markeer de actuele value als gecontroleerd om eeuwige loopen te vermijden
				{
					*(ptr_field + find(i , j , width_field))->actual_value = ' ';
				}
				else if (i < 0 || j < 0 || i > (width_field - 1) || j > (height_field - 1))     //ga niet zoeken buiten de array
				{
					continue;
				}
				else if (*(ptr_field + find( i , j , width_field))->vissible_value == 'F' ||*(ptr_field + find(i , j , width_field))->vissible_value == '0' || *(ptr_field + find(i , j , width_field))->actual_value == 'B')
				{
					continue;      //skip als dit een bom/vlag of 0 is
				}
				else
				{
					check_suroundings(ptr_field , i , j , 1 , width_field  , height_field);   //kijk naar bommen voor
				}

			}
		}
	}
}



void mine_checker(struct Cell *ptr_field , int move_x, int move_y , int width_field , int height_field)
{
	if (*(ptr_field + find(move_x , move_y , width_field))->vissible_value == 'q' && !(*(ptr_field + find(move_x , move_y , width_field))->actual_value == 'B'))   //indien we niet weten wat er zich op de positie bevind en dit geen bom is dan
	{
		check_suroundings(ptr_field , move_x , move_y , 1 , width_field  , height_field);                           //dan kijken we hoeveel mijnen er rondom het element zitten
	}
	else if(*(ptr_field +  find(move_x , move_y , width_field))->vissible_value == '0')
	{
		check_suroundings(ptr_field , move_x , move_y , 0 , width_field , height_field);                           //kijk naar omliggende spots

	}

}



int el_ctr(char el , struct Cell *ptr_field ,int vis_or_act , int columns , int rows ) //telt het aantal elementen van iets
{
	int ctr = 0;
	for (int i = 0 ; i < columns ; i++)
	{
		for (int j = 0 ; j < rows ; j++)
		{
			if (vis_or_act == 1)          //telt elementen van el en vergelijkt deze met de visuele value
			{
				if (el == *(ptr_field + find(i , j , columns))->vissible_value)
				{
					ctr++;
				}
			}
			else if (vis_or_act == 2)     //teller voor te kijken of alle vlaggen op alle bommen staan
			{
				if (el == *(ptr_field + find(i , j , columns))->vissible_value && *(ptr_field + find(i , j , columns))->actual_value == 'B')
				{
					ctr++;
				}
			}
			else       					//telt elementen van de actuele value
			{
				if (el == *(ptr_field + find(i , j , columns))->actual_value)
				{
					ctr++;
				}
			}

		}
	}
	return ctr;
}


 void place_mines(int first_move_x, int first_move_y, struct Cell *ptr_field , struct Constants info)
{
	int i = 0;
	int upper_bound_x = info.no_vertical_cels ;
	int upper_bound_y = info.no_horizontal_cels ; 
	while (i != info.no_Bombs )
	
	{
		int random_x = rand() % (upper_bound_y);   //mentioned in references
		int random_y = rand() % (upper_bound_x);
		if ((random_x == first_move_x  || random_x == first_move_x + 1 || random_x == first_move_x - 1) &&
			(random_y == first_move_y || random_y == first_move_y - 1 || random_y == first_move_y + 1 ))     //if test voor mijnen rondom eerste zet de vermijden
		{

			continue;
		}
		else if (*(ptr_field + find(random_x , random_y , info.no_horizontal_cels))->actual_value == 'B')    //we willen niet 2 bommen op dezelfde plek plaatsten(wat zou resulteren in minder bommen dan total BOMBS)
		{
			continue;
		}
		else
		{
			printf("\n this was the old value at the pointer %c "  ,*(ptr_field + find(random_x , random_y , info.no_horizontal_cels))->actual_value );
			*(ptr_field + find(random_x , random_y , info.no_horizontal_cels))->vissible_value = 'q';
			*(ptr_field + find(random_x , random_y , info.no_horizontal_cels))->actual_value = 'B';        //de actuele value van een BOM is B
			printf("\n this was the new value at the pointer %c "  ,*(ptr_field + find(random_x , random_y , info.no_horizontal_cels))->actual_value );

			i++;
		}
	}
}

//HULPFUNCTIES 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////										FRONTEND FUNCTIONS																	///////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print_grid_frontend(struct Cell *ptr_field , struct Constants *info , char action) //also used for saving stuff
{

	for (int i=0; i < info->no_vertical_cels; i++)
	{
		printf("\n");
		for (int j=0; j < info->no_horizontal_cels ; j++)
		{
			int horizontal_cels = info->no_horizontal_cels;
			switch (action)
			{
			case '0':   //making of start grid

				*(ptr_field + find(j, i , horizontal_cels))->vissible_value = 'q';				//generate new_field
				*(ptr_field + find(j, i , horizontal_cels))->actual_value = 'q';
				break;
			case '1':  //making of normal grid //only for debugging now
				printf("%c" , *(ptr_field + find(j, i , horizontal_cels))->vissible_value);
				//printf("%c" , *(ptr_field + find(j, i , horizontal_cels))->actual_value);
				break;

			case '2':  //making of cheat grid
				break;

			}
		}
	}
}




