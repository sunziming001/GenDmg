local Class = require "middleclass"
local DamageObject = require "damage_object"

local DamageGroup = Class('DamageGroup', DamageObject)


local _private = setmetatable({}, {__mode = "k"}) 
local initPrivateMembers = function(self)
	_private[self]={
		objs = {},
	}
end

function DamageGroup:initialize()
	DamageObject.initialize(self)
	initPrivateMembers(self)
end

function DamageGroup:addObj(obj)
	self:merge(obj)
end

function DamageGroup:clear()
	_private[self].objs = nil
	
	_private[self].objs = {}
end




return DamageGroup