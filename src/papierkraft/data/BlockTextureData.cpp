#include "BlockTextureData.h"

namespace PapierKraft
{
	BlockTextureData::BlockTextureData(std::string sideTexture, std::string topTexture, std::string bottomTexture)
	{
		if (sideTexture != topTexture &&
			sideTexture != bottomTexture &&
			topTexture != bottomTexture)
		{
			m_SideTexture = std::make_shared<Texture>(sideTexture.c_str());
			m_TopTexture = std::make_shared<Texture>(topTexture.c_str());
			m_BottomTexture = std::make_shared<Texture>(bottomTexture.c_str());
		}
	}

	BlockTextureData::BlockTextureData(std::string sideTexture, std::string topBottomTexture)
	{
		if (sideTexture != topBottomTexture)
		{
			m_SideTexture = std::make_shared<Texture>(sideTexture.c_str());
			m_TopTexture = std::make_shared<Texture>(topBottomTexture.c_str());
			m_BottomTexture = m_TopTexture;
		}
	}

	BlockTextureData::BlockTextureData(std::string uniformTexture) :
		BlockTextureData(uniformTexture, uniformTexture, uniformTexture)
	{
		m_SideTexture = std::make_shared<Texture>(uniformTexture.c_str());
		m_TopTexture = m_SideTexture;
		m_BottomTexture = m_SideTexture;
	}
}