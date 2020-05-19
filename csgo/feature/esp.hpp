#pragma once
#include "csgo/engine.hpp"
#include "sdk/object/entity.hpp"

namespace csgo::feature
{
	class Esp : public detail::Singleton<Esp>
	{
	public:
		void Present();
	private:
		bool GetBBox(C_BaseEntity* entity,Vector4D& box);
	};
}