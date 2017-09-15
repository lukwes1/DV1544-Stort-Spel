#include <Entity/Entity.h>

using namespace Logic;

Entity::Entity(btRigidBody* body)
{
	m_body = body;
	m_transform = &m_body->getWorldTransform();
}

Entity::~Entity() 
{
	// ALL physics is getting cleared by the Physics class, 
}

void Entity::clear() { }

void Entity::update(float deltaTime)
{
	m_statusManager.update(deltaTime);
	updateSpecific(deltaTime);
}

void Entity::collision(Entity& other)
{
	onCollision(other);
}

btRigidBody* Entity::getRigidbody()
{
	return m_body;
}

// JUST FOR TESTING, REMOVE
void Entity::consoleWritePosition()
{
	printf("Position = { %f, %f, %f }\n", m_transform->getOrigin().getX(), m_transform->getOrigin().getY(), m_transform->getOrigin().getZ());
}

DirectX::SimpleMath::Vector3 Entity::getPosition() const
{
	return DirectX::SimpleMath::Vector3(m_transform->getOrigin());
}

DirectX::SimpleMath::Quaternion Entity::getRotation() const
{
	return DirectX::SimpleMath::Quaternion(m_transform->getRotation());
}

DirectX::SimpleMath::Vector3 Entity::getScale() const
{
	return DirectX::SimpleMath::Vector3(m_body->getCollisionShape()->getLocalScaling());
}

DirectX::SimpleMath::Matrix Logic::Entity::getTransformMatrix() const
{
	// Making memory for a matrix
	float* m = new float[4 * 16];

	// Getting this entity's matrix
	m_transform->getOpenGLMatrix((btScalar*)(m));

	// Translating to DirectX Math and assigning the variables
	DirectX::SimpleMath::Matrix transformMatrix(m);

	// Deleting the old created variables from memory
	delete m;

	return transformMatrix;
}
