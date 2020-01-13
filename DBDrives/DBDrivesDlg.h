#pragma once

class Drives;

class CDBDrivesDlg : public CDialogEx
{
public:
    CDBDrivesDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DBDRIVES_DIALOG };
#endif

protected:
    HICON m_hIcon;

    void DoDataExchange(CDataExchange* pDX) override;
    BOOL OnInitDialog(void) override;
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint(void);
    afx_msg HCURSOR OnQueryDragIcon(void);
    DECLARE_MESSAGE_MAP()

private:
    CComboBox m_ComboBox;
    CEdit m_EditID;
    CEdit m_EditVendor;
    CEdit m_EditModelNumber;
    CEdit m_EditSerialNumber;
    CEdit m_EditWarrantyExpires;
    std::shared_ptr<Drives> m_pDrives;

    afx_msg void OnCbnSelchangeCombobox(void);
};
