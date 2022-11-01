local Class = require "middleclass"
local Character = require "character"
local ganyu = Class('ganyu', Character)

function ganyu:initialize()
	Character.initialize(self)
end

function ganyu:getSkillTable()
	return {
		{'普攻1',0.317,2},
		{'普攻2',0.356,2},
		{'普攻3',0.455,2},
		{'普攻4',0.317,2},
		{'普攻5',0.317,2},
		{'普攻6',0.317,2},
	}
end


SetCurCharacter(ganyu())

return ganyu