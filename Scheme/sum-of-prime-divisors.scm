; sum of divisors
(define (sum-of-divisors n)
  (define (iter n temp sum)
    (cond
      ((= temp 0) sum)
      ((= (remainder n temp) 0) (iter n (- temp 1) (+ sum temp)))
      (else (iter n (- temp 1) sum))))
  (iter n n 0))

; is prime
(define (is-prime? n)
  (= (sum-of-divisors n) (+ n 1))
)

(define (sum-of-prime-divisors  n)
  (define (iter n divisor sum)
    (cond 
      ((> divisor n) sum)
      ((and (is-prime? divisor) (= (remainder n divisor) 0)) (iter n (+ divisor 1) (+ sum divisor)))
      (else (iter n (+ divisor 1) sum))))
  (iter n 2 0)
  )