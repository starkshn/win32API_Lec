#include "pch.h"
#include "Trace.h"

#include "CSceneManager.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeManager.h"

Trace::Trace() : State(MONSTER_STATE::TRACE)
{

}

Trace::~Trace()
{

}

void Trace::EnterState()
{
	
}

void Trace::ExitState()
{

}

void Trace::update()
{
	// 타겟팅된 플레이어를 쫒아온다.
	CPlayer* player = dynamic_cast<CPlayer*>(CSceneManager::GetInstance()->GetCurScene()->GetCurPlayer());

	player->GetPos();
	Vector2 playerPos = player->GetPos();

	// 범위 안에 들어오면 추적 상태로 전환
	CMonster* monster = GetOwnerMonter(); // 나다.
	Vector2 monsterPos = monster->GetPos();

	Vector2 diff = playerPos - monsterPos; // 방향 벡터 나온다.
	diff.Normalize(); // 단위 벡터 만듦.

	const MonsterInfo& mInfo = monster->GetMonsterInfo();

	// 방향 벡터에 따라서 이동하도록
	monsterPos += diff * mInfo._speed * DeltaTime_F;

	monster->SetPos(monsterPos);
}