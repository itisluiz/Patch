#pragma once
#include <vector>

namespace patch
{
	/**
	 * @brief Provides functionality for patching and unpatching a specified memory region.
	 *
	 * The Patch class allows you to apply patches to a specified memory region, providing
	 * options to enable or disable the patch, apply virtual protection, and manage the attachment.
	 */
	class Patch
	{
		bool m_enabled, m_vprotect, m_attached;
		uint8_t* m_address;
		std::vector<uint8_t> m_patchBytes, m_originalBytes;

	public:
		Patch(const Patch&) = delete;

		/**
		 * @brief Constructs a Patch instance for the specified memory region.
		 *
		 * @param address The starting address of the memory region.
		 * @param patchBytes The bytes representing the patch to be applied.
		 * @param enable Flag indicating whether the patch should be enabled immediately.
		 * @param vprotect Flag indicating whether virtual protection overriding should be applied.
		 * @param attached Flag indicating whether the object lifetime should determine the lifetime of the patch.
		 */
		Patch(void* address, const std::vector<uint8_t>& patchBytes, bool enable = true, bool vprotect = true, bool attached = true);

		/**
		 * @brief Constructs a Patch instance for the specified memory region using a patch buffer.
		 *
		 * @param address The starting address of the memory region.
		 * @param patchBuffer The buffer containing the bytes representing the patch.
		 * @param patchSize The size of the patch in bytes.
		 * @param enable Flag indicating whether the patch should be enabled immediately.
		 * @param vprotect Flag indicating whether virtual protection overriding should be applied.
		 * @param attached Flag indicating whether the object lifetime should determine the lifetime of the patch.
		 */
		Patch(void* address, const void* patchBuffer, size_t patchSize, bool enable = true, bool vprotect = true, bool attached = true);

		~Patch();

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
		 * @brief Checks if the patch is currently enabled.
		 *
		 * @return true if the patch is enabled, false otherwise.
		 */
		bool enabled() const;

		/**
		 * @brief Enables or disables the patch.
		 *
		 * @param enable Flag indicating whether to enable or disable the patch.
		 */
		void enabled(bool enable);

		/**
		 * @brief Detaches the patch lifetime from the object's lifetime.
		 */
		void detach();

	public:
		Patch& operator=(const Patch&) = delete;

		/**
		 * @brief Conversion operator to check if the patch is currently enabled.
		 *
		 * @return true if enabled, false otherwise.
		 */
		operator bool() const;

	};

}
