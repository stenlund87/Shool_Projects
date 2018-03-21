
local Node = {}
function Node:init()
    local node = {}
    node.x = 0
    node.y = 0
    node.FValue = 0
    node.valueH = 0
    node.valueG = 0
    node.FValue = node.valueG+node.valueH
    node.weight = 0
    node.parent = nil
    node.plane = nil
    node.isWalkable = false
    node.line = nil
    node.aPath = nil
    node.visited = false

    function node:SetPosition(xPos, yPos)
        self.x = xPos
        self.y = yPos
    end
    
    function node:IsWalkable(val)
        self.isWalkable = val
    end
    
    function node:SetParent(parentNode)
        self.parent = parentNode
    end
    
    function node:SetFValue()
        node.FValue = node.valueG+node.valueH
    end
    
    return node
end

return Node
