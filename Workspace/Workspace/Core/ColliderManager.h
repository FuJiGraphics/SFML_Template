#pragma once
#include "Core.h"
#include "Collider.h"

namespace fz {
	
	std::vector<Collider*>& GetColliderManager();
	int ColliderFind(Collider* target);

}