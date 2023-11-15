; Auto-generated. Do not edit!


(cl:in-package robot_control-msg)


;//! \htmlinclude encoder_data.msg.html

(cl:defclass <encoder_data> (roslisp-msg-protocol:ros-message)
  ((left_encoder_data
    :reader left_encoder_data
    :initarg :left_encoder_data
    :type cl:float
    :initform 0.0)
   (right_encoder_data
    :reader right_encoder_data
    :initarg :right_encoder_data
    :type cl:float
    :initform 0.0))
)

(cl:defclass encoder_data (<encoder_data>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <encoder_data>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'encoder_data)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_control-msg:<encoder_data> is deprecated: use robot_control-msg:encoder_data instead.")))

(cl:ensure-generic-function 'left_encoder_data-val :lambda-list '(m))
(cl:defmethod left_encoder_data-val ((m <encoder_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-msg:left_encoder_data-val is deprecated.  Use robot_control-msg:left_encoder_data instead.")
  (left_encoder_data m))

(cl:ensure-generic-function 'right_encoder_data-val :lambda-list '(m))
(cl:defmethod right_encoder_data-val ((m <encoder_data>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-msg:right_encoder_data-val is deprecated.  Use robot_control-msg:right_encoder_data instead.")
  (right_encoder_data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <encoder_data>) ostream)
  "Serializes a message object of type '<encoder_data>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'left_encoder_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'right_encoder_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <encoder_data>) istream)
  "Deserializes a message object of type '<encoder_data>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'left_encoder_data) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'right_encoder_data) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<encoder_data>)))
  "Returns string type for a message object of type '<encoder_data>"
  "robot_control/encoder_data")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'encoder_data)))
  "Returns string type for a message object of type 'encoder_data"
  "robot_control/encoder_data")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<encoder_data>)))
  "Returns md5sum for a message object of type '<encoder_data>"
  "e8a513d02103e6ca180cd050ef8b19c8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'encoder_data)))
  "Returns md5sum for a message object of type 'encoder_data"
  "e8a513d02103e6ca180cd050ef8b19c8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<encoder_data>)))
  "Returns full string definition for message of type '<encoder_data>"
  (cl:format cl:nil "# encoder_data.msg~%~%float64 left_encoder_data~%float64 right_encoder_data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'encoder_data)))
  "Returns full string definition for message of type 'encoder_data"
  (cl:format cl:nil "# encoder_data.msg~%~%float64 left_encoder_data~%float64 right_encoder_data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <encoder_data>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <encoder_data>))
  "Converts a ROS message object to a list"
  (cl:list 'encoder_data
    (cl:cons ':left_encoder_data (left_encoder_data msg))
    (cl:cons ':right_encoder_data (right_encoder_data msg))
))
