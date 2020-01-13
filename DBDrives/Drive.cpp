#include "pch.h"
#include "Drive.h"

using namespace std;

Drive::Drive(size_t id, const CString& driveLetter, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const COleDateTime& warrantyExpires)
    : id_(id)
    , driveLetter_(driveLetter)
    , vendor_(vendor)
    , modelNumber_(modelNumber)
    , serialNumber_(serialNumber)
    , warrantyExpires_(warrantyExpires)
{
    TRACE2("DriveID = %d, Driveletter = %s\n", id_, driveLetter_);
    TRACE2("\tVendor = %s, ModelNumber = %s\n", vendor_, modelNumber_);
    TRACE2("\tSeriaNumber = %s, WarrantyExpires = %s\n", serialNumber_, warrantyExpires_.Format(_T("%Y/%m/%d")));
}

size_t Drive::id(void) const
{
    return id_;
}

void Drive::id(size_t id)
{
    id_ = id;
}

CString Drive::driveLetter(void) const
{
    return driveLetter_;
}

CString Drive::vendor(void) const
{
    return vendor_;
}

void Drive::vendor(const CString& vendor)
{
    vendor_ = vendor;
}

CString Drive::modelNumber(void) const
{
    return modelNumber_;
}

void Drive::modelNumber(const CString& modelNumber)
{
    modelNumber_ = modelNumber;
}

CString Drive::serialNumber(void) const
{
    return serialNumber_;
}

void Drive::serialNumber(const CString& serialNumber)
{
    serialNumber_ = serialNumber;
}

COleDateTime Drive::warrantyExpires(void) const
{
    return warrantyExpires_;
}

void Drive::warrantyExpires(const COleDateTime& warrantyExpires)
{
    warrantyExpires_ = warrantyExpires;
}
