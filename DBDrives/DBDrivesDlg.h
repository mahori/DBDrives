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
    std::shared_ptr<Drives> m_pDrives;
};
