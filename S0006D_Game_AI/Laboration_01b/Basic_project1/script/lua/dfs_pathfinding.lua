
local s = require "script/lua/stack"
local depth = {}

function depth.init()
    local dfs = {}
    dfs.pathFound = {}
    
 --------------------------------------------------------------------------------------   
 --------------------------------------------------------------------------------------       
    function dfs:TableContainsNode(nodeTable, node)
        for placeHolder, Node in ipairs(nodeTable) do
            if Node == currentNode then
                return true
            end
        end
        return false
    end
  --------------------------------------------------------------------------------------   
 --------------------------------------------------------------------------------------   
 
    function dfs:IsTheSameNode(nodeA, nodeB)
        return nodeA == nodeB
    end
 
 
 --------------------------------------------------------------------------------------   
 --------------------------------------------------------------------------------------   
    function dfs:CheckChildren(currentNode, nodeList, visitedList)
        local neighborNodes = {}
        
        local rightWalkable = false -- local variable to prevent cutting corners
        local leftWalkable = false -- local variable to prevent cutting corners
        local topWalkable = false -- local variable to prevent cutting corners
        local bottomWalkable = false -- local variable to prevent cutting corners
        
        local currentPos = stingray.Vector3(currentNode.x, currentNode.y,0)
        for placeHolder, tempNode in ipairs(nodeList) do
            
            --We check the node to the left
            if ((currentPos.x + 1) == tempNode.x) and (currentPos.y == tempNode.y)and (not self:IsTheSameNode(currentNode,tempNode)) and tempNode.isWalkable and tempNode.visited == false then
                tempNode.visited = true
                tempNode.parent = currentNode
                table.insert(neighborNodes, tempNode)
                leftWalkable = true
                
            --We check the node to the right
            elseif (currentPos.x - 1 == tempNode.x) and (currentPos.y == tempNode.y) and (not self:IsTheSameNode(currentNode,tempNode)) and tempNode.isWalkable and tempNode.visited == false then
                tempNode.visited = true
                tempNode.parent = currentNode
                table.insert(neighborNodes, tempNode)
                rightWalkable = true
                
            --We check the node to the top
            elseif (currentPos.y + 1 == tempNode.y) and (currentPos.x == tempNode.x)and  (not self:IsTheSameNode(currentNode,tempNode)) and tempNode.isWalkable and tempNode.visited == false then 
                tempNode.visited = true
                tempNode.parent = currentNode
                table.insert(neighborNodes, tempNode)
                topWalkable = true
                
            --We check the node to the bottom
            elseif (currentPos.y - 1 == tempNode.y) and (currentPos.x == tempNode.x) and (not self:IsTheSameNode(currentNode,tempNode)) and tempNode.isWalkable and tempNode.visited == false then 
                tempNode.visited = true
                tempNode.parent = currentNode
                table.insert(neighborNodes, tempNode)
                bottomWalkable = true
            end
            
            --We check the node to the top-left
            if ((currentPos.x + 1) == tempNode.x) and ((currentPos.y + 1) == tempNode.y) and  (not self:IsTheSameNode(currentNode,tempNode)) and tempNode.isWalkable and tempNode.visited == false and leftWalkable and topWalkable then 
                tempNode.visited = true
                tempNode.parent = currentNode
                table.insert(neighborNodes, tempNode)
                
            --We check the node to the bottom-left
            elseif ((currentPos.x + 1) == tempNode.x) and ((currentPos.y - 1) == tempNode.y) and  (not self:IsTheSameNode(currentNode,tempNode)) and tempNode.isWalkable and tempNode.visited == false and leftWalkable and bottomWalkable then 
                tempNode.visited = true
                tempNode.parent = currentNode
                table.insert(neighborNodes, tempNode)
            
            --We check the node to the top-right
            elseif ((currentPos.x - 1) == tempNode.x) and ((currentPos.y + 1) == tempNode.y) and  (not self:IsTheSameNode(currentNode,tempNode)) and tempNode.isWalkable and tempNode.visited == false and rightWalkable and topWalkable then 
                tempNode.visited = true
                tempNode.parent = currentNode
                table.insert(neighborNodes, tempNode)
            
            --We check the node to the bottom-right
            elseif ((currentPos.x - 1) == tempNode.x) and ((currentPos.y - 1) == tempNode.y) and (not self:IsTheSameNode(currentNode,tempNode)) and tempNode.isWalkable and tempNode.visited == false and rightWalkable and bottomWalkable then
                tempNode.visited = true
                tempNode.parent = currentNode
                table.insert(neighborNodes, tempNode)
            end
            if table.getn(neighborNodes) == 8 then
                break
            end
        end
        return neighborNodes
    end
    
    function dfs:BackTrace(nodePath, targetNode)
        local currentNode = targetNode
        while currentNode.parent ~= nil do
            table.insert(nodePath, currentNode)
            currentNode = currentNode.parent
        end
        self.pathFound = nodePath
    end
--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------   

    function dfs:DepthFirstSearch(graph, startNode, goalNode)
        local vistedNodes = {}
        local stack = s.init()
        
        startNode.parent = nil
        startNode.visited = true
        stack.push(startNode)
        table.insert(vistedNodes,startNode)
        
        while stack.size > 0 do
            local current = stack.pop()
            if current == goalNode then
                self:BackTrace({}, goalNode)
                return
            end
            
            local childrenNodes = dfs:CheckChildren(current, graph, visited)
            for temp, child in ipairs(childrenNodes) do
                if not self:TableContainsNode(vistedNodes, child) then
                    table.insert(vistedNodes, child)
                    stack.push(child)
                end
             end
       end
    end 
    return dfs
end --End of class

return depth