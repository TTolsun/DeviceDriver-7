#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address) const;
    void write(long address, int data);

protected:
    FlashMemoryDevice* mHardware;

private:
    const int MAX_READ_COUNT = 5;
};