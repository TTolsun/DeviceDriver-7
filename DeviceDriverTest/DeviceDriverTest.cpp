#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (const long address), (override));
	MOCK_METHOD(void, write, (const long address, const unsigned char datas), (override));
};

TEST(DeviceDriverTest, Read)
{
	FlashMemoryDeviceMock flashMemoryDevice{};
	EXPECT_CALL(flashMemoryDevice, read).Times(5).WillRepeatedly(Return(0xFF));

	const DeviceDriver deviceDriver(&flashMemoryDevice);
	EXPECT_THAT(deviceDriver.read(0x00), Eq(0xFF));
}

TEST(DeviceDriverTest, ReadException)
{
	FlashMemoryDeviceMock flashMemoryDevice{};
	EXPECT_CALL(flashMemoryDevice, read).Times(5).
		WillOnce(Return(0x7)).
		WillOnce(Return(0x7)).
		WillOnce(Return(0x7)).
		WillOnce(Return(0x7)).
		WillOnce(Return(0x1));

	const DeviceDriver deviceDriver(&flashMemoryDevice);
	EXPECT_THROW(deviceDriver.read(0x00), ReadFailException);
}

TEST(DeviceDriverTest, Write)
{
	FlashMemoryDeviceMock flashMemoryDevice{};
	EXPECT_CALL(flashMemoryDevice, read).Times(1).WillOnce(Return(0xFF));
	EXPECT_CALL(flashMemoryDevice, write).Times(1);

	const DeviceDriver deviceDriver(&flashMemoryDevice);
	deviceDriver.write(0x00, 10);
}

TEST(DeviceDriverTest, WriteException)
{
	FlashMemoryDeviceMock flashMemoryDevice{};
	EXPECT_CALL(flashMemoryDevice, read).Times(1).WillOnce(Return(0xFE));

	const DeviceDriver deviceDriver(&flashMemoryDevice);
	EXPECT_THROW(deviceDriver.write(0x00, 10), WriteFailException);
}
