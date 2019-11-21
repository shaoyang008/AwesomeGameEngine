#include "ObjectModel.h"

ObjectModel::ObjectModel()
{
}


ObjectModel::~ObjectModel()
{
}

void ObjectModel::Draw()
{
	glBindVertexArray(_VAOid);
	glDrawElements(GL_TRIANGLES, _vertexIndex.size() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void ObjectModel::Initialize(std::string path)
{
	ReadModel(path);

	glGenVertexArrays(1, &_VAOid);
	glBindVertexArray(_VAOid);

	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertex.size() * 3, &_vertex[0][0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (_texcoord.size() > 0) {
		GLuint texcoord_buffer;
		glGenBuffers(1, &texcoord_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _texcoord.size() * 2, &_texcoord[0][0], GL_STATIC_DRAW);
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
	while (file >> line) {
		if (line == "v") {
			vec3 v;
			file >> v.x >> v.y >> v.z;
			_vertex.push_back(v);
		}
		else if (line == "vt") {
			vec2 vt;
			file >> vt.x >> vt.y;
			_texcoord.push_back(vt);
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
			v_idx.x = std::stoi(s1.substr(0, vpos1)) - 1;
			v_idx.y = std::stoi(s2.substr(0, vpos2)) - 1;
			v_idx.z = std::stoi(s3.substr(0, vpos3)) - 1;
			_vertexIndex.push_back(v_idx);

			if (vpos1 == std::string::npos || vpos2 == std::string::npos || vpos3 == std::string::npos) {
				continue;
			}

			if (_texcoord.size() > 0) {
				size_t tpos1 = s1.find_first_of('/', vpos1 + 1);
				size_t tpos2 = s2.find_first_of('/', vpos2 + 1);
				size_t tpos3 = s3.find_first_of('/', vpos3 + 1);
				t_idx.x = std::stoi(s1.substr(vpos1 + 1, tpos1 - vpos1)) - 1;
				t_idx.y = std::stoi(s2.substr(vpos2 + 1, tpos2 - vpos2)) - 1;
				t_idx.z = std::stoi(s3.substr(vpos3 + 1, tpos3 - vpos3)) - 1;
				_textureIndex.push_back(t_idx);
			}

			if (_normal.size() > 0) {
				size_t npos1 = s1.find_last_of('/') + 1;
				size_t npos2 = s2.find_last_of('/') + 1;
				size_t npos3 = s3.find_last_of('/') + 1;
				n_idx.x = std::stoi(s1.substr(npos1)) - 1;
				n_idx.y = std::stoi(s2.substr(npos2)) - 1;
				n_idx.z = std::stoi(s3.substr(npos3)) - 1;
				_normalIndex.push_back(n_idx);
			}
		}
		else {
			std::getline(file, line);
			continue;
		}
	}
}