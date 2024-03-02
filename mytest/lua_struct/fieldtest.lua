actor_list ={"16159196954426314188"}

function lua_func(actor_rid)
    if actor_list[1] == actor_rid then
        print("hhhh")
    end
    print("xxx")
end

lua_func("16159196954426314188")
lua_func(2)
