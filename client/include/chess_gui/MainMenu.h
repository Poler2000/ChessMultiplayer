#ifndef CHESSMULTIPLAYER_MAINMENU_H
#define CHESSMULTIPLAYER_MAINMENU_H

#include <wx/wxprec.h>
#include <string>
#include <array>
#include <mutex>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace poler::chess_gui {
    class MainMenu : public wxFrame {
    public:
        MainMenu();
    private:
        static constexpr std::string_view buttonTitles[] =
                {"Create Game", "Join Game", "Join as spectator"};
        static constexpr std::string_view title_ = "Chess Multiplayer";

        static constexpr unsigned int defWidth = 960;
        static constexpr unsigned int defHeight = 720;
        static constexpr int defYPos = 10;
        static constexpr int defXPos = 10;

        std::array<wxButton, 3> buttons;
        wxListBox gameList;
        //std::mutex mtx;
        //MenuOption currOption{0, 0};

        void OnButtonClicked(wxCommandEvent &ev);
        //void setOption(const MenuOption& option);
    };
}

#endif //CHESSMULTIPLAYER_MAINMENU_H
