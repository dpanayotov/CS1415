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

(define (non-lychrel-sum a b)
  (define (iter a b sum)
    (cond
      ((> a b) sum)
      ((int-palindrome? (+ a (reverse-int a))) (iter (+ a 1) b (+ sum a)))
      (else (iter (+ a 1) b sum))
      ))
  (iter a b 0)
  )