#pragma once
#include "Core.h"
#include "Collider.h"

namespace fz {
	
	class ColliderManager
	{
		using iter = std::vector<Collider**>::iterator;
		using const_iter = std::vector<Collider**>::const_iterator;

	public:
		/*
		* @brief	Collider�� �޸𸮸� �Ҵ�ް� ��� ����մϴ�.
		* @details	
		* - Collider�� �� ������ �ּҸ� �Ű����ڷ� �޽��ϴ�.
		* - Collider�� �� ������ �ּҿ� ���� �Ҵ��ؼ� ����մϴ�.
		* - �޸� ������ ColliderManager�� ���ӵ˴ϴ�.
		* @param[in]	Collider** collider: �޸𸮸� �Ҵ�޾� ����� collider �������� �ּ�
		*/
		void			Attach(Collider** collider);
		/*
		* @brief	Collider�� �޸𸮸� �Ҹ��Ű�� ��� ����� �����մϴ�.
		* @details
		* - ������� Collider�� ������ �ּҸ� �Ű����ڷ� �޽��ϴ�.
		* - �����͸� �Ҹ��Ű�� nullptr�� �ʱ�ȭ�մϴ�.
		* - �޸� ������ ColliderManager�� ���ӵ˴ϴ�.
		* @param[in]	Collider** collider: �޸𸮸� �Ҹ��Ű�� nullptr�� ä�� collider ������
		*/
		void			Detach(Collider** collider);
		/*
		* @brief	ColliderManager���� ��� ��ϵ� Collider�� Ž���մϴ�.
		* @details
		* - ������� Collider�� ������ �ּҸ� �Ű����ڷ� �޽��ϴ�.
		* - ��� ��ϵ� Collider�� ��ȯ�մϴ�.
		* - ���� ã�� �� ���� Collider�� ��� ColliderManager::end()�� ��ȯ�մϴ�.
		* @param[in]	Collider** collider: ã���� �ϴ� ��� ��ϵ� �������� �ּ�
		* @return		iter: ������ ��� ��� Collider�� iter, ������ ��� ColliderManager::end()
		*/
		iter			Find(Collider** target);

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