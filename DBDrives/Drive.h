#pragma once

class Drive
{
public:
	Drive(const CString& id, const CString& driveletter, int vendorID, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const CString& warrantyExpires);

private:
	CString id_;
	CString driveLetter_;
	int vendorID_;
	CString vendor_;
	CString modelNumber_;
	CString serialNumber_;
	CString warrantyExpires_;
};
