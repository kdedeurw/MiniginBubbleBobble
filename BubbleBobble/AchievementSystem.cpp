#include "MiniginPCH.h"
#include "AchievementSystem.h"
#include "GameObject.h"
#include "Events.h"

void AchievementSystem::OnNotify(GameObject* , int event)
{
    switch ((Event)event)
    {
    case Event::event_play_game:
        ++m_GamesPlayed;
        if (!m_IsGamesPlayedAch && CheckProgress(m_GamesPlayed, m_GamesPlayedThresHold))
        {
            Unlock(Achievement::achievement_player);
            m_IsGamesPlayedAch = true;
        }
        break;
    case Event::event_level_complete:
        ++m_Ducks;
        if (!m_IsDuckedAch && CheckProgress(m_Ducks, m_DucksThresHold))
        {
            Unlock(Achievement::achievement_sneaky);
            m_IsDuckedAch = true;
        }
        break;
    case Event::event_die:
        ++m_20Damage;
        if (!m_Is20DamageAch && CheckProgress(m_20Damage, m_20DamageThresHold))
        {
            Unlock(Achievement::achievement_ouch);
            m_Is20DamageAch = true;
        }
        break;
    case Event::event_jump:
        ++m_Jumps;
        if (!m_IsJumpsAch && CheckProgress(m_Jumps, m_JumpsThresHold))
        {
            Unlock(Achievement::achievement_skippy);
            m_IsJumpsAch = true;
        }
        break;
    }
}

void AchievementSystem::Unlock(Achievement achievement)
{
    switch (achievement)
    {
    case Achievement::achievement_player:
        break;
    case Achievement::achievement_sneaky:
        break;
    case Achievement::achievement_ouch:
        break;
    case Achievement::achievement_skippy:
        break;
    }
}

bool AchievementSystem::CheckProgress(unsigned int progress, unsigned int goal)
{
    if (progress >= goal)
        return true;
    return false;
}