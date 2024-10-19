#include "Tree.h"
#include "Player.h"

using namespace fz;

Tree::Tree(int posX, int posY)
	: m_pos((float)posX, (float)posY)
{
}

Tree::~Tree()
{
}

void Tree::OnAttach()
{
	auto& system = System::GetInstance();

	// 나무 생성
	Texture::Load("res/graphics/tree.png");
	auto& texture = Texture::Get("res/graphics/tree.png");
	m_tree.setTexture(texture);
	m_tree.setPosition(m_pos);
	m_tree.setOrigin(texture.getSize().x * 0.5f, 0.0f);

	int numOfBranch = 6;
	auto& treeSize = m_tree.getLocalBounds();
	auto& treeOrigin = m_tree.getOrigin();
	sf::Vector2f branchOrigin(treeOrigin.x * -1.0f, treeOrigin.y);
	bool flip = true;
	for (int i = 0; i < numOfBranch; ++i)
	{
		sf::Vector2f branchPos(m_pos.x, GetRandom(treeSize.height * -1.0f, treeSize.height * 0.5f));
		// flip = GetRandom(0, 1) ? true : false;
		m_Branches.push_back(new Branch(branchOrigin, branchPos, flip));
		system.AttachLayer(m_Branches[i]);
		flip = (flip) ? false : true;
	}
}

void Tree::OnDraw(sf::RenderWindow& device)
{
	device.draw(m_tree);
}

void Tree::OnEvent(fz::Event& event)
{
	if (System::IsPaused())
		return;

	sf::Event& ev = event.get();
	if (ev.type == ev.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->CutOff();
		event.use();
	}
	if (ev.type == ev.KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->CutOff();
		event.use();
	}
}

std::string Tree::GetName() const
{
	return ("Tree");
}

bool Tree::CutOff()
{
	bool result = false;

	auto& treeSize = m_tree.getLocalBounds();
	auto& treeOrigin = m_tree.getOrigin();

	bool flip = true;
	int branchSize = m_Branches.size();
	for (int i = 0; i < branchSize; ++i)
	{
		sf::Vector2f branchOrigin(treeOrigin.x * -1.0f, treeOrigin.y);
		sf::Vector2f branchPos(m_pos.x, (float)(GetRandom(1, 9) * -1));
		flip = GetRandom(0, 1) ? false : true;
		m_Branches[i]->Move(120.0f);
		if (m_Branches[i]->IsDestroyed())
		{
			System::DetachLayer(m_Branches[i]);
			m_Branches[i] = nullptr;
			m_Branches[i] = new Branch(branchOrigin, branchPos, flip);
			System::AttachLayer(m_Branches[i]);
		}
	}

	return (result);
}

