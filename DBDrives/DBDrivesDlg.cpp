#include "pch.h"
#include "framework.h"
#include "DBDrivesDlg.h"
#include "AboutDlg.h"
#include "Drives.h"
#include "Resource.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDBDrivesDlg::CDBDrivesDlg(CWnd* pParent)
    : CDialogEx(IDD_DBDRIVES_DIALOG, pParent)
    , m_pDrives(make_shared<Drives>())
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBDrivesDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBOBOX, m_ComboBox);
    DDX_Control(pDX, IDC_EDIT_ID, m_EditID);
    DDX_Control(pDX, IDC_EDIT_VENDOR, m_EditVendor);
    DDX_Control(pDX, IDC_EDIT_MODEL_NUMBER, m_EditModelNumber);
    DDX_Control(pDX, IDC_EDIT_SERIAL_NUMBER, m_EditSerialNumber);
    DDX_Control(pDX, IDC_EDIT_WARRANTY_EXPIRES, m_EditWarrantyExpires);
    DDX_Control(pDX, IDC_BUTTON_REGISTER, m_BottonRegister);
    DDX_Control(pDX, IDC_BUTTON_UPDATE, m_BottonUpdate);
    DDX_Control(pDX, IDC_BUTTON_DELETE, m_BottonDelete);
}

BEGIN_MESSAGE_MAP(CDBDrivesDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_CBN_SELCHANGE(IDC_COMBOBOX, &CDBDrivesDlg::OnCbnSelchangeCombobox)
    ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CDBDrivesDlg::OnBnClickedButtonRegister)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CDBDrivesDlg::OnBnClickedButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDBDrivesDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

BOOL CDBDrivesDlg::OnInitDialog(void)
{
    CDialogEx::OnInitDialog();

    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    for (auto i = 0; i < m_pDrives->count(); ++i)
    {
        CString caption;
        caption.Append(m_pDrives->driveLetter(i));
        caption.Append(_T(" "));
        caption.Append(m_pDrives->vendor(i));
        caption.Append(_T(" "));
        caption.Append(m_pDrives->modelNumber(i));
        caption.Append(_T(" "));
        caption.Append(m_pDrives->serialNumber(i));

        m_ComboBox.AddString(caption);
    }
    m_ComboBox.SetCurSel(0);
    OnCbnSelchangeCombobox();

    return TRUE;
}

void CDBDrivesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

void CDBDrivesDlg::OnPaint(void)
{
    if (IsIconic())
    {
        CPaintDC dc(this);

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width()  - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR CDBDrivesDlg::OnQueryDragIcon(void)
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CDBDrivesDlg::OnCbnSelchangeCombobox(void)
{
    int index = m_ComboBox.GetCurSel();

    m_EditID.SetWindowText(m_pDrives->id(index));
    m_EditVendor.SetWindowText(m_pDrives->vendor(index));
    m_EditModelNumber.SetWindowText(m_pDrives->modelNumber(index));
    m_EditSerialNumber.SetWindowText(m_pDrives->serialNumber(index));
    m_EditWarrantyExpires.SetWindowText(m_pDrives->warrantyExpires(index));
}

void CDBDrivesDlg::OnBnClickedButtonRegister(void)
{
    m_pDrives->registerDriveInfo(m_ComboBox.GetCurSel());
}

void CDBDrivesDlg::OnBnClickedButtonUpdate(void)
{
    m_pDrives->updateDriveInfo(m_ComboBox.GetCurSel());
}

void CDBDrivesDlg::OnBnClickedButtonDelete(void)
{
    m_pDrives->deleteDriveInfo(m_ComboBox.GetCurSel());
}
