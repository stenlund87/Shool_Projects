require "script/lua/ai/agent_states/idle_state"


Lumber_State = {}
package.loaded[...] = Lumber_State

local Walk_State = require "script/lua/ai/agent_states/walk_state"

function Lumber_State:Enter(agent)
    agent.currentlyWorking = true
    agent.waitTime = os.clock()
end
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
function Lumber_State:Execute(agent,delta_time)
    local currentTime = os.clock()
    local runningTime = currentTime - agent.waitTime
    
    
    local agentStandingOnIndex = (math.ceil(agent.y)*100+math.abs(math.floor(agent.x)))+1
    local currentNode = Entity_Manager.worldMap[agentStandingOnIndex]
    
    if(currentNode.hasTree == true) and runningTime >= 3 then
        currentNode.treeRemaining = currentNode.treeRemaining - 1
        agent.inventoryFull = true
        
        stingray.World.destroy_unit(stingray.Application.main_world(),currentNode.treeCollection[#currentNode.treeCollection])
        table.remove(currentNode.treeCollection)
        
        if currentNode.treeRemaining == 0 then
            currentNode.hasTree = false

            agent.clear = true
            Entity_Manager:RemoveTreeNode(agentStandingOnIndex)
            
            if Entity_Manager.treesCollected > 100 and Entity_Manager.numberOfBuilders < 1 then
                Entity_Manager.numberOfBuilders = Entity_Manager.numberOfBuilders +1
                Entity_Manager.numberOfWorkers = Entity_Manager.numberOfWorkers - 1
                agent.upgradeToBuilder = true
            elseif Entity_Manager.treesCollected > 10 and Entity_Manager.numberOfCoalers < Entity_Manager.numberOfBuildings then
                print(Entity_Manager.numberOfBuildings)
                Entity_Manager.numberOfCoalers = Entity_Manager.numberOfCoalers +1
                Entity_Manager.numberOfWorkers = Entity_Manager.numberOfWorkers - 1
                agent.upgradeToCoaler = true
            end
            
        end
        agent:FSM_ChangeState(Walk_State)
    end

end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

function Lumber_State:Exit(agent)
    agent.currentlyWorking = true
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
return Lumber_State