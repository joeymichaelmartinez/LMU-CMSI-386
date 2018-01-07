{-
Written by: John Hardy, Joey Martinez, and J Goocher
-}

module Warmup exposing (..)

import List exposing (..)
import Basics exposing (..)
import Regex exposing (..)
import Date exposing (..)
import Date.Extra as Date exposing (..)

change: Int -> Result String (Int, Int, Int, Int)
change amount =
  if amount < 0 then Err "amount cannot be negative" else
    Ok <|
      let
        quarters = amount
        dimes = quarters % 25
        nickles = dimes % 10
        pennies = nickles % 5
      in
        (,,,) (quarters // 25) (dimes // 10) (nickles // 5) pennies

stripQuotes: String -> String
stripQuotes input = replace All (regex "['\"]") (\_ -> "") <| input

powers: Int -> Int -> Result String (List Int)
powers base limit =
  if base < 0 then Err "negative base" else
    Ok <|
      List.map (\a -> base ^ a) (List.range 0 (Basics.floor (logBase (toFloat base) (toFloat limit))))

sumOfCubesOfOdds: List Int -> Int
sumOfCubesOfOdds input =
  foldr (+) 0 <| List.map (\b -> b * b * b) <| filter (\a -> a % 2 /= 0) input

daysBetween: String -> String  -> Result String (Int)
daysBetween firstString secondString =
    case Date.fromString firstString of
      Err msg -> Err "First input string is not a date."
      Ok firstDate ->
        case Date.fromString secondString of
          Err msg -> Err "Second input string is not a date."
          Ok secondDate ->
            Ok <| Date.diff Day firstDate secondDate
