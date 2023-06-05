#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/Application.cpp"

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

TEST(ApplicationTest, ReadAndPrint)
{
	FlashMemoryDeviceMock flashMemoryDevice{};
	EXPECT_CALL(flashMemoryDevice, read).Times(25).WillRepeatedly(Return(0x10));

	const DeviceDriver deviceDriver(&flashMemoryDevice);
	const Application application(&deviceDriver);
	application.readAndPrint(0x00, 0x4);
}

TEST(ApplicationTest, WriteAll)
{
	FlashMemoryDeviceMock flashMemoryDevice{};
	EXPECT_CALL(flashMemoryDevice, read).Times(5).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flashMemoryDevice, write).Times(5);

	const DeviceDriver deviceDriver(&flashMemoryDevice);
	const Application application(&deviceDriver);
	application.writeAll(0x10);
}
