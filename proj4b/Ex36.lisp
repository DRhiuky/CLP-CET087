(defun fatorial (n)
    (cond
        ((< n 0) nil)
        ((zerop n) 1)
        (T (* n (fatorial (- n 1))))
    )
)

(defun fibonacci (n)
    (cond
        ((< n 1) nil)
        ((< n 3) 1)
        (T (+ (fibonacci (- n 1)) (fibonacci (- n 2))))
    )
)

(defun serieG (n)
    (cond
        ((< n 1) nil)
        ((eql n 1) 1)
        ((eql (mod n 2) 0) (- (serieG (- n 1)) (/ n (fatorial (fibonacci n)))))
        (T (+ (serieG (- n 1)) (/ n (fatorial (fibonacci n)))))
    )
)

(print (serieG 5))
;-1/8
