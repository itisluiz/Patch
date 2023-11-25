#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <patch/patch.hh>

namespace
{
	int someMethod() { return 10; }
}

TEST(PatchTest, PatchData)
{
	uint8_t buffer[]{ 0xAA, 0xBB, 0xCC, 0xDD };
	patch::Patch patch(buffer, { 0x11, 0x22, 0x33 }, true, false);
	EXPECT_THAT(buffer, testing::ElementsAre(0x11, 0x22, 0x33, 0xDD));

	patch.enabled(false);
	EXPECT_THAT(buffer, testing::ElementsAre(0xAA, 0xBB, 0xCC, 0xDD));
}

TEST(PatchTest, PatchText)
{
	uint8_t* textPtr{ reinterpret_cast<uint8_t*>(someMethod) };
	uint8_t originalByte{ *textPtr };

	patch::Patch patch(someMethod, { static_cast<uint8_t>(originalByte + 1) }, true, true);
	EXPECT_NE(*textPtr, originalByte);

	patch.enabled(false);
	EXPECT_EQ(*textPtr, originalByte);
}

TEST(PatchTest, LifetimePatchData)
{
	uint8_t buffer[]{ 0xAA, 0xBB, 0xCC, 0xDD };

	{
		patch::Patch patch(buffer, { 0x11, 0x22, 0x33 }, true, false);
		EXPECT_THAT(buffer, testing::ElementsAre(0x11, 0x22, 0x33, 0xDD));
	}

	EXPECT_THAT(buffer, testing::ElementsAre(0xAA, 0xBB, 0xCC, 0xDD));
}
