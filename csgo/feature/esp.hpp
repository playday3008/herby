#pragma once
#include "csgo/engine.hpp"
#include "sdk/object/entity.hpp"

namespace csgo::feature
{
	struct box_t
	{
		float x, y, w, h;
		box_t() = default;
		box_t(float x, float y, float w, float h)
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};
	class Esp : public detail::Singleton<Esp>
	{
	public:
		void Present();
	private:
		bool GetBBox(C_BaseEntity* entity, box_t& box);
	};
}