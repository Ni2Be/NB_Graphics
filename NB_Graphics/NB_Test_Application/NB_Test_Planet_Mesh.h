#pragma once
#include <NB_Graphics/NB_Rendering_Mesh.h>


namespace NB
{
	namespace NB_Test
	{
		class NB_Planet_Test_Application
		{
		public:
			NB_Planet_Test_Application()
			{}

		private:
			void setup();
			NB_Rendering_Mesh generate_icosahedron();
		};
	}
}