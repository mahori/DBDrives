#include "pch.h"
#include "Database.h"

using namespace std;

Database::Database(void)
    : pDatabase_(make_unique<CDatabase>())
{
    connectString_ = ::AfxGetApp()->GetProfileString(_T("Database"), _T("ConnectString"), nullptr);

    pDatabase_->OpenEx(connectString_, CDatabase::openReadOnly);
}

Database::~Database(void)
{
    if (pDatabase_->IsOpen())
    {
        pDatabase_->Close();
    }
}

std::tuple<CString, CString, CString, CString, CString> Database::queryDriveInfo(const CString& serialNumber)
{
    CString id = _T("0");
    CString vendor;
    CString modelNumber;
    // CString serialNumber;
    CString warrantyExpires;

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

    return std::make_tuple(id, vendor, modelNumber, serialNumber, warrantyExpires);
}
