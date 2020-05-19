#pragma once

#include "shared/include/win32.hpp"
#include "shared/include/auto.hpp"

#include "shared/detail/no_copy.hpp"
#include "shared/detail/no_move.hpp"

namespace shared::memory
{

class ObjectHook : public detail::NoCopy, public detail::NoMove
{
public:
	using Shared = std::shared_ptr< ObjectHook >;
public:
	ObjectHook(void* instance = nullptr);
	~ObjectHook();
public:
	bool Create(void* instance);
	void Destroy();

	bool Set(bool state);
	bool Hook(void* hooked, std::size_t inde);
public:
	template< typename T >
	inline T Get(std::size_t index)
	{
		if (!m_restore || index >= m_size)
			return (T)nullptr;

		return (T)m_restore[index];
	}
private:
	std::uintptr_t** m_instance = nullptr;
	std::uintptr_t* m_restore = nullptr;
	std::unique_ptr< std::uintptr_t[] > m_replace = nullptr;
	std::size_t m_size = 0u;
};

}