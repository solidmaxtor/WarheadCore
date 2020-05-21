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

#ifndef ACORE_PASSIVEAI_H
#define ACORE_PASSIVEAI_H

#include "CreatureAI.h"
//#include "CreatureAIImpl.h"

class WH_GAME_API PassiveAI : public CreatureAI
{
    public:
        explicit PassiveAI(Creature* c);

        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit*) {}
        void UpdateAI(uint32);

        static int Permissible(const Creature*) { return PERMIT_BASE_IDLE;  }
};

class WH_GAME_API PossessedAI : public CreatureAI
{
    public:
        explicit PossessedAI(Creature* c);

        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit* target);
        void UpdateAI(uint32);
        void EnterEvadeMode() {}

        void JustDied(Unit*);
        void KilledUnit(Unit* victim);

        static int Permissible(const Creature*) { return PERMIT_BASE_IDLE;  }
};

class WH_GAME_API NullCreatureAI : public CreatureAI
{
    public:
        explicit NullCreatureAI(Creature* c);

        void MoveInLineOfSight(Unit*) {}
        void AttackStart(Unit*) {}
        void UpdateAI(uint32) {}
        void EnterEvadeMode() {}
        void OnCharmed(bool /*apply*/) {}

        static int Permissible(const Creature*) { return PERMIT_BASE_IDLE;  }
};

class WH_GAME_API CritterAI : public PassiveAI
{
    public:
        explicit CritterAI(Creature* c) : PassiveAI(c) { _combatTimer = 0; }

        void DamageTaken(Unit* /*done_by*/, uint32& /*damage*/, DamageEffectType damagetype, SpellSchoolMask damageSchoolMask);
        void EnterEvadeMode();
        void UpdateAI(uint32);

    // Xinef: Added
    private:
        uint32 _combatTimer;
};

class WH_GAME_API TriggerAI : public NullCreatureAI
{
    public:
        explicit TriggerAI(Creature* c) : NullCreatureAI(c) {}
        void IsSummonedBy(Unit* summoner);
};

#endif

