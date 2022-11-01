local Class = require "middleclass"
local Character = Class('Character')

local gCharacter = nil
local gCharacterConf = nil

function GetCurSkillTable()
	if gCharacter ~= nil then
		return gCharacter:getSkillTable()
	else
		return {}
	end
end

function SetCurCharacter(character)
	gCharacter = nil
	gCharacter = character
end

function SetCharacterConf(conf)
	print("baseHp: "..conf.baseHp)
	gCharacterConf = conf
end

function GetCharacterConf()
	return gCharacterConf
end

local _private = setmetatable({}, {__mode = "k"}) 
local initPrivateMembers = function(self)
	_private[self]={
		
	}
end

function Character:initialize(conf)
	initPrivateMembers(self)
end

function Character:getSkillTable()
	return {}
end


return Character