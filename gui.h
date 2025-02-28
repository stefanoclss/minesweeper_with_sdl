#ifndef GUI_H_
#define GUI_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <string.h>

/*
 * Importeer de benodigde functies uit SDL2.
 */
#include <SDL2/SDL.h>

/*
 * De hoogte en breedte van het venster (in pixels).
 * Deze dimensies zijn arbitrair gekozen. Deze dimensies hangen mogelijk af van de grootte van het speelveld.
 */
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1200
#define MAX_EL_HOR 12
#define MAX_EL_VER 30
#define MAX_ARR_FIELD 100000
/*
 * De hoogte en breedte (in pixels) van de afbeeldingen voor de vakjes in het speelveld die getoond worden.
 * Als je andere afbeelding wil gebruiken in je GUI, zorg er dan voor dat deze
 * dimensies ook aangepast worden.
 */
#define IMAGE_HEIGHT 50
#define IMAGE_WIDTH 50

#endif /* GUI_H_ */
