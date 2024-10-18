#include "ColliderManager.h"

namespace fz {

	void ColliderManager::Attach(Collider** collider)
	{
		if (this->Find(collider) == m_ColArray.end())
		{
			(*collider) = new Collider;
			m_ColArray.push_back(collider);
		}
	}

	void ColliderManager::Detach(Collider** collider)
	{
		auto target = this->Find(collider);
		if (target != m_ColArray.end())
		{
			m_ColArray.erase(target);
			delete (*collider);
			(*collider) = nullptr;
		}
	}

	ColliderManager::iter ColliderManager::Find(Collider** target)
	{
		return std::find_if(m_ColArray.begin(), m_ColArray.end(),
			[target](Collider** pTarget)
			{
				return (target == pTarget);
			});
	}

	ColliderManager::iter ColliderManager::begin()
	{
		return (m_ColArray.begin());
	}

	ColliderManager::iter ColliderManager::end()
	{
		return (m_ColArray.end());
	}

	ColliderManager::const_iter ColliderManager::begin() const
	{
		return (m_ColArray.begin());
	}

	ColliderManager::const_iter ColliderManager::end() const
	{
		return (m_ColArray.end());
	}

	ColliderManager& ColliderManager::GetInstance()
	{
		static ColliderManager s_instance;
		return (s_instance);
	}

	ColliderManager::ColliderManager()
		: m_ColArray()
	{
		// Empty
	}

	ColliderManager::~ColliderManager()
	{
		int size = m_ColArray.size();
		for (int i = 0; i < size; ++i)
		{
			if (m_ColArray[i])
			{
				if (*m_ColArray[i])
				{
					delete (*m_ColArray[i]);
					(*m_ColArray[i]) = nullptr;
				}
				m_ColArray[i] = nullptr;
			}
		}
	}

} // namespace fz