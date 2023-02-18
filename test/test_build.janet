(use ../build/freja-jaylib)

(defn main [& args]

(init-window 800 600 "Game of Life")
(set-target-fps 60)

(set-scroll-callback (fn [& args] (printf "scroll callback: %p" args)))
    
(while (not (window-should-close))
    #(set-key-callback (fn [& args] (printf "key callback: %p" args)))
    (set-char-callback (fn [& args] (printf "char callback: %p" args)))
    # Draw cells
    (begin-drawing)
    (clear-background :black)
            (draw-rectangle 0 0 100 80 :red)
    (end-drawing))

(close-window)
)
