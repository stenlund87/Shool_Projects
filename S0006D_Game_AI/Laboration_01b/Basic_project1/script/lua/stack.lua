
local Stack = {}
function Stack.init()
    local s = {}
    
    s.data = {}
    s.size = 0
    
    function s.push(node)
        table.insert(s.data, 1, node)
        s.size = s.size + 1
    end
    
    function s.pop()
        if s.size >0 then
            local top = s.data[1]
            table.remove(s.data, 1)
            s.size = s.size -1
            return top
        end
    end
    
    return s
end
return Stack