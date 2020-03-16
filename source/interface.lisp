(in-package :cl-webengine)

(defcfun initialize :pointer)

(defcfun newQWidget :pointer)

(defcfun newQVBoxLayout :pointer)

(defcfun newQWebEngineView :pointer)

(defcfun webEngineViewLoad :void
  (webEngineView :pointer)
  (url :string))

(defcfun webEngineViewPage :pointer
  (webEngineView :pointer))

(defcfun webEnginePageRunJavaScript :void
  (webEnginePage :pointer)
  (javascript :string))

(defcfun layoutAddWidget :void
  (layout :pointer)
  (widget :pointer))

(defcfun widgetSetLayout :void
  (widget :pointer)
  (layout :pointer))

(defcfun widgetShow :void
  (widget :pointer))

(defcfun widgetResize :void
  (widget :pointer)
  (width :int)
  (height :int))

(defcfun widgetSetFixedHeight :void
  (widget :pointer)
  (height :int))

(defcfun windowSetWindowTitle :void
  (window :pointer)
  (title :string))

(defcfun layoutSetContentsMargins :void
  (layout :pointer)
  (left :int)
  (top :int)
  (right :int)
  (bottom :int))

(defcfun layoutSetSpacing :void
  (layout :pointer)
  (spacing :int))

(defcfun layoutInsertWidget :void
  (layout :pointer)
  (index :int)
  (widget :pointer))
