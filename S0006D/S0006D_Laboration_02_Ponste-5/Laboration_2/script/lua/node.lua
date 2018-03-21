local Node = {}
function Node:init()
    local node = {}
    node.x = 0
    node.y = 0
    node.index = 0
    node.openIndex = 0
    node.FValue = 0
    node.valueH = 0
    node.valueG = 0
    node.FValue = 0
    node.inOpenList = false
    node.inClosedList = false
    
    node.hasTree = false
    node.treeRemaining = 0
    node.treeCollection = {}
    
    node.parent = nil
    node.plane = nil
    node.isWalkable = false
    node.walk = ""
    node.visited = false
    node.walkSpeed = 0
    
    node.treeBottom = nil
    node.treeMiddle = nil
    node.treeTop = nil
    node.fog = nil
    function node:SetPosition(xPos, yPos)
        self.x = xPos
        self.y = yPos
    end
    
    function node:SetFValue()
        node.FValue = node.valueG+node.valueH
    end
    
    return node
end

return Node
