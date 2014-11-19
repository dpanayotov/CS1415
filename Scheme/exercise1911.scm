(define M
  (list (list 1 2 3)
        (list 4 5 6)
        (list 7 8 9)))

(define (range a b)
  (cond
    ((> a b) (list))
    (else (cons a (range (+ a 1) b)))))

(define (filter pred? l)
  (cond
    ((null? l) (list))
    ((pred? (car l)) (cons (car l) (filter pred? (cdr l))))
    (else (filter pred? (cdr l)))))

(define (all? pred? l)
  (= (length l) (length (filter pred? l))))

(define (diagonal M)
  (map (lambda (i row)
         (nth i row))
       (range 0 (- (length M) 1))
       M))

(define (nth index l)
  (cond
    ((= index 0) (car l))
    (else (nth (- index 1) (cdr l)))))
 
(define (same? items)
  (all? (lambda (x)
          (equal? (car items) x))
        (cdr items)))

(define (secondary M)
  (diagonal
   (map reverse M)))

(define (reverse-cols M)
  (reverse M))

(define (qsort items)
  (cond
    ((null? items) (list))
    (else
     ;(append
      ;(qsort (filter (lambda (x)
      ;                        (< x (car items))) (cdr items)))
      ;(list (car items))
      ;(qsort (filter (lambda (x)
      ;                        (>= x (car items))) (cdr items)))
      ;))))
     (let*
         ;start local variables
         ( (pivot (car items))
           (rest (cdr items))
           (lesser (filter (lambda (x) (< x pivot)) rest))
           (greater (filter (lambda (x) (>= x pivot)) rest))
           ;end local variables
           )
       (append (qsort lesser) (list pivot) (qsort greater))))))

(define (fst tuple)
  (car tuple))

(define (snd tuple)
  (cond
    ((pair? (cdr tuple)) (car (cdr tuple)))
    (else (cdr tuple))))

(define (index-of x items)
  (let*
      ((n (- (length items) 1))
       (indexed (zip (range 0 n) items))
       (filtered (filter (lambda(item) (equal? (snd item) x)) indexed)))
    (fst (car filtered))))

; combine i with i element
(define (zip l1 l2)
  (define (iter l1 l2 combined)
    (cond
      ( (or (null? l1) (null? l2)) (reverse combined))
      (else (iter (cdr l1) (cdr l2) (cons (list (car l1) (car l2)) combined)))))
  (iter l1 l2 (list)))

(define (both-in f g start end)
  (lambda (x)
     (let
           ((first (and (<= (f x) end) (>= (f x) start)))
           (second (and (<= (g x) end) (>= (g x) start))))
           (and first second))))

(define (square x)
  (* x x))

(define (inc x)
  (+ x 1))