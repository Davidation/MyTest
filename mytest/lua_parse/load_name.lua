local load_name_from_file = function(file_name)
    file = io.open(file_name)
    if file == nil then
        print("load file "..file_name.."failed")
        return
    end

    line_num = 0
    for line in file:lines() do
        line_num = line_num + 1

        load_num = {}
        _len = 1
        for n in string.gmatch(line,"%S+") do
            load_num[_len] = n
            _len = _len + 1
        end

        print(load_num[1], load_num[2])

        if _len < 3 then
            print("line no: "..line_num..", format invalid")
            io.close(file)
            return
        end
    end

    io.close(file)

    return result
end

load_name_from_file("name.txt")

