-- 打印result[i]
local print_one_result= function(accounts)
    print("worldwide_achv_id:"..accounts[1].." actor_num:"..accounts[2]) 
    for k,v in ipairs(accounts[3]) do
        print("\tactor["..k.."]:"..v)
    end
end


result = {} 
local load_accounts_from_file= function(file_name)
   file = io.open(file_name)
   if file == nil then
        print("open fail "..file_name)
       return None
   end
   
   line_num = 0
   for line in file:lines() do
       line_num = line_num + 1

       load_num = {}
       _len = 1
       for n in string.gmatch(line,"[+-]?[0-9]*[%.]?[0-9]+[e]?[+]?[-]?[0-9]*") do
           load_num[_len] = n
           _len = _len + 1
       end

       if _len < 4 then
           print("line no: "..line_num..", format invalid")
           io.close(file)
           return None
       end

       world_id = tonumber(load_num[1])
       worldwide_achv_id = tonumber(load_num[2])
       actor_num = tonumber(load_num[3])

       actor_rids = {}
       for i=1,_len-4,1 do
            actor_rids[i] = load_num[i+3]
       end

       result[worldwide_achv_id] = {worldwide_achv_id, actor_num, actor_rids}
      
       --print_one_result(result[worldwide_achv_id])
   end

   io.close(file)

   return result
end

--打印result
local print_load_result = function()
    for k,v in pairs(result) do
        print("world_achv["..k.."] has "..v[2].." actors")
        for sk,sv in ipairs(v[3]) do
            print("\tactor["..sk.."]:"..sv.."")
        end
    end
end

load_accounts_from_file("accounts.txt")

print_load_result()
    
