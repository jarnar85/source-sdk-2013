#ifndef NPC_ZOMBIE_H
#define NPC_ZOMBIE_H
#ifdef _WIN32
#pragma once
#endif


#include "npc_BaseZombie.h"


class CZombie : public CAI_BlendingHost<CNPC_BaseZombie>
{
	DECLARE_DATADESC();
	DECLARE_CLASS(CZombie, CAI_BlendingHost<CNPC_BaseZombie>);

public:
	CZombie()
		: m_DurationDoorBash(2, 6),
		m_NextTimeToStartDoorBash(3.0)
	{
	}

	void Spawn(void);
	void Precache(void);

	static NPC_Basedata	GetBaseData();

	void SetZombieModel(void);
	void MoanSound(envelopePoint_t *pEnvelope, int iEnvelopeSize);
	bool ShouldBecomeTorso(const CTakeDamageInfo &info, float flDamageThreshold);
	bool CanBecomeLiveTorso() { return !m_fIsHeadless; }

	void GatherConditions(void);

	int SelectFailSchedule(int failedSchedule, int failedTask, AI_TaskFailureCode_t taskFailCode);
	int TranslateSchedule(int scheduleType);

#ifndef HL2_EPISODIC
	void CheckFlinches() {} // Zombie has custom flinch code
#endif // HL2_EPISODIC

	Activity NPC_TranslateActivity(Activity newActivity);

	void OnStateChange(NPC_STATE OldState, NPC_STATE NewState);

	void StartTask(const Task_t *pTask);
	void RunTask(const Task_t *pTask);

	virtual const char *GetLegsModel(void);
	virtual const char *GetTorsoModel(void);
	virtual const char *GetHeadcrabClassname(void);
	virtual const char *GetHeadcrabModel(void);

	virtual bool OnObstructingDoor(AILocalMoveGoal_t *pMoveGoal,
		CBaseDoor *pDoor,
		float distClear,
		AIMoveResult_t *pResult);

	Activity SelectDoorBash();

	void Ignite(float flFlameLifetime, bool bNPCOnly = true, float flSize = 0.0f, bool bCalledByLevelDesigner = false);
	void Extinguish();
	int OnTakeDamage_Alive(const CTakeDamageInfo &inputInfo);
	bool IsHeavyDamage(const CTakeDamageInfo &info);
	bool IsSquashed(const CTakeDamageInfo &info);
	void BuildScheduleTestBits(void);

	void PrescheduleThink(void);
	int SelectSchedule(void);

	void PainSound(const CTakeDamageInfo &info);
	void DeathSound(const CTakeDamageInfo &info);
	void AlertSound(void);
	void IdleSound(void);
	void AttackSound(void);
	void AttackHitSound(void);
	void AttackMissSound(void);
	void FootstepSound(bool fRightFoot);
	void FootscuffSound(bool fRightFoot);

	const char *GetMoanSound(int nSound);

public:
	DEFINE_CUSTOM_AI;

protected:
	static const char *pMoanSounds[];


private:
	CHandle< CBaseDoor > m_hBlockingDoor;
	float				 m_flDoorBashYaw;

	CRandSimTimer 		 m_DurationDoorBash;
	CSimTimer 	  		 m_NextTimeToStartDoorBash;

	Vector				 m_vPositionCharged;
};

#endif	//NPC_ZOMBIE_H