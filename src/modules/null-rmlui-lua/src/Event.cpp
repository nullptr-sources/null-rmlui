/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
 
#include <LuaType.h>
#include <IncludeLua.h>
#include <RmlUi/Core/Event.h>
#include <RmlUi/Core/Element.h>
#include <RmlUi/Core/Dictionary.h>
#include "EventParametersProxy.h"


namespace Rml {
namespace Lua {
template<> void ExtraInit<Event>(lua_State* /*L*/, int /*metatable_index*/) { return; }

//method
int EventStopPropagation(lua_State* /*L*/, Event* obj)
{
    obj->StopPropagation();
    return 0;
}

//getters
int EventGetAttrcurrent_element(lua_State* L)
{
    Event* evt = LuaType<Event>::check(L,1);
    RMLUI_CHECK_OBJ(evt);
    Element* ele = evt->GetCurrentElement();
    LuaType<Element>::push(L,ele,false);
    return 1;
}

int EventGetAttrtype(lua_State* L)
{
    Event* evt = LuaType<Event>::check(L,1);
    RMLUI_CHECK_OBJ(evt);
    String type = evt->GetType();
    lua_pushstring(L,type.c_str());
    return 1;
}

int EventGetAttrtarget_element(lua_State* L)
{
    Event* evt = LuaType<Event>::check(L,1);
    RMLUI_CHECK_OBJ(evt);
    Element* target = evt->GetTargetElement();
    LuaType<Element>::push(L,target,false);
    return 1;
}

int EventGetAttrparameters(lua_State* L)
{
    Event* evt = LuaType<Event>::check(L,1);
    RMLUI_CHECK_OBJ(evt);
    EventParametersProxy* proxy = new EventParametersProxy();
    proxy->owner = evt;
    LuaType<EventParametersProxy>::push(L,proxy,true);
    return 1;
}

RegType<Event> EventMethods[] =
{
    RMLUI_LUAMETHOD(Event,StopPropagation)
    { nullptr, nullptr },
};

luaL_Reg EventGetters[] =
{
    RMLUI_LUAGETTER(Event,current_element)
    RMLUI_LUAGETTER(Event,type)
    RMLUI_LUAGETTER(Event,target_element)
    RMLUI_LUAGETTER(Event,parameters)
    { nullptr, nullptr },
};

luaL_Reg EventSetters[] =
{
    { nullptr, nullptr },
};

RMLUI_LUATYPE_DEFINE(Event)
} // namespace Lua
} // namespace Rml
