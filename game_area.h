//
// Created by elsis on 18.5.1.
//

#ifndef GAME_OF_LIFE_GAME_AREA_H
#define GAME_OF_LIFE_GAME_AREA_H

#include <gtkmm/drawingarea.h>

class GameArea: public Gtk::DrawingArea {
public:
    static int const CELL_SIZE = 4;
    static int const PREF_HEIGHT = 900;
    static int const MIN_HEIGHT = PREF_HEIGHT - 100;
    static int const PREF_WIDTH = 1500;
    static int const MIN_WIDTH = PREF_WIDTH - 100;

    GameArea();
    ~GameArea() override;

    void play();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
    void initCells();
    void generate();
    int getAliveNeighbours(int x, int y);
    void forceRedraw();

private:
    int const maxRows = PREF_HEIGHT / CELL_SIZE;
    int const maxColumns = PREF_WIDTH / CELL_SIZE;
    bool **currentGen;
    bool **newerGen;
};


#endif //GAME_OF_LIFE_GAME_AREA_H
