; Auto-generated. Do not edit!


(cl:in-package robot_control-msg)


;//! \htmlinclude velocity_data.msg.html

(cl:defclass <velocity_data> (roslisp-msg-protocol:ros-message)
  ((left_wheel_velocity
    :reader left_wheel_velocity
    :initarg :left_wheel_velocity
    :type cl:integer
    :initform 0)
   (right_wheel_velocity
    :reader right_wheel_velocity
    :initarg :right_wheel_velocity
    :type cl:integer
    :initform 0))
)

(cl:defclass velocity_data (<velocity_data>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <velocity_data>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'velocity_data)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_control-msg:<velocity_data> is deprecated: use robot_control-msg:velocity_data instead.")))

(cl:ensure-generic-function 'left_wheel_velocity-val :lambda-list '(m))
(cl:defmethod left_wheel_velocity-val ((m <velocity_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-msg:left_wheel_velocity-val is deprecated.  Use robot_control-msg:left_wheel_velocity instead.")
  (left_wheel_velocity m))

(cl:ensure-generic-function 'right_wheel_velocity-val :lambda-list '(m))
(cl:defmethod right_wheel_velocity-val ((m <velocity_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-msg:right_wheel_velocity-val is deprecated.  Use robot_control-msg:right_wheel_velocity instead.")
  (right_wheel_velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <velocity_data>) ostream)
  "Serializes a message object of type '<velocity_data>"
  (cl:let* ((signed (cl:slot-value msg 'left_wheel_velocity)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'right_wheel_velocity)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <velocity_data>) istream)
  "Deserializes a message object of type '<velocity_data>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'left_wheel_velocity) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'right_wheel_velocity) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<velocity_data>)))
  "Returns string type for a message object of type '<velocity_data>"
  "robot_control/velocity_data")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'velocity_data)))
  "Returns string type for a message object of type 'velocity_data"
  "robot_control/velocity_data")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<velocity_data>)))
  "Returns md5sum for a message object of type '<velocity_data>"
  "b981a5e037792122a688d27bcc9ce412")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'velocity_data)))
  "Returns md5sum for a message object of type 'velocity_data"
  "b981a5e037792122a688d27bcc9ce412")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<velocity_data>)))
  "Returns full string definition for message of type '<velocity_data>"
  (cl:format cl:nil "# velocity_data.msg~%~%int64 left_wheel_velocity~%int64 right_wheel_velocity~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'velocity_data)))
  "Returns full string definition for message of type 'velocity_data"
  (cl:format cl:nil "# velocity_data.msg~%~%int64 left_wheel_velocity~%int64 right_wheel_velocity~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <velocity_data>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <velocity_data>))
  "Converts a ROS message object to a list"
  (cl:list 'velocity_data
    (cl:cons ':left_wheel_velocity (left_wheel_velocity msg))
    (cl:cons ':right_wheel_velocity (right_wheel_velocity msg))
))