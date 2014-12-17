main = putStrLn "hello"

makeList :: Integer->[Integer]
makeList num
    |div num 10 <= 0 = [num]
    |otherwise = reverse $ mod num 10 : reverse (makeList (div num 10))

isElement :: Integer->[Integer]->Bool
isElement _ [] = False
isElement n (x : xs)
    |n == x = True
    |otherwise = isElement n xs

containsAll :: [Integer]->[Integer]->Bool
containsAll items [m] = isElement m items
containsAll items (x:xs)
    |not $ isElement x items = False
    |otherwise = containsAll items xs

--for last example it needs to be Integer (Int can't hold such big values)
containsDigits :: Integer -> Integer -> Bool
containsDigits m n = containsAll (makeList m) (makeList n)