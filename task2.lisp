(defun sum (term a next b)
  (defun iter (a result)
    (if (> a b) result
	     (iter (funcall next a) (+ result (funcall term a)))))
  (iter a 0))

(defun sum-rec (term a next b)
  (if (> a b) 0
    (+ (funcall term a) (sum-rec term (funcall next a) next b))))

(defun val (x) x)

(defun inc (x) (+ x 1))

(defun sum-integers (a b)
  (sum #'val a #'inc b))

(defun rec-sum-int (a b)
  (sum-rec #'val a #'inc b))

(defvar a 0)
(setq a (read))
(write (time (sum-integers 1 a)))
(write (time (rec-sum-int 1 a)))
(fresh-line)
