module Test where

data Expr = N Int
          | Bo Bool
          | Plus Expr Expr
          | If Expr Expr Expr
          | Equal Expr Expr
	  deriving Show

e1 = If (N 3) (N 3) (N 3)
