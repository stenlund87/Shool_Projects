
--local Walk_State = Walk_State or require "script/lua/ai/agent_states/walk_state"
local m_abs = math.abs
local m_floor = math.floor
local m_ceil = math.ceil

Build_State = {}
package.loaded[...] = Build_State
local Idle_State = require "script/lua/ai/agent_states/idle_state"

function Build_State:Enter(agent)
    agent.waitTime = os.clock()
    
    agent.currentlyWorking = true
end--End of Enter
-----------------------------------------------------------
-----------------------------------------------------------

--Method that calculated the time run for each agent and increments spawns a ChamfBox when done
--Changes state to Idle when done
--@Param agent, the agent that will execute the code
--@Param delta_time, delta time from Project.Update()

function Build_State:Execute(agent,delta_time)
     local currentTime = os.clock()
     local runningTime = currentTime - agent.waitTime
     if(agent.y < 1) then agent.y = 1 end
    
     local standingOnIndex = (m_floor(agent.y)*100+ (m_ceil(m_abs(agent.x)))) --Calculate wich index we are currently on
     local rightNode = standingOnIndex+1
     local leftNode = standingOnIndex-1
     local topNode = standingOnIndex-100
     local bottomNode = standingOnIndex+100
       
     local topLeftNode = standingOnIndex-101
     local topRightNode = standingOnIndex - 99
       
     local bottomLeftNode = standingOnIndex+99
     local bottomRightNode = standingOnIndex+101
     
     --We wanna do this once
     if agent.doOnce == false then
        agent.doOnce = true
        Entity_Manager.treesCollected = Entity_Manager.treesCollected - 10
        Entity_Manager.numberOfBuildings = Entity_Manager.numberOfBuildings + 1
     end
     
     --Checks the right neighbor to see if we can spawn the chamfbox there
     if Entity_Manager.worldMap[rightNode].fog == nil and Entity_Manager.worldMap[rightNode].isWalkable == true and Entity_Manager.worldMap[rightNode].hasTree == false and runningTime >= 6 then 
        local building = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/props/ChamfBox",stingray.Vector3(Entity_Manager.worldMap[rightNode].x,Entity_Manager.worldMap[rightNode].y,0))
        stingray.Unit.set_local_scale(building,1,stingray.Vector3(0.2,0.2,0.2))
        table.insert(Entity_Manager.houseVector, rightNode)
        Entity_Manager.worldMap[rightNode].isWalkable = false
        
        agent.x = Entity_Manager.worldMap[rightNode].x -1
        agent.y = Entity_Manager.worldMap[rightNode].y
        stingray.Unit.set_local_position(agent.agentModel, 1, stingray.Vector3(agent.x,agent.y,0))
        
        agent:FSM_ChangeState(Idle_State)
        
     --Checks the left neighbor to see if we can spawn the chamfbox there
     elseif Entity_Manager.worldMap[leftNode].fog == nil and Entity_Manager.worldMap[leftNode].isWalkable == true and Entity_Manager.worldMap[leftNode].hasTree == false and runningTime >= 6 then
        local building = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/props/ChamfBox",stingray.Vector3(Entity_Manager.worldMap[leftNode].x,Entity_Manager.worldMap[leftNode].y,0))
        stingray.Unit.set_local_scale(building,1,stingray.Vector3(0.2,0.2,0.2))
        table.insert(Entity_Manager.houseVector, leftNode)
        Entity_Manager.worldMap[leftNode].isWalkable = false
        
        agent.x = Entity_Manager.worldMap[leftNode].x +1
        agent.y = Entity_Manager.worldMap[leftNode].y
        stingray.Unit.set_local_position(agent.agentModel, 1, stingray.Vector3(agent.x,agent.y,0))
        
        agent:FSM_ChangeState(Idle_State)
        
     --Checks the top neighbor to see if we can spawn the chamfbox there
     elseif Entity_Manager.worldMap[topNode].fog == nil and Entity_Manager.worldMap[topNode].isWalkable == true and Entity_Manager.worldMap[topNode].hasTree == false and runningTime >= 6 then
        local building = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/props/ChamfBox",stingray.Vector3(Entity_Manager.worldMap[topNode].x,Entity_Manager.worldMap[topNode].y,0))
        stingray.Unit.set_local_scale(building,1,stingray.Vector3(0.2,0.2,0.2))
        table.insert(Entity_Manager.houseVector, topNode)
        Entity_Manager.worldMap[topNode].isWalkable = false
        
        agent.x = Entity_Manager.worldMap[topNode].x
        agent.y = Entity_Manager.worldMap[topNode].y -1
        stingray.Unit.set_local_position(agent.agentModel, 1, stingray.Vector3(agent.x,agent.y,0))
        
        agent:FSM_ChangeState(Idle_State)
        
     --Checks the bottom neighbor to see if we can spawn the chamfbox there
     elseif Entity_Manager.worldMap[bottomNode].fog == nil and Entity_Manager.worldMap[bottomNode].isWalkable == true and Entity_Manager.worldMap[bottomNode].hasTree == false and runningTime >= 6 then
        local building = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/props/ChamfBox",stingray.Vector3(Entity_Manager.worldMap[bottomNode].x,Entity_Manager.worldMap[bottomNode].y,0))
        stingray.Unit.set_local_scale(building,1,stingray.Vector3(0.2,0.2,0.2))
        table.insert(Entity_Manager.houseVector, bottomNode)
        Entity_Manager.worldMap[bottomNode].isWalkable = false
        
        agent.x = Entity_Manager.worldMap[bottomNode].x
        agent.y = Entity_Manager.worldMap[bottomNode].y +1
        stingray.Unit.set_local_position(agent.agentModel, 1, stingray.Vector3(agent.x,agent.y,0))
        
        agent:FSM_ChangeState(Idle_State)
        
    --Checks the top-left neighbor to see if we can spawn the chamfbox there    
     elseif Entity_Manager.worldMap[topLeftNode].fog == nil and Entity_Manager.worldMap[topLeftNode].isWalkable == true and Entity_Manager.worldMap[topLeftNode].hasTree == false and runningTime >= 6 then 
        local building = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/props/ChamfBox",stingray.Vector3(Entity_Manager.worldMap[topLeftNode].x,Entity_Manager.worldMap[topLeftNode].y,0))
        stingray.Unit.set_local_scale(building,1,stingray.Vector3(0.2,0.2,0.2))
        table.insert(Entity_Manager.houseVector, topLeftNode)
        Entity_Manager.worldMap[topLeftNode].isWalkable = false
        
        agent.x = Entity_Manager.worldMap[topLeftNode].x +1
        agent.y = Entity_Manager.worldMap[topLeftNode].y -1
        stingray.Unit.set_local_position(agent.agentModel, 1, stingray.Vector3(agent.x,agent.y,0))
        
        agent:FSM_ChangeState(Idle_State)
        
    --Checks the top-right neighbor to see if we can spawn the chamfbox there
     elseif Entity_Manager.worldMap[topRightNode].fog == nil and Entity_Manager.worldMap[topRightNode].isWalkable == true and Entity_Manager.worldMap[topRightNode].hasTree == false and runningTime >= 6 then
        local building = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/props/ChamfBox",stingray.Vector3(Entity_Manager.worldMap[topRightNode].x,Entity_Manager.worldMap[topRightNode].y,0))
        stingray.Unit.set_local_scale(building,1,stingray.Vector3(0.2,0.2,0.2))
        table.insert(Entity_Manager.houseVector, topRightNode)
        
        Entity_Manager.worldMap[topRightNode].isWalkable = false
        agent.x = Entity_Manager.worldMap[topRightNode].x -1
        agent.y = Entity_Manager.worldMap[topRightNode].y -1
        stingray.Unit.set_local_position(agent.agentModel, 1, stingray.Vector3(agent.x,agent.y,0))
        
        agent:FSM_ChangeState(Idle_State)
        
    --Checks the bottom-left neighbor to see if we can spawn the chamfbox there
     elseif Entity_Manager.worldMap[bottomLeftNode].fog == nil and Entity_Manager.worldMap[bottomLeftNode].isWalkable == true and Entity_Manager.worldMap[bottomLeftNode].hasTree == false and runningTime >= 6 then
        local building = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/props/ChamfBox",stingray.Vector3(Entity_Manager.worldMap[bottomLeftNode].x,Entity_Manager.worldMap[bottomLeftNode].y,0))
        stingray.Unit.set_local_scale(building,1,stingray.Vector3(0.2,0.2,0.2))
        Entity_Manager.worldMap[bottomLeftNode].isWalkable = false
        table.insert(Entity_Manager.houseVector, bottomLeftNode)
        
        agent.x = Entity_Manager.worldMap[bottomLeftNode].x +1
        agent.y = Entity_Manager.worldMap[bottomLeftNode].y +1
        stingray.Unit.set_local_position(agent.agentModel, 1, stingray.Vector3(agent.x,agent.y,0))
        
        agent:FSM_ChangeState(Idle_State)
        
    --Checks the bottom-right neighbor to see if we can spawn the chamfbox there
     elseif Entity_Manager.worldMap[bottomRightNode].fog == nil and Entity_Manager.worldMap[bottomRightNode].isWalkable == true and Entity_Manager.worldMap[bottomRightNode].hasTree == false and runningTime >= 6 then
        local building = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/props/ChamfBox",stingray.Vector3(Entity_Manager.worldMap[bottomRightNode].x,Entity_Manager.worldMap[bottomRightNode].y,0))
        stingray.Unit.set_local_scale(building,1,stingray.Vector3(0.2,0.2,0.2))
        table.insert(Entity_Manager.houseVector, bottomRightNode)
        Entity_Manager.worldMap[bottomRightNode].isWalkable = false
        
        agent.x = Entity_Manager.worldMap[bottomRightNode].x -1
        agent.y = Entity_Manager.worldMap[bottomRightNode].y +1
        stingray.Unit.set_local_position(agent.agentModel, 1, stingray.Vector3(agent.x,agent.y,0))
        
        agent:FSM_ChangeState(Idle_State)
    end
end --End of Execute

-----------------------------------------------------------
-----------------------------------------------------------

function Build_State:Exit(agent)
    agent.currentlyWorking = false
    agent.doOnce = false
end--End of Exit

-----------------------------------------------------------
-----------------------------------------------------------

return Build_State