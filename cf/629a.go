package main

import (
	"fmt"
)

func main() {
	var n int
	var g []string
	ans := 0

	fmt.Scanf("%d\n", &n)
	for i := 0; i < n; i++ {
		var line string
		fmt.Scanf("%s\n", &line)
		g = append(g, line)

		cnt := 0
		for _, c := range line {
			if c == 'C' {
				cnt++
			}
		}
		ans += cnt * (cnt - 1) / 2
	}

	for c := 0; c < n; c++ {
		cnt := 0
		for r := 0; r < n; r++ {
			if g[r][c] == 'C' {
				cnt++
			}
		}
		ans += cnt * (cnt - 1) / 2
	}
	fmt.Println(ans)
}

