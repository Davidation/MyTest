package main

import "fmt"

type User struct {
    id   int
    name string
}

func (self *User) Test() {
    fmt.Printf("%p, %v\n", self, self)
}

func main() {
    u := User{1, "Tom"}
    u.Test()

    mValue := u.Test
    mValue() // ÒþÊ½´«µÝ receiver

    mExpression := (*User).Test
    mExpression(&u) // ÏÔÊ½´«µÝ receiver
}
