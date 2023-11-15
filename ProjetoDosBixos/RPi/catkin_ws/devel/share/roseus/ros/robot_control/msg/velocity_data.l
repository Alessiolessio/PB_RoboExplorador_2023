;; Auto-generated. Do not edit!


(when (boundp 'robot_control::velocity_data)
  (if (not (find-package "ROBOT_CONTROL"))
    (make-package "ROBOT_CONTROL"))
  (shadow 'velocity_data (find-package "ROBOT_CONTROL")))
(unless (find-package "ROBOT_CONTROL::VELOCITY_DATA")
  (make-package "ROBOT_CONTROL::VELOCITY_DATA"))

(in-package "ROS")
;;//! \htmlinclude velocity_data.msg.html


(defclass robot_control::velocity_data
  :super ros::object
  :slots (_left_wheel_velocity _right_wheel_velocity ))

(defmethod robot_control::velocity_data
  (:init
   (&key
    ((:left_wheel_velocity __left_wheel_velocity) 0)
    ((:right_wheel_velocity __right_wheel_velocity) 0)
    )
   (send-super :init)
   (setq _left_wheel_velocity (round __left_wheel_velocity))
   (setq _right_wheel_velocity (round __right_wheel_velocity))
   self)
  (:left_wheel_velocity
   (&optional __left_wheel_velocity)
   (if __left_wheel_velocity (setq _left_wheel_velocity __left_wheel_velocity)) _left_wheel_velocity)
  (:right_wheel_velocity
   (&optional __right_wheel_velocity)
   (if __right_wheel_velocity (setq _right_wheel_velocity __right_wheel_velocity)) _right_wheel_velocity)
  (:serialization-length
   ()
   (+
    ;; int64 _left_wheel_velocity
    8
    ;; int64 _right_wheel_velocity
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _left_wheel_velocity
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _left_wheel_velocity (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _left_wheel_velocity) (= (length (_left_wheel_velocity . bv)) 2)) ;; bignum
              (write-long (ash (elt (_left_wheel_velocity . bv) 0) 0) s)
              (write-long (ash (elt (_left_wheel_velocity . bv) 1) -1) s))
             ((and (class _left_wheel_velocity) (= (length (_left_wheel_velocity . bv)) 1)) ;; big1
              (write-long (elt (_left_wheel_velocity . bv) 0) s)
              (write-long (if (>= _left_wheel_velocity 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _left_wheel_velocity s)(write-long (if (>= _left_wheel_velocity 0) 0 #xffffffff) s)))
     ;; int64 _right_wheel_velocity
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _right_wheel_velocity (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _right_wheel_velocity) (= (length (_right_wheel_velocity . bv)) 2)) ;; bignum
              (write-long (ash (elt (_right_wheel_velocity . bv) 0) 0) s)
              (write-long (ash (elt (_right_wheel_velocity . bv) 1) -1) s))
             ((and (class _right_wheel_velocity) (= (length (_right_wheel_velocity . bv)) 1)) ;; big1
              (write-long (elt (_right_wheel_velocity . bv) 0) s)
              (write-long (if (>= _right_wheel_velocity 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _right_wheel_velocity s)(write-long (if (>= _right_wheel_velocity 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _left_wheel_velocity
#+(or :alpha :irix6 :x86_64)
      (setf _left_wheel_velocity (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _left_wheel_velocity (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _right_wheel_velocity
#+(or :alpha :irix6 :x86_64)
      (setf _right_wheel_velocity (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _right_wheel_velocity (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(setf (get robot_control::velocity_data :md5sum-) "b981a5e037792122a688d27bcc9ce412")
(setf (get robot_control::velocity_data :datatype-) "robot_control/velocity_data")
(setf (get robot_control::velocity_data :definition-)
      "# velocity_data.msg

int64 left_wheel_velocity
int64 right_wheel_velocity
")



(provide :robot_control/velocity_data "b981a5e037792122a688d27bcc9ce412")


