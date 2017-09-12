#include "Player/Weapon/Weapon.h"

using namespace Logic;

Weapon::Weapon()
{
	m_weaponID		= -1;
	m_ammoCap		= -1;
	m_ammo			= -1;
	m_magSize		= -1;
	m_magAmmo		= -1;
	m_damage		= -1;
	m_attackRate	= -1;
	m_freeze		= -1;
	m_reloadTime	= -1;
}

Weapon::Weapon(int weaponID, int ammoCap, int ammo, int magSize, int magAmmo, float damage, float attackRate, float freeze, float reloadTime)
{
	m_weaponID		= weaponID;
	m_ammoCap		= ammoCap;
	m_ammo			= ammo;
	m_magSize		= magSize;
	m_magAmmo		= magAmmo;
	m_damage		= damage;
	m_attackRate	= attackRate;
	m_freeze		= freeze;
	m_reloadTime	= reloadTime;
}

void Weapon::use()
{
	// use weapon
}

void Weapon::update()
{

}

int Logic::Weapon::getAmmoCap() { return m_ammoCap; }

void Logic::Weapon::setAmmoCap(int ammoCap) { m_ammoCap = ammoCap; }

int Logic::Weapon::getAmmo() { return m_ammo; }

void Logic::Weapon::setAmmo(int ammo) { m_ammo = ammo; }

int Logic::Weapon::getMagSize() { return m_magSize; }

void Logic::Weapon::setMagSize(int magSize) { m_magSize = magSize; }

int Logic::Weapon::getMagAmmo() { return m_magAmmo; }

void Logic::Weapon::removeMagAmmo() { m_magAmmo--; }

void Logic::Weapon::removeMagAmmo(int ammo) { m_magAmmo -= ammo; }

void Logic::Weapon::fillMag()
{
	int toAdd = m_magSize - m_magAmmo;

	if (m_ammo >= toAdd)
	{
		m_ammo -= toAdd;		// Remove ammo from total
		m_magAmmo = m_magSize;	// Add ammo to mag
	}
	else
	{
		m_magAmmo += m_ammo;	// Add rest of ammo to mag
		m_ammo = 0;				// Remove rest of ammo from total
	}
}
