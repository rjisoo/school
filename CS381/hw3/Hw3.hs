-- Geoffrey Corey
-- Eric Timmerman


module Hw3 where

-- 1.

data Expr = N Int
          | Bo Bool
          | Plus Expr Expr
          | Equal Expr Expr
          | Not Expr
          | If Expr Expr Expr

data Type = Int | Bool | TypeError
            deriving (Eq,Show)

tc :: Expr -> Type
tc (N i)                                      = Int
tc (Bo b)                                     = Bool
tc (Plus e e')    | tc e==Int  && tc e'==Int  = Int
tc (Equal e e')   | tc e==Int  && tc e'==Int  = Bool
                  | tc e==Bool && tc e'==Bool = Bool
tc (Not e)        | tc e==Bool                = Bool
tc (If e e' e'')  | tc e==Bool && tc (Equal e' e'')==Bool  = Bool
tc _                                          = TypeError

t1 :: Expr
t1 = N 2
t2 :: Expr
t2 = N 5
t3 :: Expr
t3 = N 7

t4 :: Expr
t4 = Equal t1 t2

t5 :: Expr
t5 = If t4 t3 t2

-- 2.
type Prog = [Cmd]

data Cmd = LD Int
         | ADD
         | MULT
         | DUP
         | INC
         | SWAP
         | POP Int

type Rank = Int
type CmdRank = (Int,Int)

type Stack = [Int]
type D = Stack -> Stack

semCmd :: Cmd -> D
semCmd (LD a) xs = [a] ++ xs
semCmd (ADD) (x1:x2:xs) = [x1+x2] ++ xs
semCmd (MULT) (x1:x2:xs) = [x1*x2] ++ xs
semCmd (DUP) (x1:xs) = [x1,x1] ++ xs
semCmd (INC) (x1:xs) = [succ x1] ++ xs
semCmd (SWAP) (x1:x2:xs) = (x2:x1:xs)
semCmd (POP n) xs = drop n xs
semCmd _ _ = []

-- a)
rankC :: Cmd -> CmdRank
rankC (LD _) = (0, 1)
rankC ADD = (2, 1)
rankC MULT = (2, 1)
rankC DUP = (1, 2)
rankC INC = (1, 1)
rankC SWAP = (2, 2)
rankC (POP a) = (a, 0)

rankP :: Prog -> Maybe Rank
rankP xs = rank xs 0

rank :: Prog -> Rank -> Maybe Rank
rank []     r | r >= 0 = Just r
rank (x:xs) r | under >= 0 = rank xs (under+adds)
              where (subs, adds) = rankC x
                    under = r - subs
rank _        _ = Nothing

-- b)
data Type' = A Stack | TypeError' deriving Show

typeSafe :: Prog -> Bool
typeSafe p = (rankP p) /= Nothing

semStatTC :: Prog -> Type'
semStatTC p | typeSafe p = A (sem p [])
            | otherwise = TypeError'

sem :: Prog -> D
sem [] a = a
sem (x:xs) a = sem xs (semCmd x a)
