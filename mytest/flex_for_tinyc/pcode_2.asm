push 1
push 2
$sum

FUNC @sum:
    arg a, b

    push a
    push b
    add
    ret ~
ENDFUNC
