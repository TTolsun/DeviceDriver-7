#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
	explicit DeviceDriver(FlashMemoryDevice* hardware);
    int read(const long address) const;
    void write(const long address, const int data) const;

protected:
    FlashMemoryDevice* mHardware;

private:
    const int MAX_READ_COUNT = 5;
};