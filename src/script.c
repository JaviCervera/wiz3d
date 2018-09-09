#include "../lib/lua/lua.h"
#include "../lib/lua/lualib.h"
#include "../lib/lua/lauxlib.h"
#include "script.h"
#include <stdio.h>
#include <string.h>

int luaopen_color(lua_State* l);
int luaopen_fog(lua_State* l);
int luaopen_input(lua_State* l);
int luaopen_light(lua_State* l);
int luaopen_log(lua_State* l);
int luaopen_material(lua_State* l);
int luaopen_object(lua_State* l);
int luaopen_screen(lua_State* l);
int luaopen_texture(lua_State* l);
int luaopen_viewer(lua_State* l);

static char _script_error[256] = { 0 };
static lua_State* _lua_state;

void _script_set_error(const char* error)
{
  strncpy(_script_error, error, sizeof(_script_error));
  _script_error[sizeof(_script_error)-1] = 0;
}

bool_t script_init()
{
  /* create lua state and register libs */
  _lua_state = luaL_newstate();
  luaL_requiref(_lua_state, "_G", luaopen_base, TRUE); lua_pop(_lua_state, 1);
  luaL_requiref(_lua_state, "string", luaopen_string, TRUE); lua_pop(_lua_state, 1);
  luaL_requiref(_lua_state, "table", luaopen_table, TRUE); lua_pop(_lua_state, 1);
  luaL_requiref(_lua_state, "math", luaopen_math, TRUE); lua_pop(_lua_state, 1);
  luaopen_color(_lua_state);
  luaopen_input(_lua_state);
  luaopen_light(_lua_state);
  luaopen_log(_lua_state);
  luaopen_material(_lua_state);
  luaopen_object(_lua_state);
  luaopen_screen(_lua_state);
  luaopen_texture(_lua_state);
  luaopen_viewer(_lua_state);

  /* move constants into global namespace */
  luaL_dostring(_lua_state, "for k,v in pairs(color) do if k:sub(1, 1) == \"_\" then _G[k]=v end end");
  luaL_dostring(_lua_state, "for k,v in pairs(input) do if k:sub(1, 1) == \"_\" then _G[k]=v end end");
  luaL_dostring(_lua_state, "for k,v in pairs(light) do if k:sub(1, 1) == \"_\" then _G[k]=v end end");
  luaL_dostring(_lua_state, "for k,v in pairs(log) do if k:sub(1, 1) == \"_\" then _G[k]=v end end");
  luaL_dostring(_lua_state, "for k,v in pairs(material) do if k:sub(1, 1) == \"_\" then _G[k]=v end end");
  luaL_dostring(_lua_state, "for k,v in pairs(object) do if k:sub(1, 1) == \"_\" then _G[k]=v end end");
  luaL_dostring(_lua_state, "for k,v in pairs(screen) do if k:sub(1, 1) == \"_\" then _G[k]=v end end");
  luaL_dostring(_lua_state, "for k,v in pairs(texture) do if k:sub(1, 1) == \"_\" then _G[k]=v end end");
  luaL_dostring(_lua_state, "for k,v in pairs(viewer) do if k:sub(1, 1) == \"_\" then _G[k]=v end end");

  return TRUE;
}

void script_finish()
{
  lua_close(_lua_state);
}

bool_t script_load(const char* filename)
{
  if ( luaL_dofile(_lua_state, filename) )
  {
    _script_set_error(lua_tostring(_lua_state, -1));
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}

const char* script_error()
{
  return _script_error;
}