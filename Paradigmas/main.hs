
import VerificacaoNumeros

-- Exemplo de uso:
main :: IO ()
main = do
  let numeros = [5, -3, 0, 8, -2, 10, -7]

  putStrLn "Números positivos:"
  print $ filtroNumeros ehPositivo numeros

  putStrLn "Números negativos:"
  print $ filtroNumeros ehNegativo numeros

  putStrLn "Números iguais a zero:"
  print $ filtroNumeros ehZero numeros