
MakeCoal_State = {}
package.loaded[...] = MakeCoal_State
local Idle_State = require "script/lua/ai/agent_states/idle_state"


function MakeCoal_State:Enter(agent)
        agent.currentlyWorking = true
        agent.waitTime = os.clock()
end--End of Enter

-----------------------------------------------------------
-----------------------------------------------------------
--Method that calculated the time run for each agent and increments coalCollected when time expires
--Changes state to Idle when done
--@Param agent, the agent that will execute the code
--@Param delta_time, delta time from Project.Update()
function MakeCoal_State:Execute(agent,delta_time)
    local executeTime = os.clock()
    local runningTime = executeTime - agent.waitTime

    if agent.doOnce == false then
        Entity_Manager.treesCollected = Entity_Manager.treesCollected - 2
        agent.doOnce = true
    end
     if runningTime >= 3 then
        Entity_Manager.coalCollected = Entity_Manager.coalCollected + 1
        print("We have this much coal "..Entity_Manager.coalCollected)

        agent:FSM_ChangeState(Idle_State)
     end
end --End of Execute

-----------------------------------------------------------
-----------------------------------------------------------

function MakeCoal_State:Exit(agent)
     agent.currentlyWorking = false
     agent.doOnce = false
end--End of Exit

-----------------------------------------------------------
-----------------------------------------------------------

return MakeCoal_State