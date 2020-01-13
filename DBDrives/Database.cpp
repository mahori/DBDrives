#include "pch.h"
#include "Database.h"

using namespace std;

#ifdef DEBUG_MAHORI
static LPCTSTR IDList[8] = { _T("63"), _T("0"), _T("11"), _T("0"), _T("68"), _T("0"), _T("0"), _T("0") };
static LPCTSTR VendorList[8] = { _T("Seagate Technology"), _T(""), _T("Western Digital"), _T(""), _T("Seagate Technology"), _T(""), _T(""), _T("") };
static LPCTSTR ModelNumberList[8] = { _T("ST4000VN008-2DR166"), _T(""), _T("WDC WD20EARS-00MVWB0"), _T(""), _T("ST6000DM003-2CY186"), _T(""), _T(""), _T("") };
static LPCTSTR WarrantyExpiresList[8] = { _T("2021-11-07 00:00:00"), _T(""), _T("2013-09-09 00:00:00") , _T("") , _T("2021-03-15 00:00:00") , _T("") , _T("") , _T("") };
#endif

Database::Database(void)
#ifdef DEBUG_MAHORI
    : index_(0)
#else
    : pDatabase_(make_unique<CDatabase>())
#endif
{
#ifndef DEBUG_MAHORI
    connectString_ = ::AfxGetApp()->GetProfileString(_T("Database"), _T("ConnectString"), nullptr);

    pDatabase_->OpenEx(connectString_, CDatabase::openReadOnly);
#endif
}

Database::~Database(void)
{
#ifndef DEBUG_MAHORI
    if (pDatabase_->IsOpen())
    {
        pDatabase_->Close();
    }
#endif
}

std::tuple<CString, CString, CString, CString, CString> Database::queryDriveInfo(const CString& serialNumber)
{
    CString id = _T("0");
    CString vendor;
    CString modelNumber;
    // CString serialNumber;
    CString warrantyExpires;

#ifdef DEBUG_MAHORI
    id              = IDList[index_];
    vendor          = VendorList[index_];
    modelNumber     = ModelNumberList[index_];
    warrantyExpires = WarrantyExpiresList[index_];
    ++index_;
#else
    if (pDatabase_->IsOpen())
    {
        CString sql;
        sql.Format(_T("SELECT ID, VENDOR, MODEL_NUMBER, SERIAL_NUMBER, WARRANTY_EXPIRES FROM DRIVES WHERE SERIAL_NUMBER = '%s'"), serialNumber.GetString());

        CRecordset recordset(pDatabase_.get());

        if (recordset.Open(CRecordset::forwardOnly, sql, CRecordset::readOnly))
        {
            if (recordset.GetRecordCount())
            {
                recordset.GetFieldValue((short)0, id);
                recordset.GetFieldValue((short)1, vendor);
                recordset.GetFieldValue((short)2, modelNumber);
                // recordset.GetFieldValue((short)3, serialNumber);
                recordset.GetFieldValue((short)4, warrantyExpires);
            }

            recordset.Close();
        }
    }
#endif

    return std::make_tuple(id, vendor, modelNumber, serialNumber, warrantyExpires);
}

bool Database::registerDriveInfo(void)
{
    return true;
}

bool Database::updateDriveInfo(void)
{
    return true;
}

bool Database::deleteDriveInfo(void)
{
    return true;
}
