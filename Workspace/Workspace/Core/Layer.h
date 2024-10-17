#pragma once

#include "Core.h"
#include "Event.h"

namespace fz {

	class Collider;

	class Layer
	{
	public:
		explicit Layer();
		virtual ~Layer();

		// �������̽�
		virtual void			OnAttach();
		virtual void			OnDetach();
		virtual void			OnEvent(fz::Event& event);
		virtual void			OnUpdate(float dt);
		virtual void			OnDraw(sf::RenderWindow& device);
		virtual void			OnUI(sf::RenderWindow& device);
		virtual void			OnCollide(Layer* pLayer, const std::string& className);
		virtual std::string		GetName() const;

		// �浹 �ý���
		bool					IsActivatedCollider() const;
		void					ActivateCollider(bool flags, const std::string& className);
		void					SetCollider(int x, int y, int rect, int right);
		void					SetColliderDisplayMode(bool enabled);

		// ��Ÿ
		static unsigned int		GetCount();

	private:
		static unsigned int		s_numOfLayers;
		Collider*				m_body;
	};

} // namespace fz