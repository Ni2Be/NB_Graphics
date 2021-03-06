#include "NB_Mesh.h"

#include "NB_Utility.h"
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
	//TODO maybe find better way to order than diffuse id
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
	m_shader->use();//TODO make clear where to call use()
	m_shader->update_transform(m_transform);

	m_shader->update_material(m_sub_meshes[0].material());
	m_sub_meshes[0].draw();
	//materials are ordered by their diffuse map id
	for (int i = 1, material_id = m_sub_meshes[0].material().diffuse_map().id(); i < m_sub_meshes.size(); i++)
	{
		//only update if new material is used
		if (m_sub_meshes[i].material().diffuse_map().id() != material_id)
		{
			material_id = m_sub_meshes[i].material().diffuse_map().id();
			m_shader->update_material(m_sub_meshes[i].material());
		}
		m_sub_meshes[i].draw();
	}
}



void NB::NB_Mesh::calculate_normals()
{
	//event log
	int vertices_count           = 0;
	int indices_count            = 0;
	int identical_vertices_count = 0;
	for (const auto& meshes : m_sub_meshes)
	{
		vertices_count           += meshes.m_vertices.size();
		indices_count            += meshes.m_indices.size();
		identical_vertices_count += meshes.m_identical_vertices_indices.size();
	}
	event_log("NB::NB_Mesh::calculate_normals", "process " 
		+ std::to_string(vertices_count) 
		+ " vertices with " 
		+ std::to_string(indices_count) + " indices and "
	    + std::to_string(identical_vertices_count) + " identical vertices");
	//end event log

	for (auto& r_mesh : m_sub_meshes)
	{
		calculate_normals(r_mesh);
	}	
}

void NB::NB_Mesh::calculate_normals(NB_Rendering_Mesh& r_mesh)
{
	//delete old normals
	for (auto& v : r_mesh.m_vertices)
	{
		v.m_normal = glm::vec3(0.0f);
	}
	//calculate new normals
	for (int i = 0; i < r_mesh.m_indices.size(); i += 3)
	{
		int p1 = r_mesh.m_indices[i];
		int p2 = r_mesh.m_indices[i + 1];
		int p3 = r_mesh.m_indices[i + 2];
		glm::vec3 p1_vector = r_mesh.m_vertices[p1].m_pos;
		glm::vec3 p2_vector = r_mesh.m_vertices[p2].m_pos;
		glm::vec3 p3_vector = r_mesh.m_vertices[p3].m_pos;
		glm::vec3 new_normal = glm::cross(p2_vector - p1_vector, p3_vector - p1_vector);
		r_mesh.m_vertices[p1].m_normal += new_normal;
		r_mesh.m_vertices[p2].m_normal += new_normal;
		r_mesh.m_vertices[p3].m_normal += new_normal;
	}
	//calculate identical vertices normals
	for (int i = 0; i < r_mesh.m_identical_vertices_indices.size(); i++)
	{
		int p1 = r_mesh.m_identical_vertices_indices[i].first;
		int p2 = r_mesh.m_identical_vertices_indices[i].second;
		glm::vec3 new_normal = r_mesh.m_vertices[p1].m_normal + r_mesh.m_vertices[p2].m_normal;
		r_mesh.m_vertices[p1].m_normal = new_normal;
		r_mesh.m_vertices[p2].m_normal = new_normal;
	}
	//normalize
	for (auto& v : r_mesh.m_vertices)
	{
		v.m_normal = glm::normalize(v.m_normal);
	}
	//setup new mesh
	r_mesh.setup_mesh();
}