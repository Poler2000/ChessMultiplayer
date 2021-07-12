#include "chess_gui/MainMenu.h"

namespace poler::chess_gui {
    MainMenu::MainMenu()
            : wxFrame(nullptr, wxID_ANY, std::string(title_) ,wxPoint(defXPos, defYPos), wxSize(defWidth, defHeight)) {
        wxSizer* butSizer = new wxBoxSizer(wxVERTICAL);

        gameList.Create(this, wxID_ANY);

        wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        sizer->Add(&gameList, 1, wxEXPAND | wxLEFT | wxRIGHT);
        std::for_each(buttons.begin(), buttons.end(), [&, i = 0](auto& button) mutable {
            button.Create(this, 10000 + i, std::string{buttonTitles[i]});
            i++;
            button.Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainMenu::OnButtonClicked, this);
            butSizer->Add(&button, 1, wxEXPAND);
        });
        sizer->Add(butSizer, 1, wxEXPAND);
        this->SetSizer(sizer);
        sizer->Layout();
    }

    void MainMenu::OnButtonClicked(wxCommandEvent& ev) {
        auto s = ev.GetString();
    }
}