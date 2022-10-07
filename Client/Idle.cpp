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
	// Player의 위치 체크 
	CPlayer* player = dynamic_cast<CPlayer*>(CSceneManager::GetInstance()->GetCurScene()->GetCurPlayer());

	Vector2 playerPos = player->GetPos();

	// 범위 안에 들어오면 추적 상태로 전환
	CMonster* monster = GetOwnerMonter(); // 나다.
	Vector2 monsterPos = monster->GetPos();

	Vector2 diff = playerPos - monsterPos;
	float distance = diff.Length();

	const MonsterInfo& mInfo = monster->GetMonsterInfo();

	// 몬스터 인식 범위 안으로 들어옴
	if (distance < mInfo._searchRange)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::TRACE);
	}
}



