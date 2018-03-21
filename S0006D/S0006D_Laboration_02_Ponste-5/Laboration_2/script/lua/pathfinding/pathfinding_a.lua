
Star = {}

function Star:init()
    local a_star = {}
    a_star.INF = 1/0
    a_star.bestPath = {}
    
    --Function to calculate the H value of the node we are at with Manhattan Distance
    function a_star:ManhattanDistanceH(currentNode, goalNode)
        if goalNode ~= nil then
            local x2 = math.abs(goalNode.x)
            local x1 = math.abs(currentNode.x)
            local y2 = math.abs(goalNode.y)
            local y1 = math.abs(currentNode.y)
            return ((x2-x1) + (y2-y1))*10
        end
    end

    function a_star:DistanceBetweenNodes(nodeA, nodeB)
        local x2 = math.abs(nodeB.x)
        local x1 = math.abs(nodeA.x)
        local y2 = math.abs(nodeB.y)
        local y1 = math.abs(nodeA.y)
        return math.sqrt(math.pow(x2-x1,2) + math.pow(y2-y1,2)) 
    end

    --Function to check if the node is Valid to walk on
    --@Param Node, temp argument
    --@Return boolean isWalkable
    function a_star:NodeIsValid(neighbor)
        if neighbor ~= nil then
            return neighbor.isWalkable
        else
            return false
        end
    end
    
    --Function to check the lowest F-score for the neighboring nodes
    --@Param nodeList, the open list or the closed list
    --@Return bestNode, the best node to go to
    function a_star:LowestFScore(nodeList, Fscore)
        local lowestFScore = self.INF
        local score = 0
        local bestNode = nil
            for placeHoler, Node in ipairs(nodeList) do
                score = Node.FValue
                if score < lowestFScore then
                    lowestFScore = score
                    bestNode = Node
                    bestNode.openIndex = placeHoler
                end
            end
        return bestNode
    end
    
    --Function to check the current Node's neighbors
    --@Param currentNode, the node we are currently on
    --@Param neighboringNodes, a list of neighboring nodes
    --@Return NodeList, a list of neigboring nodes
    function a_star:CheckNeighbors(currentNode, Nodes, closed, mapWidth)
        local neighborNodes = {}
        local currentPos = stingray.Vector3(currentNode.x, currentNode.y,0) --local variable just to keep it simple that we are checking from the current position
        local checkIndex = (currentPos.y*mapWidth) + math.abs(currentPos.x1)+1
        local rightWalkable = false -- local variable to prevent cutting corners
        local leftWalkable = false -- local variable to prevent cutting corners
        local topWalkable = false -- local variable to prevent cutting corners
        local bottomWalkable = false -- local variable to prevent cutting corners
        
        local rightNode = checkIndex+1
        local leftNode = checkIndex-1
        
        local topNode = ((currentPos.y-1)*mapWidth) + math.abs(currentPos.x1)+1
        local bottomNode = ((currentPos.y+1)*mapWidth) + math.abs(currentPos.x1) +1
        
        local topLeftNode = ((currentPos.y-1)*mapWidth) + math.abs(currentPos.x1)
        local topRightNode = ((currentPos.y-1)*mapWidth) + math.abs(currentPos.x1)+2
        
        local bottomLeftNode = ((currentPos.y+1)*mapWidth) + math.abs(currentPos.x1)
        local bottomRightNode = ((currentPos.y+1)*mapWidth) + math.abs(currentPos.x1)+2
            
            --We check for the left neighbor
            if (self:NodeIsValid(Nodes[leftNode])) then
                if Nodes[leftNode].visited == false then
                    Nodes[leftNode].valueG = currentNode.valueG + 10
                    Nodes[leftNode].visited = true
                    Nodes[leftNode].index = leftNode
                    --stingray.Unit.set_material(Nodes[leftNode].plane,"Material #26", "content/materials/black")
                end
                -- if Nodes[leftNode].inOpenList == true and Nodes[leftNode].valueG < currentNode.valueG then
                --     Nodes[leftNode].parent = currentNode
                --     Nodes[leftNode].valueG = currentNode.valueG + 10
                --     Nodes[leftNode]:SetFValue()
                -- end
                
                table.insert(neighborNodes, Nodes[leftNode])
                leftWalkable = true
            end
            --We check for the right neighbor
            if (self:NodeIsValid(Nodes[rightNode])) then
                if Nodes[rightNode].visited == false then
                    Nodes[rightNode].valueG = currentNode.valueG + 10
                    Nodes[rightNode].visited = true
                    Nodes[rightNode].index = rightNode
                    --stingray.Unit.set_material(Nodes[rightNode].plane,"Material #26", "content/materials/black")
                end
                -- if Nodes[rightNode].inOpenList == true and Nodes[rightNode].valueG < currentNode.valueG then
                --     Nodes[rightNode].parent = currentNode
                --     Nodes[rightNode].valueG = currentNode.valueG + 10
                --     Nodes[rightNode]:SetFValue()
                -- end
                
                table.insert(neighborNodes, Nodes[rightNode])
                rightWalkable = true
             end 
            --We check for the top neighbor
            if (self:NodeIsValid(Nodes[topNode])) then 
                if Nodes[topNode].visited == false then
                    Nodes[topNode].valueG = currentNode.valueG + 10
                    Nodes[topNode].visited = true
                    --stingray.Unit.set_material(Nodes[topNode].plane,"Material #26", "content/materials/black")
                end
                -- if Nodes[topNode].inOpenList == true and Nodes[topNode].valueG < currentNode.valueG then
                --     Nodes[topNode].parent = currentNode
                --     Nodes[topNode].valueG = currentNode.valueG + 10
                --     Nodes[topNode]:SetFValue()
                -- end
                
                table.insert(neighborNodes, Nodes[topNode])
                topWalkable = true
            end
            --We check for the bottom neighbor
            if (self:NodeIsValid(Nodes[bottomNode])) then 
                if Nodes[bottomNode].visited == false then
                    Nodes[bottomNode].valueG = currentNode.valueG + 10
                    Nodes[bottomNode].visited = true
                    Nodes[bottomNode].index = bottomNode
                    --stingray.Unit.set_material(Nodes[bottomNode].plane,"Material #26", "content/materials/black")
                end
                -- if Nodes[bottomNode].inOpenList == true and Nodes[bottomNode].valueG < currentNode.valueG then
                --     Nodes[bottomNode].parent = currentNode
                --     Nodes[bottomNode].valueG = currentNode.valueG + 10
                --     Nodes[bottomNode]:SetFValue()
                -- end
                table.insert(neighborNodes, Nodes[bottomNode])
                bottomWalkable = true
            end
            
            --We check for the top-left neighbor
            if (self:NodeIsValid(Nodes[topLeftNode])) and leftWalkable and topWalkable then 
                if Nodes[topLeftNode].visited == false then
                    Nodes[topLeftNode].valueG = currentNode.valueG + 14
                    Nodes[topLeftNode].visited = true
                    Nodes[topLeftNode].index = topLeftNode
                    --stingray.Unit.set_material(Nodes[topLeftNode].plane,"Material #26", "content/materials/black")
                end
                if Nodes[topLeftNode].inOpenList == true and Nodes[topLeftNode].valueG < currentNode.valueG then
                    Nodes[topLeftNode].parent = currentNode
                    Nodes[topLeftNode].valueG = currentNode.valueG + 14
                    Nodes[topLeftNode]:SetFValue()
                end
                table.insert(neighborNodes, Nodes[topLeftNode])
            end   
            --We check for the bottom-left neighbor
            if (self:NodeIsValid(Nodes[bottomLeftNode])) and leftWalkable and bottomWalkable then 
                if Nodes[bottomLeftNode].visited == false then
                    Nodes[bottomLeftNode].valueG = currentNode.valueG + 14
                    Nodes[bottomLeftNode].visited = true
                    Nodes[bottomLeftNode].index = bottomLeftNode
                    --stingray.Unit.set_material(Nodes[bottomLeftNode].plane,"Material #26", "content/materials/black")

                end
                if Nodes[bottomLeftNode].inOpenList == true and Nodes[bottomLeftNode].valueG < currentNode.valueG then
                    Nodes[bottomLeftNode].parent = currentNode
                    Nodes[bottomLeftNode].valueG = currentNode.valueG + 14
                    Nodes[bottomLeftNode]:SetFValue()
                end
                table.insert(neighborNodes, Nodes[bottomLeftNode])
           end     
            --We check for the top-right neighbor
            if (self:NodeIsValid(Nodes[topRightNode])) and rightWalkable and topWalkable then 
                if Nodes[topRightNode].visited == false then
                    Nodes[topRightNode].valueG = currentNode.valueG + 14
                    Nodes[topRightNode].modified = true
                    Nodes[topRightNode].index = topRightNode
                   --stingray.Unit.set_material(Nodes[topRightNode].plane,"Material #26", "content/materials/black")
                end
                if Nodes[topRightNode].inOpenList == true and Nodes[topRightNode].valueG < currentNode.valueG then
                    Nodes[topRightNode].parent = currentNode
                    Nodes[topRightNode].valueG = currentNode.valueG + 14
                    Nodes[topRightNode]:SetFValue()
                end                
                
                table.insert(neighborNodes, Nodes[topRightNode])
            end
            --We check for the bottom-right neighbor
            if (self:NodeIsValid(Nodes[bottomRightNode])) and rightWalkable and bottomWalkable then
                if Nodes[bottomRightNode].visited == false then
                    Nodes[bottomRightNode].valueG = currentNode.valueG + 14
                    Nodes[bottomRightNode].visited = true
                    Nodes[bottomRightNode].index = bottomRightNode
                   --stingray.Unit.set_material(Nodes[bottomRightNode].plane,"Material #26", "content/materials/black")
                end
                if Nodes[bottomRightNode].inOpenList == true and Nodes[bottomRightNode].valueG < currentNode.valueG then
                    Nodes[bottomRightNode].parent = currentNode
                    Nodes[bottomRightNode].valueG = currentNode.valueG + 14
                    Nodes[bottomRightNode]:SetFValue()
                end       
                table.insert(neighborNodes, Nodes[bottomRightNode])
            end
        return neighborNodes
    end
    
    --Function to check the path we have found
    --@Param foundPath, the path we currently have
    --@Param map, a map
    --@Param currentNode, the node we are currently on
    --@Return an list with the best path to the goal
    function a_star:UnravelPath(foundPath, currentNode, bool)
        while currentNode.parent ~= nil do --When parent is nil we are at startNode
            if bool == true then
            end
            currentNode.visited = false
            table.insert(foundPath, currentNode)
            
            currentNode = currentNode.parent
        end
        currentNode.visited = false
        return foundPath
    end
    
    function a_star:ResetNodes(NodeList)
        local startTime = os.clock()
        
        for temp, node in ipairs(NodeList) do
            node.visited = false
            node.parent = nil
        end
        local endTime = os.clock()
      
    end
    
    function a_star:AStar(start, goal, nodes, mapWidth,it_is_a_worker)
        --self:ResetNodes(nodes)
        local openList = { start }
        local closedList = {}
        start.valueG = 0
        start.valueH = self:ManhattanDistanceH(start,goal)
        start.SetFValue()
        start.visited = true
        start.parent = nil
        start.openIndex = 1
        start.inOpenList = true
        start.inClosedList = false
        local current = nil
        local neighborNodes = {}
        local notCertainGScore = 0
        while #openList > 0 do
            current = self:LowestFScore(openList, start)
            if current == goal then

                self:UnravelPath(self.bestPath, goal,it_is_a_worker)
                table.insert(self.bestPath,start)
                openList = nil
                closedList = nil
                current = nil
                neighborNodes = nil
                --collectgarbage()
                return
            end
            table.remove(openList, current.openIndex)
            current.inOpenList = false
            table.insert(closedList, current)
            current.inClosedList = true
            if it_is_a_worker == true then
                neighborNodes = self:CheckNeighborsForWorker(current, nodes, closedList, mapWidth)
            else
                neighborNodes = self:CheckNeighbors(current, nodes, closedList, mapWidth)
            end
            for temp, neighbor in ipairs(neighborNodes) do
                if neighbor.inClosedList == false then
                    notCertainGScore = current.valueG + self:DistanceBetweenNodes(current, neighbor)
                    if neighbor.inOpenList ==  false then
                        neighbor.parent = current
                        neighbor.valueH = self:ManhattanDistanceH(neighbor, goal)
                        neighbor:SetFValue()
                        if neighbor.inOpenList == false then
                            table.insert(openList, neighbor)
                            neighbor.inOpenList = true
                        end
                    end
                end
            end
        end
        openList = nil
        closedList = nil
        --collectgarbage()
        return nil --There is no path to the goal
    end
----------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------

function a_star:CheckNeighborsForWorker(currentNode, Nodes, closed, mapWidth)
        local neighborNodes = {}
        local currentPos = stingray.Vector3(currentNode.x, currentNode.y,0) --local variable just to keep it simple that we are checking from the current position
        local checkIndex = (currentPos.y*mapWidth) + math.abs(currentPos.x1)+1
        local rightWalkable = false -- local variable to prevent cutting corners
        local leftWalkable = false -- local variable to prevent cutting corners
        local topWalkable = false -- local variable to prevent cutting corners
        local bottomWalkable = false -- local variable to prevent cutting corners
        
        local rightNode = checkIndex+1
        local leftNode = checkIndex-1
        
        local topNode = ((currentPos.y-1)*mapWidth) + math.abs(currentPos.x1)+1
        local bottomNode = ((currentPos.y+1)*mapWidth) + math.abs(currentPos.x1) +1
        
        local topLeftNode = ((currentPos.y-1)*mapWidth) + math.abs(currentPos.x1)
        local topRightNode = ((currentPos.y-1)*mapWidth) + math.abs(currentPos.x1)+2
        
        local bottomLeftNode = ((currentPos.y+1)*mapWidth) + math.abs(currentPos.x1)
        local bottomRightNode = ((currentPos.y+1)*mapWidth) + math.abs(currentPos.x1)+2
            
            --We check for the left neighbor
            if (self:NodeIsValid(Nodes[leftNode])) and Nodes[leftNode].fog == nil then
                if Nodes[leftNode].visited == false then
                    Nodes[leftNode].valueG = currentNode.valueG + 10
                    Nodes[leftNode].visited = true
                    Nodes[leftNode].index = leftNode
                    --stingray.Unit.set_material(Nodes[leftNode].plane,"Material #26", "content/materials/black")
                end
                -- if Nodes[leftNode].inOpenList == true and Nodes[leftNode].valueG < currentNode.valueG then
                --     Nodes[leftNode].parent = currentNode
                --     Nodes[leftNode].valueG = currentNode.valueG + 10
                --     Nodes[leftNode]:SetFValue()
                -- end
                
                table.insert(neighborNodes, Nodes[leftNode])
                leftWalkable = true
            end
            --We check for the right neighbor
            if (self:NodeIsValid(Nodes[rightNode])) and Nodes[rightNode].fog == nil then
                if Nodes[rightNode].visited == false then
                    Nodes[rightNode].valueG = currentNode.valueG + 10
                    Nodes[rightNode].visited = true
                    Nodes[rightNode].index = rightNode
                    --stingray.Unit.set_material(Nodes[rightNode].plane,"Material #26", "content/materials/black")
                end
                -- if Nodes[rightNode].inOpenList == true and Nodes[rightNode].valueG < currentNode.valueG then
                --     Nodes[rightNode].parent = currentNode
                --     Nodes[rightNode].valueG = currentNode.valueG + 10
                --     Nodes[rightNode]:SetFValue()
                -- end
                
                table.insert(neighborNodes, Nodes[rightNode])
                rightWalkable = true
             end 
            --We check for the top neighbor
            if (self:NodeIsValid(Nodes[topNode])) and Nodes[topNode].fog == nil then 
                if Nodes[topNode].visited == false then
                    Nodes[topNode].valueG = currentNode.valueG + 10
                    Nodes[topNode].visited = true
                    --stingray.Unit.set_material(Nodes[topNode].plane,"Material #26", "content/materials/black")
                end
                -- if Nodes[topNode].inOpenList == true and Nodes[topNode].valueG < currentNode.valueG then
                --     Nodes[topNode].parent = currentNode
                --     Nodes[topNode].valueG = currentNode.valueG + 10
                --     Nodes[topNode]:SetFValue()
                -- end
                
                table.insert(neighborNodes, Nodes[topNode])
                topWalkable = true
            end
            --We check for the bottom neighbor
            if (self:NodeIsValid(Nodes[bottomNode])) and Nodes[bottomNode].fog == nil then 
                if Nodes[bottomNode].visited == false then
                    Nodes[bottomNode].valueG = currentNode.valueG + 10
                    Nodes[bottomNode].visited = true
                    Nodes[bottomNode].index = bottomNode
                    --stingray.Unit.set_material(Nodes[bottomNode].plane,"Material #26", "content/materials/black")
                end
                -- if Nodes[bottomNode].inOpenList == true and Nodes[bottomNode].valueG < currentNode.valueG then
                --     Nodes[bottomNode].parent = currentNode
                --     Nodes[bottomNode].valueG = currentNode.valueG + 10
                --     Nodes[bottomNode]:SetFValue()
                -- end
                table.insert(neighborNodes, Nodes[bottomNode])
                bottomWalkable = true
            end
            
            --We check for the top-left neighbor
            if (self:NodeIsValid(Nodes[topLeftNode])) and Nodes[topLeftNode].fog == nil and leftWalkable and topWalkable then 
                if Nodes[topLeftNode].visited == false then
                    Nodes[topLeftNode].valueG = currentNode.valueG + 14
                    Nodes[topLeftNode].visited = true
                    Nodes[topLeftNode].index = topLeftNode
                    --stingray.Unit.set_material(Nodes[topLeftNode].plane,"Material #26", "content/materials/black")
                end
                if Nodes[topLeftNode].inOpenList == true and Nodes[topLeftNode].valueG < currentNode.valueG then
                    Nodes[topLeftNode].parent = currentNode
                    Nodes[topLeftNode].valueG = currentNode.valueG + 14
                    Nodes[topLeftNode]:SetFValue()
                end
                table.insert(neighborNodes, Nodes[topLeftNode])
            end   
            --We check for the bottom-left neighbor
            if (self:NodeIsValid(Nodes[bottomLeftNode])) and Nodes[bottomLeftNode].fog == nil and leftWalkable and bottomWalkable then 
                if Nodes[bottomLeftNode].visited == false then
                    Nodes[bottomLeftNode].valueG = currentNode.valueG + 14
                    Nodes[bottomLeftNode].visited = true
                    Nodes[bottomLeftNode].index = bottomLeftNode
                    --stingray.Unit.set_material(Nodes[bottomLeftNode].plane,"Material #26", "content/materials/black")

                end
                if Nodes[bottomLeftNode].inOpenList == true and Nodes[bottomLeftNode].valueG < currentNode.valueG then
                    Nodes[bottomLeftNode].parent = currentNode
                    Nodes[bottomLeftNode].valueG = currentNode.valueG + 14
                    Nodes[bottomLeftNode]:SetFValue()
                end
                table.insert(neighborNodes, Nodes[bottomLeftNode])
           end     
            --We check for the top-right neighbor
            if (self:NodeIsValid(Nodes[topRightNode])) and Nodes[topRightNode].fog == nil and rightWalkable and topWalkable then 
                if Nodes[topRightNode].visited == false then
                    Nodes[topRightNode].valueG = currentNode.valueG + 14
                    Nodes[topRightNode].modified = true
                    Nodes[topRightNode].index = topRightNode
                   --stingray.Unit.set_material(Nodes[topRightNode].plane,"Material #26", "content/materials/black")
                end
                if Nodes[topRightNode].inOpenList == true and Nodes[rightNode].fog == nil and Nodes[topRightNode].valueG < currentNode.valueG then
                    Nodes[topRightNode].parent = currentNode
                    Nodes[topRightNode].valueG = currentNode.valueG + 14
                    Nodes[topRightNode]:SetFValue()
                end                
                
                table.insert(neighborNodes, Nodes[topRightNode])
            end
            --We check for the bottom-right neighbor
            if (self:NodeIsValid(Nodes[bottomRightNode])) and Nodes[bottomRightNode].fog == nil and rightWalkable and bottomWalkable then
                if Nodes[bottomRightNode].visited == false then
                    Nodes[bottomRightNode].valueG = currentNode.valueG + 14
                    Nodes[bottomRightNode].visited = true
                    Nodes[bottomRightNode].index = bottomRightNode
                   --stingray.Unit.set_material(Nodes[bottomRightNode].plane,"Material #26", "content/materials/black")
                end
                if Nodes[bottomRightNode].inOpenList == true  and Nodes[bottomRightNode].valueG < currentNode.valueG then
                    Nodes[bottomRightNode].parent = currentNode
                    Nodes[bottomRightNode].valueG = currentNode.valueG + 14
                    Nodes[bottomRightNode]:SetFValue()
                end       
                table.insert(neighborNodes, Nodes[bottomRightNode])
            end
        return neighborNodes
    end

----------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------
    return a_star
end

return Star