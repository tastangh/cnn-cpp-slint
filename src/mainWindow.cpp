#include "mainWindow.hpp"
#include <wx/valnum.h> // Sayısal doğrulama için (isteğe bağlı)

// ID_HELLO global veya MyFrame içinde enum olarak tanımlanmalı.
// Eğer başka .cpp dosyasında kullanılmayacaksa MyFrame.hpp içinde private enum olabilir.
// Şimdilik burada bırakıyorum ama daha iyi bir yer bulunabilir.
enum {
    ID_HELLO = 1,
    ID_NUM_INPUTS_SPIN,
    ID_NUM_HIDDEN_LAYERS_SPIN,
    ID_NUM_OUTPUTS_SPIN,
    ID_CALCULATE_BUTTON
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Neural Network Configurator") {
    // Menü (mevcut kodunuzdan)
    auto *menuFile = new wxMenu;
    menuFile->Append(ID_HELLO, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    auto *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    auto *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    // Ana Panel
    m_panel = new wxPanel(this, wxID_ANY);
    m_mainSizer = new wxBoxSizer(wxVERTICAL);

    // --- Giriş Bölümü ---
    auto *inputsSectionSizer = new wxBoxSizer(wxHORIZONTAL);
    inputsSectionSizer->Add(new wxStaticText(m_panel, wxID_ANY, "Number of Inputs:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    m_numInputsSpinCtrl = new wxSpinCtrl(m_panel, ID_NUM_INPUTS_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0);
    inputsSectionSizer->Add(m_numInputsSpinCtrl, 0, wxALIGN_CENTER_VERTICAL);
    m_mainSizer->Add(inputsSectionSizer, 0, wxEXPAND | wxALL, 5);

    m_inputsStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, m_panel, "Input Values (x_i)");
    m_inputValuesSizer = new wxFlexGridSizer(0, 2, 5, 5); // Sütun sayısı 2 (etiket + textctrl), satır sayısı dinamik (0)
    m_inputValuesSizer->AddGrowableCol(1); // TextCtrl sütunu genişlesin
    m_inputsStaticBoxSizer->Add(m_inputValuesSizer, 1, wxEXPAND | wxALL, 5);
    m_mainSizer->Add(m_inputsStaticBoxSizer, 0, wxEXPAND | wxALL, 5);

    // --- Gizli Katmanlar Bölümü ---
    auto *hiddenLayersSectionSizer = new wxBoxSizer(wxHORIZONTAL);
    hiddenLayersSectionSizer->Add(new wxStaticText(m_panel, wxID_ANY, "Number of Hidden Layers:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    m_numHiddenLayersSpinCtrl = new wxSpinCtrl(m_panel, ID_NUM_HIDDEN_LAYERS_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0);
    hiddenLayersSectionSizer->Add(m_numHiddenLayersSpinCtrl, 0, wxALIGN_CENTER_VERTICAL);
    m_mainSizer->Add(hiddenLayersSectionSizer, 0, wxEXPAND | wxALL, 5);

    m_hiddenLayersStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, m_panel, "Neurons per Hidden Layer");
    m_hiddenLayerControlsSizer = new wxBoxSizer(wxVERTICAL); // Her katman için bir satır
    m_hiddenLayersStaticBoxSizer->Add(m_hiddenLayerControlsSizer, 1, wxEXPAND | wxALL, 5);
    m_mainSizer->Add(m_hiddenLayersStaticBoxSizer, 0, wxEXPAND | wxALL, 5);

    // --- Çıkış Bölümü ---
    auto *outputsSectionSizer = new wxBoxSizer(wxHORIZONTAL);
    outputsSectionSizer->Add(new wxStaticText(m_panel, wxID_ANY, "Number of Outputs:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    m_numOutputsSpinCtrl = new wxSpinCtrl(m_panel, ID_NUM_OUTPUTS_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0);
    outputsSectionSizer->Add(m_numOutputsSpinCtrl, 0, wxALIGN_CENTER_VERTICAL);
    m_mainSizer->Add(outputsSectionSizer, 0, wxEXPAND | wxALL, 5);

    m_outputsStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, m_panel, "Output Values (y_i) - Calculated");
    m_outputValuesSizer = new wxFlexGridSizer(0, 2, 5, 5); // Sütun sayısı 2 (etiket + statictext)
    m_outputValuesSizer->AddGrowableCol(1); // Değer sütunu genişlesin
    m_outputsStaticBoxSizer->Add(m_outputValuesSizer, 1, wxEXPAND | wxALL, 5);
    m_mainSizer->Add(m_outputsStaticBoxSizer, 0, wxEXPAND | wxALL, 5);

    // --- Hesapla Butonu ---
    m_calculateButton = new wxButton(m_panel, ID_CALCULATE_BUTTON, "Calculate");
    m_mainSizer->Add(m_calculateButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    m_panel->SetSizerAndFit(m_mainSizer);
    this->Fit(); // Ana pencereyi sizer'a göre boyutlandır

    // Başlangıçta alanları güncelle
    updateInputFields();
    updateHiddenLayerFields();
    updateOutputFields();

    // Olay Bağlantıları
    Bind(wxEVT_MENU, &MyFrame::onHello, this, ID_HELLO);
    Bind(wxEVT_MENU, &MyFrame::onAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::onExit, this, wxID_EXIT);

    Bind(wxEVT_SPINCTRL, &MyFrame::onNumInputsChanged, this, ID_NUM_INPUTS_SPIN);
    Bind(wxEVT_SPINCTRL, &MyFrame::onNumHiddenLayersChanged, this, ID_NUM_HIDDEN_LAYERS_SPIN);
    Bind(wxEVT_SPINCTRL, &MyFrame::onNumOutputsChanged, this, ID_NUM_OUTPUTS_SPIN);
    Bind(wxEVT_BUTTON, &MyFrame::onCalculate, this, ID_CALCULATE_BUTTON);
}

void MyFrame::updateInputFields() {
    // Mevcut girişleri temizle
    for (auto ctrl : m_inputControls) {
        m_inputValuesSizer->Detach(ctrl); // Sizer'dan ayır
        ctrl->Destroy(); // Kontrolü sil
    }
    m_inputControls.clear();
    // m_inputValuesSizer->Clear(true); // Bu satır etiketleri de siler, etiketleri de yeniden oluşturmak gerekebilir.
    // Sadece kontrolleri silmek daha iyi. Sizer'daki boşluklar kalır ama Detach ile çözülür.
    // Alternatif olarak etiketleri de vektörde tutup hepsini yeniden oluşturabiliriz.
    // Şimdilik etiketleri sabit bırakıp sadece TextCtrl'leri dinamik yapalım.
    // Etiketleri de dinamik yapmak için aşağıdaki gibi bir yapı kullanılabilir.

    // Ya da daha basitçe:
    m_inputValuesSizer->Clear(true); // Sizer'daki tüm çocukları siler (etiketler dahil)


    int numInputs = m_numInputsSpinCtrl->GetValue();
    for (int i = 0; i < numInputs; ++i) {
        wxString label = wxString::Format("x%d:", i + 1);
        m_inputValuesSizer->Add(new wxStaticText(m_inputsStaticBoxSizer->GetStaticBox(), wxID_ANY, label), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

        wxTextCtrl *textCtrl = new wxTextCtrl(m_inputsStaticBoxSizer->GetStaticBox(), wxID_ANY);
        // İsteğe bağlı: Sadece sayısal giriş için doğrulayıcı
        // wxFloatingPointValidator<double> val; // Veya IntegerValidator
        // textCtrl->SetValidator(val);
        m_inputControls.push_back(textCtrl);
        m_inputValuesSizer->Add(textCtrl, 1, wxEXPAND);
    }

    // Sizer'ı ve pencereyi yeniden düzenle
    m_inputsStaticBoxSizer->GetStaticBox()->Layout(); // Statik kutunun içini düzenle
    m_panel->Layout(); // Paneli düzenle
    this->Fit(); // Pencere boyutunu ayarla
}

void MyFrame::updateHiddenLayerFields() {
    // Mevcut gizli katman kontrollerini temizle
    for (auto ctrl : m_hiddenLayerNeuronSpins) {
        m_hiddenLayerControlsSizer->Detach(ctrl);
        ctrl->Destroy();
    }
    m_hiddenLayerNeuronSpins.clear();
    for (auto label : m_hiddenLayerLabels) {
         m_hiddenLayerControlsSizer->Detach(label);
        label->Destroy();
    }
    m_hiddenLayerLabels.clear();

    // Ya da daha basitçe:
    m_hiddenLayerControlsSizer->Clear(true);


    int numHiddenLayers = m_numHiddenLayersSpinCtrl->GetValue();
    for (int i = 0; i < numHiddenLayers; ++i) {
        wxBoxSizer* layerSizer = new wxBoxSizer(wxHORIZONTAL);

        wxString labelText = wxString::Format("Neurons in Hidden Layer %d:", i + 1);
        auto* label = new wxStaticText(m_hiddenLayersStaticBoxSizer->GetStaticBox(), wxID_ANY, labelText);
        m_hiddenLayerLabels.push_back(label);
        layerSizer->Add(label, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5); // 1 orantılı genişleme için

        wxSpinCtrl *spinCtrl = new wxSpinCtrl(m_hiddenLayersStaticBoxSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 1, 1000, 1);
        m_hiddenLayerNeuronSpins.push_back(spinCtrl);
        layerSizer->Add(spinCtrl, 0, wxALIGN_CENTER_VERTICAL);

        m_hiddenLayerControlsSizer->Add(layerSizer, 0, wxEXPAND | wxTOP, 2);
    }

    m_hiddenLayersStaticBoxSizer->GetStaticBox()->Layout();
    m_panel->Layout();
    this->Fit();
}

void MyFrame::updateOutputFields() {
    // Mevcut çıkışları temizle
    for (auto label : m_outputLabels) {
        m_outputValuesSizer->Detach(label);
        label->Destroy();
    }
    m_outputLabels.clear();
    for (auto display : m_outputDisplays) {
        m_outputValuesSizer->Detach(display);
        display->Destroy();
    }
    m_outputDisplays.clear();
    // Ya da daha basitçe:
    m_outputValuesSizer->Clear(true);

    int numOutputs = m_numOutputsSpinCtrl->GetValue();
    for (int i = 0; i < numOutputs; ++i) {
        wxString labelText = wxString::Format("y%d:", i + 1);
        auto* label = new wxStaticText(m_outputsStaticBoxSizer->GetStaticBox(), wxID_ANY, labelText);
        m_outputLabels.push_back(label);
        m_outputValuesSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

        wxStaticText *staticText = new wxStaticText(m_outputsStaticBoxSizer->GetStaticBox(), wxID_ANY, " (pending calculation) ");
        m_outputDisplays.push_back(staticText);
        m_outputValuesSizer->Add(staticText, 1, wxEXPAND | wxALIGN_CENTER_VERTICAL);
    }

    m_outputsStaticBoxSizer->GetStaticBox()->Layout();
    m_panel->Layout();
    this->Fit();
}


void MyFrame::onNumInputsChanged(wxSpinEvent & /*event*/) {
    updateInputFields();
}

void MyFrame::onNumHiddenLayersChanged(wxSpinEvent & /*event*/) {
    updateHiddenLayerFields();
}

void MyFrame::onNumOutputsChanged(wxSpinEvent & /*event*/) {
    updateOutputFields();
}

void MyFrame::onCalculate(wxCommandEvent & /*event*/) {
    // 1. Giriş değerlerini topla
    std::vector<double> inputValues;
    wxLogMessage("Reading input values:");
    for (size_t i = 0; i < m_inputControls.size(); ++i) {
        double val;
        if (m_inputControls[i]->GetValue().ToDouble(&val)) {
            inputValues.push_back(val);
            wxLogMessage(wxString::Format("x%zu: %f", i + 1, val));
        } else {
            wxLogError(wxString::Format("Invalid input for x%zu: %s", i + 1, m_inputControls[i]->GetValue()));
            // Kullanıcıya hata göster ve hesaplamayı durdur
            wxMessageBox(wxString::Format("Invalid input for x%zu. Please enter a valid number.", i + 1), "Input Error", wxOK | wxICON_ERROR);
            return;
        }
    }

    // 2. Gizli katman yapılandırmasını topla
    std::vector<int> hiddenLayerNeurons;
    wxLogMessage("Reading hidden layer configuration:");
    for (size_t i = 0; i < m_hiddenLayerNeuronSpins.size(); ++i) {
        int neurons = m_hiddenLayerNeuronSpins[i]->GetValue();
        hiddenLayerNeurons.push_back(neurons);
        wxLogMessage(wxString::Format("Hidden Layer %zu Neurons: %d", i + 1, neurons));
    }

    // 3. Çıkış sayısını al (zaten m_numOutputsSpinCtrl->GetValue() ile alınabilir)
    int numOutputs = m_numOutputsSpinCtrl->GetValue();
    wxLogMessage(wxString::Format("Number of outputs: %d", numOutputs));


    // === BURAYA YAPAY SİNİR AĞI HESAPLAMA MANTIĞI GELECEK ===
    // Örnek: Sonuçları rastgele veya basit bir formülle dolduralım
    std::vector<double> calculatedOutputValues;
    for (int i = 0; i < numOutputs; ++i) {
        double sum_inputs = 0;
        for(double val : inputValues) sum_inputs += val;
        // Çok basit bir örnek hesaplama: (girişlerin toplamı + katman no) / (gizli katman sayısı + 1)
        calculatedOutputValues.push_back( (sum_inputs + i) / (hiddenLayerNeurons.size() + 1.0) );
    }
    // ==========================================================

    // 4. Hesaplanan çıkışları göster
    if (calculatedOutputValues.size() == m_outputDisplays.size()) {
        wxLogMessage("Displaying calculated output values:");
        for (size_t i = 0; i < m_outputDisplays.size(); ++i) {
            m_outputDisplays[i]->SetLabel(wxString::Format("%.4f", calculatedOutputValues[i]));
            wxLogMessage(wxString::Format("y%zu: %.4f", i + 1, calculatedOutputValues[i]));
        }
    } else {
        wxLogError("Mismatch between expected outputs and calculated outputs.");
        for (auto display : m_outputDisplays) {
            display->SetLabel("Error");
        }
    }
    m_panel->Layout(); // Değişikliklerin görünmesi için
}

// Mevcut onExit, onAbout, onHello fonksiyonlarınız
void MyFrame::onExit(wxCommandEvent & /*event*/) { Close(true); }

void MyFrame::onAbout(wxCommandEvent & /*event*/) {
  wxMessageBox("This is a wxWidgets Neural Network Configurator example", "About", wxOK | wxICON_INFORMATION);
}

void MyFrame::onHello(wxCommandEvent & /*event*/) { wxLogMessage("Hello world from Neural Network Configurator!"); }