(defun seriePI (n)
    (cond
        ((< n 1) nil)
        ((eql n 1) 4)
        ((eql (mod n 2) 0) (- (seriePI (- n 1))(/ 4 (- (* n 2) 1))))
        (T (+ (seriePI (- n 1))(/ 4 (- (* n 2) 1))))
    )
)
