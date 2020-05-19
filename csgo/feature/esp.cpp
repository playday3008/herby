#include "csgo/feature/esp.hpp"
namespace csgo::feature
{
	auto& renderer = engine::Renderer::Instance();
	auto& esp = option::m_visual;

	bool Esp::GetBBox(C_BaseEntity* entity,Vector4D& box)
	{
		const matrix3x4_t& tran_frame = entity->m_rgflCoordinateFrame();

		const Vector min = entity->GetCollideable()->OBBMins();
		const Vector max = entity->GetCollideable()->OBBMaxs();

		Vector screen_boxes[8];

		Vector  points[] =
		{
			{ min.x, min.y, min.z },
			{ min.x, max.y, min.z },
			{ max.x, max.y, min.z },
			{ max.x, min.y, min.z },
			{ max.x, max.y, max.z },
			{ min.x, max.y, max.z },
			{ min.x, min.y, max.z },
			{ max.x, min.y, max.z }
		};

		for (int i = 0; i <= 7; i++)
		{
			Vector out_vec;
			VectorTransform(points[i], tran_frame, out_vec);
			/*if (!WorldToScreen(out_vec, screen_boxes[i]))
				return false;*/
		}

		Vector box_array[] = {
		screen_boxes[3], // fl
		screen_boxes[5], // br
		screen_boxes[0], // bl
		screen_boxes[4], // fr
		screen_boxes[2], // fr
		screen_boxes[1], // br
		screen_boxes[6], // bl
		screen_boxes[7] // fl
		};

		float left = screen_boxes[3].x, bottom = screen_boxes[3].y, right = screen_boxes[3].x, top = screen_boxes[3].y;

		for (int i = 0; i <= 7; i++)
		{
			if (left > box_array[i].x)
				left = box_array[i].x;

			if (bottom < box_array[i].y)
				bottom = box_array[i].y;

			if (right < box_array[i].x)
				right = box_array[i].x;

			if (top > box_array[i].y)
				top = box_array[i].y;
		}

		box.x = left;
		box.y = top;
		box.w = right - left;
		box.z = bottom - top;

		return true;
	}

	void Esp::Present()
	{

	}
}