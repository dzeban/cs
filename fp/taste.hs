-- Quick sort by Erik Meijer's FP101x
f [] = []
f (x:xs) = f ys ++ [x] ++ f zs
	where 
		ys = [a | a <- xs, a <=x]
		zs = [b | b <- xs, b > x]

