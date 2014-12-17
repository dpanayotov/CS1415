import Data.Char
main = putStrLn "hello"

add3::Int->Int->Int->Int
add3 a b c = a + b + c

trim::String->String
trim = f.f
    where
        f = reverse.dropWhile isSpace
--trim word = reverse $ dropWhile isSpace $ reverse $ dropWhile isSpace word

take'::Int->[a]->[a]
take' 0 _ = []
take' _ [] = []
take' num (x:xs) = x : take' (num-1) xs

drop'::Int->[a]->[a]
drop' 0 xs = xs
drop' _ [] = []
drop' num (x:xs) =  drop' (num - 1) xs

zip'::[a]->[b]->[(a,b)]
zip' [] _ = []
zip' _ [] = []
zip' (x:xs) (y:ys)
    |length xs /= length ys = error "Can't have different lengths!"
    |otherwise =  (x,y) : zip' xs ys

qSort::[Int]->[Int]
qSort [] = []
qSort (x:xs) = less ++ pivot : greater
    where
        pivot = x
        less = qSort $ filter (\y -> y <= pivot) xs
        greater = qSort $ filter (\z -> z > pivot) xs

dropWhile'::(a->Bool)->[a]->[a]
dropWhile' f [] = []
dropWhile' f (x:xs)
    |f x == True = x : xs
    |otherwise = dropWhile' f xs

takeWhile'::(a->Bool)->[a]->[a]
takeWhile' f [] = []
takeWhile' f (x:xs)
    |f x == True = []
    |otherwise = x : takeWhile' f xs