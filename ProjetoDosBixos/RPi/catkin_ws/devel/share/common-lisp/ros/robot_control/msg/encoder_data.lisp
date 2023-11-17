; Auto-generated. Do not edit!


(cl:in-package robot_control-msg)


;//! \htmlinclude encoder_data.msg.html

(cl:defclass <encoder_data> (roslisp-msg-protocol:ros-message)
  ((left_encoder_data
    :reader left_encoder_data
    :initarg :left_encoder_data
    :type cl:integer
    :initform 0)
   (right_encoder_data
    :reader right_encoder_data
    :initarg :right_encoder_data
    :type cl:integer
    :initform 0))
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
  (cl:let* ((signed (cl:slot-value msg 'left_encoder_data)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'right_encoder_data)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <encoder_data>) istream)
  "Deserializes a message object of type '<encoder_data>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'left_encoder_data) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'right_encoder_data) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
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
  "1276b5c4b2bbf74e766582a5b67bb9b6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'encoder_data)))
  "Returns md5sum for a message object of type 'encoder_data"
  "1276b5c4b2bbf74e766582a5b67bb9b6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<encoder_data>)))
  "Returns full string definition for message of type '<encoder_data>"
  (cl:format cl:nil "# encoder_data.msg~%~%int64 left_encoder_data~%int64 right_encoder_data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'encoder_data)))
  "Returns full string definition for message of type 'encoder_data"
  (cl:format cl:nil "# encoder_data.msg~%~%int64 left_encoder_data~%int64 right_encoder_data~%~%"))
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
