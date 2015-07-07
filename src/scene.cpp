#include "scene.h"

Scene::Scene(const char *path, Shader *shader,
	     const char *model_view_matrix_name,
	     const char *model_view_projection_matrix_name,
	     const char *normal_matrix_name,
	     glm::mat4 *view_matrix,
	     glm::mat4 *projection_matrix) {

	unsigned int flags = aiProcess_GenSmoothNormals |
			     aiProcess_Triangulate |
			     aiProcess_CalcTangentSpace |
			     aiProcess_FlipUVs;
	scene = importer.ReadFile(path, flags);

	if(!scene) {
		std::cerr << "Error importing " << path << ": "
			  << importer.GetErrorString() << std::endl;
		return;
	}

	this->shader = shader;
	this->model_view_matrix_name = model_view_matrix_name;
	this->model_view_projection_matrix_name =
		model_view_projection_matrix_name;
	this->normal_matrix_name = normal_matrix_name;

	this->view_matrix = view_matrix;
	this->projection_matrix = projection_matrix;

	ai_to_glm_mat4(&scene->mRootNode->mTransformation, model_matrix);
	traverse_nodes(scene->mRootNode, NULL);
}

Scene::~Scene() {
	meshes.clear();
	textures.clear();
}

void Scene::traverse_nodes(aiNode *start_node, aiMatrix4x4 *parent_trafo) {
	aiMatrix4x4 trafo = start_node->mTransformation;;
	if(parent_trafo)
		trafo = *parent_trafo * trafo;

	for(unsigned int i = 0; i < start_node->mNumMeshes; i++) {
		create_mesh(scene->mMeshes[i], &trafo);
	}

	for(unsigned int i = 0; i < start_node->mNumChildren; i++) {
		traverse_nodes(start_node->mChildren[i], &trafo);
	}
}

void Scene::create_mesh(aiMesh *mesh, aiMatrix4x4 *trafo) {
	std::vector<sgltk::Vertex> vertices;
	std::vector<unsigned short> indices;
	aiColor4D color(0.0f, 0.0f, 0.0f, 0.0f);
	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
	mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);

	for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
		sgltk::Vertex vert_tmp;

		//position
		if(mesh->HasPositions()) {
			vert_tmp.position[0] = mesh->mVertices[i].x;
			vert_tmp.position[1] = mesh->mVertices[i].y;
			vert_tmp.position[2] = mesh->mVertices[i].z;
			vert_tmp.position[3] = 1;
		}

		//normals
		if(mesh->HasNormals()) {
			vert_tmp.normal[0] = mesh->mNormals[i].x;
			vert_tmp.normal[1] = mesh->mNormals[i].y;
			vert_tmp.normal[2] = mesh->mNormals[i].z;
		}

		//texture coordinates
		//vert_tmp.tex_coord.reserve(mesh->GetNumUVChannels());
		//for(unsigned int j = 0; j < mesh->GetNumUVChannels(); j++) {
			if(mesh->HasTextureCoords(0)) {
				vert_tmp.tex_coord[0] =
					mesh->mTextureCoords[0][i].x;
				vert_tmp.tex_coord[1] =
					mesh->mTextureCoords[0][i].y;
				vert_tmp.tex_coord[2] =
					mesh->mTextureCoords[0][i].z;
			}
		//}

		//tangent and bitangent
		if(mesh->HasTangentsAndBitangents()) {
			vert_tmp.tangent[0] = mesh->mTangents[i].x;
			vert_tmp.tangent[1] = mesh->mTangents[i].y;
			vert_tmp.tangent[2] = mesh->mTangents[i].z;
			vert_tmp.tangent[3] = 1;

			vert_tmp.bitangent[0] = mesh->mBitangents[i].x;
			vert_tmp.bitangent[1] = mesh->mBitangents[i].y;
			vert_tmp.bitangent[2] = mesh->mBitangents[i].z;
			vert_tmp.bitangent[3] = 1;
		}

		//color
		vert_tmp.color[0] = color.r;
		vert_tmp.color[1] = color.g;
		vert_tmp.color[2] = color.b;
		vert_tmp.color[3] = color.a;

		vertices.push_back(vert_tmp);
	}

	for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for(unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh<> *mesh_tmp = new Mesh<>();
	mesh_tmp->attach_vertex_array(&vertices);
	mesh_tmp->attach_index_array(&indices);
	ai_to_glm_mat4(trafo, mesh_tmp->model_matrix);

	mesh_tmp->setup_shader(shader,
			       model_view_matrix_name,
			       model_view_projection_matrix_name,
			       normal_matrix_name, view_matrix,
			       projection_matrix);
	meshes.push_back(mesh_tmp);
}

void Scene::set_vertex_attribute(const char *attrib_name, GLint size,
				 GLenum type, GLsizei stride,
				 const GLvoid *pointer) {
	for(unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i]->set_vertex_attribute(attrib_name, size, type,
						stride, pointer);
	}
}

void Scene::draw() {
	for(unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i]->draw(GL_TRIANGLES);
	}
}

void Scene::ai_to_glm_mat4(aiMatrix4x4 *in, glm::mat4 &out) {
	out[0][0] = in->a1;
	out[0][1] = in->b1;
	out[0][2] = in->c1;
	out[0][3] = in->d1;

	out[1][0] = in->a2;
	out[1][1] = in->b2;
	out[1][2] = in->c2;
	out[1][3] = in->d2;

	out[2][0] = in->a3;
	out[2][1] = in->b3;
	out[2][2] = in->c3;
	out[2][3] = in->d3;

	out[3][0] = in->a4;
	out[3][1] = in->b4;
	out[3][2] = in->c4;
	out[3][3] = in->d4;
}
