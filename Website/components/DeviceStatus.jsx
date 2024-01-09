import React from "react";
import mqtt from "mqtt";
import { useState, useEffect } from "react";


function DeviceStatus() {
  const [mainControllerStatus, setMainControllerStatus] = useState("Unknown");
  const [scanControllerStatus, setScanControllerStatus] = useState("Unknown");
  const [securityControllerStatus, setSecurityControllerStatus] =
    useState("Unknown");

  const clientId = "emqx_react_" + Math.random().toString(16).substring(2, 8);
  const username = "emqx_test";
  const password = "emqx_test";
  const mainControllerTopic = "esp8266/test";
//   const scanControllerTopic = "3yp_device_1/scan_controller";
//   const securityControllerTopic = "3yp_device_1/security_controller";

  useEffect(() => {
    const client = mqtt.connect("wss://broker.emqx.io:8084/mqtt", {
      clientId,
      username,
      password,
      // ...other options
    });

    client.on("connect", () => {
      console.log("Connected to MQTT broker");

      // Subscribe to topics
      client.subscribe(mainControllerTopic, (err) => {
        if (!err) {
          console.log(`Subscribed to ${mainControllerTopic}`);
        }
      });

    //   client.subscribe(scanControllerTopic, (err) => {
    //     if (!err) {
    //       console.log(`Subscribed to ${scanControllerTopic}`);
    //     }
    //   });

    //   client.subscribe(securityControllerTopic, (err) => {
    //     if (!err) {
    //       console.log(`Subscribed to ${securityControllerTopic}`);
    //     }
    //   });
    });

    client.on("message", (topic, message) => {
      // Received message from the subscribed topic
      console.log(
        `Received message: ${message.toString()} from topic: ${topic}`
        );
    

      //const status = JSON.parse(message.toString()).tagIDs ;

      // Update state based on the controller type
      if (topic === mainControllerTopic) {
        setMainControllerStatus(message.toString());
    //   } else if (topic === scanControllerTopic) {
    //     setScanControllerStatus(status);
    //   } else if (topic === securityControllerTopic) {
    //     setSecurityControllerStatus(status);
      }
    });

    return () => {
      // Disconnect the client when the component unmounts
      client.end();
    };
  }, []);

  // auto update status to offline after 5 seconds
//   useEffect(() => {
//     const interval = setInterval(() => {
//       setMainControllerStatus("Offline");
//       setScanControllerStatus("Offline");
//       setSecurityControllerStatus("Offline");
//     }, 5000);
//     return () => clearInterval(interval);
//   }, [mainControllerStatus, scanControllerStatus, securityControllerStatus]);

    return (
        <div>
            <h2>Received : {mainControllerStatus}</h2>
        </div>
        
  );
}

export default DeviceStatus;
