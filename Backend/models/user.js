
const mongoose = require('mongoose');

const userSchema = new mongoose.Schema({
  userId:String,
  username: String,
  password: String,
  email: String,
  phoneNumber: String,
  free: {type:Boolean,default:true},
});

const User = mongoose.model('User', userSchema);

module.exports = User;
