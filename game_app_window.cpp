//
// Created by elsis on 18.5.5.
//

#include <iostream>
#include "game_app_window.h"

std::atomic_bool GameAppWindow::app_exit(false);
std::atomic_bool GameAppWindow::jobs_finished(false);
std::mutex GameAppWindow::mtx;
std::condition_variable GameAppWindow::cv;

GameAppWindow::GameAppWindow()
: Gtk::ApplicationWindow()
{
    set_title ("Game of Life");
    //set_border_width(10);
    set_resizable(false);
    //set_default_size(500, 500);

    add(gameArea);
    gameArea.show();
}

void GameAppWindow::play() {
    gameArea.play();
}

bool GameAppWindow::on_delete_event(GdkEventAny *any_event) {
    std::cout << "Exit invoked" << std::endl;
    app_exit = true;
    std::unique_lock<std::mutex> lck(mtx);
    while(!jobs_finished) cv.wait(lck);
    std::cout << "Exiting" << std::endl;

    return Widget::on_delete_event(any_event);
}
