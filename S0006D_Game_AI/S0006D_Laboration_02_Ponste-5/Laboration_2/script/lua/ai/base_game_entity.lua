a_star = require "script/lua/pathfinding/pathfinding_a"
bfs = require "script/lua/pathfinding/bfs_pathfinding"

BGE = Appkit.class(BGE)

BGE.name = "Håkan"
BGE.hasBeenUpgraded = false

function BGE:init()

    --self.__index = self
end --End of new()
----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------

function BGE:SetPosition(xPos, yPos)
    self.x = xPos
    self.y = yPos
end -- End of SetPosition()
----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------
    
function BGE:SetID(id)
    if id > nextValidID then
        print("Invalid ID! Entity ID is set to "..nextValidID)
        self.entityID = nextValidID
        nextValidID = nextValidID + 1
    else
        self.entityID = id
        nextValidID = id + 1
    end
end --End of SetID()

----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------

function BGE:Update()
end --End of Update()

----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------


function BGE:GetName()
    return self.name
end

function BGE:GetBool()
    return self.beenUpgraded
end
function BGE:SetBool()
    self.beenUpgraded = true
end
