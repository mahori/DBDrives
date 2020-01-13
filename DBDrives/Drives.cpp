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

        if (id.Compare(_T("0")))
        {
            drives_.push_back(make_shared<Drive>(id, ataSmart.vars[i].DriveMap, vendor, modelNumber, serialNumber, warrantyExpires));
        }
        else
        {
            drives_.push_back(make_shared<Drive>(id, ataSmart.vars[i].DriveMap, VendorList[ataSmart.vars[i].DiskVendorId], modelNumber, serialNumber, warrantyExpires));
        }
    }
}

bool Drives::registerDriveInfo(std::size_t index)
{
    Database database;

    return database.registerDriveInfo();
}
bool Drives::updateDriveInfo(std::size_t index)
{
    Database database;

    return database.updateDriveInfo();
}
bool Drives::deleteDriveInfo(std::size_t index)
{
    Database database;

    return database.deleteDriveInfo();
}

size_t Drives::count(void) const
{
    return drives_.size();
}

CString Drives::driveLetter(size_t index) const
{
    return drives_.at(index)->driveLetter();
}

CString Drives::id(std::size_t index) const
{
    return drives_.at(index)->id();
}

CString Drives::vendor(std::size_t index) const
{
    return drives_.at(index)->vendor();
}

CString Drives::modelNumber(std::size_t index) const
{
    return drives_.at(index)->modelNumber();
}

CString Drives::serialNumber(std::size_t index) const
{
    return drives_.at(index)->serialNumber();
}

CString Drives::warrantyExpires(std::size_t index) const
{
    return drives_.at(index)->warrantyExpires();
}
