#include "NB_Mesh.h"
#include "NB_Standard_Shader.h"

NB::NB_Mesh::NB_Mesh(NB_Rendering_Mesh& mesh, NB_Material& material, NB_Standard_Shader& shader)
	:
	m_shader(&shader)
{
	m_materials.push_back(material);
	//TODO don't push back multiple materials that are the same (maybe heap)
	m_sub_meshes.push_back({ mesh, m_materials.size() - 1 });
}

void NB::NB_Mesh::draw()
{
	m_shader->update_material(m_materials[0]);
	for (int i = 0, material_id = 0; i < m_sub_meshes.size(); i++)
	{
		if (m_sub_meshes[i].second != material_id)
		{
			material_id++;
			m_shader->update_material(m_materials[material_id]);
		}
		m_sub_meshes[i].first.draw();
	}
}
