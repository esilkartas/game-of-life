#include <iostream>
#include "game_app.h"

int main(int argc, char *argv[])
{
    auto app = GameApp::create();
    return app->run();
}