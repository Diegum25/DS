// https://go.dev/doc/articles/wiki/#tmp_3
package main

import (
	"fmt"
	"log"
	"net/http"
)

func root(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Got Request")
	fmt.Fprintf(w, "Hello my name %s\n", r.URL.Path[1:])
}

func main() {
	http.HandleFunc("/", root)
	log.Fatal(http.ListenAndServe(":8080", nil))
}
