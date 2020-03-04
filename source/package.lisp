(defpackage :cl-webengine
  (:use :common-lisp :cffi))

(in-package :cl-webengine)

(define-foreign-library libwebengine
  (:darwin (:or
            "libwebengine.dylib"
            "libwebengine.1.dylib"
            "libwebengine.1.0.dylib"
            "libwebengine.1.0.0.dylib"))
  (:unix "libwebengine.so")
  (t (:default "libwebengine")))

(use-foreign-library libwebengine)
