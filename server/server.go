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
	Health int64
}

const (
	timeOutTime time.Duration = time.Second * 5
)

var serverState C.ServerState = C.ServerWait

var connectionsMutex sync.Mutex
var connections = make(map[uuid.UUID]Client)

func serverStatus(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "%v\n", serverState)
}

func conncet(w http.ResponseWriter, r *http.Request) {
	new := uuid.New()
	client := Client{UUID: new, IP: r.RemoteAddr, Health: time.Now().Unix()}

	connectionsMutex.Lock()
	defer connectionsMutex.Unlock()
	connections[new] = client

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

func heartbeat(w http.ResponseWriter, r *http.Request) {
	headerUUIDString := r.Header["Uuid"]

	if headerUUIDString == nil {
		http.Error(w, "No UUID", http.StatusBadRequest)
		return
	}

	headerUUID, err := uuid.Parse(headerUUIDString[0])

	if err != nil {
		http.Error(w, "Malformed UUID", http.StatusNotAcceptable)
		return
	}

	connectionsMutex.Lock()
	defer connectionsMutex.Unlock()
	client := connections[headerUUID]

	if client.UUID == uuid.Nil() {
		http.Error(w, "Bad UUID", http.StatusUnauthorized)
		return
	}

	client.Health = time.Now().Unix()
	connections[headerUUID] = client

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

func disconnect(w http.ResponseWriter, r *http.Request) {
	http.Error(w, "Not implemented :P", http.StatusNotImplemented)
}

func feetusDeletus() {
	for {
		func() {
			connectionsMutex.Lock()
			defer connectionsMutex.Unlock()

			u := time.Now().Add(-timeOutTime).Unix()

			for UUID, client := range connections {
				if client.Health < u {
					fmt.Printf("time has passed for %v\n", client)
					delete(connections, UUID)
				}
			}

			//fmt.Printf("%v\n", connections)
		}()
		time.Sleep(time.Duration(time.Second))
	}
}

func main() {
	http.HandleFunc("GET /{$}", serverStatus)
	http.HandleFunc("GET /connect", conncet)
	http.HandleFunc("POST /heartbeat", heartbeat)
	http.HandleFunc("POST /disconnect", disconnect)

	go feetusDeletus()

	log.Fatal(http.ListenAndServe(":57165", nil))
}
