main = putStrLn "hello"

sumOfDivisors :: Int -> Int
sumOfDivisors num = iter num num 0
    where
        iter num temp suma
            |temp == 0 = suma
            |mod num temp == 0 = iter num (temp - 1) (suma + temp)
            |otherwise = iter num (temp - 1) suma

interestingNumber :: Int -> Bool
interestingNumber num
    |num < 0 = False
    |otherwise = div1 == div2
        where
            div1 = sumOfDivisors num
            div2 = sumOfDivisors (div1 - num)