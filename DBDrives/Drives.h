#pragma once

class Drive;

class Drives
{
public:
	Drives(void);

private:
	std::vector<std::shared_ptr<Drive>> drives_;
};
