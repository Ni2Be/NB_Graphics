#pragma once
//NB
#include <NB_Graphics/NB_Graphics.h>
#include <NB_Graphics/NB_Window.h>
#include <NB_Graphics/NB_Rendering_Mesh.h>
#include <NB_Graphics/NB_Event_Handler.h>
#include <NB_Graphics/NB_Texture.h>
#include <NB_Graphics/NB_Illumination.h>
#include <NB_Graphics/NB_Object.h>
#include <NB_Graphics/NB_Material.h>
#include <NB_Graphics/NB_Mesh.h>
#include <NB_Graphics/NB_Standard_Shader.h>
#include <NB_Graphics/NB_Model.h>

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int HEIGHT = 768;

namespace NB 
{
	namespace NB_Test
	{
		class NB_Model_Test_Application
		{
		public:
			NB_Model_Test_Application();

			void run();
		private:
			NB::NB_Window   nb_window;
			NB::NB_Camera   camera;
			NB::NB_Model    model;

			std::vector<NB::NB_Cube> light_cubes;
			
			NB::NB_Directional_Light        dir_light;
			std::vector<NB::NB_Point_Light> point_lights;

			void event_loop();
		};
	}
}