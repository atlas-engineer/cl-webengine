(in-package :cl-webengine)

(defun run ()
  (print "Hello dear world")
  (new-q-application 1 (cffi:foreign-alloc :string
                                           :initial-contents (list "cl-webengine.lib")
                                           :null-terminated-p t)))
