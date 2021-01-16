;; The stack, implemented in common-lisp with a interactive interface
;; Written by Iep Iweidieng on 2018-11-02
;; Tested on gnu clisp 2.49


(defclass stack ()
    ((data :type vector :initform (make-array 8 :adjustable T))
     (size :type integer :initform 0 :reader size)))

(defmethod copy ((self stack))
    (let ((self-copy (make-instance 'stack)))
        (setf (slot-value self-copy 'data)
              (make-array (capacity self) :adjustable T
                    :initial-contents (slot-value self 'data)))
        (setf (slot-value self-copy 'size) (size self))
        self-copy))

(defmethod capacity ((self stack))
    (array-dimension (slot-value self 'data) 0))

(defmethod is-empty ((self stack))
    (zerop (size self)))

(defmethod is-full ((self stack))
    "Check whether the stack is full"
    (>= (size self) (capacity self)))

(defmethod push-top ((self stack) value)
    "Push a value into the stack.
     Allocate space to the stack if necessary."

    (when (is-full self)
        ;; When the stack is full, double the capacity of the stack
        (adjust-array (slot-value self 'data)
                      (max (* 2 (capacity self)) 1)))

    (setf (aref (slot-value self 'data) (size self)) value)
    (incf (slot-value self 'size))
    self)

(defmethod pop-top ((self stack))
    (unless (is-empty self)
        (setf (aref (slot-value self 'data) (- (size self) 1)) NIL)
        (decf (slot-value self 'size)))
    self)

(defmethod top ((self stack))
    (if (is-empty self)
        NIL
        (aref (slot-value self 'data) (- (size self) 1))))

(defmethod show ((self stack))
    (format T "   -~14:@<= Top =~>-~%")
    (labels ((show-internal ((self-copy stack))
                (unless (is-empty self-copy)
                    (format T "   ~16:@<~S~>~%" (top self-copy))
                    (show-internal (pop-top self-copy)))))
        (show-internal (copy self)))
    (format T "   -~14:@<= Bottom =~>-~%")
    self)


(defun main ()
    (loop with *readtable* = (copy-readtable NIL)
          with the-stack = (make-instance 'stack)
          with whether-show-prompt = NIL
          with will-exit = NIL
          with action = ""

          initially (progn
            (format T "Welcome, you have acquired a stack!~%")
            (show the-stack)
            (format T "Which action do you want to perform on the stack?~%")

            (setf (readtable-case *readtable*) :preserve))


          until will-exit
          do (progn
            (unless (listen) (setf whether-show-prompt T))
            (when whether-show-prompt
                (format T "[push/eval-push/pop/show/exit]: ")
                (setf whether-show-prompt NIL))

            (unless (peek-char T *standard-input* NIL)
                (format T "* Standard-input reached end-of-file. *~%")
                (setf will-exit T))

            (handler-case (setf action
                                (write-to-string (read *standard-input* NIL)))
                (error (err)
                    (format T "~A" err)
                    (setf action "")))  ;; Force resetting 'action

            (cond
              ((string-equal action "push")
                (unless (listen)
                    (format T "Enter a value to be pushed: ")
                    (setf whether-show-prompt T))

                (handler-case (push-top the-stack (read))
                    (error (err)
                        (format T "~A   * Failed to push. *~%" err))))

              ((string-equal action "eval-push")
                (unless (listen)
                    (format T "Enter a value to be evaluated and pushed: "))
                (setf whether-show-prompt T)

                (handler-case (push-top the-stack (eval (read)))
                    (error (err)
                        (format T "~A   * Failed to push. *~%" err))))

              ((string-equal action "pop")
                (if (not (is-empty the-stack))
                    (pop-top the-stack)
                    (format T "Nothing to pop.~%   * Failed to pop. *~%")))
              ((string-equal action "show") (show the-stack))
              ((string-equal action "exit") (setf will-exit T))

              ;; Handle 'action when it is reset
              ((string-equal action "") (setf whether-show-prompt T))

              (T
                (format T "~S: No such action.~%" action)
                (setf whether-show-prompt T))))


          finally (progn
            (show the-stack)
            (format T "Good bye. See you next time!~%")))


    0)


(main)
