-- Geoffrey Corey
-- Eric Timmerman

module Hw4 where


-- 1.
-- 1. f x = if not x then x + 1 else x
-- Static: x :: int, outputs int
-- Dynamic: x :: Bool, outputs int
-- 2. f x  = f(x+1) * 2
-- Static: x :: int, outputs int
-- Dynamic: x is any type with attribute integral


-- 2 Polymorphism
-- -- a) Parametric morphism
swap :: (a, b) -> (b, a)
swap (x, y) = (y, x)

-- -- b) Bounded Parametric morphism
maximum' :: (Ord a) => [a] -> a  
maximum' [] = error "maximum of empty list"  
maximum' [x] = x  
maximum' (x:xs)   
    | x > maxTail = x  
    | otherwise = maxTail  
    where maxTail = maximum' xs 
-- Parametric: where maxtail = maximum' xs
-- Ad-hoc: x > maxTail

-- 3 Parametric Polymorphism

-- -- a)
f x y = if null x then [y] else x -- :t f == f :: [t] -> t -> [t]
g x y = if not (null x) then [] else [y] -- :t g == g :: [a] -> a1 -> [a1]
-- -- -- 1) f: f :: [t] -> t -> [t]
-- -- -- 	g: g :: [a] -> a1 -> [a1]

-- -- -- 2)	Since f will return either [y] or x, and x is a list, and x is a 
-- -- -- 	list, the elements of x have to be the same type as y. As far as
-- -- -- 	I know, haskell can't return 2 different types from a function.

-- -- -- 	g is similar to f, but the subtle difference is that it returns
-- -- -- 	either [] or [y], which has no relation to x. Since a list in
-- -- -- 	haskell is a phantom type, haskell assumes the 2nd argument to
-- -- -- 	g is not the same type as the first.

-- -- -- 3) Since they both work with any types, both are general. However,
-- -- -- 	g could also work with more than 1 type, which might make it
-- -- -- 	more general.

-- -- -- 4) Because the interpreter tries to figure out what each function
-- -- --	is doing when the module is loaded


-- -- b)
h :: [b] -> [(a, b)] -> [b]
h b _ = b

-- -- c)
-- k :: (a -> b) -> ((a -> b) -> a) -> b
-- -- We cannot fin a (simple) definition for k as haskell does not have
-- -- a way to pattern match a function and its parameters at the same time.
-- -- It is also not feasible to deduce anything about b's representation
-- -- because the function only defines b in terms of being the return type
-- -- of another function.

-- -- d)
-- -- We cannot define a function of type a-> b because it requires knowing
-- -- something about type b. Anything used to define how b should look would
-- -- end up most likely restricting what b might be, thereby causing it to not
-- -- be of any type.


-- 4.
-- 1. (a -> Bool) -> Bool
-- 2. [Bool, b] -> [[bool, b]] -> [[bool, b]]
-- 3. Bool -> (Bool -> Bool) -> Bool
-- 4. ((Bool -> Bool) -> Bool) -> (Bool -> Bool) -> ((Bool -> Bool) -> Bool)
