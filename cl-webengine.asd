;;; -*- Mode: Lisp; Syntax: ANSI-Common-Lisp; Base: 10 -*-
;;; cl-webengine.asd

#-(or sbcl)
(warn "Unsupported implementation.")

(asdf:defsystem :cl-webengine
  :description "An FFI binding to WebEngine in Qt."
  :author "Atlas Engineer LLC"
  :licence "BSD 3-Clause"
  :version "0.0"
  :serial t
  :components ((:module "source"
                :components
                        ((:file "package")
                         (:file "interface"))))
  :depends-on (:cffi))
