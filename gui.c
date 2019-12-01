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

void read_input() {
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
	while (! SDL_PollEvent(&event)) {}

	switch (event.type) {
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
		break;
	}
}

void draw_window(struct Cell *ptr_field , struct Constants info) 
{

	SDL_RenderClear(renderer);
	int x_pos , y_pos;
	printf("\n do you pass here(before switch case)?");
	for (int i=0; i < info.no_vertical_cels; i++)
	{
		for (int j=0; j < info.no_horizontal_cels ; j++)
		{
			x_pos = j * IMAGE_WIDTH;
			y_pos = i * IMAGE_HEIGHT;
			if (*(ptr_field + find(i, j))->vissible_value == 'q')
			{

				SDL_Rect rectangle = {x_pos , y_pos, IMAGE_WIDTH, IMAGE_HEIGHT };
				SDL_RenderCopy(renderer, digit_C_texture, NULL, &rectangle);
			}
			else
			{
				continue;
			}
		}
	}

	 SDL_RenderPresent(renderer);
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

/*
 * Dealloceert alle SDL structuren die geïnitialiseerd werden.
 */
void free_gui() {
	/* Dealloceert de SDL_Textures die werden aangemaakt. */ //use fopen  for this stuff
	// SDL_DestroyTexture(digit_F_texture);
	 SDL_DestroyTexture(digit_C_texture);
	// SDL_DestroyTexture(digit_0_texture);
	//SDL_DestroyTexture(digit_1_texture);
	// SDL_DestroyTexture(digit_2_texture);
	// SDL_DestroyTexture(digit_3_texture);
	// SDL_DestroyTexture(digit_4_texture);
	// SDL_DestroyTexture(digit_5_texture);
	// SDL_DestroyTexture(digit_6_texture);
	// SDL_DestroyTexture(digit_7_texture);
	// SDL_DestroyTexture(digit_8_texture);
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
	// SDL_Surface* digit_1_texture_path = SDL_LoadBMP("Images/1.bmp");
	// SDL_Surface* digit_0_texture_path = SDL_LoadBMP("Images/0.bmp");
	// SDL_Surface* digit_2_texture_path = SDL_LoadBMP("Images/2.bmp");
	// SDL_Surface* digit_3_texture_path = SDL_LoadBMP("Images/3.bmp");
	// SDL_Surface* digit_4_texture_path = SDL_LoadBMP("Images/4.bmp");
	// SDL_Surface* digit_5_texture_path = SDL_LoadBMP("Images/5.bmp");
	// SDL_Surface* digit_6_texture_path = SDL_LoadBMP("Images/6.bmp");
	// SDL_Surface* digit_7_texture_path = SDL_LoadBMP("Images/7.bmp");
	// SDL_Surface* digit_8_texture_path = SDL_LoadBMP("Images/8.bmp");
	// SDL_Surface* digit_F_texture_path = SDL_LoadBMP("Images/flagged.bmp");
	SDL_Surface* digit_C_texture_path = SDL_LoadBMP("Images/covered.bmp");
	
	digit_C_texture = SDL_CreateTextureFromSurface(renderer, digit_C_texture_path);
	
	SDL_FreeSurface(digit_C_texture_path);
	
}

/*
 * Initialiseert onder het venster waarin het speelveld getoond zal worden, en de texture van de afbeelding die getoond zal worden.
 * Deze functie moet aangeroepen worden aan het begin van het spel, vooraleer je de spelwereld begint te tekenen.
 */
void initialize_gui(struct Cell *ptr_field , struct Constants info) 
{
	initialize_window("Minesweeper");
	initialize_textures();
	print_grid_frontend(ptr_field , info , '0');
}

int main(int argc, char *argv[]) 
{
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
						printf("\n this is the width of the field: %d", WIDTH_FIELD);
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
						printf("\n this is the height of the field: %d", HEIGHT_FIELD);
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
						printf("\n these are the amount of bombs on the field: %d", AMOUNT_OF_BOMBS);
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
			struct Constants field_info;
			field_info.no_horizontal_cels = HEIGHT_FIELD;
			field_info.no_vertical_cels = WIDTH_FIELD;
			field_info.no_Bombs = AMOUNT_OF_BOMBS;
			struct Cell field[HEIGHT_FIELD][WIDTH_FIELD];
			initialize_gui(&field , field_info);
			while (should_continue) 
			{
				 draw_window(&field , field_info);
				 read_input();
			} 
			/* Dealloceer al het geheugen dat werd aangemaakt door SDL zelf. */
			free_gui();
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
