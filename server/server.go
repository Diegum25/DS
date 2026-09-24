// stupid links
// https://go.dev/doc/articles/wiki/#tmp_3
// https://go.dev/wiki/cgo
// https://pkg.go.dev/net/http#ServeMux

package main

/*
#include "../shared/shared.h"
*/
import "C"
import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"sync"
	"time"
	"uuid"
)

type Client struct {
	UUID   uuid.UUID
	IP     string
	Health time.Time
}

const (
	timeOutTime time.Duration = -time.Second * 5
)

var serverState C.ServerState = C.ServerWait

var connectionsMutex sync.Mutex
var connections = make(map[uuid.UUID]Client)

func serverStatus(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Ok\n")
}

func conncet(w http.ResponseWriter, r *http.Request) {
	new := uuid.New()
	client := Client{UUID: new, IP: r.RemoteAddr, Health: time.Now()}

	connectionsMutex.Lock()
	connections[new] = client
	connectionsMutex.Unlock()

	son, err := json.MarshalIndent(client, "", "	")
	if err != nil {
		log.Fatalf("%v\n", err)
	}

	fmt.Fprintf(w, "%s\n", son)

}

func heartbeat(w http.ResponseWriter, r *http.Request) {
	headerUUIDString := r.Header["Uuid"]

	if headerUUIDString == nil {
		return
	}

	headerUUID, err := uuid.Parse(headerUUIDString[0])

	if err != nil {
		return
	}

	connectionsMutex.Lock()
	client := connections[headerUUID]

	if client.UUID == uuid.Nil() {
		connectionsMutex.Unlock()
		return
	}

	client.Health = time.Now()
	connections[headerUUID] = client
	connectionsMutex.Unlock()

	response := struct {
		Client      Client
		ServerState C.ServerState
	}{Client: client, ServerState: serverState}

	son, err := json.MarshalIndent(response, "", "	")
	if err != nil {
		log.Fatalf("%v\n", err)
	}

	fmt.Fprintf(w, "%s\n", son)
}

func feetusDeletus() {
	for {
		connectionsMutex.Lock()

		u := time.Now().Add(timeOutTime)

		for UUID, client := range connections {
			if client.Health.Before(u) {
				fmt.Printf("time has passed for %v\n", client)
				delete(connections, UUID)
			}
		}

		//fmt.Printf("%v\n", connections)
		connectionsMutex.Unlock()

		time.Sleep(time.Duration(time.Second))
	}
}

func main() {
	http.HandleFunc("GET /{$}", serverStatus)
	http.HandleFunc("GET /connect", conncet)
	http.HandleFunc("POST /heartbeat", heartbeat)

	go feetusDeletus()

	log.Fatal(http.ListenAndServe(":8080", nil))
}
