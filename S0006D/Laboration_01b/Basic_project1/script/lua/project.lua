-----------------------------------------------------------------------------------
-- This implementation uses the default SimpleProject and the Project extensions are 
-- used to extend the SimpleProject behavior.

-- This is the global table name used by Appkit Basic project to extend behavior
Project = Project or {}

local width = 0

local pathToMap1 = "D:\\Map1.txt"
--local pathToMap2 = "content\\script\\Map2.txt"
local pathToMap2 = "D:\\Map2.txt"
local pathToMap3 = "D:\\Map3.txt"

local vis = false
local cubeArr = {}
local planeArr = {}
local start_GoalArr = {}
local pathArr = {}

local keyboard = stingray.Keyboard

local keyQ = keyboard.button_id("q")
local keyE = keyboard.button_id("e")
local keyR = keyboard.button_id("r")
local keyF = keyboard.button_id("f")
local keyT = keyboard.button_id("t")

local keyOne = keyboard.button_id("1")
local keyTwo = keyboard.button_id("2")
local keyThree = keyboard.button_id("3")

local world = stingray.Application.main_world()
local agent = nil

aStar = require "script/lua/pathfinding_a"
local star = aStar:init()

b = require "script/lua/bfs_pathfinding"
local bfs = b.init() 

d = require "script/lua/dfs_pathfinding"
local dfs = d.init() 

c = require "script/lua/pathfinding/contour_tracing"
local ct = c.init()

require 'script/lua/flow_callbacks'

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
    	    if stringVal == "X" then --Unwalkable surface
    	        local Node = tempNode:init()
    	        Node:SetPosition(xPos, yPos)
    	        Node:IsWalkable(false)
    	        local plan = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	        stingray.Unit.set_local_scale(plan,1,stingray.Vector3(0.022,0.022,0.022))
    	        Node.plane = plan
    	        
    	        local cube = stingray.World.spawn_unit(world,"content/models/props/ChamfBox", stingray.Vector3(xPos,yPos,0))
    	        stingray.Unit.set_local_scale(cube,1,stingray.Vector3(0.2,0.2,0.2))
    	        --table.insert(cubeArr, stingray.World.spawn_unit(world,"core/units/primitives/cube_primitive", stingray.Vector3(xPos,yPos,0)))
    	        table.insert(cubeArr, cube)
    	        table.insert(planeArr, Node)
    	        xPos = xPos - 1
    	   elseif stringVal == "1" then --Unwalkable surface
    	        local Node = tempNode:init()
    	        Node:SetPosition(xPos, yPos)
    	        Node:IsWalkable(false)
    	        Node.plane = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	        table.insert(cubeArr, stingray.World.spawn_unit(world,"content/models/props/ChamfBox", stingray.Vector3(xPos,yPos,0)))
    	        --table.insert(cubeArr, stingray.World.spawn_unit(world,"core/units/primitives/cube_primitive", stingray.Vector3(xPos,yPos,0)))
    	        table.insert(planeArr, Node)
    	        xPos = xPos + 1
    	   elseif stringVal == "0" then --Walkable surface, dont spawn anything
    	       local Node = tempNode:init()
    	       Node:SetPosition(xPos,yPos)
    	       Node:IsWalkable(true)
    	       local plan = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_local_scale(plan,1,stingray.Vector3(0.022,0.022,0.022))
    	       Node.plane = plan
    	        table.insert(planeArr, Node)
    	       xPos = xPos - 1
    	   elseif stringVal == "S" then --Walkable surface, spawn Start
    	       local Node = tempNode:init()
    	       Node:SetPosition(xPos,yPos)
    	       Node:IsWalkable(true)
    	       local plan = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	       stingray.Unit.set_local_scale(plan,1,stingray.Vector3(0.022,0.022,0.022))
    	       Node.plane = plan
    	       table.insert(planeArr, Node)
    	       startPos = stingray.Vector3(xPos, yPos,0)
    	       agent = stingray.World.spawn_unit(world, "content/models/character/character",startPos)
    	       table.insert(start_GoalArr, Node)
    	       xPos = xPos - 1
	        elseif stringVal == "G" then --Walkable surface, spawn Goal
	            local Node = tempNode:init()
    	        Node:SetPosition(xPos,yPos)
    	        Node:IsWalkable(true)
    	        local plan = stingray.World.spawn_unit(world, "content/models/floor/Basic_Floor",stingray.Vector3(xPos,yPos,0))
    	        stingray.Unit.set_local_scale(plan,1,stingray.Vector3(0.022,0.022,0.022))
    	        Node.plane = plan
    	        table.insert(planeArr, Node)
	            goalPos = stingray.Vector3(xPos, yPos,0)
	            table.insert(start_GoalArr, Node)
	            xPos = xPos - 1
	        end
        end
        width = math.abs(xPos)
        yPos = yPos + 1
	    xPos = 0
    end
    for k = 1, #cubeArr do
        stingray.Unit.set_material(cubeArr[k],"material", "content/materials/yellow")
    end
    
end


function DestroyMap()
    local world = stingray.Application.main_world()
    local x = table.getn(cubeArr)
    local y = table.getn(planeArr)
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


function Project.on_level_shutdown_post_flow()
end

-- Optional function called by SimpleProject after world update (we will probably want to split to pre/post appkit calls)
function Project.update(dt)

    if stingray.Keyboard.pressed(keyOne) then
        DestroyMap()
        LoadMap(pathToMap1)
    elseif stingray.Keyboard.pressed(keyTwo) then
        DestroyMap()
        LoadMap(pathToMap2)
    elseif stingray.Keyboard.pressed(keyThree) then
        DestroyMap()
        LoadMap(pathToMap3)
    elseif stingray.Keyboard.pressed(keyQ) then
        for index = 1, #cubeArr do
            local temp = cubeArr[index]
            stingray.Unit.set_unit_visibility(temp, vis)
        end
        vis = not vis
    elseif stingray.Keyboard.pressed(keyE) then
        RemoveAgentsFromList()
        local world = stingray.Application.main_world()

        local startNode = start_GoalArr[1]
        local goalNode = start_GoalArr[2]
        local startTime = os.clock()
        star:AStar(start_GoalArr[1],start_GoalArr[2], planeArr,width)
        
        local finishTime = os.clock()
        local totalTime = finishTime - startTime
        print("Total running time of AStar algorithm: ".. totalTime .."seconds")
        
        for n, no in ipairs(star.bestPath) do
            local Pos = stingray.Vector3(no.x,no.y,0)
            table.insert(pathArr,stingray.World.spawn_unit(world, "content/models/character/character",Pos))
        end
    elseif stingray.Keyboard.pressed(keyR) then
        RemoveAgentsFromList()
        local world = stingray.Application.main_world()
        
        local startTime = os.clock()
        bfs:BreadthFirstSearch(planeArr,start_GoalArr[1],start_GoalArr[2])
        
        local finishTime = os.clock()
        local totalTime = finishTime - startTime
        print("Total running time of BFS algorithm: ".. totalTime .."seconds")
        
         for n, no in ipairs(bfs.pathFound) do
            local Pos = stingray.Vector3(no.x,no.y,0)
            table.insert(pathArr,stingray.World.spawn_unit(world, "content/models/character/character",Pos))
        end
    elseif stingray.Keyboard.pressed(keyF) then
        RemoveAgentsFromList()
        local world = stingray.Application.main_world()
        local startTime = os.clock()
        dfs:DepthFirstSearch(planeArr,start_GoalArr[1],start_GoalArr[2])
        
        local finishTime = os.clock()
        local totalTime = finishTime - startTime
        print("Total running time of DFS algorithm: ".. totalTime .."seconds")
        
         for n, no in ipairs(dfs.pathFound) do
            local Pos = stingray.Vector3(no.x,no.y,0)
            table.insert(pathArr,stingray.World.spawn_unit(world, "content/models/character/character",Pos))
        end
    elseif stingray.Keyboard.pressed(keyT) then
        RemoveAgentsFromList()
        local world = stingray.Application.main_world()
        local startTime = os.clock()
        print("Start time: "..startTime)
        ct:ContourTracing(planeArr,start_GoalArr[1],start_GoalArr[2])
        
        local finishTime = os.clock()
        print("Finish time: "..finishTime)
        local totalTime = finishTime - startTime
        print("Total running time of my own algorithm: ".. totalTime)
         for n, no in ipairs(ct.pathFound) do
            local Pos = stingray.Vector3(no.x,no.y,0)
            table.insert(pathArr,stingray.World.spawn_unit(world, "content/models/character/character",Pos))
        end
    end



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