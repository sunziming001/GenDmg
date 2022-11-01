local DamageGroup = require "damage_group"
local DamageObject = require "damage_object"

local dg = DamageGroup()
local do1 = DamageObject()
local do2 = DamageObject()


do1:setBase(100)
do1:setRate(1.5)

do2:setResist(0.1)

dg:addObj(do1)
dg:addObj(do2)

print("dmg: "..dg:calcDamage())