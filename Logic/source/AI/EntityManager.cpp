#include <AI/EntityManager.h>
using namespace Logic;

#define ENEMY_START_COUNT 16
#define TEST_NAME "helloWave"

#include <AI/EnemyTest.h>
#include <ctime>
#include <stdio.h>

EntityManager::EntityManager()
{
	m_currentWave = 0;

	reserveData();

	m_waveManager.setName(TEST_NAME);
}


EntityManager::~EntityManager()
{
	for (Enemy *enemy : m_enemies)
		delete enemy;
	for (Enemy *enemy : m_bossEnemies)
		delete enemy;
	for (Enemy *enemy : m_deadEnemies)
		delete enemy;
}

void EntityManager::reserveData()
{
	m_bossEnemies.reserve(ENEMY_START_COUNT);
	m_enemies.reserve(ENEMY_START_COUNT);
	m_deadEnemies.reserve(ENEMY_START_COUNT);
}

void EntityManager::update(Player const &player, float deltaTime) 
{
	clock_t begin = clock();

	for (int i = 0; i < m_enemies.size(); ++i)
	{
		m_enemies[i]->update(player, deltaTime);
		if (m_enemies[i]->getHealth() <= 0) {
			m_deadEnemies.push_back(m_enemies[i]);
			std::swap(m_enemies[i], m_enemies[m_enemies.size() - 1]);
			m_enemies.pop_back();
		}
	}

	for (int i = 0; i < m_bossEnemies.size(); ++i)
	{
		m_bossEnemies[i]->update(player, deltaTime);
	}

	for (int i = 0; i < m_deadEnemies.size(); ++i)
	{
		m_deadEnemies[i]->updateDead(deltaTime);
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//	printf("t: %f\n", elapsed_secs);

	m_triggerManager.update(deltaTime);
}

void EntityManager::spawnWave(Physics &physics) 
{
	std::vector<int> enemies = m_waveManager.getEnemies(m_currentWave);
	m_enemies.reserve(enemies.size() + m_enemies.size());

	if (m_currentWave == 1)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			i += 1;
			//m_enemies.push_back(new EnemyTest(physics.createBody(Cube({ i * 8.f, i * 10.f, i * 1.f }, { 0, 0, 0 }, { 0.5f, 0.5f, 0.5f}), 100, false), { 0.5f, 0.5f, 0.5f}));
            m_enemies.push_back(new EnemyTest(Graphics::CUBE, physics.createBody(Cube({ 0, 0, 0 }, { 0, 0, 0 }, { 0.5f, 0.5f, 0.5f }), 100, false), { 0.5f, 0.5f, 0.5f }));
		}

		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 10, 0.1f, 10 }, { 0, 0, 0 }, { 2, 0.1f, 2 }), 500.f, physics, { StatusManager::UPGRADE_ID::BOUNCE }, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ -10, 0.1f, 10 }, { 0, 0, 0 }, { 2, 0.1f, 2 }), 500.f, physics, { StatusManager::UPGRADE_ID::BOUNCE }, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ -10, 0.1f, -10 }, { 0, 0, 0 }, { 2, 0.1f, 2 }), 500.f, physics, { StatusManager::UPGRADE_ID::BOUNCE }, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 10, 0.1f, -10 }, { 0, 0, 0 }, { 2, 0.1f, 2 }), 500.f, physics, { StatusManager::UPGRADE_ID::BOUNCE }, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 15, 10.f, 5 }, { 0, 0, 0 }, { 2, 1.f, 2 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 20, 15.f, 10 }, { 0, 0, 0 }, { 2, 1.f, 2 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 25, 18.f, -5 }, { 0, 0, 0 }, { 2, 1.f, 2 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 30, 25.f, -0 }, { 0, 0, 0 }, { 2, 1.f, 2 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 45, 30.f, 12 }, { 0, 0, 0 }, { 2, 1.f, 2 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 50, 40.f, -5 }, { 0, 0, 0 }, { 2, 1.f, 2 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 40, 30.f, 2 }, { 0, 0, 0 }, { 2, 1.f, 2 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 70, 54.f, 10 }, { 0, 0, 0 }, { 2, 1.f, 2 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 80, 80.f, -2 }, { 0, 0, 0 }, { 2, 1.f, 2 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP, StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 50, 65.f, 5 }, { 0, 0, 0 }, { 2, 1.f, 2 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP }, true);
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 130, 128.f, 5 }, { 0, 0, 0 }, { 10, 1.f, 10 }), 500.f, physics, {}, { StatusManager::EFFECT_ID::BOOST_UP, StatusManager::EFFECT_ID::BOOST_UP, StatusManager::EFFECT_ID::BOOST_UP, StatusManager::EFFECT_ID::BOOST_UP });

		// Ammo refiller
		m_triggerManager.addTrigger(Graphics::CUBE, Cube({ 0, 10, 40 }, { 0, 0, 0 }, { 10, 10, 10 }), 1000.f, physics, { }, { StatusManager::EFFECT_ID::AMMO_PICK_UP });
	}
}

int EntityManager::getEnemiesAlive() const 
{
    return m_deadEnemies.size();
}

void EntityManager::clear() 
{
	m_deadEnemies.clear();
	m_enemies.clear();
	m_bossEnemies.clear();

	reserveData();
}

void EntityManager::setCurrentWave(int currentWave) 
{
	m_currentWave = currentWave;
}

void EntityManager::render(Graphics::Renderer &renderer)
{
	for (int i = 0; i < m_enemies.size(); ++i)
	{
		m_enemies[i]->render(renderer);
	}

	for (int i = 0; i < m_bossEnemies.size(); ++i)
	{
		m_bossEnemies[i]->render(renderer);
	}

	for (int i = 0; i < m_deadEnemies.size(); ++i)
	{
		m_deadEnemies[i]->render(renderer);
	}

	m_triggerManager.render(renderer);
}

int EntityManager::getCurrentWave() const 
{
	return m_currentWave;
}