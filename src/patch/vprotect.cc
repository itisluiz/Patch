#include <patch/vprotect.hh>
#include <Windows.h>

namespace patch
{
	VProtect::VProtect(void* address, size_t size, DWORD patchProtect, bool enable, bool attached)
		: m_address{ address }, m_size{ size }, m_patchProtect{ patchProtect }, m_attached{ attached }, m_originalProtect{ 0 }, m_enabled{ false }
	{
		enabled(enable);
	}

	VProtect::VProtect(void* startAddress, void* endAddress, DWORD patchProtect, bool enable, bool attached) :
		VProtect(startAddress, reinterpret_cast<uintptr_t>(endAddress) - reinterpret_cast<uintptr_t>(startAddress), patchProtect, enable, attached) { }

	VProtect::~VProtect()
	{
		if (m_attached)
			enabled(false);
	}

	void* VProtect::getAddress() const
	{
		return m_address;
	}

	size_t VProtect::getSize() const
	{
		return m_size;
	}

	bool VProtect::enabled() const
	{
		return m_enabled;
	}

	void VProtect::enabled(bool enable)
	{
		if (enable == m_enabled)
			return;

		DWORD auxProtect;
		VirtualProtect(m_address, m_size, enable ? m_patchProtect : m_originalProtect, enable ? &m_originalProtect : &auxProtect);

		m_enabled = enable;
	}

	void VProtect::detach()
	{
		m_attached = false;
	}

	VProtect::operator bool() const
	{
		return m_enabled;
	}

}
