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
	UUID          uuid.UUID
	IP            string
	Health        int64
	toBeKeptAlive bool
}

var server = struct {
	state            C.ServerState
	timeOutTime      time.Duration
	connections      map[uuid.UUID]Client
	connectionsMutex sync.Mutex
}{state: C.ServerWait, timeOutTime: time.Second * 10, connections: make(map[uuid.UUID]Client)}

func serverStatus(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "%v\n", server.state)
}

func conncet(w http.ResponseWriter, r *http.Request) {
	new := uuid.New()
	client := Client{UUID: new, IP: r.RemoteAddr, Health: time.Now().Unix(), toBeKeptAlive: true}

	server.connectionsMutex.Lock()
	defer server.connectionsMutex.Unlock()
	server.connections[new] = client

	response := struct {
		Client      Client
		ServerState C.ServerState
	}{Client: client, ServerState: server.state}

	son, err := json.MarshalIndent(response, "", "	")
	if err != nil {
		log.Fatalf("%v\n", err)
	}

	go func(headerUUID uuid.UUID) {
		for {
			time.Sleep(server.timeOutTime)
			if func() bool {
				server.connectionsMutex.Lock()
				defer server.connectionsMutex.Unlock()

				client := server.connections[headerUUID]

				if client.Health == 0 {
					return true
				}

				if !client.toBeKeptAlive {
					fmt.Printf("Time passed for %v\n", client)
					delete(server.connections, client.UUID)
					return true
				}

				client.toBeKeptAlive = false

				server.connections[headerUUID] = client

				return false
			}() {
				break
			}
		}
	}(client.UUID)

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

	server.connectionsMutex.Lock()
	defer server.connectionsMutex.Unlock()
	client := server.connections[headerUUID]

	if client.Health == 0 {
		http.Error(w, "Bad UUID", http.StatusUnauthorized)
		return
	}

	client.Health = time.Now().Unix()

	client.toBeKeptAlive = true

	server.connections[headerUUID] = client

	response := struct {
		Client      Client
		ServerState C.ServerState
	}{Client: client, ServerState: server.state}

	son, err := json.MarshalIndent(response, "", "	")
	if err != nil {
		log.Fatalf("%v\n", err)
	}

	fmt.Fprintf(w, "%s\n", son)
}

func disconnect(w http.ResponseWriter, r *http.Request) {
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

	server.connectionsMutex.Lock()
	defer server.connectionsMutex.Unlock()

	client := server.connections[headerUUID]

	if client.Health == 0 {
		http.Error(w, "Bad UUID", http.StatusUnauthorized)
		return
	}

	delete(server.connections, headerUUID)

	response := struct {
		ServerState C.ServerState
	}{ServerState: server.state}

	son, err := json.MarshalIndent(response, "", "	")
	if err != nil {
		log.Fatalf("%v\n", err)
	}

	fmt.Fprintf(w, "%s\n", son)
}
