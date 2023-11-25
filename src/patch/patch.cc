#include <patch/patch.hh>
#include <patch/vprotect.hh>

namespace patch
{
	Patch::Patch(void* address, const std::vector<uint8_t>& patchBytes, bool enable, bool vprotect, bool attached)
		: m_address{ reinterpret_cast<uint8_t*>(address) }, m_patchBytes{ patchBytes }, m_vprotect{ vprotect }, m_attached{ attached }, m_enabled{ false }
	{
		enabled(enable);
	}

	Patch::Patch(void* address, const void* patchBuffer, size_t patchSize, bool enable, bool vprotect, bool attached)
		: Patch(address, std::vector<uint8_t>(reinterpret_cast<const uint8_t*>(patchBuffer), reinterpret_cast<const uint8_t*>(patchBuffer) + patchSize), enable, vprotect, attached) { }

	Patch::~Patch()
	{
		if (m_attached)
			enabled(false);
	}

	void* Patch::getAddress() const
	{
		return m_address;
	}

	size_t Patch::getSize() const
	{
		return m_patchBytes.size();
	}

	bool Patch::enabled() const
	{
		return m_enabled;
	}

	void Patch::enabled(bool enable)
	{
		if (enable == m_enabled)
			return;

		VProtect vprotect(m_address, m_patchBytes.size(), PAGE_EXECUTE_READWRITE, m_vprotect);

		if (enable)
		{
			m_originalBytes = std::vector<uint8_t>(m_address, m_address + m_patchBytes.size());
			std::copy(m_patchBytes.begin(), m_patchBytes.end(), m_address);
		}
		else
			std::copy(m_originalBytes.begin(), m_originalBytes.end(), m_address);

		m_enabled = enable;
	}

	void Patch::detach()
	{
		m_attached = false;
	}

	Patch::operator bool() const
	{
		return m_enabled;
	}

}
