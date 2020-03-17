(in-package :cl-webengine)

(defun run ()
  (let ((application
          (new-q-application 1 (cffi:foreign-alloc :string
                                                   :initial-contents (list "cl-webengine.lib")
                                                   :null-terminated-p t)))
        (window (new-q-widget))
        (layout (new-qv-box-layout))
        (web-view (new-q-web-engine-view)))
    (widget-set-layout window layout)
    (layout-add-widget layout window)
    (widget-show window)
    (application-exec application)))
