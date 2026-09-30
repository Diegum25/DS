package main

import (
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("GET /{$}", serverStatus)
	http.HandleFunc("GET /connect", conncet)
	http.HandleFunc("POST /heartbeat", heartbeat)
	http.HandleFunc("POST /disconnect", disconnect)

	log.Fatal(http.ListenAndServe(":57165", nil))
}
