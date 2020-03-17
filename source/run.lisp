(in-package :cl-webengine)

(defun run ()
  (let ((application
          (new-q-application 1 (cffi:foreign-alloc :string
                                                   :initial-contents (list "cl-webengine.lib")
                                                   :null-terminated-p t)))
        (window (new-q-widget))
        (layout (new-qv-box-layout))
        (push-button (new-q-push-button "Pomelo")))
    (widget-set-layout window layout)
    (layout-add-widget layout push-button)
    (widget-show window)
    (widget-show push-button)
    (application-exec application)))
