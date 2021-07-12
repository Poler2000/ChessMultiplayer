#include "app/Launcher.h"

wxIMPLEMENT_APP(poler::Launcher);

namespace poler {

    bool Launcher::OnInit() {
        mainMenu = new chess_gui::MainMenu();
        mainMenu->Show(true);

        return wxAppConsoleBase::OnInit();
    }

    int Launcher::OnRun() {
        return wxAppBase::OnRun();
    }
}