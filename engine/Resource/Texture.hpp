#pragma once

#include "IResource.hpp"

class Texture final : public IResource
{
public:
	Texture();

	explicit Texture(std::string filepath);

	Texture(std::string x, std::string y, std::string z, std::string negx, std::string negy, std::string negz);

	void Load(const std::string& filepath) override;

	void Bind() const;

	virtual ~Texture() = default;
private:
	uint32_t m_textureId;
	bool m_isCubeMap;
};