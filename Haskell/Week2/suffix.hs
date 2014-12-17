main = putStrLn "dpanayotov"

suffix :: (Eq a) => [a] -> [a] -> Bool
suffix list1 list2
    |length list1 == length list2 = list1 == list2
    |otherwise = suffix list1 (tail list2)