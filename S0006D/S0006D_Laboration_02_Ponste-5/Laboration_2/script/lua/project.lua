-----------------------------------------------------------------------------------
-- This implementation uses the default SimpleProject and the Project extensions are 
-- used to extend the SimpleProject behavior.

-- This is the global table name used by Appkit Basic project to extend behavior
Project = Project or {}

require 'script/lua/flow_callbacks'
require "script/lua/ai/worker"
require "script/lua/ai/entity_manager"
--Walk_State = Walk_State or require "script/lua/ai/agent_states/walk_state"

local pathToMap1 = "D:\\Laboration_2.txt"

local startTime = 0
local width = 100

local cubeArr = {}
local planeArr = {}
local pathArr = {}
local treeArr = {}

local workArr = {}

local startNode = nil
local goalNode = nil

local keyboard = stingray.Keyboard

local keyQ = keyboard.button_id("q")
local keyE = keyboard.button_id("e")
local keyR = keyboard.button_id("r")
local keyF = keyboard.button_id("f")
local keyT = keyboard.button_id("t")

local keyOne = keyboard.button_id("1")

local world = stingray.Application.main_world()
local agent = nil

Project.level_names = {
	menu = "content/levels/main_menu",
	basic = "content/levels/basic"
}

-- Can provide a config for the basic project, or it will use a default if not.
local SimpleProject = require 'core/appkit/lua/simple_project'
SimpleProject.config = {
	standalone_init_level_name = Project.level_names.menu,
	camera_unit = "core/appkit/units/camera/camera",
	camera_index = 1,
	shading_environment = nil, -- Will override levels that have env set in editor.
	create_free_cam_player = false, -- Project will provide its own player.
	exit_standalone_with_esc_key = false
}

-- This optional function is called by SimpleProject after level, world and player is loaded 
-- but before lua trigger level loaded node is activated.
function Project.on_level_load_pre_flow()
	-- Spawn the player for all non-menu levels. level_name will be nil if this 
	-- is an unsaved Test Level.
	local level_name = SimpleProject.level_name
	if level_name == nil or level_name ~= Project.level_names.menu then
		local view_position = Appkit.get_editor_view_position() or stingray.Vector3(0,-14,4)
		local view_rotation = Appkit.get_editor_view_rotation() or stingray.Quaternion.identity()
		local Player = require 'script/lua/player'
		Player.spawn_player(SimpleProject.level, view_position, view_rotation)
	elseif level_name == Project.level_names.menu then
		local MainMenu = require 'script/lua/main_menu'
		MainMenu.start()
	end
	   DestroyMap()
        LoadMap(pathToMap1)
        InitAgents()
        startTime = os.clock()
end

function Project.on_level_shutdown_post_flow()
end

function InitAgents()

    
    math.randomseed(os.time())
    print("We are done")
    Entity_Manager:SetWorldMap(planeArr)
    local x
    local y
    local startIndex = 0

    while true do
        startIndex = math.random(101,10000)
        if planeArr[startIndex].isWalkable == true then
            x = planeArr[startIndex].x
            y = planeArr[startIndex].y
            stingray.World.destroy_unit(stingray.Application.main_world(), planeArr[startIndex].fog)
            planeArr[startIndex].fog = nil
            print("Found it")
            print(startIndex)
            break
        end
    end
     local rightNode = startIndex+1
     local leftNode = startIndex-1
     local topNode = startIndex-100
     local bottomNode = startIndex+100
       
     local topLeftNode = startIndex-101
     local topRightNode = startIndex - 99
       
     local bottomLeftNode = startIndex+99
     local bottomRightNode = startIndex+101
     
    for num = 1, 50 do
        worker = Worker()
        worker:SetPosition(x,y)
        Entity_Manager:RegisterEntity(worker.id, worker)
        worker:FSM_SetCurrentState(Idle_State)
        table.insert(workArr,worker)
    end
    
    stingray.World.destroy_unit(stingray.Application.main_world(), planeArr[rightNode].fog)
    planeArr[rightNode].fog = nil
    -- local planeX =  planeArr[rightNode].x
    -- local planeY = planeArr[rightNode].y
    
    -- for index = 1, 5 do
    --     workArr[index]:SetPosition(planeX,planeY)
    -- end
    
    stingray.World.destroy_unit(stingray.Application.main_world(), planeArr[leftNode].fog)
    planeArr[leftNode].fog = nil
    
    -- local planeX =  planeArr[leftNode].x
    -- local planeY = planeArr[leftNode].y
    
    -- for index = 6, 10 do
    --     workArr[index]:SetPosition(planeX,planeY)
    -- end
    
    stingray.World.destroy_unit(stingray.Application.main_world(), planeArr[topNode].fog)
    planeArr[topNode].fog = nil
    -- local planeX =  planeArr[topNode].x
    -- local planeY = planeArr[topNode].y
    
    -- for index = 11, 15 do
    --     workArr[index]:SetPosition(planeX,planeY)
    -- end
    
    stingray.World.destroy_unit(stingray.Application.main_world(), planeArr[bottomNode].fog)
    planeArr[bottomNode].fog = nil
    
    -- local planeX =  planeArr[bottomNode].x
    -- local planeY = planeArr[bottomNode].y
    
    -- for index = 16, 20 do
    --     workArr[index]:SetPosition(planeX,planeY)
    -- end
    
    stingray.World.destroy_unit(stingray.Application.main_world(), planeArr[topLeftNode].fog)
    planeArr[topLeftNode].fog = nil
    
    -- local planeX =  planeArr[topLeftNode].x
    -- local planeY = planeArr[topLeftNode].y
    
    -- for index = 21, 25 do
    --     workArr[index]:SetPosition(planeX,planeY)
    -- end
    
    stingray.World.destroy_unit(stingray.Application.main_world(), planeArr[topRightNode].fog)
    planeArr[topRightNode].fog = nil
    
    -- local planeX =  planeArr[topRightNode].x
    -- local planeY = planeArr[topRightNode].y
    
    -- for index = 26, 30 do
    --     workArr[index]:SetPosition(planeX,planeY)
    -- end
    
    stingray.World.destroy_unit(stingray.Application.main_world(), planeArr[bottomLeftNode].fog)
    planeArr[bottomLeftNode].fog = nil
    
    -- local planeX =  planeArr[bottomLeftNode].x
    -- local planeY = planeArr[bottomLeftNode].y
    
    -- for index = 31, 35 do
    --     workArr[index]:SetPosition(planeX,planeY)
    -- end
    
    stingray.World.destroy_unit(stingray.Application.main_world(), planeArr[bottomRightNode].fog)
    planeArr[bottomRightNode].fog = nil

    -- local planeX =  planeArr[bottomRightNode].x
    -- local planeY = planeArr[bottomRightNode].y
    
    -- for index = 36, 40 do
    --     workArr[index]:SetPosition(planeX,planeY)
    -- end

    
    
    Entity_Manager:UpgradeToScout()

end


function LoadMap(Path)
    tempNode = require "script/lua/node"
    local sceneGraph = stingray.SceneGraphComponent
	local playerMap = stingray.BiggerPlugin.load_navmesh(Path)
    local startPos = stingray.Vector3(0,0,0)
    local goalPos = stingray.Vector3(0,0,0)
	local world = stingray.Application.main_world()
	local xPos = 0
	local yPos = 0
	for index = 0, #playerMap do
        local val = playerMap[index]
    	for i = 0, string.len(val) do
    	    local stringVal = string.sub(val,i,i)
    	    
    	   if stringVal == "V" then --Unwalkable surface, water
    	        local Node = tempNode:init()
    	        Node:SetPosition(xPos, yPos)
    	        Node.isWalkable = false
    	        Node.plane = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	        stingray.Unit.set_local_scale(Node.plane,1,stingray.Vector3(0.022,0.022,0.022))
    	        stingray.Unit.set_material(Node.plane, "Material #26" ,"content/materials/light_blue")
    	        
    	        local tempFog = stingray.World.spawn_unit(world,"content/models/props/fog", stingray.Vector3(xPos,yPos,0))
    	        stingray.Unit.set_local_scale(tempFog,1,stingray.Vector3(0.2,0.2,0.5))
    	        Node.fog = tempFog
    	        
    	        table.insert(planeArr, Node)
    	        xPos = xPos - 1
    	   elseif stringVal == "S" then
    	       local Node = tempNode:init()
    	       Node:SetPosition(xPos,yPos)
    	       Node.isWalkable = true
    	       Node.walk = "Go ahead"
    	       Node.index = (yPos*100)+ math.abs(xPos)+1
    	       local plan = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_local_scale(plan,1,stingray.Vector3(0.022,0.022,0.022))
    	       Node.plane = plan
    	       Node.walkSpeed = 1
    	       table.insert(planeArr, Node)
    	       startPos = stingray.Vector3(xPos, yPos,0)
    	       --agent = stingray.World.spawn_unit(world, "content/models/character/character",startPos)
    	       startNode = Node
    	       --table.insert(start_GoalArr, Node)
    	       xPos = xPos - 1
    	   elseif stringVal == "H" then --Walkable surface, spawn Goal
	            local Node = tempNode:init()
    	        Node:SetPosition(xPos,yPos)
    	        Node.isWalkable = true
    	        local plan = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	        stingray.Unit.set_local_scale(plan,1,stingray.Vector3(0.022,0.022,0.022))
    	        Node.plane = plan
    	        Node.walkSpeed = 1
    	        table.insert(planeArr, Node)
    	        goalNode = Node
	            --table.insert(start_GoalArr, Node)
	            xPos = xPos - 1
    	   elseif stringVal == "B" then --Unwalkable surface. mountains
    	        local Node = tempNode:init()
    	        Node:SetPosition(xPos, yPos)
    	        Node.isWalkable = false
    	        --Node.plane = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	        local cube = stingray.World.spawn_unit(world,"content/models/props/ChamfBox", stingray.Vector3(xPos,yPos,0))
    	        stingray.Unit.set_material(cube, "ChamfBox_01","content/materials/grey")
    	        
    	       local plan = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_local_scale(plan,1,stingray.Vector3(0.022,0.022,0.022))
    	       stingray.Unit.set_material(plan, "Material #26" ,"content/materials/grey")
    	       Node.plane = plan
    	        
    	        --stingray.Unit.set_local_scale(Node.plane,1,stingray.Vector3(0.022,0.022,0.022))
    	        stingray.Unit.set_local_scale(cube,1,stingray.Vector3(0.2,0.2,0.2))
    	        
    	        local mountainTop = stingray.World.spawn_unit(world,"core/units/primitives/stairs_primitive", stingray.Vector3(xPos,yPos,1))
    	        
    	       local tempFog = stingray.World.spawn_unit(world,"content/models/props/fog", stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_local_scale(tempFog,1,stingray.Vector3(0.3,0.3,0.5))
    	       Node.fog = tempFog 
    	        
    	        table.insert(planeArr, Node)
    	        table.insert(cubeArr, cube)
    	        xPos = xPos - 1
    	   elseif stringVal == "M" then --Walkable surface, ground
    	       local Node = tempNode:init()
    	       Node:SetPosition(xPos,yPos)
    	       Node.isWalkable = true
    	       Node.walk = "Go ahead"
    	       Node.walkSpeed = 1
    	       local plan = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_material(plan, "Material #26" ,"content/materials/green")
    	       stingray.Unit.set_local_scale(plan,1,stingray.Vector3(0.022,0.022,0.022))
    	       Node.plane =  plan
    	       
    	       local tempFog = stingray.World.spawn_unit(world,"content/models/props/fog", stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_local_scale(tempFog,1,stingray.Vector3(0.2,0.2,0.5))
    	       Node.fog = tempFog 
    	       
    	       table.insert(planeArr, Node)
    	       xPos = xPos - 1
    	        
    	   elseif stringVal == "G" then --Walkable surface, swamp
    	       local Node = tempNode:init()
    	       Node:SetPosition(xPos,yPos)
    	       Node.isWalkable = true
    	       Node.walkSpeed = 0.5
    	       local plan = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_local_scale(plan,1,stingray.Vector3(0.022,0.022,0.022))
    	       stingray.Unit.set_material(plan, "Material #26" ,"content/materials/swamp")
    	       Node.plane = plan
    	       
    	       local tempFog = stingray.World.spawn_unit(world,"content/models/props/fog", stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_local_scale(tempFog,1,stingray.Vector3(0.2,0.2,0.5))
    	       Node.fog = tempFog 
    	       
    	       table.insert(planeArr, Node)
    	       xPos = xPos - 1
    	       
    	   elseif stringVal == "T" then --Walkable surface, forrest with trees
    	       local Node = tempNode:init()
    	       Node:SetPosition(xPos,yPos)
    	       Node.isWalkable = true
    	       local plan = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_local_scale(plan,1,stingray.Vector3(0.022,0.022,0.022))
    	       stingray.Unit.set_material(plan, "Material #26" ,"content/materials/green")
    	       Node.plane = plan
    	       Node.walkSpeed = 1
    	       Node.hasTree = true
    	       Node.treeRemaining = 5
    	       
    	       
    	       
    	       local tempFog = stingray.World.spawn_unit(world,"content/models/props/fog", stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_local_scale(tempFog,1,stingray.Vector3(0.2,0.2,0.5))
    	       Node.fog = tempFog 
    	       
    	       
    	       table.insert(planeArr, Node)
    	       startPos = stingray.Vector3(xPos, yPos,0)
    	       
    	       for i = 1, 5 do
    	           local treeX = math.random(-5,5)
    	           local treeY = math.random(-5,5)
    	           local x = startPos.x + treeX*0.1
    	           local y = startPos.y + treeY*0.1
    	           local tempTree = stingray.World.spawn_unit(world, "core/units/primitives/cone_primitive",stingray.Vector3(x,y,0))
    	           stingray.Unit.set_local_scale(tempTree, 1 ,stingray.Vector3(0.2,0.2,2))
    	           stingray.Unit.set_material(tempTree, "material" ,"content/materials/tree")
                   table.insert(Node.treeCollection, tempTree)
    	       end
    	       
    	       
    	       --Node.treeBottom = stingray.World.spawn_unit(world, "core/units/primitives/cone_primitive",startPos)
    	       --Node.treeMiddle = stingray.World.spawn_unit(world, "core/units/primitives/cone_primitive",stingray.Vector3(xPos,yPos,0.5))
    	       --Node.treeTop = stingray.World.spawn_unit(world, "core/units/primitives/cone_primitive",stingray.Vector3(xPos,yPos,1))
    	       
    	       --stingray.Unit.set_material(Node.treeBottom, "material" ,"content/materials/tree")
    	       --stingray.Unit.set_material(Node.treeMiddle, "material" ,"content/materials/tree")
    	       --stingray.Unit.set_material(Node.treeTop, "material" ,"content/materials/tree")
    	       
    	       --stingray.Unit.set_local_scale(Node.treeBottom, 1 ,stingray.Vector3(0.5,0.5,0.5))
    	       --stingray.Unit.set_local_scale(Node.treeMiddle, 1 ,stingray.Vector3(0.5,0.5,0.5))
    	       --stingray.Unit.set_local_scale(Node.treeTop, 1 ,stingray.Vector3(0.5,0.5,0.5))
    	       
    	       xPos = xPos - 1
	        end
        end

        yPos = yPos + 1
	    xPos = 0
    end

end


function DestroyMap()
    local world = stingray.Application.main_world()
    -- local x = table.getn(cubeArr)
    -- local y = table.getn(planeArr)
    if table.getn(cubeArr) ~= 0 then
        for index = 1, #cubeArr do
            stingray.World.destroy_unit(world, cubeArr[index])
            cubeArr[index] = nil
        end
    if table.getn(pathArr) ~= 0 then
        for k = 1, #pathArr do
            if pathArr[k] ~= nil then
                stingray.World.destroy_unit(world,pathArr[k])
                pathArr[k] = nil
            end
        end
    end
    star.aPath = nil
    for i = 1, #planeArr do
        stingray.World.destroy_unit(world, planeArr[i].plane)
        planeArr[i] = nil
    end
    planeArr = {}
    cubeArr = {}
    start_GoalArr = {}
    pathArr = {}
    
    if agent ~= nil then
        stingray.World.destroy_unit(world, agent)
        agent = nil
    end
    end
    vis = false
end

function RemoveAgentsFromList()
    local world = stingray.Application.main_world()
    if table.getn(pathArr) ~= 0 then
        for k = 1, #pathArr do
            if pathArr[k] ~= nil then
                stingray.World.destroy_unit(world,pathArr[k])
                pathArr[k] = nil
            end
        end
    end
end

function ClearAll()
    cubeArr = nil
    cubeArr = {}
    planeArr = nil
    planeArr = {}
    star = nil
    start_GoalArr = nil
    start_GoalArr = {}
    pathArr = nil
end



-- Optional function called by SimpleProject after world update (we will probably want to split to pre/post appkit calls)
function Project.update(dt)
    
    
    for k, worker in ipairs(workArr) do
        worker:Update(dt)
    end
    if Entity_Manager.coalCollected >= 200 then
        local endTime = os.clock()
        local goalTime = endTime - startTime
        print(goalTime)
        print("WEEEEE AREEE THEEE WIIIINNNEEEEERS")
        Project.shutdown(self)
    end
end


-- Optional function called by SimpleProject *before* appkit/world render
function Project.render()
end

-- Optional function called by SimpleProject *before* appkit/level/player/world shutdown
function Project.shutdown()
    cubeArr = {}
    planeArr = {}
    star = nil
    start_GoalArr = {}
    pathArr = nil
end




return Project