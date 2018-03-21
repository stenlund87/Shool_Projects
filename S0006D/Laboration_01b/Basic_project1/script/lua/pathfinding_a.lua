
Star = {}

function Star:init()
    local a_star = {}
    
    a_star.INF = 1/0
    
    --Function to calculate the H value of the node we are at with Manhattan Distance
    function a_star:ManhattanDistanceH(currentNode, goalNode)
        local x2 = math.abs(goalNode.x)
        local x1 = math.abs(currentNode.x)
        local y2 = math.abs(goalNode.y)
        local y1 = math.abs(currentNode.y)
        return ((x2-x1) + (y2-y1))*10
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
        return neighbor.isWalkable
    end
    
    --Function to check the lowest F-score for the neighboring nodes
    --@Param nodeList, the open list or the closed list
    --@Return bestNode, the best node to go to
    function a_star:LowestFScore(nodeList, Fscore)
        local lowestFScore = self.INF
        local bestNode = nil
            for placeHoler, Node in ipairs(nodeList) do
                local score = Node.FValue
                if score < lowestFScore then
                    lowestFScore = score
                    bestNode = Node
                end
            end
        return bestNode
    end
    
    --Function to check if the node is the same
    --@Param NodeA, NodeB
    --@Return boolean value
    function a_star:NodeIsTheSame(nodeA, nodeB)
        return nodeA == nodeB
    end
    
    --Function to check the current Node's neighbors
    --@Param currentNode, the node we are currently on
    --@Param neighboringNodes, a list of neighboring nodes
    --@Return NodeList, a list of neigboring nodes
    function a_star:CheckNeighbors(currentNode, Nodes, closed, mapWidth)
        local neighborNodes = {}
        local currentPos = stingray.Vector3(currentNode.x, currentNode.y,0) --local variable just to keep it simple that we are checking from the current position
        local checkIndex = (currentPos.y*mapWidth) + math.abs(currentPos.x1) +1
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
        
        local tempNode = nil
        
       -- for placeHolder, Nodes[] in ipairs(Nodes) do
            
            --We check for the left neighbor
            if (self:NodeIsValid(Nodes[leftNode])) and (self.NotInNodeList(closed, Nodes[leftNode])) then
                if Nodes[leftNode].visited == false then
                    Nodes[leftNode].valueG = currentNode.valueG + 10
                    Nodes[leftNode].visited = true
                end
                table.insert(neighborNodes, Nodes[leftNode])
                leftWalkable = true
            end
            --We check for the right neighbor
            if (self:NodeIsValid(Nodes[rightNode])) and (self.NotInNodeList(closed, Nodes[rightNode])) then
                if Nodes[rightNode].visited == false then
                    Nodes[rightNode].valueG = currentNode.valueG + 10
                    Nodes[rightNode].visited = true
                end
                table.insert(neighborNodes, Nodes[rightNode])
                rightWalkable = true
             end 
            --We check for the top neighbor
            if (self:NodeIsValid(Nodes[topNode])) and (self.NotInNodeList(closed, Nodes[topNode])) then 
                if Nodes[topNode].visited == false then
                    Nodes[topNode].valueG = currentNode.valueG + 10
                    Nodes[topNode].visited = true
                end
                table.insert(neighborNodes, Nodes[topNode])
                topWalkable = true
            end
            --We check for the bottom neighbor
            if (self:NodeIsValid(Nodes[bottomNode])) and (self.NotInNodeList(closed, Nodes[bottomNode])) then 
                if Nodes[bottomNode].visited == false then
                    Nodes[bottomNode].valueG = currentNode.valueG + 10
                    Nodes[bottomNode].visited = true
                end
                table.insert(neighborNodes, Nodes[bottomNode])
                bottomWalkable = true
            end
            
            --We check for the top-left neighbor
            if (self:NodeIsValid(Nodes[topLeftNode])) and (self.NotInNodeList(closed, Nodes[topLeftNode])) and leftWalkable and topWalkable then 
                if Nodes[topLeftNode].visited == false then
                    Nodes[topLeftNode].valueG = currentNode.valueG + 14
                    Nodes[topLeftNode].visited = true
                end
                table.insert(neighborNodes, Nodes[topLeftNode])
            end   
            --We check for the bottom-left neighbor
            if (self:NodeIsValid(Nodes[bottomLeftNode])) and (self.NotInNodeList(closed, Nodes[bottomLeftNode])) and leftWalkable and bottomWalkable then 
                if Nodes[bottomLeftNode].visited == false then
                    Nodes[bottomLeftNode].valueG = currentNode.valueG + 14
                    Nodes[bottomLeftNode].visited = true
                end
                table.insert(neighborNodes, Nodes[bottomLeftNode])
           end     
            --We check for the top-right neighbor
            if (self:NodeIsValid(Nodes[topRightNode])) and (self.NotInNodeList(closed, Nodes[topRightNode])) and rightWalkable and topWalkable then 
                if Nodes[topRightNode].visited == false then
                    Nodes[topRightNode].valueG = currentNode.valueG + 14
                    Nodes[topRightNode].modified = true
                end
                table.insert(neighborNodes, Nodes[topRightNode])
            end
            --We check for the bottom-right neighbor
            if (self:NodeIsValid(Nodes[bottomRightNode])) and (self.NotInNodeList(closed, Nodes[bottomRightNode])) and rightWalkable and bottomWalkable then
                if Nodes[bottomRightNode].visited == false then
                    Nodes[bottomRightNode].valueG = currentNode.valueG + 14
                    Nodes[bottomRightNode].visited = true
                end
                table.insert(neighborNodes, Nodes[bottomRightNode])
            end
        return neighborNodes
    end
    
    --Function to check if currentNode is not in list
    --@Param nodeList, the open or closed list
    --@Param currentNode, the current node we are standing on
    --@Return boolean value
    function a_star:NotInNodeList(nodeList, currentNode)
        for placeHolder, Node in ipairs(nodeList) do
            if Node == currentNode then
                return false
            end
        end
        return true
    end
    
    --Function to remove a node from list
    --@Param nodeList, the open or closed list
    --@Param curretnNode, the current node we are on
    function a_star:RemoveNode(nodeList, currentNode)
        for index, Node in ipairs(nodeList) do
            if Node == currentNode then 
                nodeList[index] = nodeList[#nodeList]
                nodeList[#nodeList] = nil
                break
            end
        end
    end
    
    --Function to check the path we have found
    --@Param foundPath, the path we currently have
    --@Param map, a map
    --@Param currentNode, the node we are currently on
    --@Return an list with the best path to the goal
    function a_star:UnravelPath(foundPath, currentNode)
        while currentNode.parent ~= nil do --When parent is nil we are at startNode
            table.insert(foundPath, currentNode)
            currentNode = currentNode.parent
        end
         return foundPath
    end
    
    
    function a_star:AStar(start, goal, nodes, mapWidth)
        local openList = { start }
        local closedList = {}
        start.valueG = 0
        start.valueH = self:ManhattanDistanceH(start,goal)
        start.SetFValue()
        start.parent = nil
        while #openList > 0 do
            
            local current = self:LowestFScore(openList, start)
            if current == goal then
                local currentPath = self:UnravelPath({}, goal)
                table.insert(currentPath, start)
                self.bestPath = currentPath
                return
            end
            
            self:RemoveNode(openList, current)
            table.insert(closedList, current)
            
            local neighborNodes = self:CheckNeighbors(current, nodes, openList, mapWidth)
            for temp, neighbor in ipairs(neighborNodes) do
                if self:NotInNodeList(closedList, neighbor) then
                    local notCertainGScore = current.valueG + self:DistanceBetweenNodes(current, neighbor)
                    
                    if self:NotInNodeList(openList, neighbor) or notCertainGScore < neighbor.valueG then
                        neighbor.parent = current
                        neighbor.valueH = self:ManhattanDistanceH(neighbor, goal)
                        neighbor:SetFValue()
                        
                        if self:NotInNodeList(openList, neightbor) then
                            table.insert(openList, neighbor)
                        end
                    end
                end
            end
        end
        return nil --There is no path to the goal
    end
    
    return a_star
end

return Star