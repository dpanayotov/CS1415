main = putStrLn "hello"

productOfDigits :: Int -> Int
productOfDigits num
    |div num 10 == 0 = num
    |otherwise= mod num 10 * productOfDigits (div num 10)