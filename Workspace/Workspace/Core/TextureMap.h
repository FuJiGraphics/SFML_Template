#pragma once
#include "Core.h"

namespace fz {

	class TextureMap
	{
	public:
		static const sf::Texture& GetTexture(const std::string& path);

	private:
		static MemoryPool<sf::Texture> m_Textures;
	};

} // namespace fz