//
// Created by elsis on 18.5.1.
//

#include <cstdlib>
#include "game_area.h"

GameArea::GameArea() {
    srand (static_cast <unsigned> (time(nullptr)));
    set_size_request(PREF_WIDTH, PREF_HEIGHT);

    currentGen = new bool*[maxRows];
    for (int i = 0; i < maxRows; ++i) {
        currentGen[i] = new bool[maxColumns];
    }

    newerGen = new bool*[maxRows];
    for (int i = 0; i < maxRows; ++i) {
        newerGen[i] = new bool[maxColumns];
    }

    initCells();
}

GameArea::~GameArea() {
    for (int i = 0; i < maxRows; ++i) {
        delete [] currentGen[i];
    }

    delete [] currentGen;

    for (int i = 0; i < maxRows; ++i) {
        delete [] newerGen[i];
    }

    delete [] newerGen;
}

void GameArea::initCells() {
    for (int i = 0; i < maxRows; ++i) {
        for (int j = 0; j < maxColumns; ++j) {
            // 10% of cell being alive at first generation
            currentGen[i][j] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) <= 0.1);
        }
    }
}

void GameArea::generate() {
    for (int i = 0; i < maxRows; ++i) {
        for (int j = 0; j < maxColumns; ++j) {
            int neighbours = getAliveNeighbours(i, j);
            if (neighbours >= 4 || neighbours <= 1) {
                newerGen[i][j] = false;
            }
            else if (neighbours == 3) {
                newerGen[i][j] = true;
            }
            else {
                newerGen[i][j] = currentGen[i][j];
            }
        }
    }

    bool **temp = currentGen;
    currentGen = newerGen;
    newerGen = temp;
}

int GameArea::getAliveNeighbours(int x, int y) {
    int count = 0;

    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (i == 0 && j == 0) continue;
            if (currentGen[(x+i+maxRows) % maxRows][(y+j+maxColumns) % maxColumns]) ++count;
        }
    }

    return count;
}

bool GameArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    //Gtk::Allocation allocation = get_allocation();
    //const int width = allocation.get_width();
    //const int height = allocation.get_height();

    // draw default grid
    cr->set_line_width(2.0);

    for (int i = 0; i < PREF_WIDTH; i += CELL_SIZE)
    {
        cr->move_to(i, 0);
        cr->line_to(i, PREF_HEIGHT);
    }

    for (int i = 0; i < PREF_HEIGHT; i += CELL_SIZE)
    {
        cr->move_to(0, i);
        cr->line_to(PREF_WIDTH, i);
    }

    cr->stroke();

    for (int i = 0; i < maxRows; ++i) {
        for (int j = 0; j < maxColumns; ++j) {
            if (currentGen[i][j]) {
                cr->rectangle(CELL_SIZE*j, CELL_SIZE*i, CELL_SIZE, CELL_SIZE);
            }
        }
    }

    cr->fill();

    return true;
}

void GameArea::forceRedraw() {
    auto win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
}

void GameArea::play() {
    generate();
    forceRedraw();
}
