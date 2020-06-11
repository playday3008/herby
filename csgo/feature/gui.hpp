#pragma once

#include "csgo/engine/renderer.hpp"

namespace csgo::feature
{

	class Gui : public detail::Singleton< Gui >
	{
	public:
		bool Create();
		void Destroy();

		void Present();

	public:
		static bool MessageProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
	private:
		int m_directory = -1;
		char m_directory_input[MAX_PATH] = { };
	};

}