package main

import (
	"fmt"
	MQTT "github.com/eclipse/paho.mqtt.golang"
	"os"
	"encoding/json"
	"strconv"
	"os/signal"
	"time"
)

type MetaData struct {
	Frequency float64
	Datarate string
	Codingrate string
	Gateway_timestamp int
	Gateway_time string
	Channel int
	Server_time string
	Rssi float64
	Lsnr float64
	Rfchain int
	Crc int
	Modulation string
	Gateway_eui string
	Altitude float64
	Longitude float64
	Latitude float64
}

type Fields struct {
	Lux int
	Temperature float64
}

type Data struct {
	Payload string
	Fields Fields
	Port int
	Counter int
	Dev_eui string
	Metadata []MetaData
}

var OSc MQTT.Client
var OSTopic string
var TTNc MQTT.Client


// Callback
var mHandler MQTT.MessageHandler = func(client MQTT.Client, msg MQTT.Message) {
	fmt.Printf("TOPIC: %s\n", msg.Topic())
	fmt.Printf("MSG: %s\n", msg.Payload())

	data := Data{}
	err := json.Unmarshal(msg.Payload(), &data)

	if err != nil {
		panic(err.Error())
		return
	}

	token := OSc.Publish(OSTopic, 0, false, []byte("Dev_eui : " + data.Dev_eui))
	token.Wait()
	token = OSc.Publish(OSTopic, 0, false, []byte("Temperature : " + strconv.FormatFloat(data.Fields.Temperature, 'f', 2, 64)))
	token.Wait()
}

func exit() {

	TTNc.Disconnect(250)
	OSc.Disconnect(250)
	fmt.Println("\nExit.\n")
	os.Exit(0)
}

func init() {

	var text string

	//OpenSensor init
	OSopts := MQTT.NewClientOptions().AddBroker("tcp://mqtt.opensensors.io:1883")
	fmt.Print("OpenSensor ClientID: ")
	fmt.Scanln(&text)
	OSopts.SetClientID(text)
	fmt.Print("OpenSensor Username: ")
	fmt.Scanln(&text)
	OSopts.SetUsername(text)
	fmt.Print("OpenSensor Password: ")
	fmt.Scanln(&text)
	OSopts.SetPassword(text)
	fmt.Print("OpenSensor Topic: ")
	fmt.Scanln(&text)
	OSTopic = text
	OSopts.SetConnectTimeout(5 * time.Second)
	OSopts.SetPingTimeout(5 * time.Second)

	OSc = MQTT.NewClient(OSopts)
	if token := OSc.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
		exit()
	}

	//TheThingsNetwork broker init
	TTNopts := MQTT.NewClientOptions().AddBroker("tcp://staging.thethingsnetwork.org:1883")
	fmt.Print("TheThingsNetwork Username: ")
	fmt.Scanln(&text)
	TTNopts.SetUsername(text)
	fmt.Print("TheThingsNetwork Password: ")
	fmt.Scanln(&text)
	TTNopts.SetPassword(text)
	TTNopts.SetDefaultPublishHandler(mHandler)
	TTNopts.SetConnectTimeout(5 * time.Second)
	TTNopts.SetPingTimeout(5 * time.Second)

	TTNc = MQTT.NewClient(TTNopts)
	if token := TTNc.Connect(); token.Wait() && token.Error() != nil {
		panic(token.Error())
		exit()
	}

	if token := TTNc.Subscribe(TTNopts.Username + "/devices/+/up", 0, nil); token.Wait() && token.Error() != nil {
		fmt.Println(token.Error())
		exit()
	}
}

func main() {

	s := make(chan os.Signal, 1)
	signal.Notify(s, os.Interrupt)
	go func() {
		<-s
		exit()
		os.Exit(1)
	}()

	for TTNc.IsConnected() != false  {

	}
	exit()
}
