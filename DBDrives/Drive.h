#pragma once

class Drive
{
public:
	Drive(std::size_t, const CString& driveletter, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const COleDateTime& warrantyExpires);

	std::size_t id(void) const;
	void id(std::size_t id);
	CString driveLetter(void) const;
	CString vendor(void) const;
	void vendor(const CString& vendor);
	CString modelNumber(void) const;
	void modelNumber(const CString& modelNumber);
	CString serialNumber(void) const;
	void serialNumber(const CString& serialNumber);
	COleDateTime warrantyExpires(void) const;
	void warrantyExpires(const COleDateTime& warrantyExpires);

private:
	std::size_t id_;
	CString driveLetter_;
	CString vendor_;
	CString modelNumber_;
	CString serialNumber_;
	COleDateTime warrantyExpires_;
};
