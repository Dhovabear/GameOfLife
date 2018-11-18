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
    std::vector<Cellule> inactiveCells(0);// ici on stockera les cellules a désactiver

    std::vector<Cellule> cellInGrid(0);

    Cellule *cel1 = new Cellule();
    cel1->xPos = 5;
    cel1->yPos = 5;
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

    for(int i = 0; i < activeCells.size() ; i++){
            std::cout << "Cellule " << i << " : x=" << activeCells[i].xPos << "  y=" << activeCells[i].yPos << std::endl;
    }

    //Boucle Principale

    while(!terminer){

        //Gestion des evenements
        SDL_WaitEvent(&events);

        if(events.window.event == SDL_WINDOWEVENT_CLOSE){
            terminer = true;
        }

        //on rafraichit la liste des cases a traiter

        for(int i = 0 ; i < cellInGrid.size() ; i++){
            //PArtie CALCUL

        }







        //inactive cells
        for(int i = 0; i < inactiveCells.size(); i++){
            if(inactiveCells[i].xPos > nbrCases -1 ||inactiveCells[i].yPos > nbrCases-1){//on supprime les èlèments du tableau qui pourrait faire bugger
                inactiveCells.erase(inactiveCells.begin()+i , inactiveCells.begin()+i+1);
                std::cout << "Erased inactive !" << std::endl;
            }else{
                grille->setCell(inactiveCells[i].xPos , inactiveCells[i].yPos , 0); //ici on désactive les case qui doivent lètre
            }
        }

        //activesCells
        //cellsToDraw.erase(cellsToDraw.begin() , cellsToDraw.end()); // on efface la liste a aff
        for(int i = 0; i < activeCells.size(); i++ ){
            if(activeCells[i].xPos > nbrCases-1 || activeCells[i].yPos > nbrCases-1){ // si la condition est vrai alors on hors des imites et on delete
                activeCells.erase(activeCells.begin()+ i , activeCells.begin()+i+1);
                std::cout << "Erased Active!" << std::endl;
            }else{
                grille->setCell(activeCells[i].xPos , activeCells[i].yPos , 1);
                //cel1->xPos = activeCells[i].xPos;
                //cel1->yPos = activeCells[i].yPos;
                //cellsToDraw.push_back(*cel1);
            }


        }

        cellInGrid.erase(cellInGrid.begin() , cellInGrid.end());
        //On fait un rendu
        SDL_RenderClear(rendu);
        SDL_SetRenderDrawColor(rendu , 0 , 0 , 0 , 255);
        for(int i = 0 ; i < nbrCases ; i++){
            for(int j = 0 ; j < nbrCases ; j++){
                if(!grille->isCellEmpty(i , j)){
                    SDL_Rect rectangle ;
                    rectangle.x = i * (600/nbrCases);
                    rectangle.y = j * (600/nbrCases);
                    rectangle.h = (600/nbrCases);
                    rectangle.w = (600/nbrCases);
                    SDL_RenderDrawRect(rendu , &rectangle);
                    SDL_RenderFillRect(rendu , &rectangle);

                    //on prévoit la prochaine boucle en enregistrant les cases coloriés
                    cel1->xPos = activeCells[i].xPos;
                    cel1->yPos = activeCells[i].yPos;
                    cellInGrid.push_back(*cel1);
                }
            }
        }
        grille->draw(*rendu); // on dessine la grille
        SDL_RenderPresent(rendu);
    }

    for(int i = 0; i < activeCells.size() ; i++){
            std::cout << "Cellule " << i << " : x=" << activeCells[i].xPos << "  y=" << activeCells[i].yPos << std::endl;
    }

    //On détruit les pointeurs
    delete grille;

    // on quitte la SDL



    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}


