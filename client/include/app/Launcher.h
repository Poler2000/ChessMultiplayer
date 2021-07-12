#ifndef CHESSMULTIPLAYER_LAUNCHER_H
#define CHESSMULTIPLAYER_LAUNCHER_H

#include "chess_gui/MainMenu.h"

namespace poler {
    class Launcher : public wxApp {
    public:
        bool OnInit() override;
        int OnRun() override;

    private:
        static constexpr unsigned int defaultPort = 8080;
        chess_gui::MainMenu* mainMenu;
    };
}



#endif //CHESSMULTIPLAYER_LAUNCHER_H
