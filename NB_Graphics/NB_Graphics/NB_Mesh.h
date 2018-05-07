/*
NB_Mesh:
Attention:
Purpose:
Usage:
*/
#ifdef NB_PRAGMA_ONCE_SUPPORT
#pragma once
#endif
#ifndef NB_MESH_H_INCLUDED
#define NB_MESH_H_INCLUDED

//GLM
#include <glm/glm.hpp>

//GLEW
#include <GL/glew.h>

//STL
#include <vector>

//NB
#include "NB_Texture.h"
#include "NB_Rendering_Mesh.h"
#include "NB_Material.h"
#include "NB_Transform.h"

namespace NB
{
	class NB_Shader;

	enum NB_Mesh_Flags
	{
		NB_SOFT_EDGES,
		NB_HARD_EDGES
	};

	class NB_Mesh
	{
	public:
		//constructor
		NB_Mesh();
		NB_Mesh(const NB_Rendering_Mesh& mesh);
		NB_Mesh(const NB_Rendering_Mesh& mesh, NB_Shader& shader);

		//functions
		void draw();
		void calculate_normals(NB_Mesh_Flags mode = NB_SOFT_EDGES, float cut_off_alpha = glm::pi<float>());
		
		//get/set
		NB_Rendering_Mesh&              mesh()              { return m_sub_meshes[0]; }
		NB_Rendering_Mesh&              sub_mesh(int index) { return m_sub_meshes[index]; }
		std::vector<NB_Rendering_Mesh>& sub_meshes()        { return m_sub_meshes; }
		NB_Shader&                      shader()            { return *m_shader; }
		NB_Transform&                   transform()         { return m_transform; }

		
		const NB_Rendering_Mesh&              mesh()              const { return m_sub_meshes[0]; }
		const NB_Rendering_Mesh&              sub_mesh(int index) const { return m_sub_meshes[index]; }
		const std::vector<NB_Rendering_Mesh>& sub_meshes()        const { return m_sub_meshes; }
		const NB_Shader&                      shader()            const { return *m_shader; }
		const NB_Transform&                   transform()         const { return m_transform; }
	private:
		//member
		std::vector<NB_Rendering_Mesh> m_sub_meshes;
		NB_Transform                   m_transform;

		NB_Shader* m_shader;
	};
}
#endif