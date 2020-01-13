#pragma once

class Database
{
public:
    Database(void);
    ~Database(void);

    std::tuple<std::size_t, CString, CString, CString, COleDateTime> queryDriveInfo(const CString& serialNumber);
    std::size_t Database::registerDriveInfo(const CString& vendor, const CString& modelNumber, const CString& serialNumber, const COleDateTime& warrantyExpires);
    bool updateDriveInfo(std::size_t id, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const COleDateTime& warrantyExpires);
    bool deleteDriveInfo(const CString& serialNumber);

private:
#ifdef DEBUG_MAHORI
    std::size_t index_;
#else
    std::unique_ptr<CDatabase> pDatabase_;
    CString connectString_;
#endif
};
