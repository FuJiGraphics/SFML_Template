#include "ColliderManager.h"

namespace fz {

	static std::vector<Collider*> s_ColliderManager;

	std::vector<Collider*>& GetColliderManager()
	{
		return (s_ColliderManager);
	}

	int ColliderFind(Collider* target)
	{
		int i = 0;
		int size = s_ColliderManager.size();
		for (i = 0; i < size; ++i)
		{
			if (s_ColliderManager[i] == target)
				return (i);
		}
		return (-1);
	}

}