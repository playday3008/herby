#include "shared/memory/object_hook.hpp"
#include "shared/memory/scan.hpp"
namespace shared::memory
{
	ObjectHook::ObjectHook(void* instance /*= nullptr*/)
	{
		if (instance)
			Create(instance);
	}

	ObjectHook::~ObjectHook()
	{
		Destroy();
	}

	bool ObjectHook::Create(void* instance)
	{
		m_instance = reinterpret_cast<std::uintptr_t**>(instance);

		if (!m_instance)
			return false;

		m_restore = *m_instance;

		if (!m_restore)
			return false;

		while (m_restore[m_size])
			m_size++;

		if (!m_size)
			return false;

		m_replace = std::make_unique< std::uintptr_t[] >(m_size);
		std::memcpy(m_replace.get(), m_restore, m_size * sizeof(std::uintptr_t));

		if (!Set(true))
			return false;

		return true;
	}

	void ObjectHook::Destroy()
	{
		Set(false);

		m_instance = nullptr;
		m_restore = nullptr;
		m_replace.reset();
		m_size = 0u;
	}

	bool ObjectHook::Set(bool state)
	{
		if (!m_instance || !m_restore || !m_replace)
			return false;

		auto data = state ? m_replace.get() : m_restore;
		return (*m_instance = data);
	}

	bool ObjectHook::Hook(void* hooked, std::size_t index)
	{
		if (!m_replace)
			return false;

		return (m_replace[index] = (std::uintptr_t)hooked);
	}
}