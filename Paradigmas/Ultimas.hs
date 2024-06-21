module Ultimas where

    type TuplaBase = (String, String, Char)

    base :: Int -> TuplaBase
    base x
        | x == 1 = ("joao", "mestre", 'm')
        | x == 2 = ("jonas", "doutor", 'm')
        | x == 3 = ("joice", "mestre", 'f')
        | x == 4 = ("janete", "doutor", 'f')
        | x == 5 = ("jocileide", "doutor", 'f')
        | otherwise = ("ninguem", "", 'x')


    contMestre :: [Int] -> Int
    contMestre [] = 0
    contMestre (x:xs)
        | secondElement (base x) == "mestre" = 1 + contMestre xs
        | otherwise = contMestre xs
            where
                secondElement (_, b, _) = b