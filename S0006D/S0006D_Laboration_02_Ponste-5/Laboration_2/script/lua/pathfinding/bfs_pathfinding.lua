
local q = require "script/lua/pathfinding/queue"
BFS = {}
package.loaded[...] = BFS
BFS.pathFound = {}


--------------------------------------------------------------------------------------   
--------------------------------------------------------------------------------------   
function BFS:CheckChildren(currentNode, Nodes, visitedList,mapWidth)
    local Entity_Manager = require "script/lua/ai/entity_manager"
    local neighborNodes = {}
    
    local rightisWalkable = false -- local variable to prevent cutting corners
    local leftisWalkable = false -- local variable to prevent cutting corners
    local topisWalkable = false -- local variable to prevent cutting corners
    local bottomisWalkable = false -- local variable to prevent cutting corners
    
    local checkIndex = (currentNode.y*mapWidth) + math.abs(currentNode.x) +1

    local rightNode = checkIndex+1
    local leftNode = checkIndex-1
    
    local topNode = ((currentNode.y-1)*mapWidth) + math.abs(currentNode.x)+1
    local bottomNode = ((currentNode.y+1)*mapWidth) + math.abs(currentNode.x) +1
    
    local topLeftNode = ((currentNode.y-1)*mapWidth) + math.abs(currentNode.x)
    local topRightNode = ((currentNode.y-1)*mapWidth) + math.abs(currentNode.x)+2
    
    local bottomLeftNode = ((currentNode.y+1)*mapWidth) + math.abs(currentNode.x)
    local bottomRightNode = ((currentNode.y+1)*mapWidth) + math.abs(currentNode.x)+2
    --We check the node to the left
     --We check for the left neighbor
    if Nodes[leftNode].isWalkable == true and Nodes[leftNode].visited == false then
        Nodes[leftNode].visited = true
        Nodes[leftNode].index = leftNode
        leftisWalkable = true
        Nodes[leftNode].parent = currentNode
        if Nodes[leftNode].hasTree == true then
            table.insert(Entity_Manager.treeList, Nodes[leftNode])
        end
        table.insert(neighborNodes, Nodes[leftNode])
    end
    --We check for the right neighbor
    if Nodes[rightNode].isWalkable == true and Nodes[rightNode].visited == false then
        Nodes[rightNode].visited = true
        Nodes[rightNode].index = rightNode
        Nodes[rightNode].parent = currentNode
        rightisWalkable = true
        
        if Nodes[rightNode].hasTree == true then
            table.insert(Entity_Manager.treeList, Nodes[rightNode])
        end
        table.insert(neighborNodes, Nodes[rightNode])
     end 
    --We check for the top neighbor
    if Nodes[topNode].isWalkable == true and Nodes[topNode].visited == false then 
        Nodes[topNode].visited = true
        Nodes[topNode].parent = currentNode
        topisWalkable = true
        if Nodes[topNode].hasTree == true then
            table.insert(Entity_Manager.treeList, Nodes[topNode])
        end
        table.insert(neighborNodes, Nodes[topNode])
    end
    --We check for the bottom neighbor
    if Nodes[bottomNode].isWalkable == true and Nodes[bottomNode].visited == false then 
        Nodes[bottomNode].visited = true
        Nodes[bottomNode].index = bottomNode
        Nodes[bottomNode].parent = currentNode
        bottomisWalkable = true
        if Nodes[bottomNode].hasTree == true then
            table.insert(Entity_Manager.treeList, Nodes[bottomNode])
        end
        table.insert(neighborNodes, Nodes[bottomNode])
    end
    
    --We check for the top-left neighbor
    if Nodes[topLeftNode].isWalkable == true and Nodes[topLeftNode].visited == false and leftisWalkable and topisWalkable then 
        Nodes[topLeftNode].visited = true
        Nodes[topLeftNode].index = topLeftNode
        Nodes[topLeftNode].parent = currentNode
        if Nodes[topLeftNode].hasTree == true then
            table.insert(Entity_Manager.treeList, Nodes[topLeftNode])
        end
        table.insert(neighborNodes, Nodes[topLeftNode])
    end   
    --We check for the bottom-left neighbor
    if Nodes[bottomLeftNode].isWalkable == true and Nodes[bottomLeftNode].visited == false and leftisWalkable and bottomisWalkable then 
        Nodes[bottomLeftNode].visited = true
        Nodes[bottomLeftNode].index = bottomLeftNode
        Nodes[bottomLeftNode].parent = currentNode
        
        if Nodes[bottomLeftNode].hasTree == true then
            table.insert(Entity_Manager.treeList, Nodes[bottomLeftNode])
        end
        table.insert(neighborNodes, Nodes[bottomLeftNode])
   end     
    --We check for the top-right neighbor
    if Nodes[topRightNode].isWalkable == true and Nodes[topRightNode].visited == false and rightisWalkable and topisWalkable then 
        Nodes[topRightNode].modified = true
        Nodes[topRightNode].index = topRightNode
        Nodes[topRightNode].parent = currentNode
        
        if Nodes[topRightNode].hasTree == true then
            table.insert(Entity_Manager.treeList, Nodes[topRightNode])
        end
        table.insert(neighborNodes, Nodes[topRightNode])
    end
    --We check for the bottom-right neighbor
    if Nodes[bottomRightNode].isWalkable == true and Nodes[bottomRightNode].visited == false and rightisWalkable and bottomisWalkable then
        Nodes[bottomRightNode].visited = true
        Nodes[bottomRightNode].index = bottomRightNode
        Nodes[bottomRightNode].parent = currentNode
        
        if Nodes[bottomRightNode].hasTree == true then
            table.insert(Entity_Manager.treeList, Nodes[bottomRightNode])
        end
        table.insert(neighborNodes, Nodes[bottomRightNode])
    end
    return neighborNodes
end--End of CheckChildren()
--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------   

function BFS:FoundPath(nodePath, targetNode)
    local currentNode = targetNode
    while currentNode.parent ~= nil do
        table.insert(nodePath, currentNode)
        currentNode = currentNode.parent
    end
    self.pathFound = nodePath
end --End of FoundPath()
--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------   

function BFS:BreadthFirstSearch(graph, startNode, goalNode, width)
    local vistedNodes = {}
    local queue = q.init()
    
    startNode.parent = nil
    startNode.visited = true
    queue.push(startNode)
    table.insert(vistedNodes,startNode)
    
    while queue.size > 0 do
        local current = queue.pop()
        if current == goalNode then
            self:FoundPath({}, goalNode)
            return
        end
        
        local childrenNodes = BFS:CheckChildren(current, graph, visited,width)
        for temp, child in ipairs(childrenNodes) do
            if child.inOpenList == false then
                table.insert(vistedNodes, child)
                child.inOpenList = true
                queue.push(child)
            end
        end
   end
   self.pathFound = vistedNodes
end --End of BreadthFirstSearch()

--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------   
return BFS

--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------   
