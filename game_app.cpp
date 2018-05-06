//
// Created by elsis on 18.5.4.
//

#include <iostream>
#include <chrono>
#include "game_app.h"

GameApp::GameApp()
: Gtk::Application("org.elsis.game-of-life", Gio::APPLICATION_FLAGS_NONE)
{
}

Glib::RefPtr<GameApp> GameApp::create() {
    return Glib::RefPtr<GameApp>(new GameApp());
}

GameAppWindow *GameApp::create_appwindow() {
    auto appwindow = new GameAppWindow();

    add_window(*appwindow);

    appwindow->signal_hide().connect
            (sigc::bind<Gtk::Window*>(sigc::mem_fun(*this, &GameApp::on_hide_window), appwindow));

    return appwindow;
}

void GameApp::on_activate() {
    auto appwindow = create_appwindow();
    appwindow->present();

    std::thread(game_thread, appwindow).detach();
}

void GameApp::on_hide_window(Gtk::Window *window) {
    delete window;
}

void GameApp::game_thread(GameAppWindow *game) {

    std::cout << "Starting Game of Life in..." << std::endl;
    for (int i = 3; i > 0; --i) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Go!" << std::endl;

    int iterations = 100000;
    int percent = iterations / 100;
    for (int i = 0; i < iterations; ++i) {
        if (GameAppWindow::app_exit) break;

        game->play();
        if (i % (percent*10) == 0 && i != 0) {
            std::cout << i / percent << "% Completed" << std::endl;
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    std::unique_lock<std::mutex> lck(GameAppWindow::mtx);
    std::cout << "Finishing all jobs" << std::endl;
    GameAppWindow::jobs_finished = true;
    GameAppWindow::cv.notify_one();
}
