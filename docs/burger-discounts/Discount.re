let _ =
  (items: array(Item.t)) => {
    let burgers =
      items
      // #region type-annotate-argument
      |> Js.Array.filter(~f=(item: Item.t) =>
           switch (item) {
           | Burger(_) => true
           | Sandwich(_)
           | Hotdog => false
           }
         );
    // #endregion type-annotate-argument
    ignore(burgers);
  };

let _ =
  (items: array(Item.t)) => {
    let burgers =
      items
      // #region full-name-constructors
      |> Js.Array.filter(~f=item =>
           switch (item) {
           | Item.Burger(_) => true
           | Item.Sandwich(_)
           | Item.Hotdog => false
           }
         );
    // #endregion full-name-constructors
    ignore(burgers);
  };

let _ =
  (items: array(Item.t)) => {
    let burgers =
      items
      // #region full-name-constructor
      |> Js.Array.filter(~f=item =>
           switch (item) {
           | Item.Burger(_) => true
           | Sandwich(_)
           | Hotdog => false
           }
         );
    // #endregion full-name-constructor
    ignore(burgers);
  };

let _ =
  (items: array(Item.t)) => {
    let burgers =
      items
      // #region full-name-fun
      |> Js.Array.filter(
           ~f=
             fun
             | Item.Burger(_) => true
             | Sandwich(_)
             | Hotdog => false,
         );
    // #endregion full-name-fun
    ignore(burgers);
  };

let _ =
  (items: array(Item.t)) => {
    // #region swap-function-order
    items
    |> Js.Array.filter(~f=item =>
         switch (item) {
         | Item.Burger(_) => true
         | Sandwich(_)
         | Hotdog => false
         }
       )
    |> Js.Array.sortInPlaceWith(~f=(item1, item2) =>
         - compare(Item.toPrice(item1), Item.toPrice(item2))
       )
    // #endregion swap-function-order
    |> ignore;
  };

// Mock function just to get code to compile
let getFreeBurger = (_items: array(Item.t)) => None;
