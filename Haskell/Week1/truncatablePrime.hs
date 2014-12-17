main = putStrLn "hello"

isPrime ::Int->Bool
isPrime n
    |n <= 1 = False
    |otherwise = iter 2 n
        where
            iter current n
                |current == n = True
                |mod n current == 0 = False
                |otherwise = iter (current+1) n

truncatablePrime :: Int->Bool
truncatablePrime n
    |n == 0 = True
    |isPrime n = truncatablePrime $ div n 10
    |otherwise = False