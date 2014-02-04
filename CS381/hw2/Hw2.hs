-- Geoffrey Corey
-- -- Eric Timmerman

module Hw2 where

-- 1.
data Dir = Lft | Rgt | Up | Dwn deriving Show

data Step = Go Dir Int deriving Show

type Move = [Step]

type Pos = (Int, Int)
type Dist = Int
type Trip = (Pos, Dist)

-- a)
semDist :: Move -> Dist
semDist [] = 0
semDist (x:xs) = semInt x + semDist xs

semInt :: Step -> Int
semInt (Go _ r) = r

t1 :: Move
t1 = [Go Lft 10, Go Rgt 20]


-- b)
--semTrip :: Move -> Trip
