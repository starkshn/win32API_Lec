#include "pch.h"
#include "Idle.h"

#include "CSceneManager.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

Idle::Idle() : State(MONSTER_STATE::IDLE)
{

}

Idle::~Idle()
{

}

void Idle::EnterState()
{

}

void Idle::ExitState()
{

}

void Idle::update()
{
	// Player�� ��ġ üũ 
	CPlayer* player = dynamic_cast<CPlayer*>(CSceneManager::GetInstance()->GetCurScene()->GetCurPlayer());

	Vector2 playerPos = player->GetPos();

	// ���� �ȿ� ������ ���� ���·� ��ȯ
	CMonster* monster = GetOwnerMonter(); // ����.
	Vector2 monsterPos = monster->GetPos();

	Vector2 diff = playerPos - monsterPos;
	float distance = diff.Length();

	const MonsterInfo& mInfo = monster->GetMonsterInfo();

	// ���� �ν� ���� ������ ����
	if (distance < mInfo._searchRange)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::TRACE);
	}
}



