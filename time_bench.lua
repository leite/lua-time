
package.cpath = "c:\\dev\\testes\\?.dll"

require 'time'
local bit = require('bit')

local rshift = bit.rshift
local floor  = math.floor

local TIME_TEST = 10000000
local tb = {}
local utils = {}	
	
function round(num, idp)
  local mult = 10^(idp or 0)
  return floor(num * mult + 0.5) / mult
end	
	
utils.round2 = function( pValue )
	return (pValue >= (rshift(pValue,0)+.5)) and rshift(pValue,0)+1 or rshift(pValue,0)
end
	
function getTime() return time.getMiliseconds() end	
function getDiff( t ) return time:getDiff( t ) end
	
tb.test1 = function()
	
	local t = getTime()
	
	for i=0, TIME_TEST do
		local test = utils.round2(i)
	end
	
	print("time test1: ", getDiff( t ) )
end

tb.test3 = function()
	
	local t = getTime()
	
	for i=0, TIME_TEST do
		local test = (i >= (rshift(i,0)+.5)) and rshift(i,0)+1 or rshift(i,0)
	end
	
	print("time test3: ", getDiff( t ) )
end

tb.test2 = function()
	
	local t = getTime()
	
	for i=0, TIME_TEST do
		local test = round(i)
	end
	
	print("time teste2:", getDiff( t ))
	
end

print( time.getMiliseconds(), time.getSeconds() )

 tb.test1()
 tb.test2()
 tb.test3()

--[[

private function test1():void{
			time = getTimer();
			for (var i:int=0; i<TIME_TEST; i++) 
			{
				var test:int = BitwiseMathUtils.round(i);
			} 
			trace("time test1:", getTimer() - time);
		}
		
		private function test2():void
		{
			time = getTimer();
			for (var i:int=0; i<TIME_TEST; i++) 
			{
				var test:int = Math.round(i);
			} 
			trace("time test2:", getTimer() - time);
		} --]]
		