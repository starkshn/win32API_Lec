#pragma once
#include "CObject.h"
#include "CCharingMissile.h"
#include "Collider.h"

class Texture;

class CPlayer : public CObject
{
private:
	CLONE(CPlayer);
	// Texture*	p_myObject;

	OBJECT_STATE	_curState;
	OBJECT_STATE	_prevState;
	int				_dir;
	int				_prevDir;
	bool			_onJump;
	

public :
	CPlayer();
	virtual ~CPlayer() override;

public:
	virtual void update() final;
	virtual void render(HDC dc) final;

	virtual void OnCollisionEnter(Collider* other);
	virtual void OnCollisionExit(Collider* other);

public:
	void UpdateState();
	void UpdateMove();
	void UpdateAnimation();
	void UpdateGravity();

public :
	void CreateMissile();
	void CreateThreeMissile();

};