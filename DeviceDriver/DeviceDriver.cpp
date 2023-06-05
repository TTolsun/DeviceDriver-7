#include <windows.h>
#include <stdexcept>
#include "DeviceDriver.h"

using namespace std;

class ReadFailException final : public std::exception
{
public:
	ReadFailException(const long address) : exception()
	{
		printf("%s: address(%ld), invalid value.", __FUNCTION__, address);
	}
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : mHardware(hardware)
{
}

int DeviceDriver::read(const long address) const
{
	const auto value = mHardware->read(address);
	Sleep(500);
	for (int tryCount = 0; tryCount < MAX_READ_COUNT - 1; tryCount++)
	{
		if (value != mHardware->read(address))
			throw ReadFailException(address);
		Sleep(500);
	}
	return value;
}

void DeviceDriver::write(long address, int data)
{
	// TODO: implement this method
	mHardware->write(address, static_cast<unsigned char>(data));
}
