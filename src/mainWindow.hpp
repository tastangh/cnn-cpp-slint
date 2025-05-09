#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h> // SpinCtrl için
#include <wx/stattext.h> // StaticText için
#include <wx/textctrl.h> // TextCtrl için
#include <wx/sizer.h>    // Sizer'lar için
#include <vector>        // Dinamik kontrol listeleri için

class MyFrame : public wxFrame {
public:
  MyFrame();

private:
  // Olay İşleyicileri
  void onHello(wxCommandEvent &event);
  void onExit(wxCommandEvent &event);
  void onAbout(wxCommandEvent &event);
  void onNumInputsChanged(wxSpinEvent &event); // Giriş sayısı değiştiğinde
  void onNumHiddenLayersChanged(wxSpinEvent &event); // Gizli katman sayısı değiştiğinde
  void onNumOutputsChanged(wxSpinEvent &event); // Çıkış sayısı değiştiğinde
  void onCalculate(wxCommandEvent &event); // Hesapla butonuna basıldığında

  // UI Elemanlarını Güncelleme Fonksiyonları
  void updateInputFields();
  void updateHiddenLayerFields();
  void updateOutputFields();

  // Ana Panel ve Sizer'lar
  wxPanel *m_panel;
  wxBoxSizer *m_mainSizer; // Ana dikey sizer

  // Giriş Bölümü
  wxSpinCtrl *m_numInputsSpinCtrl;
  wxStaticBoxSizer *m_inputsStaticBoxSizer; // Giriş değerleri için grup
  wxFlexGridSizer *m_inputValuesSizer;      // x1, x2,... değerleri için grid
  std::vector<wxTextCtrl*> m_inputControls; // Dinamik giriş TextCtrl'leri

  // Gizli Katmanlar Bölümü
  wxSpinCtrl *m_numHiddenLayersSpinCtrl;
  wxStaticBoxSizer *m_hiddenLayersStaticBoxSizer; // Gizli katman ayarları için grup
  wxBoxSizer *m_hiddenLayerControlsSizer;         // Her katmanın eleman sayısı için dikey sizer
  std::vector<wxSpinCtrl*> m_hiddenLayerNeuronSpins; // Dinamik gizli katman SpinCtrl'leri
  std::vector<wxStaticText*> m_hiddenLayerLabels;    // Dinamik gizli katman etiketleri

  // Çıkış Bölümü
  wxSpinCtrl *m_numOutputsSpinCtrl;
  wxStaticBoxSizer *m_outputsStaticBoxSizer; // Çıkış değerleri için grup
  wxFlexGridSizer *m_outputValuesSizer;      // y1, y2,... değerleri için grid
  std::vector<wxStaticText*> m_outputLabels; // Dinamik çıkış etiketleri (y1:, y2:)
  std::vector<wxStaticText*> m_outputDisplays; // Dinamik çıkış değerleri (okunur)

  // Hesapla Butonu
  wxButton *m_calculateButton;

  // Menü için ID'ler (zaten var)
  // enum { ID_HELLO = 1 }; // Bu zaten MyFrame.cpp'de, global olmalı ya da burada da olabilir
};