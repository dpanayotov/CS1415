main = putStrLn "dpanayotov"

removeAt :: Int -> [a] -> [a]
removeAt _ [] = []
removeAt index (x : xs)
    |index > length xs || index < 0 = error "Index out of bounds"
    |index == 0 = xs
    |otherwise = x : removeAt (index - 1) xs