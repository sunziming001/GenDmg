local Class = require "middleclass"
local Character = require "character"
local mona = Class('mona', Character)

function mona:initialize()
	Character.initialize(self)
end

function mona:getSkillTable()
	return {
		atk1={1.2,}
	}
end


SetCurCharacter(mona())

return mona