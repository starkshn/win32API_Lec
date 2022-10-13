#include "pch.h"
#include "Gravity.h"

#include "CObject.h"
#include "RigidBody.h"

Gravity::Gravity() 
	: 
	p_owner(nullptr),
	_ground(false)
{

}

Gravity::~Gravity()
{

}

void Gravity::finalUpdate()
{
	p_owner->GetRigidBody()->AddForce();
}
