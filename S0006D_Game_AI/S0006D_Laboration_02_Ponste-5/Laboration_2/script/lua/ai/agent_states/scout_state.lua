local m_abs = math.abs
local m_floor = math.floor
local m_ceil = math.ceil

Scout_State = {}
totalScout = 0

---------------------------------------------------
---------------------------------------------------

function Scout_State:Enter(agent)
    Entity_Manager:ScoutMap(agent)
    agent.currentIndex = #agent.currentPath
end--End of Enter
---------------------------------------------------
---------------------------------------------------

--Method that for given agent executes the code
--@Param agent, the entity you want to execute the code
--@Param delta_time, time between frames
function Scout_State:Execute(agent, delta_time)
    local directionX = 0
    local directionY = 0
    local speed = 1
    local model = agent.agentModel
    local currentPos = stingray.Vector3(0,0,0)
    local standingOnIndex = 0
    local rightNode = 0
    local leftNode = 0
    local topNode = 0
    local bottomNode = 0
    local topLeftNode = 0
    local topRightNode = 0
    local bottomLeftNode = 0
    local bottomRightNode = 0
    

    --Safety measure to ensure that we dont go below 1 in index
    if agent.currentIndex < 2 then
        agent.currentPath = nil
        agent:FSM_ChangeState(Idle_State)
        return
    end
    
    --Checks if we are near enough to the next node to decrease the index
    if (m_abs(agent.currentPath[agent.currentIndex - 1].x - agent.x))< 0.1 and (m_abs(agent.currentPath[agent.currentIndex - 1].y - agent.y))< 0.1 then
        agent.currentIndex = agent.currentIndex - 1
        agent.x = agent.currentPath[agent.currentIndex].x
        agent.y = agent.currentPath[agent.currentIndex].y
        
        --local currentPos = stingray.Vector3(agent.x,agent.y,0)
        currentPos = stingray.Vector3(agent.x,agent.y,0)
        standingOnIndex = (m_ceil(agent.y)*100+m_abs(m_ceil(agent.x)))+1
       
        rightNode = standingOnIndex+1
        leftNode = standingOnIndex-1
       
        topNode = ((currentPos.y-1)*100) + m_abs(currentPos.x1)+1
        bottomNode = ((currentPos.y+1)*100) + m_abs(currentPos.x1) +1
       
        topLeftNode = ((currentPos.y-1)*100) + m_abs(currentPos.x1)
        topRightNode = ((currentPos.y-1)*100) + m_abs(currentPos.x1)+2
       
        bottomLeftNode = ((currentPos.y+1)*100) + m_abs(currentPos.x1)
        bottomRightNode = ((currentPos.y+1)*100) + m_abs(currentPos.x1)+2
        
        --We check if the neighbor has a fog and deletes it if it has
        if Entity_Manager.worldMap[rightNode].fog ~= nil then 
            stingray.World.destroy_unit(stingray.Application.main_world(),Entity_Manager.worldMap[rightNode].fog)
            Entity_Manager.worldMap[rightNode].fog = nil 
            table.insert(Entity_Manager.discoveredWorld, rightNode)
            
            if Entity_Manager.worldMap[rightNode].hasTree == true and not Entity_Manager:CheckTree(rightNode) then
                Entity_Manager:CallWorker(rightNode)
            end
         end
    
        --We check if the neighbor has a fog and deletes it if it has        
        if Entity_Manager.worldMap[leftNode].fog ~= nil then 
            stingray.World.destroy_unit(stingray.Application.main_world(),Entity_Manager.worldMap[leftNode].fog)
            Entity_Manager.worldMap[leftNode].fog = nil 
            table.insert(Entity_Manager.discoveredWorld, leftNode)
            
            if Entity_Manager.worldMap[leftNode].hasTree == true and not Entity_Manager:CheckTree(leftNode) then
                Entity_Manager:CallWorker(leftNode)
            end
        end
        --We check if the neighbor has a fog and deletes it if it has        
        if Entity_Manager.worldMap[topNode].fog ~= nil then 
            stingray.World.destroy_unit(stingray.Application.main_world(),Entity_Manager.worldMap[topNode].fog)
            Entity_Manager.worldMap[topNode].fog = nil
            table.insert(Entity_Manager.discoveredWorld, topNode)
            
            if Entity_Manager.worldMap[topNode].hasTree == true and not Entity_Manager:CheckTree(topNode) then
                Entity_Manager:CallWorker(topNode)
            end
        end
        --We check if the neighbor has a fog and deletes it if it has        
        if Entity_Manager.worldMap[bottomNode].fog ~= nil then 
            stingray.World.destroy_unit(stingray.Application.main_world(),Entity_Manager.worldMap[bottomNode].fog)
            Entity_Manager.worldMap[bottomNode].fog = nil 
            table.insert(Entity_Manager.discoveredWorld, bottomNode)
            
            if Entity_Manager.worldMap[bottomNode].hasTree == true and not Entity_Manager:CheckTree(bottomNode) then
                Entity_Manager:CallWorker(bottomNode)
            end
        end
        --We check if the neighbor has a fog and deletes it if it has        
         if Entity_Manager.worldMap[topLeftNode].fog ~= nil then 
            stingray.World.destroy_unit(stingray.Application.main_world(),Entity_Manager.worldMap[topLeftNode].fog)
            Entity_Manager.worldMap[topLeftNode].fog = nil 
            table.insert(Entity_Manager.discoveredWorld, topLeftNode)
            
            if Entity_Manager.worldMap[topLeftNode].hasTree == true and not Entity_Manager:CheckTree(topLeftNode) then
                Entity_Manager:CallWorker(topLeftNode)
            end
        end
        --We check if the neighbor has a fog and deletes it if it has        
         if Entity_Manager.worldMap[topRightNode].fog ~= nil then 
             stingray.World.destroy_unit(stingray.Application.main_world(),Entity_Manager.worldMap[topRightNode].fog)
            Entity_Manager.worldMap[topRightNode].fog = nil
            table.insert(Entity_Manager.discoveredWorld, topRightNode)
            
            if Entity_Manager.worldMap[topRightNode].hasTree == true and not Entity_Manager:CheckTree(topRightNode) then
                Entity_Manager:CallWorker(topRightNode)
            end
            
        end
        --We check if the neighbor has a fog and deletes it if it has        
         if Entity_Manager.worldMap[bottomLeftNode].fog ~= nil then 
             stingray.World.destroy_unit(stingray.Application.main_world(),Entity_Manager.worldMap[bottomLeftNode].fog)
            Entity_Manager.worldMap[bottomLeftNode].fog = nil
            table.insert(Entity_Manager.discoveredWorld, bottomLeftNode)
            
            if Entity_Manager.worldMap[bottomLeftNode].hasTree == true and not Entity_Manager:CheckTree(bottomLeftNode) then
                Entity_Manager:CallWorker(bottomLeftNode)
            end
            
        end
        --We check if the neighbor has a fog and deletes it if it has        
        if Entity_Manager.worldMap[bottomRightNode].fog ~= nil then 
            stingray.World.destroy_unit(stingray.Application.main_world(),Entity_Manager.worldMap[bottomRightNode].fog)
            Entity_Manager.worldMap[bottomRightNode].fog = nil
            table.insert(Entity_Manager.discoveredWorld, bottomRightNode)
            
            if Entity_Manager.worldMap[bottomRightNode].hasTree == true and not Entity_Manager:CheckTree(bottomRightNode) then
                Entity_Manager:CallWorker(bottomRightNode)
            end
            
        end
        
        --If we are at the first element of the table we get a new path to go and changes state to self
        if agent.currentIndex == 1 then
            agent.currentPath = nil
            Entity_Manager:ScoutMap(agent)
            agent:FSM_ChangeState(self)
            agent.endReached = true
            agent.coaler = true
            return
        end
    end

     speed = agent.currentPath[agent.currentIndex].walkSpeed
     local aim = stingray.Vector3(agent.currentPath[agent.currentIndex - 1].x, agent.currentPath[agent.currentIndex - 1].y, 0)-stingray.Vector3(agent.x, agent.y, 0)
     local move = stingray.Vector3.normalize(aim)*delta_time*speed*10
     stingray.Unit.set_local_position(model, 1,move+stingray.Vector3(agent.x,agent.y,0))
    -- end
    agent.x = agent.x + move.x
    agent.y = agent.y + move.y

    stingray.Unit.set_local_position(model, 1, stingray.Vector3(agent.x,agent.y,0))
    nextPos = nil
    model = nil
    move = nil
    aim = nil
    --collectgarbage()
    --return
end--End of Execute

---------------------------------------------------
---------------------------------------------------

function Scout_State:Exit(agent)
    agent.currentPath = nil
    --collectgarbage()
    agent.currentPath = {}
end

---------------------------------------------------
---------------------------------------------------
return Scout_State