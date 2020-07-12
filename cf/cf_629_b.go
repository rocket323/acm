package main

import "fmt"

var n int

type Node struct {
	sex byte
	a, b int
}
var l []Node

func gao(d int) int {
	f := 0
	m := 0
	for _, v := range l {
		if v.a <= d && d <= v.b {
			if v.sex == 'F' { f++ }
			if v.sex == 'M' { m++ }
		}
	}
	if f < m { return f }
	return m
}

func main() {
	fmt.Scanf("%d\n", &n)
	for i := 0; i < n; i++ {
		var node Node
		fmt.Scanf("%c%d%d\n", &node.sex, &node.a, &node.b)
		l = append(l, node)
	}

	ans := 0
	for d := 1; d <= 366; d++ {
		tmp := gao(d) * 2
		if tmp > ans {
			ans = tmp
		}
	}
	fmt.Println(ans)
}

