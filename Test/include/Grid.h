#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <SDL2\SDL.h>


class Grid
{
    public:

        Grid(int NbrCases , int xSize , int ySize);
        virtual ~Grid();

        bool isCellEmpty(int x , int y);
        void draw(SDL_Renderer &tRendu);

        bool setCell(int x , int y , int state);

        bool setTmpCell( int x , int y , int state);
        bool applyTmp();

        bool clearTmp();
        bool clearGrid();

    protected:

    private:
        int *m_size;
        int** m_gridCells;
        int** m_tmpGrid;
        int *m_wWidth;
        int *m_wHeight;


};

#endif // GRID_H
