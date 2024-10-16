#pragma once

#include "Core.h"
#include "Layer.h"

namespace fz {

	class LayerArray
	{
		using iter = std::vector<Layer*>::iterator;
		using const_iter = std::vector<Layer*>::const_iterator;

	public:
		explicit	LayerArray();
		virtual		~LayerArray();

		bool		InsertLayer(Layer* pLevel);
		bool		InsertOverlay(Layer* pOverlay);
		bool		RemoveLayer(Layer* pLevel);
		bool		RemoveOverlay(Layer* pOverlay);

		iter		find(Layer* target);
		bool		empty() const;
		iter		begin();
		iter		end();		
		const_iter	begin() const;
		const_iter	end() const;

	private:
		std::vector<Layer*>		m_LayerArray;
		int						m_InsertIndex;
	};

} // namespace fz