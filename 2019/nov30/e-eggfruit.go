
package main

import (
    // formatted IO
    // https://golang.org/pkg/fmt/
    "fmt"
    _ "bufio"
    "os"
    // IO utility functions
    _ "io/ioutil"
    // math library alias to m
    // m "math"
    // web server stuff
    _ "net/http"
    // OS and file system functions
    // string conversions
    _ "strconv"
)

func ok(err error) {
    if err != nil {
        panic(err)
    }
}

func Min(x, y int) int {
    if x < y {
        return x
    }
    return y
}

func Max(x, y int) int {
    if x < y {
        return y
    }
    return x
}

/*
I get TLE on this problem
*/

func cakeProblem() {
    // cake contains E or P
    // slice should contain at least one E
    var cake, cake_in string
    var s, dist int
    var count int64 = 0
    _, err := fmt.Fscan(os.Stdin, &cake_in, &s)
    ok(err)
    cake = cake_in + cake_in;
    n := len(cake_in)
    a := make([]int, n*2)

    a[0] = -1;
    for i := 1; i < n * 2; i++ {
        if cake[i - 1] == 'E' {
            a[i] = i - 1
        } else {
            a[i] = a[i - 1]
        }

        if i >= n {
            if a[i] == -1 {
                break;
            }
            if cake[i] == 'E' {
                dist = i - a[i]
                for j := 1; j <= Min(dist, s); j++ {
                    count += int64(j)
                }
                for j := dist + 1; j <= s; j++ {
                    count += int64(dist)
                }
            }
        }
    }

    fmt.Println(count)
}

func main() {
    cakeProblem()
}

