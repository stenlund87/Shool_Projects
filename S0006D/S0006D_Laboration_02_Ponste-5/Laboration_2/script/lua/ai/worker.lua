State_Machine = State_Machine or require "script/lua/ai/agent_states/state_machine"
require "script/lua/ai/agent_states/walk_state"

Worker = Appkit.class(Worker)
nextValidID = 1
totalWorkers = 0

function Worker:init()
    self.currentPath = {}
    
    self.endReached = false
    self.inventoryFull = false
    self.clear = false
    
    self.upgradeToBuilder = false
    self.upgradeToCoaler = false

    self.worker = true
    self.scout = false
    self.builder = false
    self.coaler = false
    
    
    self.currentlyWorking = false
    self.doOnce = false
    
    self.stateMachine = State_Machine(self)
    self.currentState = Walk_State
    self.agentModel = stingray.World.spawn_unit(stingray.Application.main_world(), "content/models/character/character",stingray.Vector3(-1,1,0))
    stingray.Unit.set_local_scale(self.agentModel,1,stingray.Vector3(0.5,0.5,0.5))
    
    self.id = nextValidID

    self.x = -1
    self.y = 1
    self.walkSpeed = 9
    self.treeIndex = 0
    self.waitTime = 0
    
    nextValidID = nextValidID + 1
    totalWorkers = totalWorkers +1
end

function Worker:FSM_SetCurrentState(new_state)
    self.stateMachine:SetCurrentState(new_state)
end
----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------    

function Worker:FSM_ChangeState(new_state)
    self.stateMachine:ChangeState(new_state)
end--End of FSMChangeState()

----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------    

    function Worker:Update(delta_time)
        self.stateMachine:Update(delta_time)
    end --End of Update()

----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------

    function Worker:SetPosition(startX, startY)
        self.x = startX
        self.y = startY
        stingray.Unit.set_local_position(self.agentModel, 1,stingray.Vector3(self.x,self.y,0))
    end --End of Update()

----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------

return Worker
    
