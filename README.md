# Patch
![my machine badge](https://forthebadge.com/images/badges/works-on-my-machine.svg)
![workflow badge](https://github.com/itisluiz/Acquire/actions/workflows/cmake-ci.yml/badge.svg)

The `patch` library is a barebones library that implements utilities related to patching / overwriting data in memory.

## Classes

### `patch::Patch`

Writes a specified, toggleable patch in some arbitrary address in memory, can optionally override the page's virtual protection.

**Usage:**
```cpp
#include <patch/patch.hh>

uint8_t buffer[]{ 0xAA, 0xBB, 0xCC, 0xDD };
patch::Patch patch(buffer, { 0x11, 0x22, 0x33 }, false, false);
// buffer[] is { 0xAA, 0xBB, 0xCC, 0xDD }
patch.enabled(true);
// buffer[] is { 0x11, 0x22, 0x33, 0xDD }
```

### `patch::VProtect`

Overrides the page protection at a specified address and length.

**Usage:**
```cpp
#include <patch/vprotect.hh>

patch::VProtect vprotect(someMethod, 32, PAGE_EXECUTE_READWRITE, false, true);
// someMethod is PAGE_EXECUTE_READ
vprotect.enabled(true);
// someMethod is PAGE_EXECUTE_READWRITE
```

## Patch lifetime

Both `VProtect` and `Patch` can have their effects associated with an object's lifetime via a construction parameter (`attached`), an object created with `attached` set to true may still be detached via `.detach()`, in a similar fashion to `std::thread`. When an object with `attached` set to true when it is destroyed, `enabled(false)` will be called.

## More examples

You may look at the tests in order to see more ways objects can be constructed and what they yield.
