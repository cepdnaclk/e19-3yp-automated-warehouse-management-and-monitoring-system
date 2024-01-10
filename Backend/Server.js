const express = require('express');
const mongoose = require('mongoose');
const User = require('./models/user');
const Pallet = require('./models/pallet');
const bodyParser = require('body-parser');
const cors = require('cors'); // Import the cors middlewareconst http = require('http');
const http = require('http');
const socketIo = require('socket.io');
// const mqtt = require("mqtt");


const app = express();
app.use(cors());
app.use(bodyParser.json());
const port = 3001;

// Connect to MongoDB Atlas
mongoose.connect('mongodb+srv://dolly:dolly@cluster0.5kvep8k.mongodb.net/?retryWrites=true&w=majority');
const db = mongoose.connection;
db.on('error', console.error.bind(console, 'MongoDB connection error:'));


async function getPalletJacksData() {
  try {
    const pallets = await Pallet.find();
    return pallets.map(pallet => ({
      palletId: pallet.palletId,
      status: pallet.status,
      location: pallet.location,
      assignedWorker: pallet.assignedWorker,
      batteryLevel: pallet.batteryLevel,
      currentWeight: pallet.currentWeight
    }));
  } catch (error) {
    console.error('Error fetching pallet data:', error);
    return [];
  }
}

async function getEmployees() {
  try {
    const users = await User.find();
    return users.map(u => ({
      userId: u.userId,
      username: u.username,
      email : u.email,
      phoneNumber: u.phoneNumber,
      available: u.free,
    }));
  } catch (error) {
    console.error('Error fetching pallet data:', error);
    return [];
  }
}

// Create HTTP server and attach Socket.io
const server = http.createServer(app);
const io = socketIo(server, {
  cors: {
    origin:  "*", // Your frontend domain
    methods: ["GET", "POST"]
  }
});

io.on('connection', async (socket) => {
  socket.emit('palletJacks', await getPalletJacksData());
  socket.emit('employees', await getEmployees());
});


// const clientId = "emqx_express_" + Math.random().toString(16).substring(2, 8);
// const username = "emqx_test";
// const password = "emqx_test";
// const mainControllerTopic = "esp8266/test";

// // Create an MQTT client
// const mqttClient = mqtt.connect("wss://broker.emqx.io:8084/mqtt", {
//   clientId,
//   username,
//   password,
// });

// mqttClient.on("connect", () => {
//   console.log("Connected to MQTT broker");

//   // Subscribe to the main controller topic
//   mqttClient.subscribe(mainControllerTopic, (err) => {
//     if (!err) {
//       console.log(mainControllerTopic);
//     }
//   });
// });

// mqttClient.on("message", (topic, message) => {
//   // Received message from the subscribed topic
//   console.log(message.toString());
//   // You can process the message here or send it to your Express routes.
// });



app.post('/signup', async (req, res) => {
  const { username, password,email,phoneNumber,userId } = req.body;
  console.log(req.body);

  if (!username || !password) {
    return res.status(400).json({ error: 'Username and password are required' });
  }
  const newUser = new User({ username, password,email,phoneNumber,userId });

  try {
    await newUser.save();
    res.status(201).json({ message: 'User created successfully' });
  } catch (error) {
    console.error(error);
    res.status(500).json({ error: 'Internal server error' });
  }
});


app.post('/login', async (req, res) => {
    const { username, password} = req.body;
  
    if (!username || !password) {
      return res.status(400).json({ error: 'Username and password are required' });
    }
    console.log(req.body);
    try {
      // Find all users in the database with the provided username
      const users = await User.find({ username });
  
      // Check if any user with the given username exists and if the password matches (you should use bcrypt for real-world scenarios)
      const validUser = users.find(user => user.password === password);
  
      if (validUser) {
        res.status(200).json({ message: 'Login successful' });
      } else {
        res.status(401).json({ error: 'Invalid credentials' });
      }
    } catch (error) {
      console.error('Error during login:', error);
      res.status(500).json({ error: 'Internal server error' });
    }
  });


  app.post('/addpallet', async (req, res) => {
    const { palletId, assignedWorker} = req.body;
    console.log(req.body);
  
    try {
      // Check if a pallet with the same palletId exists in the database
      const existingPallet = await Pallet.findOne({ palletId });
  
      if (existingPallet) {
        // If exists, update the assignedWorker field
        if(assignedWorker==''){
          existingPallet.assignedWorker = assignedWorker;
          existingPallet.status = 'Available';
        }else{
          existingPallet.assignedWorker = assignedWorker;
          existingPallet.status = 'Unavailable';
        }
        await existingPallet.save();
        res.status(200).json({ message: 'Pallet updated successfully' });
      } else {
        // If doesn't exist, create a new pallet entry
        const newPallet = new Pallet({
          palletId,
          assignedWorker,
        });
        if(assignedWorker==''){
          newPallet.status = 'Available';
        }else{
          newPallet.status = 'Unavailable';
        }
        await newPallet.save();
        res.status(200).json({ message: 'Pallet added successfully' });

      }   
    } catch (error) {
      console.error(error);
      res.status(500).json({ error: 'Internal server error' });
    }
    io.emit('palletJacks', await getPalletJacksData());
  });

server.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});


app.get('/palletJacksData', async (req, res) => {
  try {
    res.json(await getPalletJacksData());
  } catch (error) {
    console.error('Error fetching pallet data:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

// // Start the server
// app.listen(port, () => {
//   console.log(`Server is running on http://localhost:${port}`);
// });