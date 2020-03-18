(defpackage :cl-webengine
  (:nicknames :webengine :qt)
  (:use :common-lisp :cffi))

(in-package :cl-webengine)

(define-foreign-library libwebengine
  (:darwin (:or
            "libwebengine.dylib"
            "libwebengine.1.dylib"
            "libwebengine.1.0.dylib"
            "libwebengine.1.0.0.dylib"))
  (:unix (:or "libwebengine.so"
              "libwebengine.so.1"
              "libwebengine.so.1.0"
              "libwebengine.so.1.0.0"))
  (t (:default "libwebengine")))

(use-foreign-library libwebengine)
