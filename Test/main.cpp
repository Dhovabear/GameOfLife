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

    int nbrCases = 100;

    std::vector<Cellule> cellInGrid(0);
    std::vector<Cellule> alreadyComptuedCells(0);

    Cellule *cell = new Cellule();

    grille->setCell(10 ,10 , 1);


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

    //Boucle Principale

    while(!terminer){

        //Gestion des evenements
        SDL_WaitEvent(&events);

        if(events.window.event == SDL_WINDOWEVENT_CLOSE){
            terminer = true;
        }

        //On supprime la grille temporaire
        grille->clearTmp();
        alreadyComptuedCells.erase(alreadyComptuedCells.begin() , alreadyComptuedCells.end());

        //on rafraichit la liste des cases a traiter

        for(int i = 0; i < nbrCases ; i++){
            for(int j = 0; j < nbrCases ; j++){
                if(!grille->isCellEmpty(i , j)){
                    cell->xPos = i;
                    cell->yPos = j;
                    cellInGrid.push_back(*cell);
                }
            }
        }

        for(int i = 0 ; i < cellInGrid.size() ; i++){
            //PArtie CALCUL
            int mainVois = 0;
            for(int j = -1; j < 2 ; j ++){ //y
                for(int k = -1; k < 2 ; k++ ){//x
                    if(j == 0 && k == 0){
                        continue;
                    }

                    int voisins = 0;

                    if(!grille->isCellEmpty(cellInGrid[i].xPos + k  , cellInGrid[i].yPos + j -1)){
                        voisins ++;
                    }
                    if(!grille->isCellEmpty(cellInGrid[i].xPos + k +1  , cellInGrid[i].yPos + j -1)){
                        voisins ++;
                    }
                    if(!grille->isCellEmpty(cellInGrid[i].xPos + k +1 , cellInGrid[i].yPos + j )){
                        voisins ++;
                    }
                    if(!grille->isCellEmpty(cellInGrid[i].xPos + k +1  , cellInGrid[i].yPos + j +1)){
                        voisins ++;
                    }
                    if(!grille->isCellEmpty(cellInGrid[i].xPos + k  , cellInGrid[i].yPos + j +1 )){
                        voisins ++;
                    }
                    if(!grille->isCellEmpty(cellInGrid[i].xPos + k -1  , cellInGrid[i].yPos + j +1)){
                        voisins ++;
                    }
                    if(!grille->isCellEmpty(cellInGrid[i].xPos + k -1 , cellInGrid[i].yPos + j )){
                        voisins ++;
                    }
                    if(!grille->isCellEmpty(cellInGrid[i].xPos + k -1  , cellInGrid[i].yPos + j -1)){
                        voisins ++;
                    }
                    if(!grille->isCellEmpty(cellInGrid[i].xPos+k , cellInGrid[i].yPos+j)){
                            mainVois++;
                        if(voisins == 3 || voisins == 2 ){
                            grille->setTmpCell( i + k , i+j , 1);
                        }else{
                            grille->setTmpCell(i+k , i+j , 0);
                        }
                    }else{
                        if(voisins == 3){
                            grille->setTmpCell(i+k , i+j , 1);
                        }
                    }


                }
            }

            if(mainVois == 2 || mainVois == 3){
                grille->setTmpCell(cellInGrid[i].xPos , cellInGrid[i].yPos , 1);
            }else{
                grille->setTmpCell(cellInGrid[i].xPos , cellInGrid[i].yPos , 0);
            }

        }

        grille->applyTmp();
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

                }
            }
        }
        grille->draw(*rendu); // on dessine la grille
        SDL_RenderPresent(rendu);
        SDL_Delay(500);
    }


    //On détruit les pointeurs
    delete grille;

    // on quitte la SDL



    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}


