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

    try
    {
        pDatabase_->OpenEx(connectString_);
    }
    catch (CDBException* pe)
    {
        pe->ReportError();
        pe->Delete();
    }
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

tuple<size_t, CString, CString, CString, COleDateTime> Database::queryDriveInfo(const CString& serialNumber)
{
    size_t id = 0;
    CString vendor;
    CString modelNumber;
    // CString serialNumber;
    COleDateTime warrantyExpires;

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
        sql.Format(_T("SELECT ID, VENDOR, MODEL_NUMBER, SERIAL_NUMBER, WARRANTY_EXPIRES FROM DRIVES WHERE SERIAL_NUMBER = '%s'"), serialNumber);

        CRecordset recordset(pDatabase_.get());

        try
        {
            if (recordset.Open(CRecordset::forwardOnly, sql, CRecordset::readOnly))
            {
                if (recordset.GetRecordCount())
                {
                    CDBVariant v;

                    // ID
                    v.Clear();
                    recordset.GetFieldValue(_T("ID"), v, SQL_C_SLONG);
                    id = static_cast<size_t>(v.m_lVal);

                    // VENDOR
                    v.Clear();
                    recordset.GetFieldValue(_T("VENDOR"), v, SQL_C_WCHAR);
                    vendor = *(v.m_pstringW);

                    // MODEL_NUMBER
                    v.Clear();
                    recordset.GetFieldValue(_T("MODEL_NUMBER"), v, SQL_C_WCHAR);
                    modelNumber = *(v.m_pstringW);

                    // SERIAL_NUMBER
                    //v.Clear();
                    //recordset.GetFieldValue(_T("SERIAL_NUMBER"), v, SQL_C_WCHAR);
                    //serialNumber = *(v.m_pstringW);

                    // WARRANTY_EXPIRES
                    v.Clear();
                    recordset.GetFieldValue(_T("WARRANTY_EXPIRES"), v, SQL_C_TIMESTAMP);
                    if (v.m_dwType == DBVT_DATE)
                    {
                        warrantyExpires = COleDateTime(v.m_pdate->year, v.m_pdate->month, v.m_pdate->day, 0, 0, 0);
                    }
                }

                recordset.Close();
            }
        }
        catch (CDBException* pe)
        {
            pe->ReportError();
            pe->Delete();
        }
    }
#endif

    return make_tuple(id, vendor, modelNumber, serialNumber, warrantyExpires);
}

size_t Database::registerDriveInfo(const CString& vendor, const CString& modelNumber, const CString& serialNumber, const COleDateTime& warrantyExpires)
{
    size_t newID = 0;

    if (pDatabase_->IsOpen())
    {
        CString sql;

        if (warrantyExpires == COleDateTime())
        {
            sql.Format(_T("INSERT INTO DRIVES ( VENDOR, MODEL_NUMBER, SERIAL_NUMBER ) VALUES ( '%s', '%s', '%s' )"), vendor, modelNumber, serialNumber);
        }
        else
        {
            sql.Format(_T("INSERT INTO DRIVES ( VENDOR, MODEL_NUMBER, SERIAL_NUMBER, WARRANTY_EXPIRES ) VALUES ( '%s', '%s', '%s', TO_DATE( '%s', 'YYYY/MM/DD' ) )"), vendor, modelNumber, serialNumber, warrantyExpires.Format(_T("%Y/%m/%d")));
        }

        try
        {
            pDatabase_->ExecuteSQL(sql);
        }
        catch (CDBException* pe)
        {
            pe->ReportError();
            pe->Delete();

            return 0;
        }

        sql.Format(_T("SELECT ID FROM DRIVES WHERE SERIAL_NUMBER = '%s'"), serialNumber);

        CRecordset recordset(pDatabase_.get());

        try
        {
            if (recordset.Open(CRecordset::forwardOnly, sql, CRecordset::readOnly))
            {
                if (recordset.GetRecordCount())
                {
                    CDBVariant v;
                    v.Clear();
                    recordset.GetFieldValue(_T("ID"), v, SQL_C_SLONG);
                    newID = static_cast<size_t>(v.m_lVal);
                }

                recordset.Close();
            }
        }
        catch (CDBException* pe)
        {
            pe->ReportError();
            pe->Delete();

            return 0;
        }
    }

    return newID;
}

bool Database::updateDriveInfo(size_t id, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const COleDateTime& warrantyExpires)
{
    if (pDatabase_->IsOpen())
    {
        CString sql;
        if (warrantyExpires == COleDateTime())
        {
            sql.Format(_T("UPDATE DRIVES SET ID = %llu, VENDOR = '%s', MODEL_NUMBER = '%s' WHERE SERIAL_NUMBER = '%s'"), id, vendor, modelNumber, serialNumber);
        }
        else
        {
            sql.Format(_T("UPDATE DRIVES SET ID = %llu, VENDOR = '%s', MODEL_NUMBER = '%s', WARRANTY_EXPIRES = TO_DATE( '%s', 'YYYY/MM/DD' ) WHERE SERIAL_NUMBER = '%s'"), id, vendor, modelNumber, warrantyExpires.Format(_T("%Y/%m/%d")), serialNumber);
        }

        try
        {
            pDatabase_->ExecuteSQL(sql);
        }
        catch (CDBException* pe)
        {
            pe->ReportError();
            pe->Delete();

            return false;
        }
    }

    return true;
}

bool Database::deleteDriveInfo(const CString& serialNumber)
{
    if (pDatabase_->IsOpen())
    {
        CString sql;
        sql.Format(_T("DELETE FROM DRIVES WHERE SERIAL_NUMBER = '%s'"), serialNumber);

        try
        {
            pDatabase_->ExecuteSQL(sql);
        }
        catch (CDBException* pe)
        {
            pe->ReportError();
            pe->Delete();

            return false;
        }
    }

    return true;
}
