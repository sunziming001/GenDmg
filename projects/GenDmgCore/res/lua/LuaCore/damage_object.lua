
local Class = require "middleclass"
local DamageObject = Class('DamageObject')

local _private = setmetatable({}, {__mode = "k"}) 


local initPrivateMembers= function(self)
	_private[self]={
	
		base = 0.0,				

		rate = 0.0,
		

		resist = 0.0,
		

		addition = 0.0,
		

		reflect = 0.0,
		

		cirtical_rate = 0.0,
		

		cirtical_dmg = 0.0,
	}
end

function DamageObject:initialize()
	initPrivateMembers(self)
end

function DamageObject:merge(obj)
	self:setBase( self:getBase() + obj:getBase() )
	self:setRate( self:getRate() + obj:getRate() )
	self:setResist( self:getResist() + obj:getResist() )
	self:setAddition( self:getAddition() + obj:getAddition() )
	self:setReflect( self:getReflect() + obj:getReflect() )
	self:setCriticalRate( self:getCriticalRate() + obj:getCriticalRate() )
	self:setCriticalDmg( self:getCriticalDmg() + obj:getCriticalDmg() )
end

function DamageObject:setBase(v)
	_private[self].base = v
end

function DamageObject:getBase()
	return _private[self].base
end

function DamageObject:setRate(rate)
	_private[self].rate = rate
end

function DamageObject:getRate()
	return _private[self].rate
end

function DamageObject:setResist(resist)
	_private[self].resist = resist
end

function DamageObject:getResist()
	local ret = 0.0
	if _private[self].resist <= 0.0 then
		ret = _private[self].resist / -2.0
	elseif _private[self].resist >= 0.75 then
		ret = -1.0/(1.0+4.0 * _private[self].resist) +1.0
	else
		ret = _private[self].resist
	end
	
	return ret
end


function DamageObject:setAddition(addition)
	_private[self].addition = addition
end

function DamageObject:getAddition()
	return _private[self].addition
end


function DamageObject:setReflect(reflect)
	_private[self].reflect = reflect
end

function DamageObject:getReflect()
	return _private[self].reflect
end

function DamageObject:setCriticalRate(cirtical_rate)
	_private[self].cirtical_rate = cirtical_rate
end

function DamageObject:getCriticalRate()
	return _private[self].cirtical_rate
end


function DamageObject:setCriticalDmg(cirtical_dmg)
	_private[self].cirtical_dmg = cirtical_dmg
end

function DamageObject:getCriticalDmg()
	return _private[self].cirtical_dmg
end


function DamageObject:calcDamage()
	local v = self:getBase()
	
	v = v * (self:getRate())
	
	v = v * (1.0 + self:getAddition())
	
	v = v * (1.0 + self:getReflect())
	
	v = v * (1.0 - self:getResist())
	
	return v
end

function DamageObject:calcCriticalDamage()
	local v = self:calcDamage()
	
	v = v *(1.0 + self:getCriticalDmg())
	
	return v
end

function DamageObject:calcCriticalExpDamage()
	local v = self:calcDamage()
	
	v = v *(1.0 + self:getCriticalDmg() * self:getCriticalRate())
	
	return v
end


return DamageObject

