/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2024 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "creatures/players/grouping/groups.hpp"
#include "game/game.hpp"
#include "lua/functions/creatures/player/group_functions.hpp"

int GroupFunctions::luaGroupCreate(lua_State* L) {
	// Group(id)
	const uint32_t id = getNumber<uint32_t>(L, 2);

	const auto &group = g_game().groups.getGroup(id);
	if (group) {
		pushUserdata<Group>(L, group);
		setMetatable(L, -1, "Group");
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetId(lua_State* L) {
	// group:getId()
	const auto &group = getUserdataShared<Group>(L, 1);
	if (group) {
		lua_pushnumber(L, group->id);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetName(lua_State* L) {
	// group:getName()
	const auto &group = getUserdataShared<Group>(L, 1);
	if (group) {
		pushString(L, group->name);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetFlags(lua_State* L) {
	// group:getFlags()
	const auto &group = getUserdataShared<Group>(L, 1);
	if (group) {
		std::bitset<magic_enum::enum_integer(PlayerFlags_t::FlagLast)> flags;
		for (uint8_t i = 0; i < magic_enum::enum_integer(PlayerFlags_t::FlagLast); ++i) {
			if (group->flags[i]) {
				flags.set(i);
			}
		}
		lua_pushnumber(L, static_cast<lua_Number>(flags.to_ulong()));
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetAccess(lua_State* L) {
	// group:getAccess()
	const auto &group = getUserdataShared<Group>(L, 1);
	if (group) {
		pushBoolean(L, group->access);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetMaxDepotItems(lua_State* L) {
	// group:getMaxDepotItems()
	const auto &group = getUserdataShared<Group>(L, 1);
	if (group) {
		lua_pushnumber(L, group->maxDepotItems);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupGetMaxVipEntries(lua_State* L) {
	// group:getMaxVipEntries()
	const auto &group = getUserdataShared<Group>(L, 1);
	if (group) {
		lua_pushnumber(L, group->maxVipEntries);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int GroupFunctions::luaGroupHasFlag(lua_State* L) {
	// group:hasFlag(flag)
	const auto &group = getUserdataShared<Group>(L, 1);
	if (group) {
		const auto flag = static_cast<PlayerFlags_t>(getNumber<int>(L, 2));
		pushBoolean(L, group->flags[Groups::getFlagNumber(flag)]);
	} else {
		lua_pushnil(L);
	}
	return 1;
}
