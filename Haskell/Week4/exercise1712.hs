foldl2 _ sv [] = sv
foldl2 f sv (x:xs) = foldl2 f (f sv x) xs

foldr2 _ sv [] = sv
foldr2 f sv (x:xs) = f x (foldr2 f sv xs)

allTrue::[Bool] -> Bool
allTrue = foldl2 (&&) True

anyTrue::[Bool]->Bool
anyTrue = foldr2 (||) False

allFalse::[Bool] ->Bool
allFalse = allTrue.map not

anyFalse::[Bool]->Bool
anyFalse = anyTrue.map not

any'::(a->Bool)->[a]->Bool
any' predicate = foldr (||) False . (map predicate)

all'::(a->Bool)->[a]->Bool
all' predicate = foldl (&&) True . map predicate

same::(Eq a) => [a] -> Bool
same (x:xs) = allTrue $ map (\y -> x == y) xs

map2 f = foldr (\x y -> f x : y) []