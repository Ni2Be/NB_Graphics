# NB_Graphics

The project is currently on ice.

![Model with pointlights](https://raw.githubusercontent.com/Ni2Be/NB_Graphics/master/readme_model.gif)


A simple OpenGL graphics framework.

## Examples

### Light

```cpp
NB::NB_Directional_Light dir_light;
std::vector<NB::NB_Point_Light> point_lights;

dir_light.direction() = { 0.5f, 0.5f, -0.3f };

point_lights = {
  {
    glm::vec3(1.5f, 0.5f, 0.0f),                 //position
    glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 1.0f }, //color, brightness
  {
    glm::vec3(-1.5f, 0.2f, 0.0f),
    glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f }, 1.0f }
};

// render loop
while (nb_window.is_running())
{
  NB::NB_Event_Handler::poll_events();
  nb_window.clear();

  NB::NB_Standard_Shader::shader().update_light(dir_light);
  NB::NB_Standard_Shader::shader().update_light(point_lights);

  //other stuff..

  nb_window.update();
}
```


### Model loading

```cpp
NB::NB_Model model;

//load Model
model.load_model("./nanosuit.obj");
model.transform().pos() = glm::vec3(0.5f, -0.0f, 0.0f);
model.transform().set_scale(0.14f);

// render loop
while (nb_window.is_running())
{
  NB::NB_Event_Handler::poll_events();
  nb_window.clear();
  //other stuff..

  model.transform().rot().y -= 0.005f;
  model.draw();

  nb_window.update();
}
```

### Custom Mesh
```cpp
//Vertices
std::vector<NB_Rendering_Vertex> vertices{
  NB_Rendering_Vertex{ { 0.0f, 0.0f, 1.0f }, { 0.00f, 0.5f } },//0
  NB_Rendering_Vertex{ { 1.0f, 0.0f, 0.0f }, { 0.25f, 0.5f } },//1
  NB_Rendering_Vertex{ { 0.0f, 0.0f,-1.0f }, { 0.50f, 0.5f } },//2
  NB_Rendering_Vertex{ {-1.0f, 0.0f, 0.0f }, { 0.75f, 0.5f } },//3
  NB_Rendering_Vertex{ { 0.0f, 0.0f, 1.0f }, { 1.00f, 0.5f } },//4
  NB_Rendering_Vertex{ { 0.0f,-1.0f, 0.0f }, { 0.50f, 0.0f } },//5
  NB_Rendering_Vertex{ { 0.0f, 1.0f, 0.0f }, { 0.50f, 1.0f } },//6
};

//Indices
std::vector<unsigned int> indices{
  0,1,6,
  0,5,1,
  1,2,6,
  1,5,2,
  2,3,6,
  2,5,3,
  3,4,6,
  3,5,4
};

//Identical Vertices
std::vector<NB::NB_Rendering_Mesh::vertex_pair> identical_vertices_indices{
  {0,4}
};

NB_Mesh mesh;
mesh.sub_meshes().push_back(NB_Rendering_Mesh(vertices, indices, identical_vertices_indices));
mesh.calculate_normals();

// render loop
while (nb_window.is_running())
{
  NB::NB_Event_Handler::poll_events();
  nb_window.clear();
  //other stuff..

  mesh.draw();

  nb_window.update();
}
```


### Class diagram
![Class diagram](https://raw.githubusercontent.com/Ni2Be/NB_Graphics/blob/master/class.PNG)

