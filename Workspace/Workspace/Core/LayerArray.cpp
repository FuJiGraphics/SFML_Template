#include "LayerArray.h"

namespace fz {

	LayerArray::LayerArray() 
		: m_LayerArray()
		, m_InsertIndex(0)
	{
		// Empty
	}

	LayerArray::~LayerArray()
	{
		if (!m_LayerArray.empty())
		{
			int arrSize = m_LayerArray.size();
			for (int i = 0; i < arrSize; ++i)
			{
				if (m_LayerArray[i] != nullptr)
				{
					delete m_LayerArray[i];
					m_LayerArray[i] = nullptr;
				}
			}
		}
	}

	bool LayerArray::InsertLayer(Layer* pLevel)
	{
		bool result = false;
		auto findLevel = this->find(pLevel);
		if (findLevel == this->end())
		{
			m_LayerArray.emplace_back(pLevel);
			result = true;
		}
		return (result);
	}

	bool LayerArray::InsertOverlay(Layer* pOverlay)
	{
		bool result = false;
		auto findOverlay = this->find(pOverlay);
		if (findOverlay == m_LayerArray.end())
		{
			m_LayerArray.emplace(m_LayerArray.begin() + m_InsertIndex, pOverlay);
			m_InsertIndex++;
			result = true;
		}
		return (result);
	}

	bool LayerArray::RemoveLayer(Layer* pLevel)
	{
		bool result = false;
		auto findLevel = this->find(pLevel);
		if (findLevel != m_LayerArray.end())
		{
			m_LayerArray.erase(findLevel);
			m_InsertIndex--;
			result = true;
		}
		return (result);
	}

	bool LayerArray::RemoveOverlay(Layer* pOverlay)
	{
		bool result = false;
		auto findOverlay = this->find(pOverlay);
		if (findOverlay != m_LayerArray.end())
		{
			m_LayerArray.erase(findOverlay);
			result = true;
		}
		return (result);
	}

	LayerArray::iter LayerArray::find(Layer* target)
	{
		return std::find_if(m_LayerArray.begin(), m_LayerArray.end(),
			[target](Layer* pTarget)
			{
				return (target == pTarget);
			});
	}

	bool LayerArray::empty() const
	{
		return (m_LayerArray.empty());
	}

	LayerArray::iter LayerArray::begin()
	{
		return (m_LayerArray.begin());
	}

	LayerArray::iter LayerArray::end()
	{
		return (m_LayerArray.end());
	}

	LayerArray::const_iter LayerArray::begin() const
	{
		return (m_LayerArray.begin());
	}

	LayerArray::const_iter LayerArray::end() const
	{
		return (m_LayerArray.end());
	}

}