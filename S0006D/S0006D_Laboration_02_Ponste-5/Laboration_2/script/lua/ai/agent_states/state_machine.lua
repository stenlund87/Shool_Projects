
State_Machine = Appkit.class(State_Machine)
totalSM = 0
----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------    

    function State_Machine:init(agent)
    self.currentState = nil
    self.previousState = nil
    self.owner = agent
    totalSM = totalSM +1
    end --End of init()
    
----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------

    function State_Machine:SetCurrentState(state_type)
        self.currentState = state_type
    end -- End of SetCurrentState()
----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------
    
    function State_Machine:SetPreviousState(state_type)
        self.previousState = state_type
    end --End of SetPreviousState()

----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------

    function State_Machine:Update(delta_time)
        if self.currentState ~= nil then
            self.currentState:Execute(self.owner,delta_time)
        end
    end --End of Update()

----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------

    function State_Machine:ChangeState(newState)
        self.previousState = self.currentState
        self.previousState:Exit(self.owner)
        self.currentState = newState
        self.currentState:Enter(self.owner)
    end --End of ChangeState()

----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------


    function State_Machine:RevertToPreviousState()
        self:ChangeState(self.previousState)
    end --End of RevertToPreviousState()

----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------



return State_Machine
