#include "Life.h"

Life::Life() :m_isAlive(false)
{

}

Life::~Life()
{

}

void Life::SetAlive(bool alive)
{
	m_isAlive = alive;
}

bool Life::GetAlive() const
{
	return m_isAlive;
}