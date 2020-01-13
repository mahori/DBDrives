#pragma once

class Drive;

class Drives
{
public:
	Drives(void);

	std::size_t count(void) const;
	CString driveLetter(std::size_t index) const;
	CString id(std::size_t index) const;
	CString vendor(std::size_t index) const;
	CString modelNumber(std::size_t index) const;
	CString serialNumber(std::size_t index) const;
	CString warrantyExpires(std::size_t index) const;

private:
	std::vector<std::shared_ptr<Drive>> drives_;
};
