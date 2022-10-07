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
	// Ÿ���õ� �÷��̾ �i�ƿ´�.
	CPlayer* player = dynamic_cast<CPlayer*>(CSceneManager::GetInstance()->GetCurScene()->GetCurPlayer());

	player->GetPos();
	Vector2 playerPos = player->GetPos();

	// ���� �ȿ� ������ ���� ���·� ��ȯ
	CMonster* monster = GetOwnerMonter(); // ����.
	Vector2 monsterPos = monster->GetPos();

	Vector2 diff = playerPos - monsterPos; // ���� ���� ���´�.
	diff.Normalize(); // ���� ���� ����.

	const MonsterInfo& mInfo = monster->GetMonsterInfo();

	// ���� ���Ϳ� ���� �̵��ϵ���
	monsterPos += diff * mInfo._speed * DeltaTime_F;

	monster->SetPos(monsterPos);
}