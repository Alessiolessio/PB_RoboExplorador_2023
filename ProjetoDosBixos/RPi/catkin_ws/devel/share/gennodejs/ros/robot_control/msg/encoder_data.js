// Auto-generated. Do not edit!

// (in-package robot_control.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class encoder_data {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.left_encoder_data = null;
      this.right_encoder_data = null;
    }
    else {
      if (initObj.hasOwnProperty('left_encoder_data')) {
        this.left_encoder_data = initObj.left_encoder_data
      }
      else {
        this.left_encoder_data = 0.0;
      }
      if (initObj.hasOwnProperty('right_encoder_data')) {
        this.right_encoder_data = initObj.right_encoder_data
      }
      else {
        this.right_encoder_data = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type encoder_data
    // Serialize message field [left_encoder_data]
    bufferOffset = _serializer.float64(obj.left_encoder_data, buffer, bufferOffset);
    // Serialize message field [right_encoder_data]
    bufferOffset = _serializer.float64(obj.right_encoder_data, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type encoder_data
    let len;
    let data = new encoder_data(null);
    // Deserialize message field [left_encoder_data]
    data.left_encoder_data = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [right_encoder_data]
    data.right_encoder_data = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_control/encoder_data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e8a513d02103e6ca180cd050ef8b19c8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # encoder_data.msg
    
    float64 left_encoder_data
    float64 right_encoder_data
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new encoder_data(null);
    if (msg.left_encoder_data !== undefined) {
      resolved.left_encoder_data = msg.left_encoder_data;
    }
    else {
      resolved.left_encoder_data = 0.0
    }

    if (msg.right_encoder_data !== undefined) {
      resolved.right_encoder_data = msg.right_encoder_data;
    }
    else {
      resolved.right_encoder_data = 0.0
    }

    return resolved;
    }
};

module.exports = encoder_data;
