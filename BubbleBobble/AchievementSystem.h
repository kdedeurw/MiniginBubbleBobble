#pragma once
#include "Observer.h"

class AchievementSystem final : public Observer
{
public:
	AchievementSystem() = default;
	~AchievementSystem() = default;

	void OnNotify(GameObject* pEntity, int event) override;

	enum class Achievement
	{
		achievement_player,
		achievement_sneaky,
		achievement_ouch,
		achievement_skippy,
	};

private:
	unsigned int m_GamesPlayed{}, m_Ducks{}, m_20Damage{}, m_Jumps{};
	unsigned int m_GamesPlayedThresHold{ 5 }, m_DucksThresHold{ 10 }, m_20DamageThresHold{ 1 }, m_JumpsThresHold{ 10 };
	bool m_IsGamesPlayedAch{}, m_IsDuckedAch{}, m_Is20DamageAch{}, m_IsJumpsAch{};
	//this is a somewhat bad implementation imo, but it can work if managed correctly

	void Unlock(Achievement achievement);
	bool CheckProgress(unsigned int progress, unsigned int goal);

};