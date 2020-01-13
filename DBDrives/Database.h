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
#ifdef DEBUG_MAHORI
    std::size_t index_;
#else
    std::unique_ptr<CDatabase> pDatabase_;
    CString connectString_;
#endif
};
