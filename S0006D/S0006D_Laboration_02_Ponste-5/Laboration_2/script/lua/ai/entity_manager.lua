
require "script/lua/pathfinding/pathfinding_a"
--require "script/lua/ai/agent_states/upgrade_state"
local oldRandom = 0

local m_abs = math.abs
local m_floor = math.floor
local m_ceil = math.ceil


Entity_Manager = {}
package.loaded[...] = Entity_Manager
    math.randomseed(os.clock())
    Entity_Manager.entityList = {}
    Entity_Manager.treeList = {}
    Entity_Manager.a_star = Star:init()
    Entity_Manager.worldMap = {}
    Entity_Manager.discoveredWorld = {}
    
    
    Entity_Manager.numberOfScouts = 0
    Entity_Manager.numberOfWorkers = 0
    Entity_Manager.numberOfBuilders = 0
    Entity_Manager.numberOfCoalers = 0
    
    Entity_Manager.treesCollected = 0
    Entity_Manager.numberOfBuildings = 0
    Entity_Manager.coalCollected = 0
    
    Entity_Manager.doneWithBuilders = false
    
    Entity_Manager.houseVector = {}
    

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------


--Method that adds the entity to entityList table with ID as key and pointer as value
--@Param entity_id, the id of the entity
--@Param new_entity, the entity that you want to add
function Entity_Manager:RegisterEntity(entity_id, new_entity)
    table.insert(Entity_Manager.entityList, new_entity)
end
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------


--Method that returns the pointer to the entity of given ID
--@Param id, id of the entity you want to search for
--@Return, pointer to the object
function Entity_Manager:GetEntityFromId(id)
    for i = 0, #Entity_Manager.entityList do
        if Entity_Manager.entityList[i].id == id then
            return Entity_Manager.entityList[i].entity
        end
    end
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

--Method that removes entity from entityList
--@Param entity, the entity that you want to remove
function Entity_Manager:RemoveEntity(entity)
    for i = 0, #Entity_Manager.entityList do
        if Entity_Manager.entityList[i].entity == entity then
            table.remove(Entity_Manager.entityList, i)
        end
    end
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------


--Method that removes tree from treeList
--@Param index, the index of the node in worldMap that the tree is on
function Entity_Manager:RemoveTreeNode(index)
    --Entity_Manager.treeList[index] = nil
    table.remove(Entity_Manager.treeList, index)
    print("Tree removed!")
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

--Method that gets a tree from treeList and returns the index that it is in worldMap
--@Return tree, int index of the tree
function Entity_Manager:GetTree()
    for index = #self.treeList,1 ,-1 do
        local tree = self.treeList[index]
        if tree ~= nil then
            table.remove(self.treeList,index,tree)
            return tree
        end
    end
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

--Method that does a deep copy of given table
--@Param orig, the original table that you want to copy
--@Return copy, a copy of the table you gave as an argument
function Entity_Manager:DeepCopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in next, orig, nil do
            copy[self:DeepCopy(orig_key)] = self:DeepCopy(orig_value)
        end
        setmetatable(copy, self:DeepCopy(getmetatable(orig)))
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end

-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------


--Method that does A* and gives the path to given agent
--@Param agent, the entity you want to find a path for

function Entity_Manager:ScoutMap(agent)
    local startIndex = (m_floor(agent.y)*100+m_abs(m_ceil(agent.x)))+1
    local goalIndex = 0
    local goalNode = nil
    local tempMap = self:DeepCopy(self.worldMap)
    local startNode = tempMap[startIndex]
    for i = 0, 10 do
        math.random(#self.worldMap)
    end
    goalIndex = math.random(1,10000)
        goalNode = tempMap[goalIndex]
        if goalNode.isWalkable == true and goalIndex ~= startIndex then
            oldRandom = goalIndex
            self.a_star:AStar(startNode, goalNode, tempMap, 100,false)

            agent.currentPath = Entity_Manager.a_star.bestPath
            self.a_star.bestPath = nil
            self.a_star.bestPath = {}
            tempMap = nil
        end
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------


--Method that does A* to given index
--@Param agent, the entity you want to give a path to
--@Param treeIndex, the index in worldMap that the tree is in
--@Return 
function Entity_Manager:GoToTree(agent,treeIndex)
    local startIndex = (m_floor(agent.y)*100+m_abs(m_ceil(agent.x)))+1
    local goalNode = nil
    local tempMap = self:DeepCopy(self.worldMap)
    local startNode = tempMap[startIndex]
    goalNode = tempMap[treeIndex]
    if treeIndex ~= startIndex then
        self.a_star:AStar(startNode, goalNode, tempMap, 100,true)
        agent.currentPath = self.a_star.bestPath
        self.a_star.bestPath = nil
        self.a_star.bestPath = {}
        tempMap = nil
        if #agent.currentPath == 0 then
            local tree = self:GetTree()
            self:GoToTree(agent, tree)
            return
        end
    end
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

--Method that sets Entity_Manager.worldMap to given table
--@Param map, the table you want worldMap to be
function Entity_Manager:SetWorldMap(map)
    self.worldMap = map
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

--Method that upgrades 10 workers to scouts
function Entity_Manager:UpgradeToScout()
    for index = 1, #self.entityList do
        if self.entityList[index].worker == true and self.numberOfScouts <10 then
            self.entityList[index].worker = false
            self.entityList[index].scout = true
            self.numberOfScouts = self.numberOfScouts +1
            self.numberOfWorkers = self.numberOfWorkers - 1
            self.entityList[index]:FSM_ChangeState(Upgrade_State)
            --break
        end
    end
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

--Method that searches for a worker that isnt currently working and calls GoToTree
--@Param nodeIndex, index to the tree you want an agent to go to
--@Return
function Entity_Manager:CallWorker(nodeIndex)
    for k, agent in ipairs(self.entityList) do
        if agent.worker == true and agent.currentlyWorking == false then

            self:GoToTree(agent,nodeIndex)
            if #agent.currentPath ~= 0 then 
                agent:FSM_ChangeState(Walk_State)
                agent.currentlyWorking = true
                return
            end
            break
        end
        if k == #self.entityList and not self:CheckTree(nodeIndex) then
            table.insert(self.treeList,nodeIndex)
        end
    end
    return
end

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

--Method that checks if given treeIndex is already in treeList
--@Return boolean value
function Entity_Manager:CheckTree(nodeIndex)
    for k, tree in ipairs(self.treeList) do
        if nodeIndex == tree then return true end
    end
    return false
end
