//
// Created by elsis on 18.5.5.
//

#ifndef GAME_OF_LIFE_GAME_APP_WINDOW_H
#define GAME_OF_LIFE_GAME_APP_WINDOW_H

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <gtkmm/applicationwindow.h>
#include "game_area.h"

class GameAppWindow: public Gtk::ApplicationWindow {
public:
    GameAppWindow();
    ~GameAppWindow() override = default;

    void play();

protected:
    bool on_delete_event(GdkEventAny *any_event) override;

public:
    static std::atomic_bool app_exit;
    static std::atomic_bool jobs_finished;
    static std::mutex mtx;
    static std::condition_variable cv;

private:
    GameArea gameArea;
};


#endif //GAME_OF_LIFE_GAME_APP_WINDOW_H
