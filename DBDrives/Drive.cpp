#include "pch.h"
#include "Drive.h"

static LPCTSTR vendors[] = {
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
    _T("HDD_SSD_VENDOR_SEAGATE"),
    _T("HDD_VENDOR_WESTERN_DIGITAL"),
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

Drive::Drive(const CString& id, const CString& driveLetter, int vendorID, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const CString& warrantyExpires)
    : id_(id)
    , driveLetter_(driveLetter)
    , vendorID_(vendorID)
    , vendor_(vendor)
    , modelNumber_(modelNumber)
    , serialNumber_(serialNumber)
    , warrantyExpires_(warrantyExpires)
{
    TRACE2("DriveID = %s, Driveletter = %s\n", id_, driveLetter_);
    TRACE2("\tVendorID = %d, Vendor = %s\n", vendorID_, vendor_);
    TRACE3("\tModelNumber = %s, SeriaNumber = %s, WarrantyExpires = %s\n", modelNumber_, serialNumber_, warrantyExpires_);
}

CString Drive::id(void) const
{
    return id_;
}

CString Drive::serialNumber(void) const
{
    return serialNumber_;
}

CString Drive::driveLetter(void) const
{
    return driveLetter_;
}

CString Drive::vendor(void) const
{
    return vendor_;
}

CString Drive::modelNumber(void) const
{
    return modelNumber_;
}

CString Drive::warrantyExpires(void) const
{
    return warrantyExpires_;
}
