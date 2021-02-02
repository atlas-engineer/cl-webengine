(in-package :cl-webengine)

(defvar callback-counter 0)
(defvar callbacks ())
(defstruct callback
  (id)
  (function))

(defclass event ()
  ((qt-object :accessor qt-object :documentation "The pointer to the
   Qt event object.")
   (init-time :accessor init-time :initarg :init-time)))

(defclass keypress-event (event)
  ((key-code :accessor key-code :initarg :key-code)
   (key-string :accessor key-string :initarg :key-string)
   (modifier-flags :accessor modifier-flags :initarg :modifier-flags
   :documentation "The unmasked integer value of the currently
   depressed modifiers as reported by Qt.")
   (modifiers :accessor modifiers :initarg :modifiers)))
(export '(key-code key-string modifiers))

(defparameter qt-keyboard-modifiers
  (list 33554432  "shift"   ; Shift
        67108864  "control" ; Control
        134217728 "meta"    ; Alt
        268435456 "meta"))  ; Meta
(defmethod initialize-instance :after ((event keypress-event) &key)
  (setf (modifiers event)
        (loop for (i y) on qt-keyboard-modifiers by #'cddr
              unless (zerop (logand i (modifier-flags event)))
                collect y)))

(cffi:defcallback key-pressed :void
    ((id :int)
     (key-code :int)
     (key-string :string)
     (modifier-flags :int))
  (let* ((callback (find id callbacks :key (function callback-id))))
    (when (callback-function callback)
      (let ((event (make-instance
                    'keypress-event
                    :key-code key-code
                    :key-string key-string
                    :modifier-flags modifier-flags)))
        (funcall (callback-function callback) event)))))

(defcfun ("newKeyPressFilter" new-key-press-filter) :pointer
  (id :int)
  (callback :pointer))
(export 'new-key-press-filter)

(defcfun ("newEmptyKeyPressFilter" new-empty-key-press-filter) :pointer)
(export 'new-empty-key-press-filter)

(defcfun ("widgetInstallKeyPressFilter" %widget-install-key-press-filter) :pointer
  (widget :pointer)
  (key-press-filter :pointer))

(defun widget-install-key-press-filter (widget callback)
  (incf callback-counter)
  (push (make-callback :id callback-counter :function callback) callbacks)
  (%widget-install-key-press-filter
   widget
   (new-key-press-filter callback-counter (cffi:callback key-pressed))))
(export 'widget-install-key-press-filter)

(defcfun ("newLoadFinishedListener" new-load-finished-listener) :pointer
  (id :int)
  (callback :pointer))
(export 'new-load-finished-listener)

(defcfun ("loadFinishedListenerConnect" %load-finished-listener-connect) :void
  (load-finished-listener :pointer)
  (web-engine-view :pointer))

(defun load-finished-listener-connect (web-engine-view callback)
  (incf callback-counter)
  (push (make-callback :id callback-counter :function callback) callbacks)
  (%load-finished-listener-connect
   (new-load-finished-listener callback-counter (cffi:callback load-finished))
   web-engine-view))
(export 'load-finished-listener-connect)

(cffi:defcallback load-finished :void
    ((id :int))
  (let* ((callback (find id callbacks :key (function callback-id))))
    (when (callback-function callback)
      (funcall (callback-function callback)))))

(defcfun ("newLoadStartedListener" new-load-started-listener) :pointer
  (id :int)
  (callback :pointer))
(export 'new-load-started-listener)

(defcfun ("loadStartedListenerConnect" %load-started-listener-connect) :void
  (load-started-listener :pointer)
  (web-engine-view :pointer))

(defun load-started-listener-connect (web-engine-view callback)
  (incf callback-counter)
  (push (make-callback :id callback-counter :function callback) callbacks)
  (%load-started-listener-connect
   (new-load-started-listener callback-counter (cffi:callback load-started))
   web-engine-view))
(export 'load-started-listener-connect)

(cffi:defcallback load-started :void
    ((id :int))
  (let* ((callback (find id callbacks :key (function callback-id))))
    (when (callback-function callback)
      (funcall (callback-function callback)))))

(defcfun ("newQApplication" new-q-application) :pointer
  (argc :int)
  (argv :pointer))
(export 'new-q-application)

(defcfun ("applicationExec" application-exec) :int
  (application :pointer))
(export 'application-exec)

(defcfun ("applicationQuit" application-quit) :void
  (application :pointer))
(export 'application-quit)

(defcfun ("newQWindow" new-q-window) :pointer)
(export 'new-q-window)

(defcfun ("newQWidget" new-q-widget) :pointer)
(export 'new-q-widget)

(defcfun ("newQPushButton" new-q-push-button) :pointer
  (label :string))
(export 'new-q-push-button)

(defcfun ("newQVBoxLayout" new-qv-box-layout) :pointer)
(export 'new-qv-box-layout)

(defcfun ("newQHBoxLayout" new-qh-box-layout) :pointer)
(export 'new-qh-box-layout)

(defcfun ("newQWebEngineView" new-q-web-engine-view) :pointer)
(export 'new-q-web-engine-view)

(defcfun ("webEngineViewLoad" web-engine-view-load) :void
  (webEngineView :pointer)
  (url :string))
(export 'web-engine-view-load)

(defcfun ("webEngineViewUrl" web-engine-view-url) :string
  (webEngineView :pointer))
(export 'web-engine-view-url)

(defcfun ("webEngineViewPage" web-engine-view-page) :pointer
  (webEngineView :pointer))
(export 'web-engine-view-page)

(defcfun ("webEnginePageSetHtml" web-engine-page-set-html) :void
  (webEnginePage :pointer)
  (html :string))
(export 'web-engine-page-set-html)

(defcfun ("webEnginePageRunJavaScript" %web-engine-page-run-javascript) :void
  (webEnginePage :pointer)
  (javascript :string)
  (id :int)
  (callback :pointer))

(cffi:defcallback javascript-finished :void
    ((id :int)
     (result :string))
  (let* ((callback (find id callbacks :key (function callback-id))))
    (setf callbacks (delete callback callbacks))
    (when (callback-function callback)
      (funcall (callback-function callback) result))))

(defun web-engine-page-run-javascript (web-engine-page javascript &optional callback)
  (incf callback-counter)
  (push (make-callback :id callback-counter :function callback) callbacks)
  (%web-engine-page-run-javascript 
   web-engine-page 
   javascript 
   callback-counter 
   (cffi:callback javascript-finished)))
(export 'web-engine-page-run-javascript)

(defcfun ("layoutAddWidget" layout-add-widget) :void
  (layout :pointer)
  (widget :pointer))
(export 'layout-add-widget)

(defcfun ("windowShow" window-show) :void
  (window :pointer))
(export 'window-show)

(defcfun ("windowPresent" window-present) :void
  (window :pointer))
(export 'window-present)

(defcfun ("windowSetTitle" window-set-title) :void
  (window :pointer)
  (title :string))
(export 'window-set-title)

(defcfun ("windowTitle" window-title) :string
  (window :pointer))
(export 'window-title)

(defcfun ("windowIsActive" %window-is-active) :int
  (window :pointer))

(defun window-is-active (window)
  (> (%window-is-active window) 0))
(export 'window-is-active)

(defcfun ("widgetSetLayout" widget-set-layout) :void
  (widget :pointer)
  (layout :pointer))
(export 'widget-set-layout)

(defcfun ("widgetSetParent" widget-set-parent) :void
  (widget :pointer)
  (parent :pointer))
(export 'widget-set-parent)

(defcfun ("widgetShow" widget-show) :void
  (widget :pointer))
(export 'widget-show)

(defcfun ("widgetHide" widget-hide) :void
  (widget :pointer))
(export 'widget-hide)

(defcfun ("widgetDelete" widget-delete) :void
  (widget :pointer))
(export 'widget-delete)

(defcfun ("widgetResize" widget-resize) :void
  (widget :pointer)
  (width :int)
  (height :int))
(export 'widget-resize)

(defcfun ("widgetSetFixedHeight" widget-set-fixed-height) :void
  (widget :pointer)
  (height :int))
(export 'widget-set-fixed-height)

(defcfun ("widgetSetFixedSize" widget-set-fixed-size) :void
  (widget :pointer)
  (width :int)
  (height :int))
(export 'widget-set-fixed-size)

(defcfun ("widgetSetWindowTitle" widget-set-window-title) :void
  (widget :pointer)
  (title :string))
(export 'widget-set-window-title)

(defcfun ("widgetShowFullScreen" widget-show-full-screen) :void
  (widget :pointer))
(export 'widget-show-full-screen)

(defcfun ("widgetShowNormal" widget-show-normal) :void
  (widget :pointer))
(export 'widget-show-normal)

(defcfun ("widgetPresent" widget-present) :void
  (widget :pointer))
(export 'widget-present)

(defcfun ("widgetIsActiveWindow" %widget-is-active-window) :int
  (widget :pointer))

(defun widget-is-active-window (widget)
  (if (> (%widget-is-active-window widget) 0) t nil))
(export 'widget-is-active-window)

(defcfun ("layoutSetContentsMargins" layout-set-contents-margins) :void
  (layout :pointer)
  (left :int)
  (top :int)
  (right :int)
  (bottom :int))
(export 'layout-set-contents-margins)

(defcfun ("layoutSetSpacing" layout-set-spacing) :void
  (layout :pointer)
  (spacing :int))
(export 'layout-set-spacing)

(defcfun ("layoutInsertWidget" layout-insert-widget) :void
  (layout :pointer)
  (index :int)
  (widget :pointer))
(export 'layout-insert-widget)
