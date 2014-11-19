;fact, fib, sod

(define (fact n)
  (define (iter n result)
    (cond 
      ((= n 1) result)
      (else (iter (- n 1) (* result n))))
    )
  (iter n 1)
  )

(define (fib n)
  (define (iter n a b)
    (cond
      ((= n 1) a)
      (else (iter (- n 1) b (+ a b)))))
  (iter n 1 1))

(define (sum-of-digits n)
  (define (iter n sum)
    (cond 
      ((= n 0) sum)
      (else (iter (quotient n 10) (+ (remainder n 10) sum)))))
  (iter n 0))

;sum from a to b
(define (sum a b)
  (define (iter a b result)
    (cond 
      ((> a b) result)
      (else (iter (+ a 1) b (+ result a)))))
  (iter a b 0)
  )

;reverse digits
(define (reverse-int n)
  (define (iter n result)
    (cond
      ((= n 0) result)
      (else (iter (quotient n 10) (+(remainder n 10) (* result 10))))))
  (iter n 0))

;palindrome
(define (int-palindrome? n)
  (= n (reverse-int n))
  )

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

; sum of primes
(define (sum-of-primes a b)
  (define (iter a b sum)
    (cond
      ((> a b) sum)
      ((is-prime? a) (iter (+ a 1) b (+ sum a)))
      (else (iter (+ a 1) b sum))
      ))
  (iter a b 0)
  )

; number of divisors
(define (divisors n)
  (define (iter n current amount)
    (cond
      ((= n current) (+ amount 1))
      ((= (remainder n current) 0) (iter n (+ current 1) (+ amount 1)))
      (else (iter n (+ current 1) amount))))
  (iter n 1 0))

; even number of divisors
(define (evenly? n)
  (= (remainder (divisors n) 2) 0))

; odd number of divisors
(define (oddly? n)
  (not (evenly? n)))
