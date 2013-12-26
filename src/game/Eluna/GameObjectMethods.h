/**
 * mangos-zero is a full featured server for World of Warcraft in its vanilla
 * version, supporting clients for patch 1.12.x.
 *
 * Eluna provides an alternative Lua based scripting which allows your to
 * easily customize game content without the need for compilers or any
 * other development tools.
 *
 * Copyright (C) 2010-2013  Eluna Lua Engine <http://emudevs.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

#ifndef GAMEOBJECTMETHODS_H
#define GAMEOBJECTMETHODS_H

namespace LuaGameObject
{
    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int GetRelativePoint(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        float dist = luaL_checknumber(L, 1);
        int deg = luaL_checkinteger(L, 2);

        float o = MapManager::NormalizeOrientation(go->GetOrientation() + (deg * M_PI / 180));
        sEluna.Push(L, go->GetPositionX() + (dist * cosf(o)));
        sEluna.Push(L, go->GetPositionY() + (dist * sinf(o)));
        sEluna.Push(L, o);
        return 3;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int SummonCreature(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        uint32 entry = luaL_checkunsigned(L, 1);
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        float z = luaL_checknumber(L, 4);
        float o = luaL_checknumber(L, 5);
        uint32 spawnType = luaL_optunsigned(L, 6, 0);
        uint32 despawnTimer = luaL_optunsigned(L, 7, 0);

        TempSummonType type;
        switch (spawnType)
        {
            case 1:
                type = TEMPSUMMON_TIMED_OR_DEAD_DESPAWN;
                break;
            case 2:
                type = TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN;
                break;
            case 3:
                type = TEMPSUMMON_TIMED_DESPAWN;
                break;
            // case 4:
            //     type = TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT;
            //    break;
            case 5:
                type = TEMPSUMMON_CORPSE_DESPAWN;
                break;
            case 6:
                type = TEMPSUMMON_CORPSE_TIMED_DESPAWN;
                break;
            case 7:
                type = TEMPSUMMON_DEAD_DESPAWN;
                break;
            case 8:
                type = TEMPSUMMON_MANUAL_DESPAWN;
                break;
            default:
                return 0;
        }
        sEluna.Push(L, go->SummonCreature(entry, x, y, z, o, type, despawnTimer));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int SummonGameObject(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        uint32 entry = luaL_checkunsigned(L, 1);
        float x = luaL_checknumber(L, 2);
        float y = luaL_checknumber(L, 3);
        float z = luaL_checknumber(L, 4);
        float o = luaL_checknumber(L, 5);
        uint32 respawnDelay = luaL_optunsigned(L, 6, 30);
        sEluna.Push(L, go->SummonGameObject(entry, x, y, z, o, respawnDelay));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int GetDisplayId(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        sEluna.Push(L, go->GetDisplayId());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int HasQuest(lua_State* L, GameObject* go)
    {
        uint32 questId = luaL_checkunsigned(L, 1);

        sEluna.Push(L, go->HasQuest(questId));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int IsSpawned(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            sEluna.Push(L, false);
        else
            sEluna.Push(L, go->isSpawned());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int IsTransport(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            sEluna.Push(L, false);
        else
            sEluna.Push(L, go->IsTransport());
        return 1;
    }

    /*int IsDestructible(lua_State* L, GameObject* go) // TODO: Implementation core side
    {
        if (!go || !go->IsInWorld())
            sEluna.Push(L, false);
        else
            sEluna.Push(L, go->IsDestructibleBuilding());
        return 1;
    }*/

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int IsActive(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            sEluna.Push(L, false);
        else
            sEluna.Push(L, go->isActiveObject());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int Move(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = luaL_checknumber(L, 3);
        float o = luaL_checknumber(L, 4);
        go->Relocate(x, y, z, o);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int SaveToDB(lua_State* L, GameObject* go)
    {
        go->SaveToDB();
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int RemoveFromWorld(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        bool del = luaL_optbool(L, 1, false);
        if (del)
            go->DeleteFromDB();
        go->RemoveFromWorld();
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int RegisterEvent(lua_State* L, GameObject* go)
    {
        luaL_checktype(L, 1, LUA_TFUNCTION);
        uint32 delay = luaL_checkunsigned(L, 2);
        uint32 repeats = luaL_checkunsigned(L, 3);

        lua_settop(L, 1);
        int functionRef = lua_ref(L, true);
        sEluna.Push(L, sEluna.EventMgr.AddEvent(go->GetObjectGuid().GetRawValue(), functionRef, delay, repeats, go));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int RemoveEventById(lua_State* L, GameObject* go)
    {
        int eventId = luaL_checkinteger(L, 1);
        sEluna.EventMgr.RemoveEvent(go->GetObjectGuid().GetRawValue(), eventId);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int RemoveEvents(lua_State* L, GameObject* go)
    {
        sEluna.EventMgr.RemoveEvents(go->GetObjectGuid().GetRawValue());
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int UseDoorOrButton(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        uint32 delay = luaL_optunsigned(L, 1, 0);

        go->UseDoorOrButton(delay);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int SetGoState(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        uint32 state = luaL_optunsigned(L, 1, 0);

        if (state == 0)
            go->SetGoState(GO_STATE_ACTIVE);
        else if (state == 1)
            go->SetGoState(GO_STATE_READY);
        else if (state == 2)
            go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);

        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int GetGoState(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        sEluna.Push(L, go->GetGoState());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int SetLootState(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        uint32 state = luaL_optunsigned(L, 1, 0);

        if (state == 0)
            go->SetLootState(GO_NOT_READY);
        else if (state == 1)
            go->SetLootState(GO_READY);
        else if (state == 2)
            go->SetLootState(GO_ACTIVATED);
        else if (state == 3)
            go->SetLootState(GO_JUST_DEACTIVATED);

        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int GetLootState(lua_State* L, GameObject* go)
    {
        if (!go || !go->IsInWorld())
            return 0;

        sEluna.Push(L, go->getLootState());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int Despawn(lua_State* L, GameObject* go)
    {
        uint32 delay = luaL_optunsigned(L, 1, 1);
        if (!delay)
            delay = 1;

        go->SetSpawnedByDefault(false);
        go->SetRespawnTime(delay);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param go
     * @return int
     */
    int Respawn(lua_State* L, GameObject* go)
    {
        uint32 delay = luaL_optunsigned(L, 1, 1);
        if (!delay)
            delay = 1;

        go->SetSpawnedByDefault(true);
        go->SetRespawnTime(delay);
        return 0;
    }
};
#endif