    module Idade where

    idade :: Int->String
    idade x = if x >= 18 then "Maior De Idade" else "Menor de Idade"

    idade1 :: Int->String
    idade1 x
        | x>= 18 = "Maior de Idade"
        | otherwise = "Menor de Idade"

    fatorial :: Int->Int
    fatorial x = if x == 0 then 0 else x + fatorial(x-1)

    fatorial1 :: Int->Int
    fatorial1 x
        | x == 0 = 0
        | otherwise = x + fatorial1(x-1)

    fatorial2 :: Int->Int
    fatorial2 0 = 0
    fatorial2 x = x + fatorial2(x-1)

    fibonnaci :: Int -> Int
    fibonnaci x 
        | x == 0 = 0
        | x == 1 = 1
        | otherwise = fibonnaci(x-2) + fibonnaci(x-1)