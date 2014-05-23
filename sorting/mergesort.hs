merge :: Ord a => [a] -> [a] -> [a]
merge []  ys                   = ys
merge xs  []                   = xs
merge xs@(x:xt) ys@(y:yt) 
        | x <= y    = x : merge xt ys
        | otherwise = y : merge xs yt

mergesort :: Ord a => [a] -> [a]
mergesort [] = []
mergesort [x] = [x]
mergesort list = 
    merge left right
    where 
        half = div (length list) 2
        left = mergesort (take half list)
        right = mergesort (drop half list)

