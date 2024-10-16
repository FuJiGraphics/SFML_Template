#include "TextureMap.h"

namespace fz {

	MemoryPool<sf::Texture> TextureMap::m_Textures;

	const sf::Texture& TextureMap::GetTexture(const std::string& path)
	{
		if (!path.empty())
		{
			auto texItem = m_Textures.find(path);
			if (texItem == m_Textures.end())
			{
				m_Textures.insert(std::make_pair(path, sf::Texture()));
				m_Textures[path].loadFromFile(path);
			}
		}
		return (m_Textures[path]);
	}

} // namespace fz

