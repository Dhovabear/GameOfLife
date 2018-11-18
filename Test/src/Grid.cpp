
#include <iostream>

#include "../include/Grid.h"


Grid::Grid(int NbrCases , int xSize , int ySize)
{
    m_wWidth = new int(xSize);
    m_wHeight = new int(ySize);

    m_size = new int (NbrCases);

    m_gridCells = new int*[NbrCases];
    for(int i = 0 ; i < NbrCases ; i++ ){
        m_gridCells[i] = new int[NbrCases];
    }

    //ctor
}

Grid::~Grid()
{
    for(int i = 0 ; i < *m_size ; i++){
        delete [] m_gridCells[i];
    }
    delete [] m_gridCells;

    delete m_wHeight;
    delete m_wWidth;
    delete m_size;
}

bool Grid::isCellEmpty(int x, int y){
    if(m_gridCells[x][y] != 1){
        return true;
    }else{
        return false;
    }
}

 void Grid::draw(SDL_Renderer &tRendu){


    SDL_SetRenderDrawColor(&tRendu , 214 , 214 , 214 , 255); // On colorie en gris
    for(int i = 0 ; i < *m_size+1 ; i++){ // boucle qui dessine la grille
            SDL_RenderDrawLine(&tRendu , 0 , i*( *m_wHeight/ *m_size) , *m_wWidth , i*( *m_wHeight/ *m_size) ); // horizontal
        for(int j = 0 ; j < *m_size+1 ; j++){
            SDL_RenderDrawLine(&tRendu , i*( *m_wWidth/ *m_size) , 0 , i*( *m_wWidth/ *m_size) , *m_wHeight );//vertical
        }
    }

    SDL_RenderDrawLine(&tRendu , *m_wWidth-1 , 0 , *m_wWidth-1 , *m_wHeight-1);
    SDL_RenderDrawLine(&tRendu , 0 , *m_wHeight-1 , *m_wWidth-1 , *m_wHeight-1);// Ces 2 lignes servent a dessiner les bords droit et bas

    SDL_SetRenderDrawColor(&tRendu , 255 , 255 , 255 , 255);//On remet la couleur blanche
}
