#pragma once

class Drive
{
public:
	Drive(const CString& id, const CString& driveletter, int vendorID, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const CString& warrantyExpires);

	CString id(void) const;
	CString driveLetter(void) const;
	CString vendor(void) const;
	CString modelNumber(void) const;
	CString serialNumber(void) const;
	CString warrantyExpires(void) const;

private:
	CString id_;
	CString driveLetter_;
	int vendorID_;
	CString vendor_;
	CString modelNumber_;
	CString serialNumber_;
	CString warrantyExpires_;
};
