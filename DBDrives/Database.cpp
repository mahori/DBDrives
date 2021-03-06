#include "pch.h"
#include "Database.h"

using namespace std;

Database::Database(void)
    : pDatabase_(make_unique<CDatabase>())
{
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
}

Database::~Database(void)
{
    if (pDatabase_->IsOpen())
    {
        pDatabase_->Close();
    }
}

tuple<size_t, CString, CString, CString, COleDateTime> Database::queryDriveInfo(const CString& serialNumber)
{
    size_t id = 0;
    CString vendor;
    CString modelNumber;
    // CString serialNumber;
    COleDateTime warrantyExpires;

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
