#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/listctrl.h>

#include "./../../res/arrow_down.xpm"
#include "./../../res/arrow_up.xpm"

#include "./../app.h"

#include "./smalldlgs.h"

BEGIN_EVENT_TABLE( wxStfFileInfoDlg, wxDialog )
END_EVENT_TABLE()

wxStfFileInfoDlg::wxStfFileInfoDlg( wxWindow* parent,
        const std::string& szGeneral,
        const std::string& szFile,
        const std::string& szSection,
        int id,
        wxString title,
        wxPoint pos,
        wxSize size,
        int style
)
: wxDialog( parent, id, title, pos, size, style )
{
    //	this->SetSize(464,464);
    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );
    wxString wxs = stf::std2wx(szGeneral);
    wxTextCtrl* textCtrlGeneral = new wxTextCtrl(
            this, 
            wxID_ANY,
            wxs,
            wxDefaultPosition,
            wxSize(640,100),
            wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY
    );
    topSizer->Add( textCtrlGeneral, 0, wxALL, 5 );

    wxBoxSizer* subSizer;
    subSizer = new wxBoxSizer( wxHORIZONTAL );
    wxTextCtrl* textCtrlFile = new wxTextCtrl(
            this, 
            wxID_ANY,
            stf::std2wx(szFile),
            wxDefaultPosition,
            wxSize(416,400),
            wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY
    );
    subSizer->Add( textCtrlFile, 0, wxALL, 5 );

    wxTextCtrl* textCtrlSection  = new wxTextCtrl(
            this, 
            wxID_ANY,
            stf::std2wx(szSection),
            wxDefaultPosition,
            wxSize(214,400),
            wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY
    );
    subSizer->Add( textCtrlSection, 0, wxALL, 5 );
    topSizer->Add( subSizer, 0, wxALIGN_CENTER, 5 );

    m_sdbSizer = new wxStdDialogButtonSizer();
    m_sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    m_sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    m_sdbSizer->Realize();
    topSizer->Add( m_sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    this->Layout();
}

#define wxCOMBOCH1 1000
#define wxCOMBOCH2 1001

BEGIN_EVENT_TABLE( wxStfChannelSelDlg, wxDialog )
EVT_COMBOBOX( wxCOMBOCH1, wxStfChannelSelDlg::OnComboCh1 )
EVT_COMBOBOX( wxCOMBOCH2, wxStfChannelSelDlg::OnComboCh2 )
END_EVENT_TABLE()

wxStfChannelSelDlg::wxStfChannelSelDlg( wxWindow* parent, const std::vector<wxString>& channelNames,
        int id, wxString title, wxPoint pos, wxSize size, int style ) 
: wxDialog( parent, id, title, pos, size, style ), m_selChannel1(0), m_selChannel2(1)
{
    wxArrayString strArray;
    strArray.Alloc(channelNames.size());
    for (c_wxs_it cit = channelNames.begin(); cit != channelNames.end(); cit++) {
        strArray.Add( *cit );
    }

    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );

    // Add static boxes and combo boxes:
    wxStaticBoxSizer* ch1Sizer;
    ch1Sizer =
        new wxStaticBoxSizer(
                new wxStaticBox(
                        this,
                        -1,
                        wxT("Select active channel:") 
                ),
                wxVERTICAL
        );
    m_comboBoxCh1 = 
        new wxComboBox( 
                this, 
                wxCOMBOCH1, 
                channelNames[0], 
                wxDefaultPosition, 
                wxSize(128,20), 
                strArray, 
                wxCB_DROPDOWN | wxCB_READONLY 
        ); 

    ch1Sizer->Add( m_comboBoxCh1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
    topSizer->Add( ch1Sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBoxSizer* ch2Sizer;
    ch2Sizer =
        new wxStaticBoxSizer(
                new wxStaticBox(
                        this,
                        -1,
                        wxT("Select second channel:") 
                ),
                wxVERTICAL
        );
    m_comboBoxCh2 = 
        new wxComboBox( 
                this, 
                wxCOMBOCH2, 
                channelNames[1], 
                wxDefaultPosition, 
                wxSize(128,20), 
                strArray, 
                wxCB_DROPDOWN | wxCB_READONLY 
        ); 

    ch2Sizer->Add( m_comboBoxCh2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
    topSizer->Add( ch2Sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

    m_comboBoxCh1->SetSelection(0);
    m_comboBoxCh2->SetSelection(1);

    m_sdbSizer = new wxStdDialogButtonSizer();
    m_sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    m_sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    m_sdbSizer->Realize();
    topSizer->Add( m_sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    this->Layout();
}

void wxStfChannelSelDlg::OnComboCh1( wxCommandEvent& event ) {
    event.Skip();
    if (m_comboBoxCh1->GetCurrentSelection()==m_comboBoxCh2->GetCurrentSelection()) {
        // correct selection:
        for (int n_c=0;n_c<(int)m_comboBoxCh1->GetCount();++n_c) {
            if (n_c!=m_comboBoxCh1->GetCurrentSelection()) {
                m_comboBoxCh2->SetSelection(n_c);
                break;
            }
        }
    }
}

void wxStfChannelSelDlg::OnComboCh2( wxCommandEvent& event ) {
    event.Skip();
    if (m_comboBoxCh2->GetCurrentSelection()==m_comboBoxCh1->GetCurrentSelection()) {
        // correct selection:
        for (int n_c=0;n_c<(int)m_comboBoxCh2->GetCount();++n_c) {
            if (n_c!=m_comboBoxCh2->GetCurrentSelection()) {
                m_comboBoxCh1->SetSelection(n_c);
                break;
            }
        }
    }
}

void wxStfChannelSelDlg::EndModal(int retCode) {
    // similar to overriding OnOK in MFC (I hope...)
    if (retCode==wxID_OK) {
        if (!OnOK()) {
            wxGetApp().ErrorMsg(wxT("Please select a valid function"));
            return;
        }
    }
    wxDialog::EndModal(retCode);
}

bool wxStfChannelSelDlg::OnOK() {
    m_selChannel1 = m_comboBoxCh1->GetCurrentSelection();
    m_selChannel2 = m_comboBoxCh2->GetCurrentSelection();
    return true;
}

BEGIN_EVENT_TABLE( wxStfAlignDlg, wxDialog )
END_EVENT_TABLE()

wxStfAlignDlg::wxStfAlignDlg(wxWindow* parent, bool hasReference, int id, wxString title, wxPoint pos,
        wxSize size, int style)
: wxDialog( parent, id, title, pos, size, style ), m_alignRise(0), m_useReference(true), m_hasReference(hasReference)
{
    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );
    if (m_hasReference) {
        m_checkBox=new wxCheckBox( 
            this, 
            wxID_ANY, 
            wxT("Use reference channel"),
            wxDefaultPosition, 
            wxDefaultSize, 
            0
                                   );
        m_checkBox->SetValue(true);
        topSizer->Add( m_checkBox, 0, wxALIGN_LEFT | wxALL, 5 );
    }

    wxString m_radioBoxChoices[] = {
        wxT("peak"),
        wxT("steepest slope during rise"),
        wxT("half amplitude"),
        wxT("onset")
    };
    int m_radioBoxNChoices = sizeof( m_radioBoxChoices ) / sizeof( wxString );
    m_radioBox = new wxRadioBox(
        this, wxID_ANY, wxT("Alignment point"), wxDefaultPosition,
        wxDefaultSize, m_radioBoxNChoices, m_radioBoxChoices, m_radioBoxNChoices, wxRA_SPECIFY_ROWS);
    topSizer->Add( m_radioBox, 0, wxALL, 5 );

    m_sdbSizer = new wxStdDialogButtonSizer();
    m_sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    m_sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    m_sdbSizer->Realize();
    topSizer->Add( m_sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    this->Layout();
}

void wxStfAlignDlg::EndModal(int retCode) {
    // similar to overriding OnOK in MFC (I hope...)
    if (retCode==wxID_OK) {
        if (!OnOK()) {
            wxLogMessage(wxT("Please select a valid function"));
            return;
        }
    }
    wxDialog::EndModal(retCode);
}

bool wxStfAlignDlg::OnOK() {
    m_alignRise = m_radioBox->GetSelection();
    if (m_hasReference) {
        m_useReference = m_checkBox->IsChecked();
    } else {
        m_useReference = false;
    }
    return true;
}

BEGIN_EVENT_TABLE( wxStfFilterSelDlg, wxDialog )
END_EVENT_TABLE()

wxStfFilterSelDlg::wxStfFilterSelDlg(wxWindow* parent, int id, wxString title, wxPoint pos,
        wxSize size,int style)
: wxDialog( parent, id, title, pos, size, style ), m_filterSelect(0)
{
    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );

    wxString m_radioBoxChoices[] = { 
            wxT("Notch (inverted Gaussian)"),
            wxT("Low pass (4th-order Bessel)"), 
            wxT("Low pass (Gaussian)") 
    };
    int m_radioBoxNChoices = sizeof( m_radioBoxChoices ) / sizeof( wxString );
    m_radioBox = new wxRadioBox( this, wxID_ANY, wxT("Select filter function"), wxDefaultPosition,
            wxDefaultSize, m_radioBoxNChoices, m_radioBoxChoices, 3, wxRA_SPECIFY_ROWS );
    topSizer->Add( m_radioBox, 0, wxALL, 5 );

    m_sdbSizer = new wxStdDialogButtonSizer();
    m_sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    m_sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    m_sdbSizer->Realize();
    topSizer->Add( m_sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    this->Layout();
}

void wxStfFilterSelDlg::EndModal(int retCode) {
    // similar to overriding OnOK in MFC (I hope...)
    if (retCode==wxID_OK) {
        if (!OnOK()) {
            wxLogMessage(wxT("Please select a valid function"));
            return;
        }
    }
    wxDialog::EndModal(retCode);
}

bool wxStfFilterSelDlg::OnOK() {
    m_filterSelect=m_radioBox->GetSelection()+1;
    return true;
}

BEGIN_EVENT_TABLE( wxStfTransformDlg, wxDialog )
END_EVENT_TABLE()

wxStfTransformDlg::wxStfTransformDlg(wxWindow* parent, int id, wxString title, wxPoint pos,
        wxSize size, int style)
: wxDialog( parent, id, title, pos, size, style ), m_fSelect(0)
{
    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );

    wxString m_radioBoxChoices[] = { 
            wxT(" ln(x) ")
    };
    int m_radioBoxNChoices = sizeof( m_radioBoxChoices ) / sizeof( wxString );
    m_radioBox = new wxRadioBox(
            this,
            wxID_ANY,
            wxT("Select function"),
            wxDefaultPosition,
            wxDefaultSize,
            m_radioBoxNChoices,
            m_radioBoxChoices,
            0,
            wxRA_SPECIFY_ROWS );
    topSizer->Add( m_radioBox, 0, wxALIGN_CENTER | wxALL, 5 );

    m_sdbSizer = new wxStdDialogButtonSizer();
    m_sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    m_sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    m_sdbSizer->Realize();
    topSizer->Add( m_sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    this->Layout();
}

void wxStfTransformDlg::EndModal(int retCode) {
    // similar to overriding OnOK in MFC (I hope...)
    if (retCode==wxID_OK) {
        if (!OnOK()) {
            wxLogMessage(wxT("Please select a valid function"));
            return;
        }
    }
    wxDialog::EndModal(retCode);
}

bool wxStfTransformDlg::OnOK() {
    m_fSelect=m_radioBox->GetSelection()+1;
    return true;
}

BEGIN_EVENT_TABLE( wxStfFitInfoDlg, wxDialog )
END_EVENT_TABLE()

wxStfFitInfoDlg::wxStfFitInfoDlg(wxWindow* parent, const wxString& info, int id, wxString title,
        wxPoint pos, wxSize size, int style)
: wxDialog( parent, id, title, pos, size, style )
{
    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );

    wxTextCtrl* m_textCtrl;
    m_textCtrl=new wxTextCtrl(
            this,
            wxID_ANY,
            info,
            wxDefaultPosition,
            wxSize(320,120),
            wxTE_MULTILINE | wxTE_READONLY | wxTE_DONTWRAP
    );
    topSizer->Add( m_textCtrl, 0, wxALIGN_CENTER | wxALL, 5 );

    m_sdbSizer = new wxStdDialogButtonSizer();
    m_sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    m_sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    m_sdbSizer->Realize();
    topSizer->Add( m_sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    this->Layout();
}

BEGIN_EVENT_TABLE( wxStfBatchDlg, wxDialog )
END_EVENT_TABLE()

wxStfBatchDlg::wxStfBatchDlg(wxWindow* parent, int id, wxString title, wxPoint pos,
        wxSize size, int style)
: wxDialog( parent, id, wxT("Choose values"), pos, size, style ), batchOptions( 0 )
{
    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );

    batchOptions.push_back( BatchOption( wxT("Base"), true, id_base ) );
    batchOptions.push_back( BatchOption( wxT("Base SD"), false, id_basesd ) );
    batchOptions.push_back( BatchOption( wxT("Threshold"), true, id_threshold ) );
    batchOptions.push_back( BatchOption( wxT("time of slope threshold crossing"), false, id_slopethresholdtime ) );
    batchOptions.push_back( BatchOption( wxT("Peak (from 0)"), true, id_peakzero ) );
    batchOptions.push_back( BatchOption( wxT("Peak (from base)"), true, id_peakbase ) );
    batchOptions.push_back( BatchOption( wxT("Peak (from threshold)"), true, id_peakthreshold ) );
    batchOptions.push_back( BatchOption( wxT("Peak time"), true, id_peaktime ) );
    batchOptions.push_back( BatchOption( wxT("Lo-Hi% risetime"), false, id_rtLoHi ) );
    batchOptions.push_back( BatchOption( wxT("inner risetime"), false, id_innerLoHi ) );
    batchOptions.push_back( BatchOption( wxT("outer risetime"), false, id_outerLoHi ) );
    batchOptions.push_back( BatchOption( wxT("Half amplitude duration"), false, id_t50 ) );
    batchOptions.push_back( BatchOption( wxT("start and end time of half amplitude"), false, id_t50se ) );
    batchOptions.push_back( BatchOption( wxT("Max slopes"), false, id_slopes ) );
    batchOptions.push_back( BatchOption( wxT("Max slope times"), false, id_slopetimes ) );
    batchOptions.push_back( BatchOption( wxT("Latencies"), false, id_latencies ) );
    batchOptions.push_back( BatchOption( wxT("Fit results"), false, id_fit ) );
#ifdef WITH_PSLOPE
    batchOptions.push_back( BatchOption( wxT("pSlope"), false, id_pslopes ) );
#endif
    batchOptions.push_back( BatchOption( wxT("Threshold crossings"), false, id_crossings ) );
    std::vector<BatchOption>::const_iterator bo_it;
    std::vector<wxString> checkListChoices(batchOptions.size());
    for (bo_it = batchOptions.begin(); bo_it != batchOptions.end(); ++bo_it) {
        try {
            checkListChoices.at(bo_it->index) = bo_it->label;
        }
        catch (const std::out_of_range& e) {
            wxString errorMsg( wxT("Error while populating checkbox list:\n") );
            errorMsg += wxString(e.what(), wxConvLocal);
            wxGetApp().ExceptMsg( errorMsg );
        }
    };
    m_checkList =
        new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxSize(280,350),
                            checkListChoices.size(), &checkListChoices[0], 0 );
    for (bo_it = batchOptions.begin(); bo_it != batchOptions.end(); ++bo_it) {
        m_checkList->Check(bo_it->index, wxGetApp().wxGetProfileInt( wxT("Batch Dialog"), bo_it->label, bo_it->selection) );
    }
    topSizer->Add( m_checkList, 0, wxALIGN_CENTER | wxALL, 5 );

    m_sdbSizer = new wxStdDialogButtonSizer();
    m_sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    m_sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    m_sdbSizer->Realize();
    topSizer->Add( m_sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    this->Layout();
}

void wxStfBatchDlg::EndModal(int retCode) {
    // similar to overriding OnOK in MFC (I hope...)
    if (retCode==wxID_OK) {
        if (!OnOK()) {
            wxLogMessage(wxT("Please select a valid function"));
            return;
        }
    }
    wxDialog::EndModal(retCode);
}

bool wxStfBatchDlg::OnOK() {
    std::vector<BatchOption>::iterator bo_it;
    for (bo_it = batchOptions.begin(); bo_it != batchOptions.end(); ++bo_it) {
        bo_it->selection = m_checkList->IsChecked( bo_it->index );
        wxGetApp().wxWriteProfileInt( wxT("Batch Dialog"), bo_it->label, bo_it->selection );
    }
    return true;
}

BatchOption wxStfBatchDlg::LookUp( int index ) const {
    std::vector<BatchOption>::const_iterator bo_it;
    for (bo_it = batchOptions.begin(); bo_it != batchOptions.end(); ++bo_it) {
        if ( bo_it->index == index ) {
            return *bo_it;
        }
    }
    return BatchOption( wxT(""), false, -1 );
}

BEGIN_EVENT_TABLE( wxStfPreprintDlg, wxDialog )
END_EVENT_TABLE()

wxStfPreprintDlg::wxStfPreprintDlg(wxWindow* parent, bool isFile_, int id, wxString title,
        wxPoint pos, wxSize size, int style)
: wxDialog( parent, id, title, pos, size, style ), m_gimmicks(true), m_isFile(isFile_),
m_downsampling(1)
{
    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );

    if (!m_isFile) {
        m_checkBox=new wxCheckBox( 
                this, 
                wxID_ANY, 
                wxT("Print gimmicks (Cursors etc.)"), 
                wxDefaultPosition, 
                wxDefaultSize, 
                0 
        );
        m_checkBox->SetValue(true);
        topSizer->Add( m_checkBox, 0, wxALIGN_LEFT | wxALL, 5 );
    }

    wxFlexGridSizer* gridSizer;
    gridSizer=new wxFlexGridSizer(1,2,0,0);

    wxStaticText* staticText;
    staticText=new wxStaticText(
            this,
            wxID_ANY,
            wxT("Print every n-th point:"),
            wxDefaultPosition,
            wxSize(112,20),
            0
    );
    gridSizer->Add( staticText, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );
    wxString def; def << 1;
    m_textCtrl=new wxTextCtrl(
            this,
            wxID_ANY,
            def,
            wxDefaultPosition,
            wxSize(32,20),
            wxTE_RIGHT
    );
    gridSizer->Add( m_textCtrl, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );
    topSizer->Add( gridSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    m_sdbSizer = new wxStdDialogButtonSizer();
    m_sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    m_sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    m_sdbSizer->Realize();
    topSizer->Add( m_sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    this->Layout();
}

void wxStfPreprintDlg::EndModal(int retCode) {
    // similar to overriding OnOK in MFC (I hope...)
    if (retCode==wxID_OK) {
        if (!OnOK()) {
            wxLogMessage(wxT("Please select a valid function"));
            return;
        }
    }
    wxDialog::EndModal(retCode);
}

bool wxStfPreprintDlg::OnOK() {
    if (!m_isFile) {
        m_gimmicks=m_checkBox->IsChecked();
    } else {
        m_gimmicks=false;
    }
    // Read entry to string:
    wxString entry = m_textCtrl->GetValue();
    long tempLong;
    entry.ToLong( &tempLong );
    m_downsampling = (int) tempLong;
    return true;
}


BEGIN_EVENT_TABLE( wxStfGaussianDlg, wxDialog )
END_EVENT_TABLE()

wxStfGaussianDlg::wxStfGaussianDlg(wxWindow* parent, int id, wxString title, wxPoint pos,
        wxSize size, int style)
: wxDialog( parent, id, title, pos, size, style ), m_width(0.001), m_center(0.05), m_amp(1.0)
{
    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );

    wxFlexGridSizer *gridSizer;
    gridSizer=new wxFlexGridSizer(3,2,0,0);
    wxStaticText* staticTextAmp;
    staticTextAmp=new wxStaticText( this, wxID_ANY, wxT("Amplitude:"), wxDefaultPosition,
            wxDefaultSize, 0);
    gridSizer->Add( staticTextAmp, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    m_slider = new wxSlider( this, wxID_ANY, 100, 0, 100, 
                             wxDefaultPosition, wxSize(128,-1), wxSL_HORIZONTAL );
    gridSizer->Add( m_slider, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    wxStaticText* staticTextCenter;
    staticTextCenter=new wxStaticText(
            this,
            wxID_ANY,
            wxT("Center (kHz):"),
            wxDefaultPosition,
            wxDefaultSize,
            0
    );
    gridSizer->Add( staticTextCenter, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );
    wxString def; def << m_center;
    m_textCtrlCenter=new wxTextCtrl(
            this,
            wxID_ANY,
            def,
            wxDefaultPosition,
            wxSize(40,20),
            wxTE_RIGHT
    );
    gridSizer->Add( m_textCtrlCenter, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    wxStaticText* staticTextWidth;
    staticTextWidth=new wxStaticText(
            this,
            wxID_ANY,
            wxT("Width (kHz):"),
            wxDefaultPosition,
            wxDefaultSize,
            0
    );
    gridSizer->Add( staticTextWidth, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );
    wxString def2; def2 << m_width;
    m_textCtrlWidth=new wxTextCtrl(
            this,
            wxID_ANY,
            def2,
            wxDefaultPosition,
            wxSize(40,20),
            wxTE_RIGHT
    );
    gridSizer->Add( m_textCtrlWidth, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );
    topSizer->Add( gridSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    m_sdbSizer = new wxStdDialogButtonSizer();
    m_sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    m_sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    m_sdbSizer->Realize();
    topSizer->Add( m_sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    this->Layout();
}

void wxStfGaussianDlg::EndModal(int retCode) {
    // similar to overriding OnOK in MFC (I hope...)
    if (retCode==wxID_OK) {
        if (!OnOK()) {
            wxLogMessage(wxT("Please select a valid function"));
            return;
        }
    }
    wxDialog::EndModal(retCode);
}

bool wxStfGaussianDlg::OnOK() {
    m_amp=m_slider->GetValue() / 100.0;
    // Read entry to string:
    wxString entryCenter = m_textCtrlCenter->GetValue();
    entryCenter.ToDouble( &m_center );
    wxString entryWidth = m_textCtrlWidth->GetValue();
    entryWidth.ToDouble( &m_width );
    return true;
}

#define wxCOMBONCOLUMNS  1000
#define wxCOMBOFIRSTTIME 1001
#define wxCOMBOSECORCH   1002

BEGIN_EVENT_TABLE( wxStfTextImportDlg, wxDialog )
EVT_COMBOBOX( wxCOMBONCOLUMNS, wxStfTextImportDlg::OnComboNcolumns )
EVT_COMBOBOX( wxCOMBOFIRSTTIME, wxStfTextImportDlg::OnComboFirsttime )
EVT_COMBOBOX( wxCOMBOSECORCH, wxStfTextImportDlg::OnComboSecorch )
END_EVENT_TABLE()

wxStfTextImportDlg::wxStfTextImportDlg(wxWindow* parent,
        const wxString& textPreview,
        int hLines_,
        bool isSeries,
        int id,
        wxString title,
        wxPoint pos,
        wxSize size,
        int style) 
: wxDialog( parent, id, title, pos, size, style ), m_hLines(hLines_),m_toSection(true),
m_firstIsTime(true),m_isSeries(isSeries),m_ncolumns(2),
m_sr(20),m_yUnits(wxT("mV")),m_yUnitsCh2(wxT("pA")),m_xUnits(wxT("ms"))
{
    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );

    wxFlexGridSizer *gridSizer;
    gridSizer=new wxFlexGridSizer(4,4,0,10);

    // Header lines------------------------------------------------------
    wxStaticText* staticTextHLines;
    staticTextHLines=new wxStaticText(
            this,
            wxID_ANY,
            wxT("Header lines to skip:"),
            wxDefaultPosition,
            wxDefaultSize,
            0
    );
    gridSizer->Add( staticTextHLines, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    wxString strHLines; strHLines << m_hLines;
    m_textCtrlHLines=new wxTextCtrl(
            this,
            wxID_ANY,
            strHLines,
            wxDefaultPosition,
            wxSize(64,20),
            wxTE_RIGHT
    );
    gridSizer->Add( m_textCtrlHLines, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    // Number of columns-------------------------------------------------
    wxStaticText* staticTextNcolumns;
    staticTextNcolumns=new wxStaticText(
            this,
            wxID_ANY,
            wxT("Number of columns:"),
            wxDefaultPosition,
            wxDefaultSize,
            0
    );
    gridSizer->Add( staticTextNcolumns, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    wxString szNcolumns[] = { 
            wxT("1"),
            wxT("2"), 
            wxT("3") 
    };
    int szNcolumnsSize = sizeof( szNcolumns ) / sizeof( wxString );
    m_comboBoxNcolumns = 
        new wxComboBox( 
                this, 
                wxCOMBONCOLUMNS, 
                wxT("1"), 
                wxDefaultPosition, 
                wxSize(64,20),
                szNcolumnsSize,
                szNcolumns, 
                wxCB_DROPDOWN | wxCB_READONLY 
        ); 
    gridSizer->Add( m_comboBoxNcolumns, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    // Type of first column---------------------------------------------
    wxStaticText* staticTextFirsttime;
    staticTextFirsttime=new wxStaticText(
            this,
            wxID_ANY,
            wxT("First column is time:"),
            wxDefaultPosition,
            wxDefaultSize,
            0
    );
    gridSizer->Add( staticTextFirsttime, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    wxString szFirsttime[] = { 
            wxT("Yes"),
            wxT("No"), 
    };
    int szFirsttimeSize = sizeof( szFirsttime ) / sizeof( wxString );
    m_comboBoxFirsttime = 
        new wxComboBox( 
                this, 
                wxCOMBOFIRSTTIME, 
                wxT("Yes"),
                wxDefaultPosition, 
                wxSize(64,20),
                szFirsttimeSize,
                szFirsttime, 
                wxCB_DROPDOWN | wxCB_READONLY 
        ); 
    gridSizer->Add( m_comboBoxFirsttime, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    // Read into sections or channels-----------------------------------
    wxStaticText* staticTextSecorch;
    staticTextSecorch=new wxStaticText(
            this,
            wxID_ANY,
            wxT("Read columns into:"),
            wxDefaultPosition,
            wxDefaultSize,
            0
    );
    gridSizer->Add( staticTextSecorch, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    wxString szSecorch[] = { 
            wxT("Sections"),
            wxT("Channels"), 
    };
    int szSecorchSize = sizeof( szSecorch ) / sizeof( wxString );
    m_comboBoxSecorch = 
        new wxComboBox( 
                this, 
                wxCOMBOSECORCH, 
                wxT("Sections"),
                wxDefaultPosition, 
                wxSize(64,20),
                szSecorchSize,
                szSecorch, 
                wxCB_DROPDOWN | wxCB_READONLY 
        ); 
    gridSizer->Add( m_comboBoxSecorch, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    // Y units-----------------------------------------------------------
    wxStaticText* staticTextYUnits;
    staticTextYUnits=new wxStaticText(
            this,
            wxID_ANY,
            wxT("Y units:"),
            wxDefaultPosition,
            wxDefaultSize,
            0
    );
    gridSizer->Add( staticTextYUnits, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    m_textCtrlYUnits=new wxTextCtrl(
            this,
            wxID_ANY,
            m_yUnits,
            wxDefaultPosition,
            wxSize(64,20),
            wxTE_LEFT
    );
    gridSizer->Add( m_textCtrlYUnits, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    // Y units of channel 2----------------------------------------------
    wxStaticText* staticTextYUnitsCh2;
    staticTextYUnitsCh2=new wxStaticText(
            this,
            wxID_ANY,
            wxT("Y units, channel 2:"),
            wxDefaultPosition,
            wxDefaultSize,
            0
    );
    gridSizer->Add( staticTextYUnitsCh2, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    m_textCtrlYUnitsCh2=new wxTextCtrl(
            this,
            wxID_ANY,
            m_yUnitsCh2,
            wxDefaultPosition,
            wxSize(64,20),
            wxTE_LEFT
    );
    gridSizer->Add( m_textCtrlYUnitsCh2, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    // X units-----------------------------------------------------------
    wxStaticText* staticTextXUnits;
    staticTextXUnits=new wxStaticText(
            this,
            wxID_ANY,
            wxT("X units:"),
            wxDefaultPosition,
            wxDefaultSize,
            0
    );
    gridSizer->Add( staticTextXUnits, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    m_textCtrlXUnits=new wxTextCtrl(
            this,
            wxID_ANY,
            m_xUnits,
            wxDefaultPosition,
            wxSize(64,20),
            wxTE_LEFT
    );
    gridSizer->Add( m_textCtrlXUnits, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    // Sampling rate-----------------------------------------------------
    wxStaticText* staticTextSR;
    staticTextSR=new wxStaticText(
            this,
            wxID_ANY,
            wxT("Sampling rate (kHz):"),
            wxDefaultPosition,
            wxDefaultSize,
            0
    );
    gridSizer->Add( staticTextSR, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    wxString strSR; strSR << m_sr;
    m_textCtrlSR=new wxTextCtrl(
            this,
            wxID_ANY,
            strSR,
            wxDefaultPosition,
            wxSize(64,20),
            wxTE_RIGHT
    );
    gridSizer->Add( m_textCtrlSR, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 2 );

    topSizer->Add( gridSizer, 0, wxALIGN_CENTER, 5 );

    // Check box for batch import----------------------------------------
    if (m_isSeries) {
        m_checkBoxApplyToAll=new wxCheckBox( 
                this, 
                wxID_ANY, 
                wxT("Apply settings to all files in series"), 
                wxDefaultPosition, 
                wxDefaultSize, 
                0 
        );
        m_checkBoxApplyToAll->SetValue(false);
        topSizer->Add( m_checkBoxApplyToAll, 0, wxALIGN_CENTER | wxALL, 5 );
    }
    // OK / Cancel buttons-----------------------------------------------
    m_sdbSizer = new wxStdDialogButtonSizer();
    m_sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    m_sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    m_sdbSizer->Realize();
    topSizer->Add( m_sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    // Text preview------------------------------------------------------
    wxTextCtrl* previewCtrl;
    previewCtrl=new wxTextCtrl(
            this, 
            wxID_ANY,
            textPreview, 
            wxDefaultPosition,
            wxSize(368,160),
            wxTE_MULTILINE | wxTE_DONTWRAP | wxTE_READONLY
    );
    topSizer->Add( previewCtrl, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    disableSenseless();
    this->Layout();
}

void wxStfTextImportDlg::EndModal(int retCode) {
    // similar to overriding OnOK in MFC (I hope...)
    if (retCode==wxID_OK) {
        if (!OnOK()) {
            wxLogMessage(wxT("Please select a valid function"));
            return;
        }
    }
    wxDialog::EndModal(retCode);
}

bool wxStfTextImportDlg::OnOK() {
    long tempLong;
    m_textCtrlHLines->GetValue().ToLong( &tempLong );
    m_hLines = tempLong;

    m_toSection=(m_comboBoxSecorch->GetCurrentSelection()==0);
    m_firstIsTime=(m_comboBoxFirsttime->GetCurrentSelection()==0);
    m_ncolumns=m_comboBoxNcolumns->GetCurrentSelection()+1;

    m_yUnits = m_textCtrlYUnits->GetValue();
    m_yUnitsCh2 = m_textCtrlYUnitsCh2->GetValue();
    m_xUnits = m_textCtrlXUnits->GetValue();
    double tempDouble;
    m_textCtrlSR->GetValue().ToDouble ( &tempDouble );
    m_sr = tempDouble;
    if (m_isSeries) {
        m_applyToAll=m_checkBoxApplyToAll->IsChecked();
    }
    return true;
}

stfio::txtImportSettings wxStfTextImportDlg::GetTxtImport() const {
    stfio::txtImportSettings retTxtImport; 
    retTxtImport.firstIsTime=m_firstIsTime;
    retTxtImport.hLines=m_hLines;
    retTxtImport.ncolumns=m_ncolumns;
    retTxtImport.sr=m_sr;
    retTxtImport.toSection=m_toSection;
    retTxtImport.xUnits = stf::wx2std(m_xUnits);
    retTxtImport.yUnits = stf::wx2std(m_yUnits);
    retTxtImport.yUnitsCh2 = stf::wx2std(m_yUnitsCh2);
    return retTxtImport;
}

void wxStfTextImportDlg::disableSenseless() {
    // if there is only one column, it can't be time:
    if (m_comboBoxNcolumns->GetCurrentSelection()==0) {
        m_firstIsTime=false;
        m_comboBoxFirsttime->SetSelection(1);
        m_comboBoxFirsttime->Enable(false);
    } else {
        m_comboBoxFirsttime->Enable();
    }

    // if the first column is time, disable manual sampling rate settings:
    if (m_comboBoxFirsttime->GetCurrentSelection()==0) {
        m_textCtrlSR->Enable(false);
    } else {
        m_textCtrlSR->Enable();
    }

    // if there is only one data column,
    // it doesn't make sense to choose between channels and sections
    int temp_nColumns=m_comboBoxNcolumns->GetCurrentSelection()+1;
    int temp_nTime=(m_comboBoxFirsttime->GetCurrentSelection()==0)? 1:0;
    int nData=temp_nColumns-temp_nTime;
    if (nData<2) {
        m_comboBoxSecorch->Enable(false);
    } else {
        m_comboBoxSecorch->Enable();
    }

    // Enable units of second channel only if
    // there is a second channel at all:
    if (nData>1 &&
            m_comboBoxSecorch->GetCurrentSelection()==1)
    {
        m_textCtrlYUnitsCh2->Enable();
    } else {
        m_textCtrlYUnitsCh2->Enable(false);
    }
}

void wxStfTextImportDlg::OnComboNcolumns( wxCommandEvent& event ) {
    event.Skip();
    m_ncolumns=m_comboBoxNcolumns->GetCurrentSelection()+1;
    disableSenseless();
}

void wxStfTextImportDlg::OnComboFirsttime( wxCommandEvent& event ) {
    event.Skip();
    m_firstIsTime=(m_comboBoxFirsttime->GetCurrentSelection()==0);
    disableSenseless();
}

void wxStfTextImportDlg::OnComboSecorch( wxCommandEvent& event ) {
    event.Skip();
    m_toSection=(m_comboBoxSecorch->GetCurrentSelection()==0);
    disableSenseless();
}

enum {
    wxID_BUP,
    wxID_BDOWN,
    wxID_LISTCH
};

BEGIN_EVENT_TABLE( wxStfOrderChannelsDlg, wxDialog )
EVT_BUTTON( wxID_BUP, wxStfOrderChannelsDlg::OnUparrow )
EVT_BUTTON( wxID_BDOWN, wxStfOrderChannelsDlg::OnDownarrow )
END_EVENT_TABLE()

wxStfOrderChannelsDlg::wxStfOrderChannelsDlg(wxWindow* parent, const std::vector<wxString>& channelNames,
        int id, wxString title, wxPoint pos, wxSize size, int style)
: wxDialog( parent, id, title, pos, size, style ), channelOrder(channelNames.size())
{
    wxBoxSizer* topSizer;
    topSizer = new wxBoxSizer( wxVERTICAL );

    // 2-column sizer for funcs (left) and settings (right)
    wxFlexGridSizer* mainGrid;
    mainGrid=new wxFlexGridSizer(1,2,0,5);
    m_List = new wxListCtrl(
            this,
            wxID_LISTCH, 
            wxDefaultPosition, 
            wxSize(240,(int)channelNames.size()*24), 
            wxLC_LIST | wxLC_SINGLE_SEL 
    );

    for (long n_c=0;n_c<(long)channelNames.size();++n_c) {
        m_List->InsertItem(
                n_c,
                channelNames[n_c]
        );
        channelOrder[n_c]=n_c;
    }

    mainGrid->Add( m_List, 0, wxALIGN_CENTER_HORIZONTAL, 2 );

    // Add up and down arrows:
    wxBoxSizer* arrowSizer;
    arrowSizer = new wxBoxSizer( wxVERTICAL );
    wxBitmapButton *bUp, *bDown;
    bUp = new wxBitmapButton(this,wxID_BUP,arrow_up);
    bDown = new wxBitmapButton(this,wxID_BDOWN,arrow_down);
    arrowSizer->Add(bUp, 0, wxALIGN_CENTER | wxALL, 2 );
    arrowSizer->Add(bDown, 0, wxALIGN_CENTER | wxALL, 2 );
    mainGrid->Add( arrowSizer, 0, wxALIGN_CENTER_HORIZONTAL, 2 );
    topSizer->Add( mainGrid, 0, wxALIGN_CENTER_HORIZONTAL| wxALL, 5 );

    wxStdDialogButtonSizer* sdbSizer = new wxStdDialogButtonSizer();
    sdbSizer->AddButton( new wxButton( this, wxID_OK ) );
    sdbSizer->AddButton( new wxButton( this, wxID_CANCEL ) );
    sdbSizer->Realize();
    topSizer->Add( sdbSizer, 0, wxALIGN_CENTER | wxALL, 5 );

    topSizer->SetSizeHints(this);
    this->SetSizer( topSizer );

    this->Layout();
}

void wxStfOrderChannelsDlg::EndModal(int retCode) {
    // similar to overriding OnOK in MFC (I hope...)
    if (retCode==wxID_OK) {
        if (!OnOK()) {
            wxGetApp().ErrorMsg(wxT("Please select a valid function"));
            return;
        }
    }
    wxDialog::EndModal(retCode);
}

bool wxStfOrderChannelsDlg::OnOK() {
    return true;
}

void wxStfOrderChannelsDlg::OnUparrow( wxCommandEvent& event ) {
    event.Skip();
    // Get currently selected item in list:
    if (m_List->GetSelectedItemCount()>0) {
        // Get first selected item:
        long item = -1;
        item=m_List->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
        // Return if this is already the topmost item:
        if (item <= 0) return;
        // Otherwise, move this item up by swapping with the previous item:
        SwapItems(item-1,item);
        // Focus on list:
        m_List->SetFocus();
    }
}

void wxStfOrderChannelsDlg::OnDownarrow( wxCommandEvent& event ) {
    event.Skip();
    // Get currently selected item in list:
    if (m_List->GetSelectedItemCount()>0) {
        // Get first selected item:
        long item = -1;
        item=m_List->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
        // Return if this is the last item:
        if (item >= m_List->GetItemCount()-1) return;
        // Otherwise, move this item down by swapping with the next item:
        SwapItems(item,item+1);
        // Focus on list:
        m_List->SetFocus();
    }
}

void wxStfOrderChannelsDlg::SwapItems(long itemId1, long itemId2) {
    // Store the first item:
    wxString labelFirst=m_List->GetItemText(itemId1);
    int orderFirst=channelOrder[itemId1];
    // Change first item label:
    m_List->SetItemText(itemId1,m_List->GetItemText(itemId2));
    // Change second item label:
    m_List->SetItemText(itemId2,labelFirst);
    // Update channel order:
    channelOrder[itemId1]=channelOrder[itemId2];
    channelOrder[itemId2]=orderFirst;
}
