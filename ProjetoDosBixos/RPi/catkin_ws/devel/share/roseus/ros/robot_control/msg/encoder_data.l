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
    ((:left_encoder_data __left_encoder_data) 0)
    ((:right_encoder_data __right_encoder_data) 0)
    )
   (send-super :init)
   (setq _left_encoder_data (round __left_encoder_data))
   (setq _right_encoder_data (round __right_encoder_data))
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
    ;; int64 _left_encoder_data
    8
    ;; int64 _right_encoder_data
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _left_encoder_data
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _left_encoder_data (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _left_encoder_data) (= (length (_left_encoder_data . bv)) 2)) ;; bignum
              (write-long (ash (elt (_left_encoder_data . bv) 0) 0) s)
              (write-long (ash (elt (_left_encoder_data . bv) 1) -1) s))
             ((and (class _left_encoder_data) (= (length (_left_encoder_data . bv)) 1)) ;; big1
              (write-long (elt (_left_encoder_data . bv) 0) s)
              (write-long (if (>= _left_encoder_data 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _left_encoder_data s)(write-long (if (>= _left_encoder_data 0) 0 #xffffffff) s)))
     ;; int64 _right_encoder_data
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _right_encoder_data (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _right_encoder_data) (= (length (_right_encoder_data . bv)) 2)) ;; bignum
              (write-long (ash (elt (_right_encoder_data . bv) 0) 0) s)
              (write-long (ash (elt (_right_encoder_data . bv) 1) -1) s))
             ((and (class _right_encoder_data) (= (length (_right_encoder_data . bv)) 1)) ;; big1
              (write-long (elt (_right_encoder_data . bv) 0) s)
              (write-long (if (>= _right_encoder_data 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _right_encoder_data s)(write-long (if (>= _right_encoder_data 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _left_encoder_data
#+(or :alpha :irix6 :x86_64)
      (setf _left_encoder_data (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _left_encoder_data (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _right_encoder_data
#+(or :alpha :irix6 :x86_64)
      (setf _right_encoder_data (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _right_encoder_data (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
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

(setf (get robot_control::encoder_data :md5sum-) "1276b5c4b2bbf74e766582a5b67bb9b6")
(setf (get robot_control::encoder_data :datatype-) "robot_control/encoder_data")
(setf (get robot_control::encoder_data :definition-)
      "# encoder_data.msg

int64 left_encoder_data
int64 right_encoder_data
")



(provide :robot_control/encoder_data "1276b5c4b2bbf74e766582a5b67bb9b6")


