/*
 * main.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: jschober
 */

#include "plainc_hooks.h"
#include "luabind_test.h"
#include "luabind_sequencer.h"

#include <lua.hpp>

#include <iostream>

int main( int argc, char* argv[] )
{
    int s(0);
    lua_State* lua = lua_open();

    luaopen_base(lua);
    luaopen_math(lua);
    luaopen_string(lua);
    luaopen_table(lua);
//    luaopen_io(lua); -- crashes??

    plainc::Register( lua );

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Calling from string: " << std::endl;
    s = luaL_loadstring( lua, plainc::luascript );
    if ( s == 0 ) {
        lua_pcall( lua, 0, LUA_MULTRET, 0 );
    }
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Calling from file: " << std::endl;
    s = luaL_loadfile( lua, "lua/math.lua" );
    if ( s == 0 ) {
        lua_call( lua, 0, 0 );
    }

#ifdef _HAS_LUA_BIND_
    luabind::Register( lua );
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Calling from luabind: " << std::endl;
    s = luaL_loadstring( lua, luabind::luascript );
    if ( s == 0 ) {
        lua_pcall( lua, 0, LUA_MULTRET, 0 );
    }

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Lua sequencer" << std::endl;
    luasequencer::Register( lua );

    s = luaL_loadfile( lua, "lua/sequencer.lua" );
    if ( s == 0 ) {
        lua_pcall( lua, 0, LUA_MULTRET, 0 );
    }

    std::cout << "------------------------------------------------" << std::endl;

#endif
    lua_close(lua);
    return 0;
}

