#pragma once

class Database
{
public:
    Database(void);
    ~Database(void);

    std::tuple<CString, CString, CString, CString, CString> queryDriveInfo(const CString& serialNumber);
    bool registerDriveInfo(void);
    bool updateDriveInfo(void);
    bool deleteDriveInfo(void);

private:
    std::unique_ptr<CDatabase> pDatabase_;
    CString connectString_;
};
