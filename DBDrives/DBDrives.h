#pragma once

#ifndef __AFXWIN_H__
#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"

class CDBDrivesApp : public CWinApp
{
public:
    CDBDrivesApp(void);

    BOOL InitInstance(void) override;

protected:
    DECLARE_MESSAGE_MAP()
};

extern CDBDrivesApp theApp;
