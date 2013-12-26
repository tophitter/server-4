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

#ifndef ITEMMETHODS_H
#define ITEMMETHODS_H

namespace LuaItem
{
    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetItemLink(lua_State* L, Item* item) // TODO: Implement
    {
        // LOCALE_enUS = 0,
        // LOCALE_koKR = 1,
        // LOCALE_frFR = 2,
        // LOCALE_deDE = 3,
        // LOCALE_zhCN = 4,
        // LOCALE_zhTW = 5,
        // LOCALE_esES = 6,
        // LOCALE_esMX = 7,
        // LOCALE_ruRU = 8

        int loc_idx = luaL_optint(L, 1, DEFAULT_LOCALE);
        if (loc_idx < 0 || loc_idx >= MAX_LOCALE)
        {
            luaL_error(L, "Invalid locale index (%d)", loc_idx);
            return 0;
        }

        const ItemPrototype* temp = item->GetProto();
        std::string name = temp->Name1;
        if (ItemLocale const* il = sObjectMgr.GetItemLocale(temp->ItemId))
            ObjectMgr::GetLocaleString(il->Name, loc_idx, name);

        if (int32 itemRandPropId = item->GetItemRandomPropertyId())
        {
            char* const* suffix = NULL;
            if (itemRandPropId < 0)
            {
                const ItemRandomSuffixEntry* itemRandEntry = sItemRandomSuffixStore.LookupEntry(-item->GetItemRandomPropertyId());
                if (itemRandEntry)
                    suffix = itemRandEntry->nameSuffix;
            }
            else
            {
                const ItemRandomPropertiesEntry* itemRandEntry = sItemRandomPropertiesStore.LookupEntry(item->GetItemRandomPropertyId());
                if (itemRandEntry)
                    suffix = itemRandEntry->nameSuffix;
            }
            if (suffix)
            {
                std::string test(suffix[(name != temp->Name1) ? loc_idx : DEFAULT_LOCALE]);
                if (!test.empty())
                {
                    name += ' ';
                    name += test;
                }
            }
        }

        std::ostringstream oss;
        oss << "|c" << std::hex << ItemQualityColors[temp->Quality] << std::dec <<
            "|Hitem:" << temp->ItemId << ":" <<
            item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT) << ":" <<
            item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT) << ":" <<
            item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_2) << ":" <<
            item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_3) << ":" <<
            item->GetEnchantmentId(BONUS_ENCHANTMENT_SLOT) << ":" <<
            item->GetItemRandomPropertyId() << ":" << item->GetItemSuffixFactor() << ":" <<
            (uint32)item->GetOwner()->getLevel() << "|h[" << name << "]|h|r";

        sEluna.Push(L, oss.str());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetGUID(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetGUIDLow());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetOwnerGUID(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetOwnerGuid());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetOwner(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetOwner());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int SetOwner(lua_State* L, Item* item)
    {
        Player* player = sEluna.CHECK_PLAYER(L, 1);

        if (player)
            item->SetOwnerGuid(player->GetObjectGuid());
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int SetBinding(lua_State* L, Item* item)
    {
        bool soulbound = luaL_checkbool(L, 1);

        item->SetBinding(soulbound);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsSoulBound(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsSoulBound());
        return 1;
    }

    /*int IsBoundAccountWide(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsBoundAccountWide());
        return 1;
    }*/

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsBoundByEnchant(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsBoundByEnchant());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsNotBoundToPlayer(lua_State* L, Item* item)
    {
        Player* player = sEluna.CHECK_PLAYER(L, 1);
        if (!player)
            return 0;

        sEluna.Push(L, item->IsBindedNotWith(player));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsLocked(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsLocked());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsBag(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsBag());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsCurrencyToken(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsCurrencyToken());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsNotEmptyBag(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsNotEmptyBag());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsBroken(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsBroken());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int CanBeTraded(lua_State* L, Item* item) // TODO: Implement trade bool
    {
        // bool mail = luaL_optbool(L, 1, false);
        // bool trade = luaL_optbool(L, 2, false);
        sEluna.Push(L, item->CanBeTraded(/*mail, trade*/));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsInTrade(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsInTrade());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetCount(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetCount());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int SetCount(lua_State* L, Item* item)
    {
        uint32 count = luaL_checkunsigned(L, 1);
        item->SetCount(count);
        return 0;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetMaxStackCount(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetMaxStackCount());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetSlot(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetSlot());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetBagSlot(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetBagSlot());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsInBag(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsInBag());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsEquipped(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsEquipped());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int HasQuest(lua_State* L, Item* item)
    {
        uint32 quest = luaL_checkunsigned(L, 1);
        sEluna.Push(L, item->HasQuest(quest));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsPotion(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsPotion());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsWeaponVellum(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsWeaponVellum());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsArmorVellum(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsArmorVellum());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsConjuredConsumable(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->IsConjuredConsumable());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int IsRefundExpired(lua_State* L, Item* item)// TODO: Implement core support
    {
        /*sEluna.Push(L, item->IsRefundExpired());
        return 1;*/
        return 0; // Temp till supported
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int SetEnchantment(lua_State* L, Item* item)
    {
        Player* owner = item->GetOwner();
        if (!owner)
        {
            sEluna.Push(L, false);
            return 1;
        }

        uint32 enchant = luaL_checkunsigned(L, 1);
        if (!sSpellItemEnchantmentStore.LookupEntry(enchant))
        {
            sEluna.Push(L, false);
            return 1;
        }

        EnchantmentSlot slot = EnchantmentSlot(luaL_checkunsigned(L, 2));
        if (slot >= MAX_INSPECTED_ENCHANTMENT_SLOT)
        {
            luaL_error(L, "Invalid enchantment slot (%d)", slot);
            sEluna.Push(L, false);
            return 1;
        }

        owner->ApplyEnchantment(item, slot, false);
        item->SetEnchantment(slot, enchant, 0, 0);
        owner->ApplyEnchantment(item, slot, true);
        sEluna.Push(L, true);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int ClearEnchantment(lua_State* L, Item* item)
    {
        Player* owner = item->GetOwner();
        if (!owner)
        {
            sEluna.Push(L, false);
            return 1;
        }

        EnchantmentSlot slot = EnchantmentSlot(luaL_checkunsigned(L, 1));
        if (slot >= MAX_INSPECTED_ENCHANTMENT_SLOT)
        {
            luaL_error(L, "Invalid enchantment slot (%d)", slot);
            sEluna.Push(L, false);
            return 1;
        }

        if (!item->GetEnchantmentId(slot))
        {
            sEluna.Push(L, false);
            return 1;
        }

        owner->ApplyEnchantment(item, slot, false);
        item->ClearEnchantment(slot);
        sEluna.Push(L, true);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetGUIDLow(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetGUIDLow());
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetEnchantmentId(lua_State* L, Item* item)
    {
        uint32 enchant_slot = luaL_checkunsigned(L, 1);

        EnchantmentSlot slot = EnchantmentSlot(luaL_checkunsigned(L, 2));
        if (slot >= MAX_INSPECTED_ENCHANTMENT_SLOT)
            sEluna.Push(L, 0);
        else
            sEluna.Push(L, item->GetEnchantmentId(EnchantmentSlot(enchant_slot)));
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetSpellId(lua_State* L, Item* item)
    {
        uint32 index = luaL_checkunsigned(L, 1);
        if (index >= MAX_ITEM_PROTO_SPELLS)
        {
            luaL_error(L, "Invalid index (%d)", index);
            return 0;
        }

        sEluna.Push(L, item->GetProto()->Spells[index].SpellId);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetSpellTrigger(lua_State* L, Item* item)
    {
        uint32 index = luaL_checkunsigned(L, 1);
        if (index >= MAX_ITEM_PROTO_SPELLS)
        {
            luaL_error(L, "Invalid index (%d)", index);
            return 0;
        }

        sEluna.Push(L, item->GetProto()->Spells[index].SpellTrigger);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetClass(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->Class);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetSubClass(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->SubClass);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetName(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->Name1);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetDisplayId(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->DisplayInfoID);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetQuality(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->Quality);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetBuyCount(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->BuyCount);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetBuyPrice(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->BuyPrice);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetSellPrice(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->SellPrice);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetInventoryType(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->InventoryType);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetAllowableClass(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->AllowableClass);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetAllowableRace(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->AllowableRace);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetItemLevel(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->ItemLevel);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetRequiredLevel(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->RequiredLevel);
        return 1;
    }

    /*int GetStatsCount(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->StatsCount);
        return 1;
    }*/

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetRandomProperty(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->RandomProperty);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetRandomSuffix(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->RandomSuffix);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetItemSet(lua_State* L, Item* item)
    {
        sEluna.Push(L, item->GetProto()->ItemSet);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int GetBagSize(lua_State* L, Item* item)
    {
        if (Bag* bag = item->ToBag())
            sEluna.Push(L, bag->GetBagSize());
        else
            sEluna.Push(L, 0);
        return 1;
    }

    /**
     * @brief
     *
     * @param L
     * @param item
     * @return int
     */
    int SaveToDB(lua_State* L, Item* item)
    {
        item->SaveToDB();
        return 0;
    }
};
#endif