(use ../build/freja-jaylib)

(init-window 800 600 "Game of Life")
(set-target-fps 60)

(while (not (window-should-close))
(set-key-callback (fn [& args] (pp args)))
    # Draw cells
    (begin-drawing)
    (clear-background :black)
            (draw-rectangle 0 0 100 80 :red)
    (end-drawing))

(close-window)
