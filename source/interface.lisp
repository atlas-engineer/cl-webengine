(in-package :cl-webengine)

(defcfun ("newQApplication" new-q-application) :pointer
  (argc :int)
  (argv :pointer))

(defcfun ("applicationExec" application-exec) :int
  (application :pointer))

(defcfun ("newQWidget" new-q-widget) :pointer)

(defcfun ("newQPushButton" new-q-push-button) :pointer
  (label :string))

(defcfun ("newQVBoxLayout" new-qv-box-layout) :pointer)

(defcfun ("newQHBoxLayout" new-qv-box-layout) :pointer)

(defcfun ("newQWebEngineView" new-q-web-engine-view) :pointer)

(defcfun ("webEngineViewLoad" web-engine-view-load) :void
  (webEngineView :pointer)
  (url :string))

(defcfun ("webEngineViewPage" web-engine-view-page) :pointer
  (webEngineView :pointer))

(defcfun ("webEnginePageRunJavaScript" web-engine-page-run-javascript) :void
  (webEnginePage :pointer)
  (javascript :string))

(defcfun ("layoutAddWidget" layout-add-widget) :void
  (layout :pointer)
  (widget :pointer))

(defcfun ("widgetSetLayout" widget-set-layout) :void
  (widget :pointer)
  (layout :pointer))

(defcfun ("widgetShow" widget-show) :void
  (widget :pointer))

(defcfun ("widgetResize" widget-resize) :void
  (widget :pointer)
  (width :int)
  (height :int))

(defcfun ("widgetSetFixedHeight" widget-set-fixed-height) :void
  (widget :pointer)
  (height :int))

(defcfun ("windowSetWindowTitle" window-set-window-title) :void
  (window :pointer)
  (title :string))

(defcfun ("layoutSetContentsMargins" layout-set-contents-margins) :void
  (layout :pointer)
  (left :int)
  (top :int)
  (right :int)
  (bottom :int))

(defcfun ("layoutSetSpacing" layout-set-spacing) :void
  (layout :pointer)
  (spacing :int))

(defcfun ("layoutInsertWidget" layout-insert-widget) :void
  (layout :pointer)
  (index :int)
  (widget :pointer))
