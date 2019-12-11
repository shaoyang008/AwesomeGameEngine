/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ObjectModel.cpp
Purpose: Read and save OBJ files
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "ObjectModel.h"

ObjectModel::ObjectModel(): _material(0)
{
}


ObjectModel::~ObjectModel()
{
}

void ObjectModel::DrawChildren(GLuint programId, bool use_material)
{
	for (int i = 0; i < _children.size(); ++i) _children[i]->Draw(programId, use_material);
}

void ObjectModel::Draw(GLuint programId, bool use_material)
{
	if (use_material && _material) {
		_material->Use(programId);
	}

	glBindVertexArray(_VAOid);
	glDrawElements(GL_TRIANGLES, _vertexIndex.size() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	if (use_material && _material) _material->Unuse();
}

void ObjectModel::Initialize()
{
	glGenVertexArrays(1, &_VAOid);
	glBindVertexArray(_VAOid);

	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertex.size() * 3, &_vertex[0][0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (_texture.size() > 0) {
		GLuint texcoord_buffer;
		glGenBuffers(1, &texcoord_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _texture.size() * 2, &_texture[0][0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if (_normal.size() > 0) {
		GLuint normal_buffer;
		glGenBuffers(1, &normal_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _normal.size() * 3, &_normal[0][0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLuint triangle_buffer;
	glGenBuffers(1, &triangle_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * _vertexIndex.size() * 3, &_vertexIndex[0][0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}


// Read Model data from obj file
void ObjectModel::ReadModel(std::string path)
{
	std::ifstream file;
	file.open(path);

	std::string line;
	ObjectModel * child = 0;
	int v_offset = 0, v_idx_offset = 0, n_idx_offset = 0, t_idx_offset = 0;
	std::map<std::string, Material*> materials;

	std::vector<vec3> normal_index, texture_index;

	while (file >> line) {
		if (line == "mtllib") {
			file >> line;
			ReadMtl(line, materials);
		}
		else if (line == "o") {
			if (child) {
				// clear up previous child when new object begins
				// set all child's value and push back
				
				child->_vertex.resize(_vertex.size() - v_offset);
				std::copy(_vertex.begin() + v_offset, _vertex.end(), child->_vertex.begin());

				child->_vertexIndex.resize(_vertexIndex.size() - v_idx_offset);
				std::copy(_vertexIndex.begin() + v_idx_offset, _vertexIndex.end(), child->_vertexIndex.begin());
				
				child->_texture.resize(child->_vertex.size());
				child->_normal.resize(child->_vertex.size());

				if (t_idx_offset < texture_index.size()) {
					for (int i = 0; i < child->_vertexIndex.size(); ++i) {
						child->_texture[child->_vertexIndex[i].x] = _texture[texture_index[i].x];
						child->_texture[child->_vertexIndex[i].y] = _texture[texture_index[i].y];
						child->_texture[child->_vertexIndex[i].z] = _texture[texture_index[i].z];
					}
				}

				if (n_idx_offset < normal_index.size()) {
					for (int i = 0; i < child->_vertexIndex.size(); ++i) {
						child->_normal[child->_vertexIndex[i].x] = _normal[normal_index[i].x];
						child->_normal[child->_vertexIndex[i].y] = _normal[normal_index[i].y];
						child->_normal[child->_vertexIndex[i].z] = _normal[normal_index[i].z];
					}
				}

				child->Initialize();
				_children.push_back(child);
			}
			// open new object model
			child = new ObjectModel;
			
			v_offset = _vertex.size();
			v_idx_offset = _vertexIndex.size();
			t_idx_offset = texture_index.size();
			n_idx_offset = normal_index.size();
		}
		else if (line == "v") {
			vec3 v;
			file >> v.x >> v.y >> v.z;
			_vertex.push_back(v);
		}
		else if (line == "vt") {
			vec2 vt;
			file >> vt.x >> vt.y;
			_texture.push_back(vt);
		}
		else if (line == "vn") {
			vec3 vn;
			file >> vn.x >> vn.y >> vn.z;
			_normal.push_back(vn);
		}
		else if (line == "f") {
			ivec3 v_idx, t_idx, n_idx;
			std::string s1, s2, s3;
			file >> s1 >> s2 >> s3;

			size_t vpos1 = s1.find_first_of('/');
			size_t vpos2 = s2.find_first_of('/');
			size_t vpos3 = s3.find_first_of('/');
			v_idx.x = std::stoi(s1.substr(0, vpos1)) - 1 - v_offset;
			v_idx.y = std::stoi(s2.substr(0, vpos2)) - 1 - v_offset;
			v_idx.z = std::stoi(s3.substr(0, vpos3)) - 1 - v_offset;
			_vertexIndex.push_back(v_idx);

			if (vpos1 == std::string::npos || vpos2 == std::string::npos || vpos3 == std::string::npos) {
				continue;
			}

			if (_texture.size() > 0) {
				size_t tpos1 = s1.find_first_of('/', vpos1 + 1);
				size_t tpos2 = s2.find_first_of('/', vpos2 + 1);
				size_t tpos3 = s3.find_first_of('/', vpos3 + 1);
				t_idx.x = std::stoi(s1.substr(vpos1 + 1, tpos1 - vpos1)) - 1;
				t_idx.y = std::stoi(s2.substr(vpos2 + 1, tpos2 - vpos2)) - 1;
				t_idx.z = std::stoi(s3.substr(vpos3 + 1, tpos3 - vpos3)) - 1;
				texture_index.push_back(t_idx);
			}

			if (_normal.size() > 0) {
				size_t npos1 = s1.find_last_of('/') + 1;
				size_t npos2 = s2.find_last_of('/') + 1;
				size_t npos3 = s3.find_last_of('/') + 1;
				n_idx.x = std::stoi(s1.substr(npos1)) - 1;
				n_idx.y = std::stoi(s2.substr(npos2)) - 1;
				n_idx.z = std::stoi(s3.substr(npos3)) - 1;
				normal_index.push_back(n_idx);
			}
		}
		else if (line == "usemtl") {
			if (child) {
				file >> line;
				child->_material = materials[line];
			}
		}
		else {
			std::getline(file, line);
			continue;
		}
	}

	if (child) {
		// create a new child and push back
		
		child->_vertex.resize(_vertex.size() - v_offset);
		std::copy(_vertex.begin() + v_offset, _vertex.end(), child->_vertex.begin());

		child->_vertexIndex.resize(_vertexIndex.size() - v_idx_offset);
		std::copy(_vertexIndex.begin() + v_idx_offset, _vertexIndex.end(), child->_vertexIndex.begin());

		child->_texture.resize(child->_vertex.size());
		child->_normal.resize(child->_vertex.size());

		if (t_idx_offset < texture_index.size()) {
			for (int i = 0; i < child->_vertexIndex.size(); ++i) {
				child->_texture[child->_vertexIndex[i].x] = _texture[texture_index[i].x];
				child->_texture[child->_vertexIndex[i].y] = _texture[texture_index[i].y];
				child->_texture[child->_vertexIndex[i].z] = _texture[texture_index[i].z];
			}
		}

		if (n_idx_offset < normal_index.size()) {
			for (int i = 0; i < child->_vertexIndex.size(); ++i) {
				child->_normal[child->_vertexIndex[i].x] = _normal[normal_index[i].x];
				child->_normal[child->_vertexIndex[i].y] = _normal[normal_index[i].y];
				child->_normal[child->_vertexIndex[i].z] = _normal[normal_index[i].z];
			}
		}

		child->Initialize();
		_children.push_back(child);
	}

	_vertex.clear();
	_vertexIndex.clear();
	_texture.clear();
	_normal.clear(); 
	file.close();
}

void ObjectModel::ReadMtl(std::string path, std::map<std::string, Material*>& materials)
{
	std::ifstream file;
	file.open("./Resources/Models/" + path);

	std::string line, tag;
	while (file >> line) {
		if (line == "newmtl") {
			file >> tag;
			if (materials.find(tag) == materials.end()) {
				materials[tag] = new Material;
			}
		}
		else if (line == "Ns") {
			file >> materials[tag]->_shininess;
		}
		else if (line == "Ka") {
			file >> materials[tag]->_ambient.x;
			file >> materials[tag]->_ambient.y;
			file >> materials[tag]->_ambient.z;
		}
		else if (line == "Kd") {
			file >> materials[tag]->_diffuse.x;
			file >> materials[tag]->_diffuse.y;
			file >> materials[tag]->_diffuse.z;
		}
		else if (line == "Ks") {
			file >> materials[tag]->_specular.x;
			file >> materials[tag]->_specular.y;
			file >> materials[tag]->_specular.z;
		}
		else if (line == "map_Kd") {
			file >> line;
			materials[tag]->LoadMap("./Resources/Models/" + line);
		}
	}
}