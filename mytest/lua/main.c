#include<stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"


void print_stacknum(const char * desc, const int count)
{
    printf("%s stack num = %d\n",desc, count);
}

void test_api_getfield()
{
    lua_State *L = lua_open();

    luaL_dofile(L,"fieldtest.lua");     // ����ִ��lua�ļ�
    lua_getglobal(L,"param");           // ����param����ѹ��ջ��
    print_stacknum("stage1", lua_gettop(L));

    lua_getfield(L, -1, "a");           // ��Param.a��ջ
    int nParam_a = lua_tointeger(L,-1); // ��Param.aȡ����ֵ������nParam_a
    lua_getfield(L, -2, "b");           // ��Param.b��ջ
    int nParam_b = lua_tointeger(L,-1); // ��Param.bȡ����ֵ������nParam_b
    print_stacknum("stage2",lua_gettop(L));

    lua_pop(L, 3);                  // �����ջ�ж����3������param��param.a��param.b
    print_stacknum("stage3",lua_gettop(L));

    int nParam_c = 2 * nParam_a + nParam_b;
    lua_pushinteger(L, nParam_c);       // ��c=2a+b������ɣ�ѹ��ջ��
    lua_setfield(L, LUA_GLOBALSINDEX, "c");// ʹ��ջ����ֵ���ýű�ȫ�ֱ���c
    print_stacknum("stage4",lua_gettop(L));

    lua_getglobal(L,"lua_func");        // ����lua_func����ѹ��ջ��
    lua_pushinteger(L, 3);              // ѹ�뺯������x=3    
    lua_pcall(L,1,1,0);             // ִ�нű�����lua_func
    print_stacknum("stage5",lua_gettop(L));

    int result = lua_tointeger(L,-1);   // ��ջ��ȡ�ط���ֵ 
    lua_pop(L,1);                       // �������ؽ��
    print_stacknum("stage6",lua_gettop(L));

    printf("\nresult = %d\n", result);  
    lua_close(L);                       //�ر�lua����  
}

void main()
{
    return test_api_getfield();
}
