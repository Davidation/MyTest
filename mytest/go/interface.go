package main

import "fmt"

type People interface {
	Speak(string) string
}

type Student struct{}

func (stu *Student) Speak(think string) (talk string) {
	if think == "sb" {
		talk = "aaa"
	} else {
		talk = "bbb"
	}
	return
}

func main() {
	var peo People = &Student{}
	fmt.Println(peo);
	think := "bitch"
	fmt.Println(peo.Speak(think))
}
