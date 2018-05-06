//
// Created by elsis on 18.5.4.
//

#ifndef GAME_OF_LIFE_GAME_APP_H
#define GAME_OF_LIFE_GAME_APP_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <gtkmm/application.h>
#include "game_app_window.h"

class GameApp: public Gtk::Application {
protected:
    GameApp();

public:
    static Glib::RefPtr<GameApp> create();

protected:
    void on_activate() final;

private:
    static void game_thread(GameAppWindow *game);
    GameAppWindow* create_appwindow();
    void on_hide_window(Gtk::Window *window);

private:
    std::mutex mtx;
    std::condition_variable cv;
};


#endif //GAME_OF_LIFE_GAME_APP_H
