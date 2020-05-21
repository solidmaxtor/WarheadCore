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

#ifndef _MAP_UPDATER_H_INCLUDED
#define _MAP_UPDATER_H_INCLUDED

#include <ace/Thread_Mutex.h>
#include <ace/Condition_Thread_Mutex.h>
#include "DelayExecutor.h"
#include "World.h"

class Map;

class WH_GAME_API MapUpdater
{
public:

    MapUpdater();
    virtual ~MapUpdater();

    friend class MapUpdateRequest;
    friend class LFGUpdateRequest;

    int schedule_update(Map& map, uint32 diff, uint32 s_diff);
    int schedule_lfg_update(uint32 diff);

    int wait();

    int activate(size_t num_threads);

    int deactivate();

    bool activated();

private:

    DelayExecutor m_executor;
    ACE_Thread_Mutex m_mutex;
    ACE_Condition_Thread_Mutex m_condition;
    size_t pending_requests;

    void update_finished();
};

#endif //_MAP_UPDATER_H_INCLUDED
