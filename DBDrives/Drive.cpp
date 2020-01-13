#include "pch.h"
#include "Drive.h"

Drive::Drive(const CString& id, const CString& driveLetter, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const CString& warrantyExpires)
    : id_(id)
    , driveLetter_(driveLetter)
    , vendor_(vendor)
    , modelNumber_(modelNumber)
    , serialNumber_(serialNumber)
    , warrantyExpires_(warrantyExpires)
{
    TRACE2("DriveID = %s, Driveletter = %s\n", id_, driveLetter_);
    TRACE2("\tVendor = %s, ModelNumber = %s\n", vendor_, modelNumber_);
    TRACE2("\tSeriaNumber = %s, WarrantyExpires = %s\n", serialNumber_, warrantyExpires_);
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
