/*
NB_MATRIAL:
Attention:
Purpose:
Usage:
*/

#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_MATRIAL_H_INCLUDED
#define NB_MATRIAL_H_INCLUDED

#include <glm.hpp>

//
#include "NB_Texture.h"

namespace NB
{
	struct NB_Material
	{
		NB_Material() {}

		NB_Material(float strength, float ambient_strength)
			:
			strength        (strength), 
			ambient_strength(ambient_strength)
		{}

		NB_Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
			:
			ambient  (ambient), 
			diffuse  (diffuse), 
			specular (specular), 
			shininess(shininess) 
		{}
		
		NB_Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, NB_Texture& texture, NB_Texture& diffuse_map)
			:
			ambient     (ambient), 
			diffuse     (diffuse), 
			specular    (specular), 
			shininess   (shininess), 
			texture     (&texture), 
			specular_map(&diffuse_map) 
		{}

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float     shininess;

		//only used by light
		float strength;
		float ambient_strength;

		NB_Texture* texture;
		NB_Texture* specular_map;

		inline void add_Texture(NB_Texture& texture, NB_Texture& diffuse_map)
		{
			this->texture = &texture;
			this->specular_map = &diffuse_map;
		}
	};

	const NB_Material NB_GOLD{
		glm::vec3{ 0.24725,	0.1995,	0.0745 },
		glm::vec3{ 0.75164, 0.60648, 0.22648 },
		glm::vec3{ 0.628281, 0.555802, 0.366065 },
		0.4f
	};

	const NB_Material NB_EMERALD{
		glm::vec3{ 0.0215, 0.1745, 0.0215 },
		glm::vec3{ 0.07568, 0.61424, 0.07568 },
		glm::vec3{ 0.633, 0.727811, 0.633 },
		0.6f
	};

	const NB_Material NB_JADE{
		glm::vec3{ 0.135, 0.2225, 0.1575 },
		glm::vec3{ 0.54, 0.89, 0.63 },
		glm::vec3{ 0.316228, 0.316228, 0.316228 },
		0.1f
	};

	const NB_Material NB_OBSIDIAN{
		glm::vec3{ 0.05375,0.05,0.06625 },
		glm::vec3{ 0.18275,0.17,0.22525 },
		glm::vec3{ 0.332741,0.328634,0.346435 },
		0.3f
	};

	const NB_Material NB_PEARL{
		glm::vec3{ 0.25,0.20725,0.20725 },
		glm::vec3{ 1,0.829,0.829 },
		glm::vec3{ 0.296648,0.296648,0.296648 },
		0.088f
	};

	const NB_Material NB_RUBY{
		glm::vec3{ 0.1745,0.01175,0.01175 },
		glm::vec3{ 0.61424,0.04136,0.04136 },
		glm::vec3{ 0.727811,0.626959,0.626959 },
		0.6f
	};

	const NB_Material NB_TURQUOISE{
		glm::vec3{ 0.1,0.18725,0.1745 },
		glm::vec3{ 0.396,0.74151,0.69102 },
		glm::vec3{ 0.297254,0.30829,0.306678 },
		0.1f
	};

	const NB_Material NB_BRASS{
		glm::vec3{ 0.329412,0.223529,0.027451 },
		glm::vec3{ 0.780392,0.568627,0.113725 },
		glm::vec3{ 0.992157,0.941176,0.807843 },
		0.21794872f
	};

	const NB_Material NB_BONZE{
		glm::vec3{ 0.2125,0.1275,0.054 },
		glm::vec3{ 0.714,0.4284,0.18144 },
		glm::vec3{ 0.393548,0.271906,0.166721 },
		0.2f
	};

	const NB_Material NB_CHROME{
		glm::vec3{ 0.25,0.25,0.25 },
		glm::vec3{ 0.4,0.4,0.4 },
		glm::vec3{ 0.774597,0.774597,0.774597 },
		0.6f
	};

	const NB_Material NB_COPPER{
		glm::vec3{ 0.19125,0.0735,0.0225 },
		glm::vec3{ 0.7038,0.27048,0.0828 },
		glm::vec3{ 0.256777,0.137622,0.086014 },
		0.1f
	};

	const NB_Material NB_SILVER{
		glm::vec3{ 0.19225,0.19225,0.19225 },
		glm::vec3{ 0.50754,0.50754,0.50754 },
		glm::vec3{ 0.508273,0.508273,0.508273 },
		0.4f
	};
	const NB_Material NB_PLASTIC_BLACK{
		glm::vec3{ 0.0,0.0,0.0 },
		glm::vec3{ 0.01,0.01,0.01 },
		glm::vec3{ 0.50,0.50,0.50 },
		.25f
	};
	const NB_Material NB_PLASTIC_CYAN{
		glm::vec3{ 0.0,0.1,0.06 },
		glm::vec3{ 0.0,0.50980392,0.50980392 },
		glm::vec3{ 0.50196078,0.50196078,0.50196078 },
		.25f
	};
	const NB_Material NB_PLASTIC_GREEN{
		glm::vec3{ 0.0,0.0,0.0 },
		glm::vec3{ 0.1,0.35,0.1 },
		glm::vec3{ 0.45,0.55,0.45 },
		.25f
	};
	const NB_Material NB_PLASTIC_RED{
		glm::vec3{ 0.0,0.0,0.0 },
		glm::vec3{ 0.5,0.0,0.0 },
		glm::vec3{ 0.7,0.6,0.6 },
		.25f
	};
	const NB_Material NB_PLASTIC_WHITE{
		glm::vec3{ 0.0,0.0,0.0 },
		glm::vec3{ 0.55,0.55,0.55 },
		glm::vec3{ 0.70,0.70,0.70 },
		.25f
	};
	const NB_Material NB_PLASTIC_YELLOW{
		glm::vec3{ 0.0,0.0,0.0 },
		glm::vec3{ 0.5,0.5,0.0 },
		glm::vec3{ 0.60,0.60,0.50 },
		.25f
	};
	const NB_Material NB_RUBBER_BLACK{
		glm::vec3{ 0.02,0.02,0.02 },
		glm::vec3{ 0.01,0.01,0.01 },
		glm::vec3{ 0.4,0.4,0.4 },
		.078125f
	};
	const NB_Material NB_RUBBER_CYAN{
		glm::vec3{ 0.0,0.05,0.05 },
		glm::vec3{ 0.4,0.5,0.5 },
		glm::vec3{ 0.04,0.7,0.7 },
		.078125f
	};
	const NB_Material NB_RUBBER_GREEN{
		glm::vec3{ 0.0,0.05,0.0 },
		glm::vec3{ 0.4,0.5,0.4 },
		glm::vec3{ 0.04,0.7,0.04 },
		.078125f
	};
	const NB_Material NB_RUBBER_RED{
		glm::vec3{ 0.05,0.0,0.0 },
		glm::vec3{ 0.5,0.4,0.4 },
		glm::vec3{ 0.7,0.04,0.04 },
		.078125f
	};
	const NB_Material NB_RUBBER_WHITE{
		glm::vec3{ 0.05,0.05,0.05 },
		glm::vec3{ 0.5,0.5,0.5 },
		glm::vec3{ 0.7,0.7,0.7 },
		.078125f
	};
	const NB_Material NB_RUBBER_YELLOW{
		glm::vec3{ 0.05,0.05,0.0 },
		glm::vec3{ 0.5,0.5 ,0.4 },
		glm::vec3{ 0.7 ,0.7 ,0.04 },
		.078125f
	};
}
#endif