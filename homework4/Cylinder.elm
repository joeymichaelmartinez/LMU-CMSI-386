{-
Written by: John Hardy, Joey Martinez, and J Goocher
-}

module Cylinder exposing (..)

type alias Cylinder =
    { radius : Float
    , height : Float
    }

new: Cylinder
new = Cylinder 1 1

stretch: Float -> Cylinder -> Cylinder
stretch factor c =
    { c | height = factor * c.height }

widen: Float -> Cylinder -> Cylinder
widen factor c =
    { c | radius = factor * c.radius }

volume: Cylinder -> Float
volume c =
    pi * c.radius * c.radius * c.height

surfaceArea: Cylinder -> Float
surfaceArea c =
    pi * c.radius * c.height * 2 + pi * c.radius * c.radius * 2
