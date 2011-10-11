/*
* this is a:
* time lib for lua it provide microseconds, miliseconds and seconds and diference between them 
*
* author:
* @xxleite
*
* date:
* 13:09 10/8/2011 
*
* ----------------------------------------------------------------------------
* "THE BEER-WARE LICENSE" (Revision 42):
* <xxleite@gmail.com> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a beer in return
* ----------------------------------------------------------------------------
*/

#include <stdio.h>
#include <sys/time.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#ifndef LUA_API
#define LUA_API  __declspec(dllexport)
#endif

#ifndef UINT
#define UINT unsigned int
#endif

const UINT SEC  = 	2;
const UINT MSEC = 	4;
const UINT USEC = 	8;

/* time helper function */
double get_time( UINT k ){
	
	struct timeval tv;
	gettimeofday( &tv, NULL );
	
	if( k==SEC ) 		return tv.tv_sec;
	else if( k==MSEC )	return (tv.tv_sec + (double)((int)(tv.tv_usec*0.001) * 0.001));
	else if( k==USEC )	return (tv.tv_usec*0.000001);
	else 				return 0;
}

/* get miliseconds relative to seconds since EPOCH */
int t_mili (lua_State *L) {
	
	lua_pushnumber(L, get_time( MSEC ) );
	return 1;
}

/* get seconds since EPOCH */
int t_seconds (lua_State *L) {
	
	lua_pushnumber( L, get_time( SEC ) );
	return 1;
}

/* get microseconds relative to seconds since EPOCH */
int t_micro (lua_State *L) {
	
	lua_pushnumber(L, get_time( USEC ) );
	return 1;
}

/* return the diference in miliseconds relative to seconds since EPOCH */
int t_diff (lua_State *L){
	
	double v1= (double)luaL_checknumber( L, 1 );
	
	lua_pushnumber( L, ( get_time( MSEC ) - v1 ) );
	return 1;
}

/* register functions */
const struct luaL_reg time_lib[] = {
  {"getMiliseconds", t_mili},
  {"getSeconds", t_seconds},
  {"getMicroseconds", t_micro},
  {"getDiff", t_diff},
  {NULL, NULL}
};

/* register lib */
LUALIB_API int luaopen_time (lua_State *L) {
  
  luaL_register(L, "time", time_lib);
  return 1;
}
