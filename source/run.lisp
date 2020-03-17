(in-package :cl-webengine)

(defun run ()
  (let ((application
          (new-q-application 1 (cffi:foreign-alloc :string
                                                   :initial-contents (list "cl-webengine.lib")
                                                   :null-terminated-p t)))
        (window (new-q-widget))
        (layout (new-qv-box-layout))
        (button (new-q-push-button "Pomelo")))
    (layout-add-widget layout button)
    (widget-set-layout window layout)
    (widget-show window)
    (application-exec application)))
