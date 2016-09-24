#ifndef __MESH_H__
#define __MESH_H__

#include "app.h"
#include "shader.h"
#include "texture.h"

namespace sgltk {
	/**
	 * @struct Vertex
	 * @brief A basic vertex structure
	 */
	typedef EXPORT struct Vertex {
		/**
		 * @brief Vertex position
		 */
		glm::vec4 position;
		/**
		 * @brief Vertex normal
		 */
		glm::vec3 normal;
		/**
		 * @brief Vertex tangent
		 */
		glm::vec4 tangent;
		/**
		 * @brief Vertex bi-tangent
		 */
		glm::vec4 bitangent;
		/**
		 * @brief Vertex color
		 */
		glm::vec4 color;
		/**
		 * @brief Vertex texture coordinates
		 */
		glm::vec3 tex_coord;

		Vertex() {
			position = {0, 0, 0, 1};

			normal = {0, 0, 0};

			tangent = {0, 0, 0, 1};

			bitangent = glm::vec4(glm::cross(normal, glm::vec3(tangent)), 1);

			color = {0, 0, 0, 0};
		};

		/**
		 * @param p	Vertex position
		 * @param n	Vertex normal
		 */
		Vertex(glm::vec3 p, glm::vec3 n) {
			position = glm::vec4(p, 1);

			normal = n;

			tangent = {0, 0, 0, 1};

			bitangent = glm::vec4(glm::cross(normal, glm::vec3(tangent)), 1);

			color = {0, 0, 0, 0};

			tex_coord = {0, 0, 0};
		};

		/**
		 * @param p	Vertex position
		 * @param n	Vertex normal
		 * @param tc	Texture coordinates
		 */
		Vertex(glm::vec3 p, glm::vec3 n, glm::vec3 tc) {
			position = glm::vec4(p, 1);

			normal = n;

			tangent = {0, 0, 0, 1};

			bitangent = glm::vec4(glm::cross(normal, glm::vec3(tangent)), 1);

			color = {0, 0, 0, 0};

			tex_coord = tc;
		};

		/**
		 * @param p	Vertex position
		 * @param n	Vertex normal
		 * @param t	Vertex tangent
		 * @param tc	Texture coordinates
		 */
		Vertex(glm::vec3 p, glm::vec3 n, glm::vec3 t, glm::vec3 tc) {
			position = glm::vec4(p, 1);

			normal = n;

			tangent = glm::vec4(t, 1);

			bitangent = glm::vec4(glm::cross(normal, glm::vec3(tangent)), 1);

			color = {0, 0, 0, 0};

			tex_coord = tc;
		};

		/**
		 * @param p	Vertex position
		 * @param n	Vertex normal
		 * @param t	Vertex tangent
		 * @param c	Vertex color
		 * @param tc	Texture coordinates
		 */
		Vertex(glm::vec3 p, glm::vec3 n, glm::vec3 t,
		       glm::vec4 c, glm::vec3 tc) {
			position = glm::vec4(p, 1);

			normal = n;

			tangent = glm::vec4(t, 1);

			bitangent = glm::vec4(glm::cross(normal, glm::vec3(tangent)), 1);

			color = c;

			tex_coord = tc;
		};
	} Vertex;

/**
 * @class Mesh
 * @brief Manages meshes
 */
class Mesh {
	glm::mat4 *view_matrix;
	glm::mat4 *projection_matrix;

	GLuint vao;
	std::vector<GLuint> vbo;
	std::vector<GLuint> ibo;
	std::vector<int> num_indices;

	std::map<unsigned int, unsigned int> vertex_buffer_size_map;
	std::map<unsigned int, GLenum> vertex_buffer_usage_map;

	void material_uniform();
public:
	/**
	 * @brief Number of texture coordinates
	 */
	unsigned int num_uv;
	/**
	 * @brief Number of vertex colors
	 */
	unsigned int num_col;
	/**
	 * @brief Number of vertices
	 */
	unsigned int num_vertices;
	/**
	 * @brief The name of the ambient materiel component
	 */
	std::string ambient_color_name;
	/**
	 * @brief The name of the diffuse materiel component
	 */
	std::string diffuse_color_name;
	/**
	 * @brief The name of the specular materiel component
	 */
	std::string specular_color_name;
	/**
	 * @brief The name of the specular factor
	 */
	std::string shininess_name;
	/**
	 * @brief The name of the specular exponent
	 */
	std::string shininess_strength_name;

	/**
	 * @brief The name of the texture containing the ambient color component
	 */
	std::string ambient_texture_name;
	/**
	 * @brief The name of the texture containing the diffuse color component
	 */
	std::string diffuse_texture_name;
	/**
	 * @brief The name of the texture containing the specular factor
	 */
	std::string specular_texture_name;
	/**
	 * @brief The name of the texture containing the specular exponent
	 */
	std::string shininess_texture_name;
	/**
	 * @brief The name of the texture containing the light being emitted
	 */
	std::string emissive_texture_name;
	/**
	 * @brief The name of the texture containing normal vectors
	 */
	std::string normals_texture_name;
	/**
	 * @brief The name of the texture containing the displacement factor
	 */
	std::string displacement_texture_name;
	/**
	 * @brief The name of the texture containing the opacity strength
	 */
	std::string opacity_texture_name;
	/**
	 * @brief The name of the texture containing the diffuse light factor
	 */
	std::string lightmap_texture_name;

	/**
	 * @brief The name of the model matrix in the shader
	 */
	std::string model_matrix_name;
	/**
	 * @brief The name of the view matrix in the shader
	 */
	std::string view_matrix_name;
	/**
	 * @brief The name of the projection matrix in the shader
	 */
	std::string projection_matrix_name;
	/**
	 * @brief The name of the model-view matrix in the shader
	 */
	std::string model_view_matrix_name;
	/**
	 * @brief The name of the view-projection matrix in the shader
	 */
	std::string view_proj_matrix_name;
	/**
	 * @brief The name of the model-view-projection matrix in the shader
	 */
	std::string model_view_projection_matrix_name;
	/**
	 * @brief The name of the normal matrix in the shader
	 */
	std::string normal_matrix_name;

	/**
	 * @brief The shader being used to draw the mesh
	 */
	Shader *shader;
	/**
	 * @brief The bounding box
	 */
	std::vector<glm::vec3> bounding_box;
	/**
	 * @brief The model matrix
	 */
	glm::mat4 model_matrix;
	/**
	 * @brief The shininess of the material
	 */
	float shininess;
	/**
	 * @brief The strength of the shininess of the material
	 */
	float shininess_strength;
	/**
	 * @brief The ambient color component of the material
	 */
	glm::vec4 color_ambient;
	/**
	 * @brief The diffuse color component of the material
	 */
	glm::vec4 color_diffuse;
	/**
	 * @brief The specular color component of the material
	 */
	glm::vec4 color_specular;
	/**
	 * @brief The ambient textures
	 */
	std::vector<Texture *> textures_ambient;
	/**
	 * @brief The diffuse textures
	 */
	std::vector<Texture *> textures_diffuse;
	/**
	 * @brief The specular textures
	 */
	std::vector<Texture *> textures_specular;
	/**
	 * @brief The shininess textures
	 */
	std::vector<Texture *> textures_shininess;
	/**
	 * @brief The emissive textures
	 */
	std::vector<Texture *> textures_emissive;
	/**
	 * @brief The normals textures
	 */
	std::vector<Texture *> textures_normals;
	/**
	 * @brief The displacement textures
	 */
	std::vector<Texture *> textures_displacement;
	/**
	 * @brief The opacity textures
	 */
	std::vector<Texture *> textures_opacity;
	/**
	 * @brief The lightmap textures
	 */
	std::vector<Texture *> textures_lightmap;

	/**
	 * @brief Indicates that the mesh should be drawn as a wireframe
	 */
	bool wireframe;
	/**
	 * @brief Indicates that the mesh should not be drawn using
	 * 	  back face culling
	 */
	bool twosided;

	EXPORT Mesh();
	EXPORT ~Mesh();

	/**
	 * @brief Specifies the shader to use to render the mesh
	 * @param shader The shader to be used to render the mesh
	 */
	EXPORT void setup_shader(Shader *shader);
	/**
	 * @brief Sets up the view and projection matrices that will be used
	 * 	  by the mesh
	 * @param view_matrix The view matrix
	 * @param projection_matrix The projection matrix
	 */
	EXPORT void setup_camera(glm::mat4 *view_matrix,
			  glm::mat4 *projection_matrix);
	/**
	 * @brief Sets the name of the model matrix in the shader
	 * @param name The name of the model matrix.
	 * 	The name is reset if string is empty.
	 * @note Default value is "model_matrix"
	 */
	EXPORT void set_model_matrix_name(std::string name);
	/**
	 * @brief Sets the name of the view matrix in the shader
	 * @param name The name of the view matrix.
	 * 	The name is reset if string is empty.
	 * @note Default value is "view_matrix"
	 */
	EXPORT void set_view_matrix_name(std::string name);
	/**
	 * @brief Sets the name of the projection matrix in the shader
	 * @param name The name of the projection matrix.
	 * 	The name is reset if string is empty.
	 * @note Default value is "proj_matrix"
	 */
	EXPORT void set_projection_matrix_name(std::string name);
	/**
	 * @brief Sets the name of the model-view matrix in the shader
	 * @param name The name of the model-view matrix.
	 * 	The name is reset if string is empty.
	 * @note Default value is "model_view_matrix"
	 */
	EXPORT void set_model_view_matrix_name(std::string name);
	/**
	 * @brief Sets the name of the view-projection matrix in the shader
	 * @param name The name of the view-projection matrix.
	 * 	The name is reset if string is empty.
	 * @note Default value is "view_proj_matrix"
	 */
	EXPORT void set_view_proj_matrix_name(std::string name);
	/**
	 * @brief Sets the name of the model-view-projection matrix
	 * 	in the shader
	 * @param name The name of the model-view-projection matrix.
	 * 	The name is reset if string is empty.
	 * @note Default value is "model_view_proj_matrix"
	 */
	EXPORT void set_model_view_proj_name(std::string name);
	/**
	 * @brief Sets the name of the normal matrix in the shader
	 * @param name The name of the normal matrix.
	 * 	The name is reset if string is empty.
	 * @note Default value is "normal_matrix"
	 */
	EXPORT void set_normal_matrix_name(std::string normal_matrix_name);
	/**
	 * @brief Sets the name of the ambient color in the shader
	 * @param name The name of the ambient color component.
	 * 	The name is reset if string is empty.
	 * @note Default value is "color_ambient"
	 */
	EXPORT void set_ambient_color_name(std::string name);
	/**
	 * @brief Sets the name of the diffuse color in the shader
	 * @param name The name of the diffuse color component.
	 * 	The name is reset if string is empty.
	 * @note Default value is "color_diffuse"
	 */
	EXPORT void set_diffuse_color_name(std::string name);
	/**
	 * @brief Sets the name of the specular color in the shader
	 * @param name The name of the specular color component.
	 * 	The name is reset if string is empty.
	 * @note Default value is "color_specular"
	 */
	EXPORT void set_specular_color_name(std::string name);
	/**
	 * @brief Sets the name of the shininess of the material
	 * 	in the shader
	 * @param name The name of the shininess component.
	 * 	The name is reset if string is empty.
	 * @note Default value is "shininess"
	 */
	EXPORT void set_shininess_name(std::string name);
	/**
	 * @brief Sets the name of the shininess strength of the material
	 * 	in the shader
	 * @param name The name of the shininess strength component.
	 * 	The name is reset if string is empty.
	 * @note Default value is "shininess_strength"
	 */
	EXPORT void set_shininess_strength_name(std::string name);
	/**
	 * @brief Sets the name of the ambient texture in the shader
	 * @param name The name of the ambient texture.
	 * 	The name is reset if string is empty.
	 */
	EXPORT void set_ambient_texture_name(std::string name);
	/**
	 * @brief Sets the name of the diffuse texture in the shader
	 * @param name The name of the diffuse texture.
	 * 	The name is reset if string is empty.
	 */
	EXPORT void set_diffuse_texture_name(std::string name);
	/**
	 * @brief Sets the name of the specular texture in the shader
	 * @param name The name of the specular texture.
	 * 	The name is reset if string is empty.
	 */
	EXPORT void set_specular_texture_name(std::string name);
	/**
	 * @brief Sets the name of the shininess texture in the shader
	 * @param name The name of the shininess texture.
	 * 	The name is reset if string is empty.
	 */
	EXPORT void set_shininess_texture_name(std::string name);
	/**
	 * @brief Sets the name of the emissive texture in the shader
	 * @param name The name of the emissive texture.
	 * 	The name is reset if string is empty.
	 */
	EXPORT void set_emissive_texture_name(std::string name);
	/**
	 * @brief Sets the name of the normals texture in the shader
	 * @param name The name of the normals texture.
	 * 	The name is reset if string is empty.
	 */
	EXPORT void set_normals_texture_name(std::string name);
	/**
	 * @brief Sets the name of the displacement texture in the shader
	 * @param name The name of the displacement texture.
	 * 	The name is reset if string is empty.
	 */
	EXPORT void set_displacement_texture_name(std::string name);
	/**
	 * @brief Sets the name of the opacity texture in the shader
	 * @param name The name of the opacity texture.
	 * 	The name is reset if string is empty.
	 */
	EXPORT void set_opacity_texture_name(std::string name);
	/**
	 * @brief Sets the name of the lightmap texture in the shader
	 * @param name The name of the lightmap texture.
	 * 	The name is reset if string is empty.
	 */
	EXPORT void set_lightmap_texture_name(std::string name);

	/**
	 * @brief Loads vertices into memory
	 * @param vertexdata The vertices to be loaded into memory
	 * @param number_elements Number of elements
	 * @param usage A hint as to how the buffer will be accessed.
	 * 	Valid values are GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}.
	 * @return Returns the index that the buffer was attached to
	 */
	template <typename T = Vertex>
	int attach_vertex_buffer(const void *vertexdata,
				 unsigned int number_elements,
				 GLenum usage = GL_STATIC_DRAW);
	/**
	 * @brief Loads vertices into memory
	 * @param vertexdata The vertices to be loaded into memory
	 * @param usage A hint as to how the buffer will be accessed.
	 * 	Valid values are GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}.
	 * @return Returns the index that the buffer was attached to
	 */
	template <typename T = Vertex>
	int attach_vertex_buffer(const std::vector<T>& vertexdata,
				 GLenum usage = GL_STATIC_DRAW);
	/**
	 * @brief Modifies the data in the vertex buffer
	 * @param buffer_index The index of the buffer to be modified
	 * @param data The data to be loaded into the buffer
	 * @param number_elements Number of elements
	 */
	template <typename T = Vertex>
	bool replace_buffer_data(unsigned int buffer_index,
				 const void *data,
				 unsigned int number_elements);
	/**
	 * @brief Modifies the data in the vertex buffer
	 * @param buffer_index The index of the buffer to be modified
	 * @param data The data to be loaded into the buffer
	 */
	template <typename T = Vertex>
	bool replace_buffer_data(unsigned int buffer_index, const std::vector<T>& data);
	/**
	 * @brief This is a convenience function that combines attach_vertex_buffer and
	 * 		set_vertex_attribute.
	 * @param attrib_name		The attribute name in the shader
	 * @param number_elements	Number of elements
	 * @param type			Element type
	 * @param data			The vertices to be loaded into memory
	 * @param usage A hint as to how the buffer will be accessed.
	 * 	Valid values are GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}.
	 * @return	Returns 0 on success, -1 if no shader was
	 * 		specified for the mesh, -2 if the vertex attribute
	 * 		could not be found
	 */
	template <typename T = glm::vec3>
	int add_vertex_attribute(std::string attrib_name,
					GLint number_elements,
					GLenum type,
					const void *data,
					GLenum usage = GL_STATIC_DRAW);
	/**
	 * @brief This is a convenience function that combines attach_vertex_buffer and
	 * 		set_vertex_attribute.
	 * @param attrib_name		The attribute name in the shader
	 * @param number_elements	Number of elements
	 * @param type			Element type
	 * @param data			The vertices to be loaded into memory
	 * @param usage A hint as to how the buffer will be accessed.
	 * 	Valid values are GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}.
	 * @return	Returns 0 on success, -1 if no shader was
	 * 		specified for the mesh, -2 if the vertex attribute
	 * 		could not be found
	 */
	template <typename T = glm::vec3>
	int add_vertex_attribute(std::string attrib_name,
					GLint number_elements,
					GLenum type,
					const std::vector<T>& data,
					GLenum usage = GL_STATIC_DRAW);
	/**
	 * @brief This is a convenience function that combines attach_vertex_buffer and
	 * 		set_vertex_attribute.
	 * @param attrib_location	The attribute location in the shader
	 * @param number_elements	Number of elements
	 * @param type			Element type
	 * @param data			The vertices to be loaded into memory
	 * @param usage A hint as to how the buffer will be accessed.
	 * 	Valid values are GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}.
	 * @return	Returns 0 on success, -1 if no shader was
	 * 		specified for the mesh, -2 if the vertex attribute
	 * 		could not be found
	 */
	template <typename T = glm::vec3>
	int add_vertex_attribute(int attrib_location,
					GLint number_elements,
					GLenum type,
					const void *data,
					GLenum usage = GL_STATIC_DRAW);
	/**
	 * @brief This is a convenience function that combines attach_vertex_buffer and
	 * 		set_vertex_attribute.
	 * @param attrib_location	The attribute location in the shader
	 * @param number_elements	Number of elements
	 * @param type			Element type
	 * @param data			The vertices to be loaded into memory
	 * @param usage A hint as to how the buffer will be accessed.
	 * 	Valid values are GL_{STREAM,STATIC,DYNAMIC}_{DRAW,READ,COPY}.
	 * @return	Returns 0 on success, -1 if no shader was
	 * 		specified for the mesh, -2 if the vertex attribute
	 * 		could not be found
	 */
	template <typename T = glm::vec3>
	int add_vertex_attribute(int attrib_location,
					GLint number_elements,
					GLenum type,
					const std::vector<T>& data,
					GLenum usage = GL_STATIC_DRAW);
	/**
	 * @brief Sets pointers to vertex attributes
	 * @param attrib_name		The attribute name in the shader
	 * @param buffer_index		The index of the buffer that contains
	 *				the attribute
	 * @param number_elements	Number of elements
	 * @param type			Element type
	 * @param stride		Memory offset between vertices
	 * @param pointer		The offset of the attribute in the
	 * 				vertex structure
	 * @param divisor Determines how many instances share the same attribute value.
	 * 		0 means that every shader instance gets a new value,
	 * 		1 means every mesh instance gets a new value,
	 * 		2 means that two instances get the same value and so on.
	 * @return	Returns 0 on success, -1 if no shader was
	 * 		specified for the mesh, -2 if the vertex attribute
	 * 		could not be found
	 */
	EXPORT int set_vertex_attribute(std::string attrib_name,
				 unsigned int buffer_index,
				 GLint number_elements,
				 GLenum type,
				 GLsizei stride,
				 const GLvoid *pointer,
				 unsigned int divisor = 0);
	/**
	 * @brief Sets pointers to vertex attributes
	 * @param attrib_location	The attribute location in the shader
	 * @param buffer_index		The index of the buffer that contains
	 *				the attribute
	 * @param number_elements	Number of elements
	 * @param type			Element type
	 * @param stride		Memory offset between vertices
	 * @param pointer		The offset of the attribute in the
	 * 				vertex structure
	 * @param divisor Determines how many instances share the same attribute value.
	 * 		0 means that every shader instance gets a new value,
	 * 		1 means every mesh instance gets a new value,
	 * 		2 means that two instances get the same value and so on.
	 * @return	Returns 0 on success, -1 if no shader was
	 * 		specified for the mesh, -2 if the vertex attribute
	 * 		could not be found
	 */
	EXPORT int set_vertex_attribute(int attrib_location,
				 unsigned int buffer_index,
				 GLint number_elements,
				 GLenum type,
				 GLsizei stride,
				 const GLvoid *pointer,
				 unsigned int divisor = 0);
	/**
	 * @brief Attaches an index array to the mesh
	 * @param indices Indices describing the topology of the mesh
	 * You can attach multiple index arrays
	 */
	EXPORT void attach_index_buffer(const std::vector<unsigned short>& indices);

	/**
	 * @brief Computes the bounding box of the mesh
	 * @param vertexdata The vertices of the mesh
	 * @param pointer The pointer to the position vector in the vertex
	 * 	structure
	 */
	template <typename T = Vertex>
	void compute_bounding_box(const std::vector<T>& vertexdata, size_t pointer);

	/**
	 * @brief Renders the mesh using the first index buffer
	 * @param mode Specifies the primitive that will be created from
	 * 	vertices
	 */
	EXPORT void draw(GLenum mode);

	/**
	 * @brief Renders the mesh using the first index buffer and the
	 * 	  model_matrix member as model matrix
	 * @param mode Specifies the primitive that will be created from
	 * 	  vertices
	 * @param index_buffer The index buffer to use
	 */
	EXPORT void draw(GLenum mode, unsigned int index_buffer);

	/**
	 * @brief Renders the mesh using the first index buffer
	 * @param mode Specifies the primitive that will be created from
	 * 	  vertices
	 * @param model_matrix The model matrix to use
	 *	  (NULL to use the model_matrix member)
	 */
	EXPORT void draw(GLenum mode, const glm::mat4 *model_matrix);

	/**
	 * @brief Renders the mesh
	 * @param mode Specifies the primitive that will be created from
	 * 	  vertices
	 * @param index_buffer The index buffer to use
	 * @param model_matrix The model matrix to use
	 *	  (NULL to use the model_matrix member)
	 */
	EXPORT void draw(GLenum mode, unsigned int index_buffer,
					const glm::mat4 *model_matrix);

	/**
	 * @brief Renders the mesh multiple times
	 * @param mode Specifies the primitive that will be created from
	 * 	  vertices
	 * @param num_instances Number of instances to be drawn
	 */
	EXPORT void draw_instanced(GLenum mode, unsigned int num_instances);

	/**
	 * @brief Renders the mesh multiple times
	 * @param mode Specifies the primitive that will be created from
	 * 	  vertices
	 * @param index_buffer The index buffer to use
	 * @param num_instances Number of instances to be drawn
	 */
	EXPORT void draw_instanced(GLenum mode, unsigned int index_buffer,
						unsigned int num_instances);
};

template <typename T>
int Mesh::add_vertex_attribute(std::string attrib_name,
				GLint number_elements,
				GLenum type,
				const void *data,
				GLenum usage) {
	int buffer_index;
	T *ptr = (T *)data;
	std::vector<T> tmp(ptr, ptr + number_elements);
	buffer_index = attach_vertex_buffer<T>(tmp, usage);
	return set_vertex_attribute(attrib_name, buffer_index, number_elements,
					type, 0, 0);
}

template <typename T>
int Mesh::add_vertex_attribute(std::string attrib_name,
				GLint number_elements,
				GLenum type,
				const std::vector<T>& data,
				GLenum usage) {
	int buffer_index = attach_vertex_buffer<T>(data, usage);
	return set_vertex_attribute(attrib_name, buffer_index, number_elements,
					type, 0, 0);
}

template <typename T>
int Mesh::add_vertex_attribute(int attrib_location,
				GLint number_elements,
				GLenum type,
				const void *data,
				GLenum usage) {
	int buffer_index;
	T *ptr = (T *)data;
	std::vector<T> tmp(ptr, ptr + number_elements);
	buffer_index = attach_vertex_buffer<T>(tmp, usage);
	return set_vertex_attribute(attrib_location, buffer_index, number_elements,
					type, 0, 0);
}

template <typename T>
int Mesh::add_vertex_attribute(int attrib_location,
				GLint number_elements,
				GLenum type,
				const std::vector<T>& data,
				GLenum usage) {
	int buffer_index = attach_vertex_buffer<T>(data, usage);
	return set_vertex_attribute(attrib_location, buffer_index, number_elements,
					type, 0, 0);
}

template <typename T>
int Mesh::attach_vertex_buffer(const void *vertexdata,
				       unsigned int number_elements,
				       GLenum usage) {
	T *ptr = (T *)vertexdata;
	std::vector<T> tmp(ptr, ptr + number_elements);
	return attach_vertex_buffer<T>(tmp, usage);
}

template <typename T>
int Mesh::attach_vertex_buffer(const std::vector<T>& vertexdata,
				       GLenum usage) {
	GLuint buf;
	glGenBuffers(1, &buf);
	vbo.push_back(buf);

	unsigned int buffer_size = vertexdata.size() * sizeof(T);

	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, vertexdata.data(), usage);

	vertex_buffer_size_map[vbo.size() - 1] = buffer_size;
	vertex_buffer_usage_map[vbo.size() - 1] = usage;
	return vbo.size() - 1;
}

template <typename T>
bool Mesh::replace_buffer_data(unsigned int buffer_index,
				const void *data,
				unsigned int number_elements) {
	T *ptr = (T *)data;
	std::vector<T> tmp(ptr, ptr + number_elements);
	return replace_buffer_data<T>(buffer_index, tmp);
}

template <typename T>
bool Mesh::replace_buffer_data(unsigned int buffer_index,
				const std::vector<T>& data) {
	if(buffer_index >= vbo.size()) {
		App::error_string.push_back("The value of the variable"
				"buffer_index if greater than the number"
				"of vertex buffers.");
		return false;
	}

	unsigned int current_size	= vertex_buffer_size_map[buffer_index];
	unsigned int new_size		= data.size() * sizeof(T);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[buffer_index]);
	if(current_size == new_size) {
		//replace the buffer data without reallocation
		glBufferSubData(GL_ARRAY_BUFFER, 0, new_size, data.data());
	} else {
		//replace the buffer data with reallocation
		glBufferData(GL_ARRAY_BUFFER, new_size, data.data(),
			vertex_buffer_usage_map[buffer_index]);
	}

	return true;
}

template <typename T>
void Mesh::compute_bounding_box(const std::vector<T>& vertexdata, size_t pointer) {
	glm::vec3 *pos = (glm::vec3 *)(&(vertexdata)[0] + pointer);
	bounding_box[0] = *pos;
	bounding_box[1] = *pos;
	for(size_t i = 1; i < vertexdata.size(); i++) {
		pos = (glm::vec3 *)(&(vertexdata)[i] + pointer);
		if(pos->x < bounding_box[0].x)
			bounding_box[0].x = pos->x;
		if(pos->y < bounding_box[0].y)
			bounding_box[0].y = pos->y;
		if(pos->z < bounding_box[0].z)
			bounding_box[0].z = pos->z;
		if(pos->x > bounding_box[1].x)
			bounding_box[1].x = pos->x;
		if(pos->y > bounding_box[1].y)
			bounding_box[1].y = pos->y;
		if(pos->z > bounding_box[1].z)
			bounding_box[1].z = pos->z;
	}
}
}

#endif
