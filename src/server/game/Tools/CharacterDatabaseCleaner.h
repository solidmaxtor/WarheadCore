/*
 * This file is part of the WarheadCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHARACTERDATABASECLEANER_H
#define CHARACTERDATABASECLEANER_H

namespace CharacterDatabaseCleaner
{
    enum CleaningFlags
    {
        CLEANING_FLAG_ACHIEVEMENT_PROGRESS  = 0x1,
        CLEANING_FLAG_SKILLS                = 0x2,
        CLEANING_FLAG_SPELLS                = 0x4,
        CLEANING_FLAG_TALENTS               = 0x8,
        CLEANING_FLAG_QUESTSTATUS           = 0x10
    };

    WH_GAME_API void CleanDatabase();

    WH_GAME_API void CheckUnique(const char* column, const char* table, bool (*check)(uint32));

    WH_GAME_API bool AchievementProgressCheck(uint32 criteria);
    WH_GAME_API bool SkillCheck(uint32 skill);
    WH_GAME_API bool SpellCheck(uint32 spell_id);
    WH_GAME_API bool TalentCheck(uint32 talent_id);

    WH_GAME_API void CleanCharacterAchievementProgress();
    WH_GAME_API void CleanCharacterSkills();
    WH_GAME_API void CleanCharacterSpell();
    WH_GAME_API void CleanCharacterTalent();
    WH_GAME_API void CleanCharacterQuestStatus();
}

#endif
