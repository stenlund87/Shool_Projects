#include <engine_plugin_api/plugin_api.h>
#include <plugin_foundation/platform.h>

namespace PLUGIN_NAMESPACE
{
	struct GraphResourceHeader
	{
		unsigned marker;
		unsigned version;
		unsigned nodes_offset;
		unsigned num_nodes;
		unsigned links_offset;
		unsigned num_links;
	};

	struct GraphNode
	{
		float pos[3];
	};

	struct GraphLink
	{
		unsigned from;
		unsigned to;
	};
}

#include <plugin_foundation/const_config.h>
#include <plugin_foundation/array.h>
#include <plugin_foundation/stream.h>

namespace PLUGIN_NAMESPACE
{

	LoggingApi *logger = nullptr; //<< My own

	LuaApi *_lua = nullptr;
	DataCompilerApi *_data_compiler = nullptr;
	DataCompileParametersApi *_data_compile_parameters = nullptr;
	AllocatorApi *_allocator = nullptr;
	ResourceManagerApi *_resource_manager = nullptr;
	FileSystemApi *_file_system = nullptr;

	void init_api(GetApiFunction get_engine_api)
	{
		logger = (LoggingApi *)get_engine_api(LOGGING_API_ID);

		_lua = (LuaApi *)get_engine_api(LUA_API_ID);
		_data_compiler = (DataCompilerApi *)get_engine_api(DATA_COMPILER_API_ID);
		_data_compile_parameters = (DataCompileParametersApi *)get_engine_api(DATA_COMPILE_PARAMETERS_API_ID);
		_allocator = (AllocatorApi *)get_engine_api(ALLOCATOR_API_ID);
		_resource_manager = (ResourceManagerApi *)get_engine_api(RESOURCE_MANAGER_API_ID);
		_file_system = (FileSystemApi *)get_engine_api(FILESYSTEM_API_ID);
		stingray_plugin_foundation::set_error_api((ErrorApi *)get_engine_api(ERROR_API_ID));
	}

	enum { GRAPH_MARKER = 0xbd25be6fu };
	enum { GRAPH_VERSION = 2 };

	static DataCompileResult compile_graph(DataCompileParameters *input)
	{
		using namespace stingray_plugin_foundation;
	
		DataCompileResult parse_res = _data_compile_parameters->parse(input);
		if (parse_res.error)
			return parse_res;
	
		ConstConfigItem graph(*(ConstConfigRoot *)parse_res.data.p);
	
		ApiAllocator ta(_allocator, _data_compile_parameters->allocator(input));
	
		Array<char> data(ta);
		data.resize(sizeof(GraphResourceHeader));
	
		GraphResourceHeader header = {0};
		header.marker = GRAPH_MARKER;
		header.version = GRAPH_VERSION;
	
		ConstConfigItem nodes = graph["nodes"];
		header.nodes_offset = data.size();
		header.num_nodes = nodes.size();
		for (unsigned i=0; i<header.num_nodes; ++i) {
			struct GraphNode gn = {0};
			gn.pos[0] = nodes[i]["position"][0] || 0.0f;
			gn.pos[1] = nodes[i]["position"][1] || 0.0f;
			gn.pos[2] = nodes[i]["position"][2] || 0.0f;
			stream::pack(data, gn);
		}
	
		ConstConfigItem links = graph["links"];
		header.links_offset = data.size();
		header.num_links = links.size();
		for (unsigned i=0; i<header.num_links; ++i) {
			struct GraphLink gl = {0};
			gl.from = links[i]["nodes"][0] || 0xffffffffu;
			gl.to = links[i]["nodes"][1] || 0xffffffffu;
			stream::pack(data, gl);
		}
	
		unsigned int header_offset = 0;
		stream::patch(data, header_offset, header);
	
		unsigned size = data.size();
	
		DataCompileResult result = {0};
		result.data.p = (char *)ta.allocate(size);
		result.data.len = size;
	
		memcpy(result.data.p, data.begin(), size);
	
		return result;
	}
	
	static const char *add_level_package_includes(DataCompileParameters *input)
	{
		using namespace stingray_plugin_foundation;
	
		DataCompileResult parse_res = _data_compile_parameters->parse(input);
		if (parse_res.error)
			return parse_res.error;
	
		ConstConfigItem level(*(ConstConfigRoot *)parse_res.data.p);
	
		ConstConfigItem graphs = level["graphs"];
		for (int i=0; i<graphs.size(); ++i) {
			const char *graph = graphs[i]["graph"].to_resource("graph");
			_data_compile_parameters->include_in_package(input, "graph", graph);
		}
	
		return nullptr;
	}
	
	static void setup_data_compiler(GetApiFunction get_engine_api)
	{
		const unsigned PLUGIN_ID = 0xe282145cu;
		const unsigned PLUGIN_VERSION = 0;
	
		init_api(get_engine_api);
	
		DataCompilerApi *compiler = (DataCompilerApi *)get_engine_api(DATA_COMPILER_API_ID);
		compiler->add_compiler("graph", GRAPH_VERSION, compile_graph);
		compiler->add_extra_package_include_compiler("level", PLUGIN_ID, PLUGIN_VERSION, add_level_package_includes);
	}

	static GraphNode *graph_nodes(GraphResourceHeader *graph)
	{
		return (GraphNode *)((char*)graph + graph->nodes_offset);
	}
	
	static GraphLink *graph_links(GraphResourceHeader *graph)
	{
		return (GraphLink *)((char*)graph + graph->links_offset);
	}
	
	static GraphResourceHeader *get(const char *name)
	{
		if (!_resource_manager->can_get("graph", name))
			return nullptr;
		GraphResourceHeader *graph = (GraphResourceHeader *)_resource_manager->get("graph", name);
		XASSERT(graph->marker == GRAPH_MARKER, "Compile error -- graph marker does not match expectations");
		XASSERT(graph->version == GRAPH_VERSION, "Compile error -- graph version number does not match expectations");
		return graph;
	}
	
	static int num_nodes(GraphResourceHeader *graph)
	{
		return graph->num_nodes;
	}
	
	static int num_links(GraphResourceHeader *graph)
	{
		return graph->num_links;
	}

	static void node_position(GraphResourceHeader *graph, int node, float pos[3])
	{
		GraphNode *nodes = graph_nodes(graph);
		pos[0] = nodes[node].pos[0];
		pos[1] = nodes[node].pos[1];
		pos[2] = nodes[node].pos[2];
	}
	
	static void link_nodes(GraphResourceHeader *graph, int link, int *from, int *to)
	{
		GraphLink *links = graph_links(graph);
		*from = links[link].from;
		*to = links[link].to;
	}
	
	#define LUA_ASSERT(test, L, msg, ...) do {if (!(test)) _lua->lib_error(L, msg,  ## __VA_ARGS__);} while (0)
	
	static int lua_get(struct lua_State *L)
	{
		const char *s = _lua->tolstring(L, 1, NULL);
		if (!_resource_manager->can_get("graph", s))
			_lua->lib_error(L, "Graph resource not loaded `%s`", s);
		GraphResourceHeader *graph = (GraphResourceHeader *)_resource_manager->get("graph", s);
		LUA_ASSERT(graph->marker == GRAPH_MARKER, L, "Compile error -- graph marker does not match expectations");
		LUA_ASSERT(graph->version == GRAPH_VERSION, L, "Compile error -- graph version number does not match expectations");
		_lua->pushlightuserdata(L, graph);
		return 1;
	}

	static GraphResourceHeader *lua_tograph(struct lua_State *L, int i)
	{
		GraphResourceHeader *graph = (GraphResourceHeader *)_lua->touserdata(L, 1);
		if (graph->marker != GRAPH_MARKER)
			_lua->lib_typerror(L, 1, "Graph");
		return graph;
	}
	
	static int lua_num_nodes(struct lua_State *L)
	{
		_lua->pushinteger(L, lua_tograph(L,1)->num_nodes);
		return 1;
	}
	
	static int lua_num_links(struct lua_State *L)
	{
		_lua->pushinteger(L, lua_tograph(L,1)->num_links);
		return 1;
	}
	
	static int lua_node_position(struct lua_State *L)
	{
		GraphNode *nodes = graph_nodes(lua_tograph(L, 1));
		_lua->pushvector3(L, nodes[_lua->tointeger(L, 2)].pos);
		return 1;
	}

	static int lua_link_nodes(struct lua_State *L)
	{
		GraphLink *links = graph_links(lua_tograph(L, 1));
		_lua->pushinteger(L, links[_lua->tointeger(L, 2)].from);
		_lua->pushinteger(L, links[_lua->tointeger(L, 2)].to);
		return 2;
	}

	static void setup_resources(GetApiFunction get_engine_api)
	{
		init_api(get_engine_api);

		_resource_manager->register_type("graph");
	}

	static int load_navmesh(struct lua_State *L)
	{
		size_t lenght = 0;
		const char* filePath = _lua->tolstring(L, 1, &lenght);
		FILE* file = fopen(filePath, "r");

		char lineRead[255]; //<< a line can contain 255 chars

		_lua->createtable(L, 0, 0); //<< Create lua table
		int index = 0;
		while (fgets(lineRead, 255, file)) //<< Read line
		{
			_lua->pushinteger(L, index);
			_lua->pushstring(L, lineRead); //Push line at index
			_lua->settable(L, -3);
			index++;
		}
		fclose(file);
		return 1;
	}

	static void setup_game(GetApiFunction get_engine_api)
	{
		init_api(get_engine_api);

		_lua->add_module_function("BiggerPlugin", "load_navmesh", load_navmesh);

		_lua->add_module_function("Graph", "get", lua_get);
		_lua->add_module_function("Graph", "num_nodes", lua_num_nodes);
		_lua->add_module_function("Graph", "num_links", lua_num_links);
		_lua->add_module_function("Graph", "node_position", lua_node_position);
		_lua->add_module_function("Graph", "link_nodes", lua_link_nodes);

		logger->error("BiggerPlugin", "Loaded");
	}



	static const char* get_name()
	{
		return "bigger_plugin";
	}

	unsigned GRAPH_API_ID = 0x92d3ccbe;

	struct GraphApi
	{
		struct GraphResourceHeader * (*get)(const char *graph_name);
		int(*num_nodes)(struct GraphResourceHeader *graph);
		int(*num_links)(struct GraphResourceHeader *graph);
		void(*node_position)(struct GraphResourceHeader *graph, int node, float pos[3]);
		void(*link_nodes)(struct GraphResourceHeader *graph, int link, int *from, int *to);
	};

}

extern "C" {

	static void *start_reload(GetApiFunction *get_engine_api)
	{
		return 0;
	}

	static void *finish_reload(GetApiFunction *get_engine_api)
	{
		return 0;
	}

	void *get_bigger_plugin_api(unsigned api)
	{
		if (api == PLUGIN_API_ID) {
			static PluginApi api = { 0 };
			api.setup_data_compiler = PLUGIN_NAMESPACE::setup_data_compiler;
			api.setup_resources = PLUGIN_NAMESPACE::setup_resources;
			api.setup_game = PLUGIN_NAMESPACE::setup_game;
			api.get_name = PLUGIN_NAMESPACE::get_name;

			////api.shutdown_game = shutdown_game;
			//api.start_reload = start_reload;
			//api.finish_reload = finish_reload;

			return &api;
		}
		else if (api == PLUGIN_NAMESPACE::GRAPH_API_ID) {
			static PLUGIN_NAMESPACE::GraphApi api = { 0 };
		  api.get = PLUGIN_NAMESPACE::get;
		  api.num_nodes = PLUGIN_NAMESPACE::num_nodes;
		  api.num_links = PLUGIN_NAMESPACE::num_links;
		  api.node_position = PLUGIN_NAMESPACE::node_position;
		  api.link_nodes = PLUGIN_NAMESPACE::link_nodes;
		  return &api;
		  }
		return 0;
	}

#if !defined STATIC_PLUGIN_LINKING
	PLUGIN_DLLEXPORT void *get_plugin_api(unsigned api)
	{
		return get_bigger_plugin_api(api);
	}
#endif
}
