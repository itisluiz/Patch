#include <gtest/gtest.h>
#include <patch/vprotect.hh>

namespace
{
	int someMethod() { return 10; }
}

TEST(VProtectTest, ManualProtectionOverride)
{
	uint8_t* textPtr{ reinterpret_cast<uint8_t*>(someMethod) };

	patch::VProtect vprotect(someMethod, 1, PAGE_EXECUTE_READWRITE, false, false);
	EXPECT_DEATH(*textPtr = (*textPtr + 1), ".*");
	
	vprotect.enabled(true);
	*textPtr = (*textPtr + 1), ".*";

	vprotect.enabled(false);
	EXPECT_DEATH(*textPtr = (*textPtr + 1), ".*");
}

TEST(VProtectTest, LifetimeProtectionOverride)
{
	uint8_t* textPtr{ reinterpret_cast<uint8_t*>(someMethod) };

	{
		patch::VProtect vprotect(someMethod, 1, PAGE_EXECUTE_READWRITE, false, true);
		EXPECT_DEATH(*textPtr = (*textPtr + 1), ".*");

		vprotect.enabled(true);
		*textPtr = (*textPtr + 1), ".*";
	}

	EXPECT_DEATH(*textPtr = (*textPtr + 1), ".*");
}
