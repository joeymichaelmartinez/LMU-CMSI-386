import Html exposing (..)
import Html.Attributes exposing (..)
import Html.Events exposing (..)
import Warmup exposing (..)

type alias Dates = { firstDate: String, secondDate: String }
type Msg = ChangeFirstDate String | ChangeSecondDate String

formatOutput : Result String Int -> String
formatOutput toFormat =
  case toFormat of
    Err msg -> ""
    Ok output -> toString output

main : Program Never Dates Msg
main =
  Html.beginnerProgram { model = dates, view = view, update = update }

dates : Dates
dates = { firstDate = "", secondDate = "" }

update : Msg -> Dates -> Dates
update msg dates =
  case msg of
    ChangeFirstDate f -> { dates | firstDate = f }
    ChangeSecondDate s -> { dates | secondDate = s }

view : Dates -> Html Msg
view dates =
  body
    [style
      [ ("text-align", "center")
      ,  ("font", "16px Arial")
      ,  ("background-color", "linen")
      ,  ("margin", "0")
      ]
    ]
    [ h1
      [style
        [ ("font", "bold 40px Avenir")
        ,  ("margin-top", "0")
        ,  ("padding", "5px")
        ,  ("background-color", "cyan")
        ]
      ]
      [ text "Date Calculator" ]
    , p []
      [text "From"
      , input
        [style
          [ ("border", "2px solid grey")
          , ("margin-left", "8px")
          ]
        , id "from"
        , type_ "date"
        , onInput ChangeFirstDate
        , value dates.firstDate
        ] []
      ]
    , p []
      [text "to"
      , input
        [style
          [ ("border", "2px solid grey")
          , ("margin-left", "8px")
          ]
        , id "to"
        , type_ "date"
        , onInput ChangeSecondDate
        , value dates.secondDate
        ] []
      ]
    , p []
      [text "is "
      , span
        [style
          [ ("font-size", "28px") ]
          , id "output"
        ]
        [ text ( formatOutput (daysBetween dates.firstDate dates.secondDate) ) ]
      , text "days."
      ]
    ]
