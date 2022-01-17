local DamageObject = require "damage_object"

local dmgObj = DamageObject()
dmgObj:setBase(1.0)
dmgObj:setRate(1.0)
dmgObj:setResist(0.0)

print("dmg: "..dmgObj:calcDamage())