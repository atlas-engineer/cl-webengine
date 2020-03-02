(defpackage :cl-webengine
  (:use :common-lisp :cffi))

(in-package :cl-webengine)

(define-foreign-library libwebengine
  (:darwin "libwebengine.dylib")
  (:unix "libwebengine.so")
  (t (:default "libwebengine")))

(use-foreign-library libwebengine)
