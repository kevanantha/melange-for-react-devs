// #region first-test
Fest.test("Item.Sandwich.toEmoji", () =>
  Fest.expect
  |> Fest.equal(Item.Sandwich.toEmoji(Portabello), {js|🥪(🍄)|js})
);
// #endregion first-test

// #region module-alias
module F = Fest;

F.test("Item.Sandwich.toEmoji", () =>
  F.expect |> F.equal(Item.Sandwich.toEmoji(Portabello), {js|🥪(🍄)|js})
);
// #endregion module-alias

// #region open-fest
open Fest;

test("Item.Sandwich.toEmoji", () =>
  expect |> equal(Item.Sandwich.toEmoji(Portabello), {js|🥪(🍄)|js})
);
// #endregion open-fest

// #region broken-test
test("Item.Sandwich.toEmoji", () =>
  expect |> equal(Item.Sandwich.toEmoji(Portabello), {js|🥪(🐷)|js})
);
// #endregion broken-test

// #region array-of-sandwiches
let sandwiches: array(Item.Sandwich.t) = [|
  Portabello,
  Ham,
  Unicorn,
  Turducken,
|];
// #endregion array-of-sandwiches

// #region test-to-emoji
test("Item.Sandwich.toEmoji", () => {
  let sandwiches: array(Item.Sandwich.t) = [|
    Portabello,
    Ham,
    Unicorn,
    Turducken,
  |];

  expect
  |> deepEqual(
       sandwiches |> Js.Array.map(~f=Item.Sandwich.toEmoji),
       [|
         {js|🥪(🍄)|js},
         {js|🥪(🐷)|js},
         {js|🥪(🦄)|js},
         {js|🥪(🦃🦆🐓)|js},
       |],
     );
});
// #endregion test-to-emoji

// #region test-to-price
test("Item.Sandwich.toPrice", () => {
  let sandwiches: array(Item.Sandwich.t) = [|
    Portabello,
    Ham,
    Unicorn,
    Turducken,
  |];

  // 14 Feb 2024 is a Wednesday
  let date = Js.Date.makeWithYMD(~year=2024., ~month=1., ~date=14.);

  expect
  |> deepEqual(
       sandwiches |> Js.Array.map(~f=Item.Sandwich.toPrice(~date)),
       [|10., 10., 80., 20.|],
     );
});
// #endregion test-to-price

// #region test-to-price-with-date
test("Item.Sandwich.toPrice returns lower price for Turducken on Tuesdays", () => {
  // 1 Jan 2024 is a Monday
  let dates =
    [|1., 2., 3., 4., 5., 6., 7.|]
    |> Js.Array.map(~f=date =>
         Js.Date.makeWithYMD(
           ~year=2024.,
           ~month=0.,
           ~date /* `~date` is equivalent to `~date=date` */
         )
       );

  expect
  |> deepEqual(
       dates
       |> Js.Array.map(~f=date => Item.Sandwich.toPrice(~date, Turducken)),
       [|20., 10., 20., 20., 20., 20., 20.|],
     );
});
// #endregion test-to-price-with-date
