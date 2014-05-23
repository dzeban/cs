quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x:xs) = 
    smaller ++ [x] ++ bigger
    where 
        smaller = quicksort [ e | e <- xs, e <= x ]
        bigger  = quicksort [ e | e <- xs, e > x ]
