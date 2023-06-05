#pragma once

/*
 * This class represents the interface to a Flash Memory Device. The hardware has only two methods - 'read' and 'write'
 * However, the interface for using the device is a lot more complex than that. It is outlined in the top-level README file.
 */

class FlashMemoryDevice
{
public:
    virtual unsigned char read(const long address) = 0;
    virtual void write(const long address, const unsigned char data) = 0;
};