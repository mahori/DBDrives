
// DBDrives.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CDBDrivesApp:
// このクラスの実装については、DBDrives.cpp を参照してください
//

class CDBDrivesApp : public CWinApp
{
public:
    CDBDrivesApp();

    // オーバーライド
public:
    virtual BOOL InitInstance();

    // 実装

    DECLARE_MESSAGE_MAP()
};

extern CDBDrivesApp theApp;
