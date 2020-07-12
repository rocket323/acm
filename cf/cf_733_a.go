package main

import "fmt"

func main() {
	var s string
	fmt.Scanf("%s\n", &s)

	var last = -1
	ans := 0
	for i, v := range s {
		if v == 'A' || v == 'E' || v == 'I' || v == 'O' || v == 'U' || v == 'Y' {
			l := i - last
			if l > ans {
				ans = l
			}
			last = i
		}
	}
	l := len(s) - last
	if l > ans {
		ans = l
	}

	fmt.Println(ans)
}

