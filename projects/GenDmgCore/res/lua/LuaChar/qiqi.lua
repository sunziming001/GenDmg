local Class = require "middleclass"
local Character = require "character"
local qiqi = Class('qiqi', Character)



function qiqi:initialize()
	print("qiqi created")
end

function qiqi:getSkillTable()
	return "qiqi string"
end

gCharacter = nil

gCharacter = qiqi()

return qiqi