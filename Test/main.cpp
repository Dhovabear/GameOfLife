#include <iostream>
#include <vector>
#include "include/Grid.h"

#include <SDL2\SDL.h>

struct Cellule{
    int xPos;
    int yPos;
};



int main(int argc , char *argv[])
{

    //Initialisation des variables
    SDL_Window* fenetre(0) ;
    SDL_Event events ;
    SDL_GLContext contexteOGL;
    Grid *grille;
    bool terminer = false;

    int nbrCases = 4;

    std::vector<Cellule> activeCells(0); // répertorie les cellules a traiter au début de l'update
    std::vector<Cellule> cellsToDraw(0); // résultat des calculs pour l'affichage

    Cellule *cel1 = new Cellule();
    cel1->xPos = 5;
    cel1->yPos = 5;
    cellsToDraw.push_back(*cel1);
    activeCells.push_back(*cel1);
    cel1->xPos = 2;
    cel1->yPos = 1;
    activeCells.push_back(*cel1);



    //Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Erreur lors de l'initialisation de la SDL: " << SDL_GetError() << std::endl ;
        SDL_Quit();

        return -1;
    }


    //Creation de la fenetre
    fenetre = SDL_CreateWindow("Game Of Life - By Kilian Vuillaume" , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , 600 , 600 , SDL_WINDOW_SHOWN);

    //Initialisation du Renderer
    SDL_Renderer *rendu = SDL_CreateRenderer(fenetre , -1 , SDL_RENDERER_ACCELERATED);

    //Custom Classes Ini
    grille = new Grid(nbrCases , 600 , 600);

    for(int i = 0; i < cellsToDraw.size() ; i++){
            std::cout << "Cellule " << i << " : x=" << cellsToDraw[i].xPos << "  y=" << cellsToDraw[i].yPos << std::endl;
    }

    //Boucle Principale

    while(!terminer){

        //Gestion des evenements
        SDL_WaitEvent(&events);

        if(events.window.event == SDL_WINDOWEVENT_CLOSE){
            terminer = true;
        }


        //activesCells
        for(int i = 0; i < activeCells.size(); i++ ){
            if(activeCells[i].xPos > nbrCases-1 || activeCells[i].yPos > nbrCases){ // si la condition est vrai alors on hors des imites et on delete
                activeCells.erase(activeCells.begin()+ i , activeCells.begin()+i);
                std::cout << "Erased !" << std::endl;
            }
        }


        //On fait un rendu
        SDL_RenderClear(rendu);
        SDL_SetRenderDrawColor(rendu , 0 , 0 , 0 , 255);
        for(int i = 0; i < cellsToDraw.size(); i++){
            SDL_Rect rectangle ;
            rectangle.x = cellsToDraw[i].xPos * (600/nbrCases);
            rectangle.y = cellsToDraw[i].yPos * (600/nbrCases);
            rectangle.h = (600/nbrCases);
            rectangle.w = (600/nbrCases);
            SDL_RenderDrawRect(rendu , &rectangle);
            SDL_RenderFillRect(rendu , &rectangle);
        }
        grille->draw(*rendu); // on dessine la grille
        SDL_RenderPresent(rendu);
    }



    //On détruit les pointeurs
    delete grille;

    // on quitte la SDL



    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}


