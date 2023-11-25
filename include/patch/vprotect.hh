#pragma once
#include <Windows.h>

namespace patch
{
	/**
	 * @brief Provides dynamic virtual memory protection overriding.
	 *
	 * The VProtect class allows you to manage the memory protection of a specified
	 * memory region by temporarily changing its protection attributes and restoring
	 * them when necessary, either manually or having it associated with object's lifetime.
	 */
	class VProtect
	{
		bool m_enabled, m_attached;
		void* m_address;
		size_t m_size;
		DWORD m_patchProtect, m_originalProtect;

	public:
		VProtect(const VProtect&) = delete;

		/**
		 * @brief Constructs a VProtect instance for the specified memory region.
		 *
		 * @param address The starting address of the memory region.
		 * @param size The size of the memory region in bytes.
		 * @param patchProtect The protection attribute to apply when enabled.
		 * @param enable Flag indicating whether protection should be enabled immediately.
		 * @param attached Flag indicating whether the object lifetime should determine the lifetime of the protection override.
		 */
		VProtect(void* address, size_t size, DWORD patchProtect, bool enable = true, bool attached = true);

		/**
		 * @brief Constructs a VProtect instance for the memory region between startAddress and endAddress.
		 *
		 * @param startAddress The starting address of the memory region.
		 * @param endAddress The ending address of the memory region.
		 * @param patchProtect The protection attribute to apply when enabled.
		 * @param enable Flag indicating whether protection should be enabled immediately.
		 * @param attached Flag indicating whether the object lifetime should determine the lifetime of the protection override.
		 */
		VProtect(void* startAddress, void* endAddress, DWORD patchProtect, bool enable = true, bool attached = true);

		~VProtect();

	public:
		/**
		 * @brief Gets the starting address of the memory region.
		 *
		 * @return The starting address of the memory region.
		 */
		void* getAddress() const;

		/**
		 * @brief Gets the size of the memory region in bytes.
		 *
		 * @return The size of the memory region in bytes.
		 */
		size_t getSize() const;

		/**
		 * @brief Checks if memory protection is currently enabled.
		 *
		 * @return true if protection is enabled, false otherwise.
		 */
		bool enabled() const;

		/**
		 * @brief Enables or disables memory protection.
		 *
		 * @param enable Flag indicating whether to enable or disable protection.
		 */
		void enabled(bool enable);

		/**
		 * @brief Detaches the protection lifetime from the object's lifetime.
		 */
		void detach();

	public:
		VProtect& operator=(const VProtect&) = delete;

		/**
		 * @brief Conversion operator to check if the protection override is currently enabled.
		 *
		 * @return true if enabled, false otherwise.
		 */
		operator bool() const;

	};

}
