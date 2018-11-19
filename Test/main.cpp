#include <iostream>
#include <fstream>
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
    bool pause = false;
    std::ofstream debugLogs;
    int nbrCases = 100;

    std::vector<Cellule> cellInGrid(0);
    std::vector<Cellule> alreadyComptuedCells(0);

    Cellule *cell = new Cellule();
    cell->xPos = 0;
    cell->yPos = 0;

    debugLogs.open("lastLogs.txt");


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
    grille->clearGrid();
    grille->clearTmp();

    grille->setCell(50 ,30 , 1);
    grille->setCell(51 , 30 , 1);
    grille->setCell(52 , 30 , 1);
    grille->setCell(53 , 30 , 1);
    grille->setCell(54 , 30 , 1);
    //grille->setCell(51 , 30 , 1);
    //grille->setCell(52,30,1);
    //grille->setCell(53,30,1);

    SDL_SetRenderDrawColor(rendu , 255 , 255 , 255 , 255);

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
        SDL_Delay(1000);


    //Boucle Principale
    while(!terminer){

        //Gestion des evenements
        SDL_WaitEvent(&events);

        if(events.window.event == SDL_WINDOWEVENT_CLOSE){
            terminer = true;
        }

        //On supprime la grille temporaire
        //alreadyComptuedCells.erase(alreadyComptuedCells.begin() , alreadyComptuedCells.end());
        if(!pause){
        //on rafraichit la liste des cases a traiter
            debugLogs << "---------Nouvelle-iteration-----\n";

            debugLogs << "\t ----Enregistrement des cases a calc\n";
            for(int i = 0; i < nbrCases ; i++){
                for(int j = 0; j < nbrCases ; j++){
                    if(!grille->isCellEmpty(i , j)){
                        cell->xPos = i;
                        cell->yPos = j;
                        debugLogs << "\t\t Cellule detecter a: x=" << i << " y=" << j << "\n";
                        cellInGrid.push_back(*cell);
                    }
                }
            }

            debugLogs << "\t ----Calculs\n";
            for(int i = 0 ; i < cellInGrid.size() ; i++){
            debugLogs << "\t\t--Case " << i  << ": pos(x:" << cellInGrid[i].xPos << ",y:" << cellInGrid[i].yPos << ")\n";
            //PArtie CALCUL
            std::cout << "it" << std::endl;
            int mainVois = 0;
            debugLogs << "\t\t\t--Calculs pour les voisins\n";
            for(int k = -1; k < 2 ; k ++){ //y
                for(int j = -1; j < 2 ; j++ ){//x
                    if(j == 0 && k == 0){
                        continue;
                    }
                    debugLogs << "\t\t\t\t--Voisin(x:" << k+cellInGrid[i].xPos << ",y:" << j + cellInGrid[i].yPos <<")\n";
                    std::cout << "cellule "  << i << " x = " << k << " y= " << j << std::endl;
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
                    debugLogs << "\t\t\t\t\t nbr De voisins = " << voisins << "\n";
                    if(!grille->isCellEmpty(cellInGrid[i].xPos+k , cellInGrid[i].yPos+j)){
                            mainVois++;
                            debugLogs << "\t\t\t\t\tLa case est active et\n";
                        if(voisins == 3 || voisins == 2 ){
                            grille->setTmpCell( cellInGrid[i].xPos + k , cellInGrid[i].yPos +j , 1);
                            debugLogs << "\t\t\t\t\tLa case reste en vie\n";
                        }else{
                            grille->setTmpCell(cellInGrid[i].xPos+k , cellInGrid[i].yPos+j , 0);
                            debugLogs << "\t\t\t\t\tLa case meurt en vie\n";
                        }
                    }else{
                        debugLogs << "\t\t\t\t\tLa case est inactive et\n";
                        if(voisins == 3){
                            grille->setTmpCell(cellInGrid[i].xPos+k , cellInGrid[i].yPos+j , 1);
                            debugLogs << "\t\t\t\t\tDevient vivante\n";
                        }else{
                            debugLogs << "\t\t\t\t\tReste inactive\n";
                        }
                    }


                }
            }
            debugLogs << "\t\t\t\t----------case" << i << "pos(x:" << cellInGrid[i].xPos << ",y:" << cellInGrid[i].yPos << ")\n" ;
            debugLogs << "\t\t\t\t-----a " << mainVois << " voisins et\n";
            if(mainVois == 2 || mainVois == 3){
                grille->setTmpCell(cellInGrid[i].xPos , cellInGrid[i].yPos , 1);
                debugLogs << "\t\t\t\t----reste en vie\n";
            }else{
                grille->setTmpCell(cellInGrid[i].xPos , cellInGrid[i].yPos , 0);
                debugLogs << "\t\t\t\t----meurt\n";
            }

        }
        }

        grille->applyTmp();
        grille->clearTmp();
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
        SDL_Delay(100);
    }


    //On détruit les pointeurs
    delete grille;

    // on quitte la SDL


    debugLogs.close();
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}


