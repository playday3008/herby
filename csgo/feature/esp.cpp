#include "csgo/feature/esp.hpp"
namespace csgo::feature
{
	static int alpha[65];
	static int out_alpha[65];
	int iterator;

	auto& renderer = engine::Renderer::Instance();
	auto& esp = option::m_visual;

	bool Esp::GetBBox(C_BaseEntity* entity,box_t& box)
	{
		Vector origin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
		float left, top, right, bottom;

		origin = entity->m_vecOrigin();
		min = entity->GetCollideable()->OBBMins() + origin;
		max = entity->GetCollideable()->OBBMaxs() + origin;

		Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

		Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

		if (!csgo::m_debug_overlay->ScreenPosition(points[3], flb) || !csgo::m_debug_overlay->ScreenPosition(points[5], brt)
			|| !csgo::m_debug_overlay->ScreenPosition(points[0], blb) || !csgo::m_debug_overlay->ScreenPosition(points[4], frt)
			|| !csgo::m_debug_overlay->ScreenPosition(points[2], frb) || !csgo::m_debug_overlay->ScreenPosition(points[1], brb)
			|| !csgo::m_debug_overlay->ScreenPosition(points[6], blt) || !csgo::m_debug_overlay->ScreenPosition(points[7], flt))
			return false;

		left = flb.x;
		top = flb.y;
		right = flb.x;
		bottom = flb.y;

		for (int i = 1; i < 8; i++) {
			if (left > arr[i].x)
				left = arr[i].x;
			if (bottom < arr[i].y)
				bottom = arr[i].y;
			if (right < arr[i].x)
				right = arr[i].x;
			if (top > arr[i].y)
				top = arr[i].y;
		}

		box.x = left;
		box.y = top;
		box.w = float(right - left);
		box.h = float(bottom - top);

		return true;
	}

	void Esp::Present()
	{
		
	}
}