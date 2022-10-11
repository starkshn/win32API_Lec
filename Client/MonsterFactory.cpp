#include "pch.h"
#include "MonsterFactory.h"

#include "CMonster.h"
#include "AI.h"
#include "Idle.h"
#include "Trace.h"

#include "RigidBody.h"

CMonster* MonsterFactory::CreateMonster(MONSTER_TYPE type, Vector2 pos)
{
	CMonster* monster = nullptr;
	
	switch (type)
	{
	case MONSTER_TYPE::NONE:
		{
			
		}
		break;
	case MONSTER_TYPE::NORMAL:
		{
			monster = new CMonster();
			monster->SetPos(pos);

			MonsterInfo info = {};
			info._id = 0;
			info._speed = 150.f;
			info._hp = 100.f;
			info._attackDamage = 10.f;
			info._searchRange = 300.f;
			info._attackRange = 50.f;
			
			monster->SetMonInfo(info);
			
			AI* ai = new AI();
			ai->AddState(new Idle);
			ai->AddState(new Trace);
			ai->SetCurState(MONSTER_STATE::IDLE);

			// AI
			monster->SetAI(ai);

			// RigidBody
			monster->CreateRigidBody();
			monster->GetRigidBody()->SetMess(1.f);

		}
		break;
	case MONSTER_TYPE::SLIME:
		{

		}
		break;
	case MONSTER_TYPE::ORC:
		{

		}
		break;
	case MONSTER_TYPE::SKELTON:
		{

		}
		break;
	case MONSTER_TYPE::END:
		{

		}
		break;
	default:
		break;
	}

	if (monster == nullptr)
		assert(nullptr);

	return monster;
}