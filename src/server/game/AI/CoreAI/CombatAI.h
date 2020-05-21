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

#ifndef ACORE_COMBATAI_H
#define ACORE_COMBATAI_H

#include "CreatureAI.h"
#include "CreatureAIImpl.h"
#include "ConditionMgr.h"

class Creature;

class WH_GAME_API AggressorAI : public CreatureAI
{
    public:
        explicit AggressorAI(Creature* c) : CreatureAI(c) {}

        void UpdateAI(uint32);
        static int Permissible(const Creature*);
};

typedef std::vector<uint32> SpellVct;

class WH_GAME_API CombatAI : public CreatureAI
{
    public:
        explicit CombatAI(Creature* c) : CreatureAI(c) {}

        void InitializeAI();
        void Reset();
        void EnterCombat(Unit* who);
        void JustDied(Unit* killer);
        void UpdateAI(uint32 diff);

        static int Permissible(Creature const* /*creature*/) { return PERMIT_BASE_NO; }

    protected:
        EventMap events;
        SpellVct spells;
};

class WH_GAME_API CasterAI : public CombatAI
{
    public:
        explicit CasterAI(Creature* c) : CombatAI(c) { m_attackDist = MELEE_RANGE; }
        void InitializeAI();
        void AttackStart(Unit* victim) { AttackStartCaster(victim, m_attackDist); }
        void UpdateAI(uint32 diff);
        void EnterCombat(Unit* /*who*/);
    private:
        float m_attackDist;
};

struct WH_GAME_API ArcherAI : public CreatureAI
{
    public:
        explicit ArcherAI(Creature* c);
        void AttackStart(Unit* who);
        void UpdateAI(uint32 diff);


        static int Permissible(Creature const* /*creature*/) { return PERMIT_BASE_NO; }

    protected:
        float m_minRange;
};

struct WH_GAME_API TurretAI : public CreatureAI
{
    public:
        explicit TurretAI(Creature* c);
        bool CanAIAttack(const Unit* who) const;
        void AttackStart(Unit* who);
        void UpdateAI(uint32 diff);

        static int Permissible(Creature const* /*creature*/) { return PERMIT_BASE_NO; }

    protected:
        float m_minRange;
};

#define VEHICLE_CONDITION_CHECK_TIME 1000
#define VEHICLE_DISMISS_TIME 5000

struct WH_GAME_API VehicleAI : public CreatureAI
{
    public:
        explicit VehicleAI(Creature* creature);

        void UpdateAI(uint32 diff);
        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit*) {}
        void OnCharmed(bool apply);

        static int Permissible(Creature const* /*creature*/) { return PERMIT_BASE_NO; }

    private:
        void LoadConditions();
        void CheckConditions(uint32 diff);
        ConditionList conditions;
        uint32 m_ConditionsTimer;
        bool m_DoDismiss;
        uint32 m_DismissTimer;
};

#endif
