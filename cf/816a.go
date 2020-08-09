package main

import (
    "fmt"
)

func toNum(s string) int {
    h := (int(s[0]) - int('0')) * 10 + (int(s[1]) - int('0'))
    m := (int(s[3]) - int('0')) * 10 + (int(s[4]) - int('0'))
    return h * 60 + m
}

func isPalindrome(n int) bool {
    h := n / 60
    m := n % 60

    a := fmt.Sprintf("%02d:%02d", h, m)
    for i := 0; i < len(a); i++ {
        if a[i] != a[len(a) - 1 - i] {
            return false
        }
    }
    return true
}

func main() {
    var s string
    for {
        _, err := fmt.Scan(&s)
        if err != nil { break }

        n := toNum(s)
        t := 0
        for {
            if isPalindrome(n) {
                break
            }
            t++
            n = (n + 1) % (24 * 60)
        }
        fmt.Println(t)
    }
}

