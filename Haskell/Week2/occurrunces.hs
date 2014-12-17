main = putStrLn "dpanayotov"

occurrences :: [Int] -> [Int] -> [Int]
occurrences [] _ = []
occurrences (x:xs) list = count x list : occurrences xs list

count :: Int->[Int]->Int
count _ [] = 0
count n (x : xs)
        |n == x = 1 + count n xs
        |otherwise = count n xs