#include "NB_Mesh.h"
#include "NB_Shader.h"
#include "NB_Standard_Shader.h"


NB::NB_Mesh::NB_Mesh()
	:
	m_shader(&NB_Standard_Shader::shader())
{}

NB::NB_Mesh::NB_Mesh(const NB_Rendering_Mesh& mesh)
	:
	m_shader(&NB_Standard_Shader::shader())
{
	//TODO init fuction that is used by all constructors
	//TODO order by material diffuse id
	m_sub_meshes.push_back(mesh);
}

NB::NB_Mesh::NB_Mesh(const NB_Rendering_Mesh& mesh, NB_Shader& shader)
	:
	m_shader(&shader)
{
	m_sub_meshes.push_back(mesh);
}

void NB::NB_Mesh::draw()
{
	m_shader->update_transform(m_transform);

	(*m_shader).update_material(m_sub_meshes.at(0).material());
	//materials are ordered by their diffuse map id
	for (int i = 0, material_id = m_sub_meshes[i].material().diffuse_map().id(); i < m_sub_meshes.size(); i++)
	{
		//only update if new material is used
		if (m_sub_meshes[i].material().diffuse_map().id() != material_id)
		{
			material_id = m_sub_meshes[i].material().diffuse_map().id();
			(*m_shader).update_material(m_sub_meshes[i].material());
		}
		m_sub_meshes[i].draw();
	}
}
