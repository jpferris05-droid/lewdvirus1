#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include "port_input.h"
#include "port_blit.h"
#define TITLE_PATH "sdmc:/3ds/LewdVirus/title.rgb565"
#define TITLE_BYTES (320u*240u*2u)
int main(int argc,char **argv){(void)argc;(void)argv; gfxInitDefault(); sdmcInit(); consoleInit(GFX_BOTTOM,NULL);
 printf("Lewd Virus - 3DS graphics milestone\nLoading title image...\n"); FILE *f=fopen(TITLE_PATH,"rb"); uint16_t *pixels=NULL;
 if(f){pixels=(uint16_t*)malloc(TITLE_BYTES); if(!pixels||fread(pixels,1,TITLE_BYTES,f)!=TITLE_BYTES){free(pixels);pixels=NULL;printf("Invalid/incomplete title image.\n");} fclose(f);} else printf("Missing %s\n",TITLE_PATH);
 if(pixels){port_blit_rgb565_top(pixels,320,240);gfxFlushBuffers();gfxSwapBuffers();free(pixels);printf("Title image displayed on top screen.\n");}
 printf("Graphics/input test only; not the full game.\nPress START to exit.\n"); RpgInputState input={0}; while(aptMainLoop()){port_input_update(&input);if(input.pressed[RPG_KEY_Z])break;gspWaitForVBlank();} sdmcExit();gfxExit();return 0;}
