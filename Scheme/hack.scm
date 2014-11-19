(define (reverse-int n)
  (define (iter n result)
    (cond
      ((= n 0) result)
      (else (iter (quotient n 10) (+(remainder n 10) (* result 10))))))
  (iter n 0)
)

(define (int-palindrome? n)
  (= n (reverse-int n))
)

(define (to-binary n)
  (string->number (number->string n 2))
  )

(define (odd-ones? n)
  (define (iter? n sum)
    (cond 
      ((= n 0) (not (= (remainder sum 2) 0)))
      (else (iter? (quotient n 10) (+ sum (remainder n 10))))
      ))
  (iter? n 0)
  )

(define (is-hack-number? n)
    (and (int-palindrome? (to-binary n))
         (odd-ones? (to-binary n))))