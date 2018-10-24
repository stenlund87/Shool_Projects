require "script/lua/ai/entity_manager"
local m_abs = math.abs
local m_floor = math.floor
local m_ceil = math.ceil


Walk_State = {}
package.loaded[...] = Walk_State
local Lumber_State = require "script/lua/ai/agent_states/work_lumber_state"
local Idle_State = require "script/lua/ai/agent_states/idle_state"

function Walk_State:Enter(agent)
    if agent.inventoryFull == true then
        agent.currentIndex = 1
    elseif agent.inventoryFull == false then
        agent.currentIndex = #agent.currentPath
    end
end
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
function Walk_State:Execute(agent,delta_time)
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
    local aim = stingray.Vector3(0,0,0)
    local move = stingray.Vector3(0,0,0)
    
    --When we have come back from a tree that has been depleted
    if  agent.clear == true and agent.inventoryFull == false and agent.currentIndex == #agent.currentPath then
        agent.currentPath = nil
        agent.clear = false
        agent.currentlyWorking = false
        agent.inventoryFull = false
        
        if agent.upgradeToBuilder == true then --If we had need in Lumber_State of a builder
            agent:FSM_ChangeState(Idle_State)
        elseif agent.upgradeToCoaler == true then --If we had need of a coaler in Lumber_State
            agent:FSM_ChangeState(Idle_State)

        elseif #Entity_Manager.treeList ~= 0 then --If it continues to be a worker we want to find a new tree to chop down
            local tree = Entity_Manager:GetTree()
            if tree == nil then  tree = Entity_Manager:GetTree() end
            Entity_Manager:CallWorker(tree)
        
        else
            agent:FSM_ChangeState(Idle_State)
        end
    end
    
    --If we are close enough to the next node on our way to the tree
    if agent.inventoryFull == false and agent.currentIndex > 1 and agent.currentPath ~= nil and #agent.currentPath ~= 0 and (m_abs(agent.currentPath[agent.currentIndex - 1].x - agent.x))< 0.1 and (m_abs(agent.currentPath[agent.currentIndex - 1].y - agent.y))< 0.1 then
        agent.currentIndex = agent.currentIndex - 1
        
        if agent.currentIndex == 1 then
            if agent.currentIndex == 0 then agent.currentIndex = 1 end
            
            agent.x = agent.currentPath[agent.currentIndex].x
            agent.y = agent.currentPath[agent.currentIndex].y
            
            stingray.Unit.set_local_position(agent.agentModel, 1, stingray.Vector3(agent.x,agent.y,0))
            agent.inventoryFull = true
            agent:FSM_ChangeState(Lumber_State)
            return
        end
    --If we are close enough to the next node on our way back from tree
    elseif agent.inventoryFull == true and (m_abs(agent.currentPath[agent.currentIndex + 1].x - agent.x))< 0.1 and (m_abs(agent.currentPath[agent.currentIndex + 1].y - agent.y))< 0.1 then
        agent.currentIndex = agent.currentIndex + 1
        
        if agent.currentIndex == #agent.currentPath then
            agent.inventoryFull = false
            Entity_Manager.treesCollected = Entity_Manager.treesCollected +1
            agent:FSM_ChangeState(Idle_State)
            return
        end
    end
    --We wanna change speed accordingly
    if agent.currentPath ~= nil and #agent.currentPath ~= 0 then
         speed = agent.currentPath[agent.currentIndex].walkSpeed
    end
     
     if agent.inventoryFull == false and agent.currentIndex>1 and agent.currentPath ~= nil and #agent.currentPath ~= 0 then
         aim = stingray.Vector3(agent.currentPath[agent.currentIndex - 1].x, agent.currentPath[agent.currentIndex - 1].y, 0)-stingray.Vector3(agent.x, agent.y, 0)
     elseif agent.inventoryFull == true and agent.currentIndex <= #agent.currentPath and agent.currentPath ~= nil then
         aim = stingray.Vector3(agent.currentPath[agent.currentIndex + 1].x, agent.currentPath[agent.currentIndex + 1].y, 0)-stingray.Vector3(agent.x, agent.y, 0)
    end
    
     
    move = stingray.Vector3.normalize(aim)*delta_time*speed*10
    stingray.Unit.set_local_position(model, 1,move+stingray.Vector3(agent.x,agent.y,0))

    agent.x = agent.x + move.x
    agent.y = agent.y + move.y

    stingray.Unit.set_local_position(model, 1, stingray.Vector3(agent.x,agent.y,0))
    
end --End of Execute()

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

function Walk_State:Exit(agent)
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
return Walk_State