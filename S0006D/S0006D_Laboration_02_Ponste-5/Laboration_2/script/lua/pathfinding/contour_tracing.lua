
local s = require "script/lua/pathfinding/stack"
local contour = {}

function contour:init()
    local ct = {}
    ct.pathFound = {}
    
    function ct:CheckChildren(currentNode, nodeList)
        local neighborNodes = {left  = nil, top = nil, right = nil, bottom = nil}
        local notWalkable = {}
        
        local rightWalkable = false -- local variable to prevent cutting corners
        local leftWalkable = false -- local variable to prevent cutting corners
        local topWalkable = false -- local variable to prevent cutting corners
        local bottomWalkable = false -- local variable to prevent cutting corners
        
        local temp = nil
        
        for placeHolder, tempNode in ipairs(nodeList) do
            --We check the node to the right
            if (currentNode.x - 1 == tempNode.x) and (currentNode.y == tempNode.y) and not(currentNode == tempNode) and tempNode.isWalkable and not tempNode.visited then
                tempNode.visited = true
                tempNode.parent = currentNode
                neighborNodes.right = tempNode
                rightWalkable = true
                return tempNode
            --We check the node to the left
            elseif ((currentNode.x + 1) == tempNode.x) and (currentNode.y == tempNode.y)and not(currentNode == tempNode) and tempNode.isWalkable and not tempNode.visited then
                tempNode.visited = true
                tempNode.parent = currentNode
                neighborNodes.left = tempNode
                leftWalkable = true
                return tempNode
            --We check the node to the bottom
            elseif (currentNode.y - 1 == tempNode.y) and (currentNode.x == tempNode.x) and not(currentNode == tempNode) and tempNode.isWalkable and not tempNode.visited then 
                tempNode.visited = true
                tempNode.parent = currentNode
                neighborNodes.bottom = tempNode
                bottomWalkable = true
                return tempNode

            --We check the node to the top
            elseif (currentNode.y + 1 == tempNode.y) and (currentNode.x == tempNode.x) and not(currentNode == tempNode) and tempNode.isWalkable and not tempNode.visited then 
                tempNode.visited = true
                tempNode.parent = currentNode
                neighborNodes.top = tempNode
                topWalkable = true
                return tempNode
            end
        end
        return currentNode.parent
    end
    
    function ct:BackTrace(nodePath, targetNode)
        local currentNode = targetNode
        while currentNode.parent ~= nil do
            table.insert(nodePath, currentNode)
            currentNode = currentNode.parent
        end
        self.pathFound = nodePath
    end

--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------       
    function ct:CheckEnd(graph, goal)
        local goalFound = false
        local planes = 0
        local walls = 0
        for i = 1, #graph do
            if graph[i] == goal then goalFound = true end
            if graph[i] ~= goal and graph[i].isWalkable then planes = planes + 1 end
            if graph[i] ~= goal and not graph[i].isWalkable then walls = walls + 1 end
        end
        return planes
    end
    
--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------   

    function ct:ContourTracing(graph, startNode, goalNode)
        local vistedNodes = {}
        local stack = s.init()
        
        startNode.parent = nil
        startNode.visited = true
        stack.push(startNode)
        table.insert(vistedNodes,startNode)
        
        local numberOfWalkables = ct.CheckEnd(graph, goalNode)
        
        while true do
            -- if stack.size == numberOfWalkables then
            --     return -1
            -- end
            
            local current = stack.pop()
            if current == goalNode then
                self:BackTrace(stack.data, goalNode)
                return
             end
            
            local child = self:CheckChildren(current, graph)
                if child ~= nil then
                    stack.push(child)
                    table.insert(vistedNodes, child)
                end

       end
       local bla = 0
    end
    return ct
end

return contour