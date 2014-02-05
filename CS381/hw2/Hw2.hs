-- Geoffrey Corey
-- -- Eric Timmerman

module Hw2 where

-- 1.
data Dir = Lft | Rgt | Up | Dwn deriving Show

data Step = Go Dir Int deriving Show

type Move = [Step]

type Moves = [Dir]

type Pos = (Int, Int)
type Dist = Int
type Trip = (Pos, Dist)

-- a)
semDist :: Move -> Dist
semDist [] = 0
semDist (x:xs) = semInt x + semDist xs

semInt :: Step -> Int
semInt (Go _ r) = r

-- b)
--semTrip :: Move -> Pos
--semTrip [] = (0,0)
--semTrip (x:xs) = 

semTest :: Step -> Dir
semTest (Go r _) = r

semDir :: Dir -> Pos
semDir Lft = (-1,0)
semDir Rgt = (1,0)
semDir Up = (0,1)
semDir Dwn = (0,-1)

-- 2.

type Prog = [Cmd]

data Cmd = LD Int
         | ADD
         | MULT
         | DUP

type Stack = [Int]

type D = Maybe Stack -> Maybe Stack

sem :: Prog -> D
sem [] a = a
sem (o:os) b = sem os (semCmd o b)

semCmd :: Cmd -> D
semCmd (LD e) xs = case xs of
                        Just xs -> if e < 0
                             then Nothing
                             else Just (xs ++ [e])
semCmd ADD xs = case xs of 
                     Just xs -> if length xs < 2
                          then Nothing
                          else Just (init(init xs) ++ [last xs + last(init xs)])
semCmd MULT xs = case xs of
                      Just xs -> if length xs < 2
                           then Nothing
                           else Just (init(init xs) ++ [last xs * last(init xs)])
semCmd DUP xs = case xs of
                     Just xs -> if length xs < 1
                          then Nothing
                          else Just (xs ++ [(last xs)]) 

