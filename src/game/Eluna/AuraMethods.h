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

#ifndef AURAMETHODS_H
#define AURAMETHODS_H

namespace LuaAura
{
    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int GetCaster(lua_State* L, Aura* aura)
    {
        sEluna.Push(L, aura->GetCaster());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int GetCasterGUID(lua_State* L, Aura* aura)
    {
        sEluna.Push(L, aura->GetCasterGuid());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int GetCasterLevel(lua_State* L, Aura* aura)
    {
        sEluna.Push(L, aura->GetCaster()->getLevel());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int GetDuration(lua_State* L, Aura* aura)
    {
        sEluna.Push(L, aura->GetAuraDuration());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int GetCharges(lua_State* L, Aura* aura)
    {
        sEluna.Push(L, aura->GetStackAmount());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int GetAuraId(lua_State* L, Aura* aura)
    {
        sEluna.Push(L, aura->GetId());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int GetMaxDuration(lua_State* L, Aura* aura)
    {
        sEluna.Push(L, aura->GetAuraMaxDuration());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int GetStackAmount(lua_State* L, Aura* aura)
    {
        sEluna.Push(L, aura->GetStackAmount());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int SetDuration(lua_State* L, Aura* aura)
    {
        int duration = luaL_checkinteger(L, 1);
        aura->GetHolder()->SetAuraDuration(duration);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int SetMaxDuration(lua_State* L, Aura* aura)
    {
        int duration = luaL_checkinteger(L, 1);
        aura->GetHolder()->SetAuraMaxDuration(duration);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int SetStackAmount(lua_State* L, Aura* aura)
    {
        int amount = luaL_checkunsigned(L, 1);
        aura->GetHolder()->SetStackAmount(amount);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int Remove(lua_State* L, Aura* aura)
    {
        aura->GetHolder()->RemoveAura(aura->GetEffIndex());
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param aura
     * @return int
     */
    int GetOwner(lua_State* L, Aura* aura)
    {
        sEluna.Push(L, aura->GetTarget());
        return 1;
    }
};
#endif