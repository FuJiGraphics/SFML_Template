#pragma once
#include "Core.h"
#include "Collider.h"

namespace fz {
	
	class ColliderManager
	{
		using iter = std::vector<Collider**>::iterator;
		using const_iter = std::vector<Collider**>::const_iterator;

	public:
		void	Attach(Collider** collider);
		void	Detach(Collider** collider);
		iter	Find(Collider** target);

		iter			begin();
		iter			end();
		const_iter		begin() const;
		const_iter		end() const;
		
		static ColliderManager&		GetInstance();

	protected:
		explicit ColliderManager();
		virtual ~ColliderManager();

	private:
		std::vector<Collider**>		m_ColArray;
	};

} // namespace fz