let getFreeBurgers = (_items: list(Item.t)) => Some(0.0);

let getHalfOff = (_items: list(Item.t)) => Some(0.0);

// #region simple-get-discount
let getDiscountFunction = code => {
  switch (code |> Js.String.toUpperCase) {
  | "FREE" => Some(getFreeBurgers)
  | "HALF" => Some(getHalfOff)
  | _ => None
  };
};
// #endregion simple-get-discount

ignore(getDiscountFunction);

// #region get-discount-with-date
let getDiscountFunction = (code, date) => {
  let month = date |> Js.Date.getMonth;

  switch (code |> Js.String.toUpperCase) {
  | "FREE" when month == 4.0 => Some(getFreeBurgers)
  | "HALF" => Some(getHalfOff)
  | _ => None
  };
};
// #endregion get-discount-with-date

ignore(getDiscountFunction);

// #region get-discount-return-result
let getDiscountFunction = (code, date) => {
  let month = date |> Js.Date.getMonth;

  switch (code |> Js.String.toUpperCase) {
  | "FREE" when month == 4.0 => Ok(getFreeBurgers)
  | "FREE" => Error("Expired code")
  | "HALF" => Ok(getHalfOff)
  | _ => Error("Invalid code")
  };
};
// #endregion get-discount-return-result

ignore(getDiscountFunction);

// #region get-free-burgers
let getFreeBurgers = (items: list(Item.t)) => {
  let prices =
    items
    |> List.filter_map(item =>
         switch (item) {
         | Item.Burger(burger) => Some(Item.Burger.toPrice(burger))
         | Sandwich(_)
         | Hotdog => None
         }
       );

  switch (prices) {
  | [] => Error("To enjoy this promo, buy at least 2 burgers")
  | [_] => Error("To enjoy this promo, buy at least 1 more burger")
  | prices =>
    let result =
      prices
      |> List.sort((x, y) => - Float.compare(x, y))
      |> List.filteri((index, _) => index mod 2 == 1)
      |> List.fold_left((+.), 0.0);
    Ok(result);
  };
};
// #endregion get-free-burgers

let getHalfOff = (_items: list(Item.t)) => Ok(0.0);

// #region error-type
type error =
  | ExpiredCode
  | InvalidCode;
// #endregion error-type

// #region use-error-type
let getDiscountFunction = (code, date) => {
  let month = date |> Js.Date.getMonth;

  switch (code |> Js.String.toUpperCase) {
  | "FREE" when month == 4.0 => Ok(getFreeBurgers)
  | "FREE" => Error(ExpiredCode)
  | "HALF" => Ok(getHalfOff)
  | _ => Error(InvalidCode)
  };
};
// #endregion use-error-type

ignore(getDiscountFunction);

// #region get-free-burgers-poly
let getFreeBurgers = (items: list(Item.t)) => {
  let prices =
    items
    |> List.filter_map(item =>
         switch (item) {
         | Item.Burger(burger) => Some(Item.Burger.toPrice(burger))
         | Sandwich(_)
         | Hotdog => None
         }
       );

  switch (prices) {
  | [] => Error(`NeedTwoBurgers)
  | [_] => Error(`NeedOneBurger)
  | prices =>
    let result =
      prices
      |> List.sort((x, y) => - Float.compare(x, y))
      |> List.filteri((index, _) => index mod 2 == 1)
      |> List.fold_left((+.), 0.0);
    Ok(result);
  };
};
// #endregion get-free-burgers-poly

// #region half-promo-may-28
let getDiscountFunction = (code, date) => {
  let month = date |> Js.Date.getMonth;
  let dayOfMonth = date |> Js.Date.getDate;

  switch (code |> Js.String.toUpperCase) {
  | "FREE" when month == 4.0 => Ok(getFreeBurgers)
  | "HALF" when month == 4.0 && dayOfMonth == 28.0 => Ok(getHalfOff)
  | "FREE"
  | "HALF" => Error(ExpiredCode)
  | _ => Error(InvalidCode)
  };
};
// #endregion half-promo-may-28

ignore(getDiscountFunction);

// #region get-sandwich-half-off
type sandwichTracker = {
  portabello: bool,
  ham: bool,
  unicorn: bool,
  turducken: bool,
};

/** Buy 1+ of every type of sandwich, get half off */
let getSandwichHalfOff = (items: list(Item.t)) => {
  let tracker =
    items
    |> List.filter_map(
         fun
         | Item.Sandwich(sandwich) => Some(sandwich)
         | Burger(_)
         | Hotdog => None,
       )
    |> ListLabels.fold_left(
         ~init={
           portabello: false,
           ham: false,
           unicorn: false,
           turducken: false,
         },
         ~f=(tracker, sandwich: Item.Sandwich.t) =>
         switch (sandwich) {
         | Portabello => {
             ...tracker,
             portabello: true,
           }
         | Ham => {
             ...tracker,
             ham: true,
           }
         | Unicorn => {
             ...tracker,
             unicorn: true,
           }
         | Turducken => {
             ...tracker,
             turducken: true,
           }
         }
       );

  switch (tracker) {
  | {portabello: true, ham: true, unicorn: true, turducken: true} =>
    let total =
      items
      |> ListLabels.fold_left(~init=0.0, ~f=(total, item) =>
           total +. Item.toPrice(item)
         );
    Ok(total /. 2.0);
  | _ => Error(`MissingSandwichTypes)
  };
};
// #endregion get-sandwich-half-off

// #region half-promo-nov-3
let getDiscountFunction = (code, date) => {
  let month = date |> Js.Date.getMonth;
  let dayOfMonth = date |> Js.Date.getDate;

  switch (code |> Js.String.toUpperCase) {
  | "FREE" when month == 4.0 => Ok(getFreeBurgers)
  | "HALF" when month == 4.0 && dayOfMonth == 28.0 => Ok(getHalfOff)
  | "HALF" when month == 10.0 && dayOfMonth == 3.0 => Ok(getSandwichHalfOff)
  | "FREE"
  | "HALF" => Error(ExpiredCode)
  | _ => Error(InvalidCode)
  };
};
// #endregion half-promo-nov-3
