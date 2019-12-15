#include "GUI.h"
#include <math.h>
#include "help_functions.h"
#define MAXLINE 1000
#define POSSIBLE_FIGURES 11




int getline2(char s[],int lim);
char get_char();
/*
 * Deze renderer wordt gebruikt om figuren in het venster te tekenen. De renderer
 * wordt geïnitialiseerd in de initialize_window-functie.
 */
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
static SDL_Texture *digit_B_texture;
static SDL_Texture *game_over_texture;
static SDL_Texture *you_won_texture;
static SDL_Texture *yes_texture;
static SDL_Texture *no_texture;



/*
 * Onderstaande twee lijnen maken deel uit van de minimalistische voorbeeldapplicatie:
 * ze houden de laatste positie bij waar de gebruiker geklikt heeft.
 */
int mouse_x = 0;
int mouse_y = 0;

/*
 * Geeft aan of de applicatie moet verdergaan.
 * Dit is waar zolang de gebruiker de applicatie niet wilt afsluiten door op het kruisje te klikken.
 */
int should_continue = 1;

/*
 * Dit is het venster dat getoond zal worden en waarin het speelveld weergegeven wordt.
 * Dit venster wordt aangemaakt bij het initialiseren van de GUI en wordt weer afgebroken
 * wanneer het spel ten einde komt.
 */
static SDL_Window *window;



/*
 * Vangt de input uit de GUI op. Deze functie is al deels geïmplementeerd, maar je moet die zelf
 * nog afwerken. Je mag natuurlijk alles aanpassen aan deze functie, inclusies return-type en argumenten.
 */

void read_input(struct Cell *ptr_field , struct Constants *info) 
{
	SDL_Event event;

	/*
	 * Handelt alle input uit de GUI af.
	 * Telkens de speler een input in de GUI geeft (bv. een muisklik, muis bewegen, toets indrukken enz.)
	 * wordt er een 'event' (van het type SDL_Event) gegenereerd dat hier wordt afgehandeld.
	 *
	 * Niet al deze events zijn relevant voor jou: als de muis bv. gewoon wordt bewogen, hoef
	 * je niet te reageren op dit event.
	 * We gebruiken daarom de is_relevant_event-functie die niet-gebruikte events wegfiltert.
	 *
	 * Zie ook https://wiki.libsdl.org/SDL_PollEvent en http://www.parallelrealities.co.uk/2011_09_01_archive.html
	 */
	while (! (SDL_PollEvent(&event) && is_relevant_event(&event)))
	 {
		 //printf("\n skippinggggg");
	 }

	switch (event.type) 
	{
	case SDL_QUIT:
		/* De gebruiker heeft op het kruisje van het venster geklikt om de applicatie te stoppen. */
		should_continue = 0;
		break;

	case SDL_MOUSEBUTTONDOWN:
		/*
		 * De speler heeft met de muis geklikt: met de onderstaande lijn worden de coördinaten in het
		 * het speelveld waar de speler geklikt heeft bewaard in de variabelen mouse_x en mouse_y.
		 */
		mouse_x = event.button.x;
		mouse_y = event.button.y;
		int place_x = 0;
		int place_y = 0;
		for (int i = 0 ; i < info->no_horizontal_cels  ; i++)
		{
			if (i * IMAGE_WIDTH > mouse_x)
			{
				break;
			}
			else
			{
				place_x = place_x + 1;
			}
		}
		for (int j = 0 ; j < info->no_vertical_cels ; j++)
		{
			if (j * IMAGE_WIDTH > mouse_y)
			{
				break;
			}

			else
			{
				place_y = place_y + 1;
			}
		}
		place_x = place_x - 1;
		place_y = place_y - 1;
		//printf("\n this is the bombset %d" , info->bombs_set);
		printf("\n mouse_x : %d \t mouse_y : %d" , place_x  , place_y);
		if (info->bombs_set == 0 && mouse_x  != 0 && mouse_y != 0) //doesn't matter if you clicked left or right, bombs arent set yet!
		{
			place_mines(place_x, place_y , ptr_field , *info);
			printf("hopefully you have updated correctly");
			mine_checker(ptr_field ,place_x , place_y , info->no_horizontal_cels , info->no_vertical_cels );    //for debugging purposes struct hasn't been used 
			info->bombs_set = 1;
		}
		else if (info->continue_game == 0 || info->continue_game == 2)
		{
			if(mouse_y > (WINDOW_HEIGHT / 2))
			{
				if(mouse_x > (WINDOW_WIDTH / 2))
				{
					should_continue = 0; //end game
				}
				else 
				{
					printf("\n starting new game");
					print_grid_frontend(ptr_field , info , '0');
					info->continue_game = 1;
					info->bombs_set = 0;
				}
			}
			else
			{
				printf("\n not clicking on the right place");
			}
			

		}
		else if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (*(ptr_field + find(place_x , place_y , info->no_horizontal_cels))->actual_value == 'B')
			{
				info->continue_game = 0;
			}
			else
			{
				mine_checker(ptr_field ,place_x , place_y , info->no_horizontal_cels , info->no_vertical_cels );
			}
			
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			int x = place_x;
			int y = place_y; //note make a function of all written beneath (we define x and y because the original code used this)
			printf("\n am i clicking right?");
			if (*(ptr_field + find (x , y, info->no_horizontal_cels))->vissible_value == 'F')
				{
					if (*(ptr_field + find (x , y, info->no_horizontal_cels))->actual_value == 'B')    //indien de positie waar men een vlag wilt wegnemen een bom bevat geef q als visual
					{
						*(ptr_field + find (x , y, info->no_horizontal_cels))->vissible_value = 'q';
					}
					else if (*(ptr_field + find (x , y, info->no_horizontal_cels))->actual_value == 'q')     //indien het actuele q is (kon met or met vorige if)
					{
						*(ptr_field + find (x , y, info->no_horizontal_cels))->vissible_value = 'q';
					}
					else if (*(ptr_field + find (x , y, info->no_horizontal_cels))->actual_value == ' ')   //zet een nul als er geen bommen zich rondom bevinden
					{
						*(ptr_field + find (x , y , info->no_horizontal_cels))->vissible_value = '0';
					}
					else														//anders vervang je visueel gwn door de actuele waarde
					{
						*(ptr_field + find (x , y, info->no_horizontal_cels))->vissible_value = *(ptr_field + find (x , y , info->no_horizontal_cels))->actual_value;
						mine_checker(ptr_field , x, y , info->no_horizontal_cels , info->no_vertical_cels);
					}

				}
			else if (el_ctr('F' , ptr_field, 1 , info->no_horizontal_cels , info->no_vertical_cels) >= info->no_Bombs)           //buitenste tak als alle vlaggen zijn gezet verwijder een vlag
			{
				printf("\n please remove a flag all flags are set, not all of them pinpoint bombs \n"); //hier is een visuele functie nodig
			}
			else														//anders zet je gwn een vlag op het vlakje
			{
				*(ptr_field + find(x , y , info->no_horizontal_cels))->vissible_value = 'F';
			}
		}
		break;

	}

}
void new_game(int action)
{
	printf("\n do you get to here?");
	SDL_Event event;
	
	SDL_RenderClear(renderer);
	if (action == 0)
	{
		SDL_Rect rectangle_question = {0 , 0, WINDOW_WIDTH , WINDOW_HEIGHT / 2};
		SDL_Rect yes = {0 , WINDOW_HEIGHT / 2 , WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2};
		SDL_Rect no = {WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 , WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2};
		SDL_RenderCopy(renderer, game_over_texture, NULL, &rectangle_question);
		SDL_RenderCopy(renderer, yes_texture, NULL, &yes);
		SDL_RenderCopy(renderer, no_texture, NULL, &no);	
	}
	else if (action == 2)
	{
		SDL_Rect rectangle_question = {0 , 0, WINDOW_WIDTH , WINDOW_HEIGHT / 2};
		SDL_Rect yes = {0 , WINDOW_HEIGHT / 2 , WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2};
		SDL_Rect no = {WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 , WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2};
		SDL_RenderCopy(renderer, you_won_texture, NULL, &rectangle_question);
		SDL_RenderCopy(renderer, yes_texture, NULL, &yes);
		SDL_RenderCopy(renderer, no_texture, NULL, &no);	
	}
	SDL_RenderPresent(renderer);
}

void draw_window(struct Cell *ptr_field , struct Constants *info) 
{

	SDL_RenderClear(renderer);
	if (info->continue_game == 1)
	{
		int x_pos , y_pos;
		for (int i=0; i < info->no_vertical_cels ; i++)
		{
			for (int j=0; j < info->no_horizontal_cels  ; j++)
			{
				x_pos = j * IMAGE_WIDTH;
				y_pos = i * IMAGE_HEIGHT;
				//char value_2 = *(ptr_field + find(j , i , info->no_vertical_cels))->actual_value;
				char value = *(ptr_field + find(j , i , info->no_horizontal_cels))->vissible_value;
				SDL_Rect rectangle = {x_pos , y_pos, IMAGE_WIDTH, IMAGE_HEIGHT };

				switch (value)
				{
				case 'q':
					SDL_RenderCopy(renderer, digit_C_texture, NULL, &rectangle);
					break;

				case '0':
					SDL_RenderCopy(renderer, digit_0_texture, NULL, &rectangle);
					break;

				case '1':
					SDL_RenderCopy(renderer, digit_1_texture, NULL, &rectangle);
					break;

				case '2':
					SDL_RenderCopy(renderer, digit_2_texture, NULL, &rectangle);
					break;

				case '3':
					SDL_RenderCopy(renderer, digit_3_texture, NULL, &rectangle);
					break;

				case '4':
					SDL_RenderCopy(renderer, digit_4_texture, NULL, &rectangle);
					break;

				case '5':
					SDL_RenderCopy(renderer, digit_5_texture, NULL, &rectangle);
					break;

				case '6':
					SDL_RenderCopy(renderer, digit_6_texture, NULL, &rectangle);
					break;

				case '7':
					SDL_RenderCopy(renderer, digit_7_texture, NULL, &rectangle);
					break;

				case '8':
					SDL_RenderCopy(renderer, digit_8_texture, NULL, &rectangle);
					break;

				case 'F':
					SDL_RenderCopy(renderer, digit_F_texture, NULL, &rectangle);
					break;
				
				default:
					printf("\n hidden value %c" , *(ptr_field + find(j , i , info->no_vertical_cels))->vissible_value);
					break;
				}

			}
		}
		SDL_RenderPresent(renderer);
	}
	else if (info->continue_game == 0) //you lost
	{
		new_game(0);
	}
	else if (info->continue_game == 2)
	{
		new_game(2);
	}
	else
	{
		printf("\n weird things have happend this shouldn't occur");
	}
	
}
void check_win(struct Cell *ptr_field , struct Constants *info)
{
	if (el_ctr('q' , ptr_field , 0 , info->no_horizontal_cels , info->no_vertical_cels) == 0 || el_ctr('F', ptr_field, 2 , info->no_horizontal_cels , info->no_vertical_cels) == info->no_Bombs)
	{
		info->continue_game = 2;
	}
 
}

/*
 * Initialiseert het venster en alle extra structuren die nodig zijn om het venster te manipuleren.
 */
void initialize_window(const char *title) {
	/*
	 * Code o.a. gebaseerd op:
	 * http://lazyfoo.net/tutorials/SDL/02_getting_an_image_on_the_screen/index.php
	 */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	/* Maak het venster aan met de gegeven dimensies en de gegeven titel. */
	window = SDL_CreateWindow(title, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		/* Er ging iets verkeerd bij het initialiseren. */
		printf("Couldn't set screen mode to required dimensions: %s\n", SDL_GetError());
		exit(1);
	}

	/* Initialiseert de renderer. */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	/* Laat de default-kleur die de renderer in het venster tekent wit zijn. */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

int is_relevant_event(SDL_Event *event) 
{
      if (event == NULL) 
	  {
          return 0;
      }
	return (event->type == SDL_MOUSEBUTTONDOWN) || (event->type == SDL_QUIT);
}

/*
 * Dealloceert alle SDL structuren die geïnitialiseerd werden.
 */
void free_gui() 
{
	/* Dealloceert de SDL_Textures die werden aangemaakt. */ //use fopen  for this stuff
	SDL_DestroyTexture(digit_F_texture);
	SDL_DestroyTexture(digit_C_texture);
	SDL_DestroyTexture(digit_B_texture);
	SDL_DestroyTexture(digit_0_texture);
	SDL_DestroyTexture(digit_1_texture);
	SDL_DestroyTexture(digit_2_texture);
	SDL_DestroyTexture(digit_3_texture);
	SDL_DestroyTexture(digit_4_texture);
	SDL_DestroyTexture(digit_5_texture);
	SDL_DestroyTexture(digit_6_texture);
	SDL_DestroyTexture(digit_7_texture);
	SDL_DestroyTexture(digit_8_texture);
	SDL_DestroyTexture(game_over_texture);
	SDL_DestroyTexture(you_won_texture);
	SDL_DestroyTexture(yes_texture);
	SDL_DestroyTexture(no_texture);
	/* Dealloceert het venster. */
	SDL_DestroyWindow(window);
	/* Dealloceert de renderer. */
	SDL_DestroyRenderer(renderer);

	/* Sluit SDL af. */
	SDL_Quit();
}

/*
 * Laadt alle afbeeldingen die getoond moeten worden in.
 */


void initialize_textures() 
{
	SDL_Surface* game_over_texture_path = SDL_LoadBMP("Images/game_over.bmp");
	SDL_Surface* you_won_texture_path = SDL_LoadBMP("Images/you_won.bmp");
	SDL_Surface* yes_texture_path = SDL_LoadBMP("Images/yes.bmp");
	SDL_Surface* no_texture_path = SDL_LoadBMP("Images/no.bmp");
	SDL_Surface* digit_1_texture_path = SDL_LoadBMP("Images/1.bmp");
	SDL_Surface* digit_0_texture_path = SDL_LoadBMP("Images/0.bmp");
	SDL_Surface* digit_2_texture_path = SDL_LoadBMP("Images/2.bmp");
	SDL_Surface* digit_3_texture_path = SDL_LoadBMP("Images/3.bmp");
	SDL_Surface* digit_4_texture_path = SDL_LoadBMP("Images/4.bmp");
	SDL_Surface* digit_5_texture_path = SDL_LoadBMP("Images/5.bmp");
	SDL_Surface* digit_6_texture_path = SDL_LoadBMP("Images/6.bmp");
	SDL_Surface* digit_7_texture_path = SDL_LoadBMP("Images/7.bmp");
	SDL_Surface* digit_8_texture_path = SDL_LoadBMP("Images/8.bmp");
	SDL_Surface* digit_F_texture_path = SDL_LoadBMP("Images/flagged.bmp");
	SDL_Surface* digit_C_texture_path = SDL_LoadBMP("Images/covered.bmp");
	SDL_Surface* digit_B_texture_path = SDL_LoadBMP("Images/BOMB.bmp");
	game_over_texture = SDL_CreateTextureFromSurface(renderer, game_over_texture_path);
	you_won_texture = SDL_CreateTextureFromSurface(renderer, you_won_texture_path);
	yes_texture = SDL_CreateTextureFromSurface(renderer, yes_texture_path);
	no_texture = SDL_CreateTextureFromSurface(renderer, no_texture_path);
	digit_C_texture = SDL_CreateTextureFromSurface(renderer, digit_C_texture_path);
	digit_B_texture = SDL_CreateTextureFromSurface(renderer, digit_B_texture_path);
	digit_F_texture = SDL_CreateTextureFromSurface(renderer, digit_F_texture_path);
	digit_0_texture = SDL_CreateTextureFromSurface(renderer, digit_0_texture_path);
	digit_1_texture = SDL_CreateTextureFromSurface(renderer, digit_1_texture_path);
	digit_2_texture = SDL_CreateTextureFromSurface(renderer, digit_2_texture_path);
	digit_3_texture = SDL_CreateTextureFromSurface(renderer, digit_3_texture_path);
	digit_4_texture = SDL_CreateTextureFromSurface(renderer, digit_4_texture_path);
	digit_5_texture = SDL_CreateTextureFromSurface(renderer, digit_5_texture_path);
	digit_6_texture = SDL_CreateTextureFromSurface(renderer, digit_6_texture_path);
	digit_7_texture = SDL_CreateTextureFromSurface(renderer, digit_7_texture_path);
	digit_8_texture = SDL_CreateTextureFromSurface(renderer, digit_8_texture_path);
	SDL_FreeSurface(game_over_texture_path);
	SDL_FreeSurface(you_won_texture_path);
	SDL_FreeSurface(yes_texture_path);
	SDL_FreeSurface(no_texture_path);
	SDL_FreeSurface(digit_B_texture_path);
	SDL_FreeSurface(digit_C_texture_path);
	SDL_FreeSurface(digit_F_texture_path);
	SDL_FreeSurface(digit_0_texture_path);
	SDL_FreeSurface(digit_1_texture_path);
	SDL_FreeSurface(digit_2_texture_path);
	SDL_FreeSurface(digit_3_texture_path);
	SDL_FreeSurface(digit_4_texture_path);
	SDL_FreeSurface(digit_5_texture_path);
	SDL_FreeSurface(digit_6_texture_path);
	SDL_FreeSurface(digit_7_texture_path);
	SDL_FreeSurface(digit_8_texture_path);
	
}

/*
 * Initialiseert onder het venster waarin het speelveld getoond zal worden, en de texture van de afbeelding die getoond zal worden.
 * Deze functie moet aangeroepen worden aan het begin van het spel, vooraleer je de spelwereld begint te tekenen.
 */
void initialize_gui(struct Cell *ptr_field , struct Constants *info) 
{
	initialize_window("Minesweeper");
	initialize_textures();
	print_grid_frontend(ptr_field , info , '0');
}

int main(int argc, char *argv[]) 
{
	srand(time(NULL));  
	if( argc == 0 ) 
	{
      printf("No arguments given which were expected.\n");
   	}

   else if( argc = 6 ) 
   {
	//notes for today/tomorrow use arg
	char line[MAXLINE];
	int possible_field = 1;
	int length_number;
	int parameters_checked = 0;
	int continue_loop = 1;       //true could of used bool library with true and flase but this gives us more options ttz 0,1,2, etc
	int opt, WIDTH_FIELD , HEIGHT_FIELD , AMOUNT_OF_BOMBS; //code mentioned in references. 2)
		while ((--argc >0 && **++argv =='-') )
		{
			while ((opt = *++*argv) != '\0' && continue_loop == 1)
			{
				switch (opt) 
				{
					case 'w':
						length_number = string_length(*(argv + 1));
						WIDTH_FIELD = string_to_number(*(argv + 1) , length_number);
						//printf("\n this is the width of the field: %d", WIDTH_FIELD);
						parameters_checked++;
						if (parameters_checked == 3)                         //make this generic occurs 3 times
						{
							continue_loop = 0;
							break;
						}
						else
						{
							argv = argv + length_number;
							break;
						}
					case 'h':
						length_number = string_length(*(argv + 1));
						HEIGHT_FIELD = string_to_number(*(argv + 1) , length_number);
						//printf("\n this is the height of the field: %d", HEIGHT_FIELD);
						parameters_checked++;
						if (parameters_checked == 3)
						{
							continue_loop = 0;
							break;
						}
						else
						{
							argv = argv + length_number;
							break;
						}
					case 'm':
						length_number = string_length(*(argv + 1));
						AMOUNT_OF_BOMBS = string_to_number(*(argv + 1) , length_number);
						//printf("\n these are the amount of bombs on the field: %d", AMOUNT_OF_BOMBS);
						parameters_checked++;
						if (parameters_checked == 3)
						{
							continue_loop = 0;
							break;
						}
						else
						{
							argv = argv + length_number;
							break;
						}
					default:
						printf("\n illegal option %c\n", opt);
						possible_field = 0;
						break;
				}
			}
		}
		if (possible_field == 0)
		{
			printf("\n wrong parameter given, check if you wrote them correctly");
		}
		else if (AMOUNT_OF_BOMBS > ((HEIGHT_FIELD * WIDTH_FIELD) - 9))   //pigeonhole proof
		{
			printf("\n impossible to draw field with so many bombs , remember that the first move has no adjecent bombs");
		}
		else
		{
			struct Constants *field_info;
			field_info = (struct Constants *)malloc(sizeof(struct Constants));
			field_info->no_horizontal_cels = WIDTH_FIELD ;
			field_info->no_vertical_cels = HEIGHT_FIELD ;
			field_info->no_Bombs = AMOUNT_OF_BOMBS;
			field_info->bombs_set = 0;
			field_info->continue_game = 1;
			struct Cell *field;
			field = (struct Cell *)malloc(((HEIGHT_FIELD + 1) * (WIDTH_FIELD + 1)) * sizeof(struct Cell));
			initialize_gui(field , field_info);
			while (should_continue) 
			{
				draw_window(field , field_info);
				read_input(field , field_info);
				check_win(field , field_info);
			} 
			/* Dealloceer al het geheugen dat werd aangemaakt door SDL zelf. */
			free_gui();
			free(field_info);
			free(field);
			return 0;
		}
		

   }
   else if (argc = 2) 
   {
      printf("game starting.\n");
   }
   else 
   {
	   printf("too many arguments. \n");
   }

}
/*  read a line into s, return length */
int getline2(char s[],int lim)
{
	int c, i;
	for (i=0; i < lim-1 && (c=get_char())!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}


/* read a character from input */
char get_char()
{
	char c;
	scanf("%c", &c);
	return c;
}

int string_to_number(char *given_string , int length)
{
	    // variable to store the 
    // length of the string 
    int number = 0; 
    while (*given_string != '\0') 
	{ 
		int number_to_convert = *given_string - 48 ;       //to convert given character to correct number + to int at the same time
		number = number + (number_to_convert * pow(10 , (length - 1)));
        length--; 
        given_string++; 
    } 
  
    return number; 

}

int string_length(char *given_string) //mentioned in references 3)
{ 
    // variable to store the 
    // length of the string 
    int length = 0; 
    while (*given_string != '\0') { 
        length++; 
        given_string++; 
    } 
  
    return length; 
} 
/* REFERENCES
1) https://www.eskimo.com/~scs/cclass/krnotes/sx8j.html (not used)
2)  main.c
    commandLineArgs_find

    Created by Elisa Gonzalez Boix on 08/11/16.
    Copyright © 2016 Elisa Gonzalez Boix. All rights reserved. (used in main of gui)
3) https://www.geeksforgeeks.org/length-string-using-pointers/ (used above)
 */
