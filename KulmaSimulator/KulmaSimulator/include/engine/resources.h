#ifndef RESOURCES_H
#define RESOURCES_H
#include <string>
#include <lodepng/lodepng.h>
#include <gl/glew.h>
#include <memory>
#include "GLM.h"
#include <functional>
#include <ft2build.h>
class SpriteBatch;
#include FT_FREETYPE_H

class Resource {
public:
	Resource();
	virtual ~Resource();
	virtual bool readFromFile(const std::string& path) = 0;
};

class Texture : public Resource {
public:
	size_t width;
	size_t height;
	GLuint id;
public:
	Texture(GLuint id, size_t w, size_t h);
	Texture();
	~Texture();
	bool readFromFile(const std::string& path);
	const GLuint& getId() const;
};

class Effect : public Resource {
private:
	std::string readFile(const std::string& path);
	GLuint compileShaders(const char* vertexSrc, const char* fragmentSrc);
	GLuint program = 0;
public:
	Effect();
	~Effect();
	bool readFromFile(const std::string& path);
	void bind() const;
	void unbind() const;
	GLuint getProgram() const;
	//bool isBound() const;
	
};


struct CharacterInfo {
	float ax; // advance.x
	float ay; // advance.y

	float bw; // bitmap.width;
	float bh; // bitmap.rows;

	float bl; // bitmap_left;
	float bt; // bitmap_top;

	float tx; // x offset of glyph in texture coordinates
};
typedef std::function<void(CharacterInfo&, float, float)> FontAction;
class Font : public Resource {
private:
	CharacterInfo info[128];
	float spacing;
	std::unique_ptr<Texture> texture;
	void forEachChar(const std::string& str, FontAction action);
public:
	bool readFromFile(const std::string& path);
	void drawString(SpriteBatch& spriteBatch, std::string& str, glm::vec2& position, glm::vec4& color, float rotation, glm::vec2& origin, glm::vec2& scale);
	
	Font();
	~Font();
};


class Material {
private:
	std::string name;
	// Kd from obj
	float diffuse[3];
	// Ks from obj
	float specular[3];
	const Texture* map;
public:
	Material(const std::string& name) : name(name), map(nullptr) {}
	bool readFromFile(const std::string& path);
	void setDiffuseColor(float r, float g, float b) {
		diffuse[0] = r; diffuse[1] = g; diffuse[2] = b;
	}
	void setSpecularColor(float r, float g, float b) {
		specular[0] = r; specular[1] = g; specular[2] = b;
	}
	void setTextureMap(const Texture* texture) {
		map = texture;
	}
	const std::string& getName() const {
		return name;
	}

	const Texture* getTexture() const {
		return map;
	}
};

class Mesh : public Resource {
private:
	std::vector<GLfloat> vertices;
	std::vector<Material> materials;
public:
	Mesh();
	~Mesh();
	bool readFromFile(const std::string& path);
	const std::vector<GLfloat>& getVertices() const;
	const std::vector<Material>& getMaterials() const {
		return materials;
	}
};

class Mtllib {
public:
	static std::vector<Material> import(const std::string& mtlfile);
};

#endif