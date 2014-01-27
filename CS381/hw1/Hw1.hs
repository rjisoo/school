module Hw1 where

-- 1.
--
--
-- a)   rye lettuce rye
--      wheat lettuce wheat
--      wheat lettuce rye
--
-- b)
data Bread = Rye | Wheat deriving Show

data Sand = Food Bread Bread deriving Show

-- c)
ppSand :: Sand -> String
ppSand (Food b1 b2) = ppBread b1 ++ " lettuce " ++ ppBread b2

ppBread :: Bread -> String
ppBread Rye = "rye"
ppBread Wheat = "wheat"


-- d)
-- You shouldn't include lettuce in the adstract synatx because we never define a constructor for it.

-- 2.

-- a)
-- rye mayo rye
-- rye mayo lettuce lettuce lettuce lettuce lettuce rye
-- wheat mayo lettuce wheat

-- b)
--data Sand' = Food' Bread' [Innards] Bread' deriving Show
--data Bread' = Rye' | Wheat' deriving Show

--s1 :: Sand'
--s1 = Food' Rye' Wheat'



-- c)

-- d)


-- 3.

-- a)
data Cmd = Pen Mode
         | MoveTo Pos Pos
         | Def  String [String] Cmd
         | Call String [Int] 
         | Seq Cmd Cmd

data Mode = Up | Down

data Pos = I Int | Var String

-- b)
vector :: Cmd
vector = Def "vector" ["x1","y1","x2","y2"] 
         (Seq (MoveTo (Var "x1") (Var "y1"))
              (Seq (Pen Down)
                   (Seq (MoveTo (Var "x2") (Var "y2"))
                        (Pen Up) )))

-- c)
steps :: Int -> Cmd
steps 0 = foldr1 Seq [Pen Up,  MoveTo (I 0) (I 0)]
steps 1 = foldr1 Seq [Pen Up,  MoveTo (I 0) (I 0),
                      Pen Down,MoveTo (I 0) (I 1),
                               MoveTo (I 1) (I 1)]
steps n = Seq (steps (n-1))
              (foldr1 Seq [MoveTo (I (n-1)) (I n),
                           MoveTo (I n)     (I n)])

-- d)
ppCmd :: String -> Cmd -> String
ppCmd s (Pen Up)     = s++"pen up"
ppCmd s (Pen Down)   = s++"pen down"
ppCmd s (MoveTo x y) = s++"moveto ("++show x++","++show y++")"
ppCmd s (Def n xs c) = "def "++n++"("++ppPars xs++") {\n"++
                       ppCmd "  " c++"\n}"
ppCmd s (Call n xs)  = "call "++n++"("++ppArgs xs++")"
ppCmd s (Seq c c')   = ppCmd s c++";\n"++
                       ppCmd s c'
  
printList :: (a -> String) -> String -> [a] -> String
printList f s [x]    = f x
printList f s (x:xs) = f x++s++printList f s xs

ppPars :: [String] -> String
ppPars xs = printList id "," xs
  
ppArgs :: [Int] -> String
ppArgs xs = printList show "," xs
  
instance Show Cmd where
  show = ppCmd ""
  
instance Show Pos where
  show (I i)   = show i
  show (Var s) = s

-- e)
-- def vector(x1,y1,x2,y2) {
--   moveto (x1,y1);
--   pen down;
--   moveto (x2,y2);
--   pen up
-- }

-- steps 0
-- pen up;
-- moveto (0,0)

-- steps 1
-- pen up;
-- moveto (0,0);
-- pen down;
-- moveto (0,1);
-- moveto (1,1)

-- steps 3
-- pen up;
-- moveto (0,0);
-- pen down;
-- moveto (0,1);
-- moveto (1,1);
-- moveto (1,2);
-- moveto (2,2);
-- moveto (2,3);
-- moveto (3,3)



