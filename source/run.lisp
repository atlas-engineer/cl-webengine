(in-package :cl-webengine)

(defun run ()
  (let ((application
          (new-q-application 1 (cffi:foreign-alloc :string
                                                   :initial-contents (list "cl-webengine.lib")
                                                   :null-terminated-p t)))
        (window (new-q-widget))
        (layout (new-qv-box-layout))
        (webview (new-q-web-engine-view)))
    (layout-add-widget layout webview)
    (widget-set-layout window layout)
    (web-engine-view-load webview "https://www.duckduckgo.com")
    (widget-show window)
    (application-exec application)))
