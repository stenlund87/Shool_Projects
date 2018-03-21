
--local Walk_State = Walk_State or require "script/lua/ai/agent_states/walk_state"


Idle_State = {}
package.loaded[...] = Idle_State
local Walk_State = require "script/lua/ai/agent_states/walk_state"
local Scout_State = require "script/lua/ai/agent_states/scout_state"
local Build_State = require "script/lua/ai/agent_states/build_state"
local MakeCoal_State = require "script/lua/ai/agent_states/make_coal_state"
local Upgrade_State = require "script/lua/ai/agent_states/upgrade_state"


function Idle_State:Enter(agent)
    --agent.currentlyWorking = false
end--End of Enter

-----------------------------------------------------------
-----------------------------------------------------------

--Method that we can see as global state
--Dictates where all agents will go
function Idle_State:Execute(agent,delta_time)
    if agent.scout == true then
        agent:FSM_ChangeState(Scout_State)
        
    elseif agent.worker == true and agent.currentPath ~= nil and #agent.currentPath ~= 0 and agent.currentlyWorking == true then
        --print("First")
        agent:FSM_ChangeState(Walk_State)
    
    elseif agent.worker == true and agent.currentPath == nil and agent.currentlyWorking == false and agent.upgradeToBuilder == false and agent.upgradeToCoaler == false and #Entity_Manager.treeList ~= 0 then
        local tree = Entity_Manager:GetTree()
        print(tree)
        Entity_Manager:GoToTree(agent,tree)
        
    elseif Entity_Manager.treesCollected >100 and Entity_Manager.numberOfBuildings < 2 and agent.builder == true and agent.currentlyWorking == false then
        agent:FSM_ChangeState(Build_State)
        
    elseif Entity_Manager.treesCollected >2 and agent.coaler == true and agent.currentlyWorking == false then
        agent:FSM_ChangeState(MakeCoal_State)
        
    elseif agent.upgradeToBuilder == true and agent.builder == false then
        agent:FSM_ChangeState(Upgrade_State)
        
    elseif agent.upgradeToCoaler == true and agent.coaler == false then
        agent:FSM_ChangeState(Upgrade_State)
    end
    
    return
end --End of Execute

-----------------------------------------------------------
-----------------------------------------------------------

function Idle_State:Exit(agent)
    agent.currentlyWorking = true
end--End of Exit

-----------------------------------------------------------
-----------------------------------------------------------

return Idle_State