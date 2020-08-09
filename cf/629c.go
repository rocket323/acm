package main

import "fmt"

var n, m int
var s string
const mod = 1e9 + 7
var f [2010][2010]int

func gao() {
	maxOwn, curOpen := 0, 0
	for _, c := range s {
		if c == '(' {
			curOpen++
		} else {
			curOpen--
		}
		if curOpen < 0 {
			if -curOpen > maxOwn { maxOwn = -curOpen }
		}
	}
	l := n - m
	f[0][0] = 1
	
	for i := 0; i < l; i++ {
		for j := 0; j <= i; j++ {
			if f[i][j] == 0 { continue }

			f[i+1][j+1] = (f[i+1][j+1] + f[i][j]) % mod
			if j > 0 {
				f[i+1][j-1] = (f[i+1][j-1] + f[i][j]) % mod
			}
		}
	}

	var ans int64
	for i := maxOwn; i <= l; i++ {
		for j := maxOwn; j <= i; j++ {
			if f[i][j] == 0 { continue }

			k := j + curOpen
			if k > l - i { continue }
			rv := f[l - i][k]

			ans = (ans + int64(f[i][j]) * int64(rv)) % mod
		}
	}
	fmt.Println(ans)
}

func main() {
	fmt.Scanf("%d%d\n", &n, &m)
	fmt.Scanf("%s\n", &s)

	gao()
}

