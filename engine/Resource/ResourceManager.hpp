#pragma once

#include <map>
#include <string>

#include "Shader.hpp"
#include "IResource.hpp"
#include "Texture.hpp"
#include "Render/VertexBuffer.hpp"

class ResourceManager final
{
	ResourceManager();

	static std::string TextureName(const std::string& name);

	static std::string ShaderName(const std::string& name);

	static std::string MeshName(const std::string& name);

public:

	static ResourceManager& GetInstance();

	void AddShader(std::string name);

	_NODISCARD std::shared_ptr<Shader> GetShader(std::string name);

	void AddTexture(std::string name);

	_NODISCARD std::shared_ptr<Texture> GetTexture(std::string name);

	_NODISCARD std::shared_ptr<VertexBuffer> GetMesh(std::string name);

	void AddMesh(std::string name);

private:
	std::map<std::string, std::shared_ptr<IResource>> m_resources;
};
