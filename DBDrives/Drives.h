#pragma once

class Drive;

class Drives
{
public:
	Drives(void);

	bool registerDriveInfo(std::size_t index, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const COleDateTime& warrantyExpires);
	bool updateDriveInfo(std::size_t index, std::size_t id, const CString& vendor, const CString& modelNumber, const CString& serialNumber, const COleDateTime& warrantyExpires);
	bool deleteDriveInfo(std::size_t index);

	std::size_t count(void) const;
	std::size_t id(std::size_t index) const;
	CString driveLetter(std::size_t index) const;
	CString vendor(std::size_t index) const;
	CString modelNumber(std::size_t index) const;
	CString serialNumber(std::size_t index) const;
	COleDateTime warrantyExpires(std::size_t index) const;

private:
	std::vector<std::shared_ptr<Drive>> drives_;
};
