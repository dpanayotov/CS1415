main = putStrLn "dpanayotov"

listToNumber :: [Int] -> Int
listToNumber [] = 0
listToNumber (x:xs) = x*(10^(k xs))+ listToNumber xs
    where
        k :: [Int] -> Int
        k [] = 0
        k items = length items
