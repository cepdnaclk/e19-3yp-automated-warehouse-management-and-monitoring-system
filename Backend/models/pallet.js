
const mongoose = require('mongoose');

const palletSchema = new mongoose.Schema({
  palletId: {
    type: Number,
    required: true,
    unique: true,
  },
  status: {
    type: String,
    default: 'Available', // You can set a default status if needed
  },
  location: {type:String,default:'Base Station',},
  assignedWorker:{type:String,default:'',},
  currentWeight:{type:Number,default:0},
  batteryLevel:{type:Number,default:100},
});

const Pallet = mongoose.model('Pallet', palletSchema);

module.exports = Pallet;
