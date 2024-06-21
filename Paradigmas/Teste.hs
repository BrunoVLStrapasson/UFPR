module Teste where

    multiplicacao :: Int->Int->Int
    multiplicacao x y = x*y

    reajuste :: Int->Int
    reajuste x = x + div x 4

    ano :: Int->Int
    ano x = 2023 - x

    salario :: Float->Float
    salario x = x + x / 20.0 - ((x / 100.0) * 7.0) 