#include "pch.h"
#include "Drives.h"
#include "AtaSmart.h"
#include "Database.h"
#include "Drive.h"

using namespace std;

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

        drives_.push_back(make_shared<Drive>(id, ataSmart.vars[i].DriveMap, ataSmart.vars[i].DiskVendorId, vendor, modelNumber, serialNumber, warrantyExpires));
    }
}

size_t Drives::count(void) const
{
    return drives_.size();
}

CString Drives::caption(size_t index) const
{
    shared_ptr<Drive> drive = drives_.at(index);

    CString caption;
    caption.Append(drive->driveLetter());
    caption.Append(_T(" "));
    caption.Append(drive->vendor());
    caption.Append(_T(" "));
    caption.Append(drive->modelNumber());
    caption.Append(_T(" "));
    caption.Append(drive->serialNumber());

    return caption;
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
