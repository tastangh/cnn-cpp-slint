#pragma once

#include <wx/wx.h>

class MyFrame : public wxFrame {
public:
  MyFrame();

private:
  void onHello(wxCommandEvent &event);
  void onExit(wxCommandEvent &event);
  void onAbout(wxCommandEvent &event);
};
