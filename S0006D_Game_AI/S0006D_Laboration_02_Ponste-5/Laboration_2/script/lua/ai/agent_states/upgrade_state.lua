
Upgrade_State = {}
package.loaded[...] = Upgrade_State
local Idle_State = require "script/lua/ai/agent_states/idle_state"


function Upgrade_State:Enter(agent)
    agent.waitTime = os.clock()
    if agent.upgradeToBuilder == true then
        print("Builder in Upgrade "..agent.id)
    elseif agent.upgradeToCoaler == true then
        print("Coaler in Upgrade "..agent.id)
    end
end--End of Enter

-----------------------------------------------------------
-----------------------------------------------------------

function Upgrade_State:Execute(agent,delta_time)
    local executeTime = os.clock()
    local runningTime = executeTime - agent.waitTime
    if agent.scout == true and runningTime >= 6 then
        agent.agentModel  = nil
        agent.agentModel = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/character/scout",stingray.Vector3(agent.x,agent.y,0))
        stingray.Unit.set_local_scale(agent.agentModel,1,stingray.Vector3(0.5,0.5,0.5))
        agent:FSM_ChangeState(Idle_State)
        
    elseif agent.upgradeToBuilder == true and runningTime >= 12 then
        print("We get to upgrade builder")
        agent.worker = false
        agent.builder = true
        agent.currentlyWorking = false
        agent.agentModel  = nil
        agent.agentModel = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/character/builder",stingray.Vector3(agent.x,agent.y,0))
        stingray.Unit.set_local_scale(agent.agentModel,1,stingray.Vector3(0.5,0.5,0.5))
        Entity_Manager.doneWithBuilders = true
        
        agent:FSM_ChangeState(Idle_State)
        
    elseif agent.upgradeToCoaler == true and runningTime >= 12 then
        print("We get to coaler")
        agent.worker = false
        agent.coaler = true
        agent.currentlyWorking = false
        agent.agentModel  = nil
        local house = Entity_Manager.houseVector[#Entity_Manager.houseVector]
        agent.x = Entity_Manager.worldMap[house].x-0.5
        agent.y = Entity_Manager.worldMap[house].y
        
        table.remove(Entity_Manager.houseVector,#Entity_Manager.houseVector)
        agent.agentModel = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/character/coaler",stingray.Vector3(agent.x,agent.y,0))
        stingray.Unit.set_local_scale(agent.agentModel,1,stingray.Vector3(0.5,0.5,0.6))
        agent:FSM_ChangeState(Idle_State)
    end
end --End of Execute

-----------------------------------------------------------
-----------------------------------------------------------

function Upgrade_State:Exit(agent)
end--End of Exit

-----------------------------------------------------------
-----------------------------------------------------------

return Upgrade_State