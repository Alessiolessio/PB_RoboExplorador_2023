;; Auto-generated. Do not edit!


(when (boundp 'robot_control::encoder_data)
  (if (not (find-package "ROBOT_CONTROL"))
    (make-package "ROBOT_CONTROL"))
  (shadow 'encoder_data (find-package "ROBOT_CONTROL")))
(unless (find-package "ROBOT_CONTROL::ENCODER_DATA")
  (make-package "ROBOT_CONTROL::ENCODER_DATA"))

(in-package "ROS")
;;//! \htmlinclude encoder_data.msg.html


(defclass robot_control::encoder_data
  :super ros::object
  :slots (_left_encoder_data _right_encoder_data ))

(defmethod robot_control::encoder_data
  (:init
   (&key
    ((:left_encoder_data __left_encoder_data) 0.0)
    ((:right_encoder_data __right_encoder_data) 0.0)
    )
   (send-super :init)
   (setq _left_encoder_data (float __left_encoder_data))
   (setq _right_encoder_data (float __right_encoder_data))
   self)
  (:left_encoder_data
   (&optional __left_encoder_data)
   (if __left_encoder_data (setq _left_encoder_data __left_encoder_data)) _left_encoder_data)
  (:right_encoder_data
   (&optional __right_encoder_data)
   (if __right_encoder_data (setq _right_encoder_data __right_encoder_data)) _right_encoder_data)
  (:serialization-length
   ()
   (+
    ;; float64 _left_encoder_data
    8
    ;; float64 _right_encoder_data
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _left_encoder_data
       (sys::poke _left_encoder_data (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _right_encoder_data
       (sys::poke _right_encoder_data (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _left_encoder_data
     (setq _left_encoder_data (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _right_encoder_data
     (setq _right_encoder_data (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get robot_control::encoder_data :md5sum-) "e8a513d02103e6ca180cd050ef8b19c8")
(setf (get robot_control::encoder_data :datatype-) "robot_control/encoder_data")
(setf (get robot_control::encoder_data :definition-)
      "# encoder_data.msg

float64 left_encoder_data
float64 right_encoder_data
")



(provide :robot_control/encoder_data "e8a513d02103e6ca180cd050ef8b19c8")


