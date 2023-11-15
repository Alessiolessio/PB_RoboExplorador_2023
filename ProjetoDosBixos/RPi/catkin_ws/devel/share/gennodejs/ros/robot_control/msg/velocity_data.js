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

class velocity_data {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.left_wheel_velocity = null;
      this.right_wheel_velocity = null;
    }
    else {
      if (initObj.hasOwnProperty('left_wheel_velocity')) {
        this.left_wheel_velocity = initObj.left_wheel_velocity
      }
      else {
        this.left_wheel_velocity = 0;
      }
      if (initObj.hasOwnProperty('right_wheel_velocity')) {
        this.right_wheel_velocity = initObj.right_wheel_velocity
      }
      else {
        this.right_wheel_velocity = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type velocity_data
    // Serialize message field [left_wheel_velocity]
    bufferOffset = _serializer.int64(obj.left_wheel_velocity, buffer, bufferOffset);
    // Serialize message field [right_wheel_velocity]
    bufferOffset = _serializer.int64(obj.right_wheel_velocity, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type velocity_data
    let len;
    let data = new velocity_data(null);
    // Deserialize message field [left_wheel_velocity]
    data.left_wheel_velocity = _deserializer.int64(buffer, bufferOffset);
    // Deserialize message field [right_wheel_velocity]
    data.right_wheel_velocity = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_control/velocity_data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b981a5e037792122a688d27bcc9ce412';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # velocity_data.msg
    
    int64 left_wheel_velocity
    int64 right_wheel_velocity
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new velocity_data(null);
    if (msg.left_wheel_velocity !== undefined) {
      resolved.left_wheel_velocity = msg.left_wheel_velocity;
    }
    else {
      resolved.left_wheel_velocity = 0
    }

    if (msg.right_wheel_velocity !== undefined) {
      resolved.right_wheel_velocity = msg.right_wheel_velocity;
    }
    else {
      resolved.right_wheel_velocity = 0
    }

    return resolved;
    }
};

module.exports = velocity_data;
