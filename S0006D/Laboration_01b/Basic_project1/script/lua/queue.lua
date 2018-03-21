
local Queue = {}
function Queue.init()
    local q = {}
    q.data = {}
    q.first = 0
    q.last = -1
    q.size = 0
    
    function q.push(node)
        q.last = q.last + 1
        q.data[q.last] = node
        q.size = q.size + 1
    end
    
    function q.pop()
        local val = nil
        if q.first > q.last then
            print("Queue is empty")
            val = -1
        else
            val = q.data[q.first]
            q.data[q.first] = nil
            q.first = q.first + 1
            q.size = q.size - 1

        end
        return val
    end
    
    return q
end
return Queue