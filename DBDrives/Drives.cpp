#include "pch.h"
#include "Drives.h"
#include "AtaSmart.h"
#include "Database.h"
#include "Drive.h"

using namespace std;

static LPCTSTR VendorList[] = {
    _T("HDD_GENERAL"),
    _T("SSD_GENERAL"),
    _T("SSD_VENDOR_MTRON"),
    _T("SSD_VENDOR_INDILINX"),
    _T("SSD_VENDOR_JMICRON"),
    _T("SSD_VENDOR_INTEL"),
    _T("SSD_VENDOR_SAMSUNG"),
    _T("SSD_VENDOR_SANDFORCE"),
    _T("SSD_VENDOR_MICRON"),
    _T("SSD_VENDOR_OCZ"),
    _T("Seagate Technology"),  // HDD_SSD_VENDOR_SEAGATE
    _T("Western Digital"),     // HDD_VENDOR_WESTERN_DIGITAL
    _T("SSD_VENDOR_PLEXTOR"),
    _T("SSD_VENDOR_SANDISK"),
    _T("SSD_VENDOR_OCZ_VECTOR"),
    _T("HDD_SSD_VENDOR_TOSHIBA"),
    _T("SSD_VENDOR_CORSAIR"),
    _T("SSD_VENDOR_KINGSTON"),
    _T("SSD_VENDOR_MICRON_MU02"),
    _T("SSD_VENDOR_NVME"),
    _T("SSD_VENDOR_REALTEK"),
    _T("SSD_VENDOR_SKhynix"),
    _T("SSD_VENDOR_MAX"),
};


Drives::Drives(void)
{
    CAtaSmart ataSmart;
    ataSmart.FlagUsbSat = true;
    ataSmart.FlagUsbIodata = true;
    ataSmart.FlagUsbSunplus = true;
    ataSmart.FlagUsbLogitec1 = true;
    ataSmart.FlagUsbLogitec2 = true;
    ataSmart.FlagUsbJmicron = true;
    ataSmart.FlagUsbCypress = true;
    ataSmart.FlagUsbMemory = false;
    ataSmart.FlagUsbNVMeJMicron = true;
    ataSmart.FlagUsbNVMeASMedia = true;
    ataSmart.FlagUsbNVMeRealtek = true;
    ataSmart.Init(true, false, NULL, false, true, true);

    Database database;

    for (auto i = 0; i < ataSmart.vars.GetCount(); ++i)
    {
        auto [id, vendor, modelNumber, serialNumber, warrantyExpires] = database.queryDriveInfo(ataSmart.vars[i].SerialNumber);

        if (id == 0)
        {
            drives_.push_back(make_shared<Drive>(id, ataSmart.vars[i].DriveMap, VendorList[ataSmart.vars[i].DiskVendorId], ataSmart.vars[i].Model, serialNumber, warrantyExpires));
        }
        else
        {
            drives_.push_back(make_shared<Drive>(id, ataSmart.vars[i].DriveMap, vendor, modelNumber, serialNumber, warrantyExpires));
        }
    }
}

bool Drives::registerDriveInfo(size_t index, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const COleDateTime& warrantyExpires)
{
    auto drive = drives_.at(index);
    drive->vendor(vendor);
    drive->modelNumber(modelNumber);
    drive->serialNumber(serialNumber);
    drive->warrantyExpires(warrantyExpires);

    Database database;

    size_t newID = database.registerDriveInfo(vendor, modelNumber, serialNumber, warrantyExpires);
    drive->id(newID);

    return (newID != 0) ? true : false;
}

bool Drives::updateDriveInfo(size_t index, size_t id, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const COleDateTime& warrantyExpires)
{
    auto drive = drives_.at(index);
    drive->id(id);
    drive->vendor(vendor);
    drive->modelNumber(modelNumber);
    drive->serialNumber(serialNumber);
    drive->warrantyExpires(warrantyExpires);

    Database database;

    return database.updateDriveInfo(id, vendor, modelNumber, serialNumber, warrantyExpires);
}

bool Drives::deleteDriveInfo(size_t index)
{
    auto drive = drives_.at(index);
    drive->id(0);

    Database database;

    return database.deleteDriveInfo(drive->serialNumber());
}

size_t Drives::count(void) const
{
    return drives_.size();
}

CString Drives::driveLetter(size_t index) const
{
    return drives_.at(index)->driveLetter();
}

size_t Drives::id(size_t index) const
{
    return drives_.at(index)->id();
}

CString Drives::vendor(size_t index) const
{
    return drives_.at(index)->vendor();
}

CString Drives::modelNumber(size_t index) const
{
    return drives_.at(index)->modelNumber();
}

CString Drives::serialNumber(size_t index) const
{
    return drives_.at(index)->serialNumber();
}

COleDateTime Drives::warrantyExpires(size_t index) const
{
    return drives_.at(index)->warrantyExpires();
}
