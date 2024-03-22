(defun sum (a b)
  (if (> a b) 0
    (+ a (sum (+ a 1) b))))
(defun cube(x) (* x x x))
(write (cube (sum 1 10)))
(fresh-line)
(write (cube 10000000000000))
