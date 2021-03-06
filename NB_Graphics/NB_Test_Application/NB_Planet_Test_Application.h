#pragma once
#include <NB_Graphics/NB_Rendering_Mesh.h>
#include <NB_Graphics/NB_Mesh.h>
#include <NB_Graphics/NB_Material.h>
#include <NB_Graphics/NB_Texture.h>
#include <NB_Graphics/NB_Graphics.h>
#include <NB_Graphics/NB_Window.h>
#include <NB_Graphics/NB_Camera.h>
#include <NB_Graphics/NB_Illumination.h>
#include <NB_Graphics/NB_Object.h>
#include <NB_Graphics/NB_Event_Handler.h>

namespace NB
{
	
	namespace NB_Test
	{
		// settings
		const unsigned int WIDTH = 1024;
		const unsigned int HEIGHT = 768;

		class NB_Planet_Test_Application
		{
		public:
			NB_Planet_Test_Application() :
				nb_window(WIDTH, HEIGHT, "NB Test Planet Mesh")
			{}

			void run();
		private:
			NB_Window nb_window;
			NB_Camera camera;
			NB_Mesh   planet;

			std::vector<NB::NB_Cube> light_cubes;

			NB::NB_Directional_Light        dir_light;
			std::vector<NB::NB_Point_Light> point_lights;

			void event_loop();
			
			void setup_planet();
			NB_Rendering_Mesh generate_icosahedron();
			NB_Rendering_Mesh generate_octahedron();
			void              split_octahedron(NB::NB_Rendering_Mesh& octahedron, int split_count);
		};
	}
}